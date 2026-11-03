#include "PcoRingBufferControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtSaving.h"
#include <nexuscpp/nxfile.h>
#include <yat/Exception.h>
#include <cerrno>
#include <climits>
#include <cstring>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace
{
/** @brief Create or update an integer NeXus field and close its dataset. */
void scalar(nxcpp::NexusFile& file, const char* name, int value, bool create = true)
{
    int size = 1;
    file.WriteData(name, &value, nxcpp::NX_INT32, 1, &size, create);
    file.CloseDataSet();
}

/** @brief Preserve the NeXus error stack in an exception understood by the plugin. */
std::runtime_error nexusError(const yat::Exception& error)
{
    std::ostringstream message;
    message << "PCO NeXus error";
    for (size_t i = 0; i < error.errors.size(); ++i)
        message << ": " << error.errors[i].desc;
    return std::runtime_error(message.str());
}
}

namespace Pco_ns
{
/** @brief Register this bridge and private writer with the caller-owned camera/control. */
PcoRingBufferControl::PcoRingBufferControl(lima::Pco::Camera& camera,
                                         lima::CtControl& control,
                                         const std::string& directory)
    : m_camera(&camera), m_control(&control), m_directory(directory),
      m_requestedName("ring_buffer.nxs"), m_fileName(m_requestedName),
      m_file(0), m_history(0), m_written(0), m_active(false), m_metadataReady(false)
{
    camera.setRingBufferControl(this);
}

/** @brief Close any remaining file as incomplete; the device must call detach first. */
PcoRingBufferControl::~PcoRingBufferControl()
{
    // detach() is called explicitly by the device while logging is still available.
    if (m_file)
    {
        try { closeFile(false); }
        catch (const yat::Exception& error) { std::cerr << nexusError(error).what() << std::endl; }
        catch (const std::exception& error) { std::cerr << error.what() << std::endl; }
    }
    if (m_file)
    {
        nxcpp::NexusFile* file = m_file;
        m_file = 0;
        try { delete file; }
        catch (const yat::Exception& error) { std::cerr << nexusError(error).what() << std::endl; }
        catch (const std::exception& error) { std::cerr << error.what() << std::endl; }
    }
}

/** @brief Stop and detach from the camera before invalidating borrowed control pointers. */
void PcoRingBufferControl::detach()
{
    if (m_camera)
        m_camera->releaseRingBufferControl(this);
    m_camera = 0;
    m_control = 0;
}

/** @brief Invalidate borrowed camera/control pointers without accessing the dying camera. */
void PcoRingBufferControl::cameraDestroyed()
{
    lima::AutoMutex lock(m_mutex);
    m_camera = 0;
    m_control = 0;
}

/** @brief Set a plain .nxs basename while inactive; paths and invalid names are rejected. */
void PcoRingBufferControl::setFileName(const std::string& name)
{
    lima::AutoMutex lock(m_mutex);
    if (m_active)
        throw std::runtime_error("Cannot change the NeXus filename during a ring buffer session");
    if (name.size() <= 4 || name.size() > 240 || name.substr(name.size() - 4) != ".nxs" ||
        name.find_first_of("\\/:*?\"<>|") != std::string::npos ||
        name.find_first_of("\r\n\t") != std::string::npos || name[0] == '.')
        throw std::runtime_error("Use a plain filename ending in .nxs, without a directory");
    m_requestedName = name;
    m_fileName = name;
}

/** @brief Return the requested basename, or the actual suffixed name once reserved. */
std::string PcoRingBufferControl::getFileName()
{
    lima::AutoMutex lock(m_mutex);
    return m_fileName;
}

/**
 * @brief Validate the directory, SINGLE mode, Manual saving and Snap history.
 * Remember the history without creating a file or changing LImA's frame limit.
 */
void PcoRingBufferControl::prepare(int history)
{
    lima::AutoMutex lock(m_mutex);
    if (m_active || !m_control)
        throw std::runtime_error("Ring buffer controller is busy or detached");
    if (m_directory.empty())
        throw std::runtime_error("RingBufferNexusTargetPath must name an existing directory");
#ifdef _WIN32
    struct _stat directory;
    const bool isDirectory = !_stat(m_directory.c_str(), &directory) &&
                             (directory.st_mode & _S_IFDIR) != 0;
#else
    struct stat directory;
    const bool isDirectory = !stat(m_directory.c_str(), &directory) && S_ISDIR(directory.st_mode);
#endif
    if (!isDirectory)
        throw std::runtime_error("RingBufferNexusTargetPath is not an accessible directory: " + m_directory);
    if (m_file)
        throw std::runtime_error("Previous NeXus file could not be closed; reinitialize the idle PCO device");
    lima::CtSaving::SavingMode saving;
    m_control->saving()->getSavingMode(saving);
    if (saving != lima::CtSaving::Manual)
        throw std::runtime_error("Ring buffer requires fileGeneration=false (LImA saving must be Manual)");
    lima::AcqMode mode;
    m_control->acquisition()->getAcqMode(mode);
    if (mode != lima::Single)
        throw std::runtime_error("Ring buffer requires acquisitionMode=SINGLE");
    int count;
    m_control->acquisition()->getAcqNbFrames(count);
    if (count != history)
        throw std::runtime_error("Ring buffer history differs from the Snap frame count");
    m_history = history;
    m_written = 0;
    m_metadataReady = false;
}

/** @brief Revalidate saving/history and set LImA's frame count to zero for unlimited preview. */
void PcoRingBufferControl::start()
{
    lima::AutoMutex lock(m_mutex);
    if (m_active || !m_control || m_history <= 0)
        throw std::runtime_error("Ring buffer was not prepared");
    lima::CtSaving::SavingMode saving;
    m_control->saving()->getSavingMode(saving);
    int frames;
    m_control->acquisition()->getAcqNbFrames(frames);
    if (saving != lima::CtSaving::Manual || (frames != 0 && frames != m_history))
        throw std::runtime_error("Saving or history changed since ring buffer preparation");
    // Snap can reapply nbFrames when a separate Prepare command has been used.
    m_control->acquisition()->setAcqNbFrames(0);
    m_active = true;
}

/** @brief Exclusively reserve the target filename, adding a suffix rather than overwriting. */
void PcoRingBufferControl::reserveFile()
{
    for (unsigned long suffix = 0;; ++suffix)
    {
        std::ostringstream name;
        name << m_requestedName.substr(0, m_requestedName.size() - 4);
        if (suffix)
            name << "_" << std::setw(6) << std::setfill('0') << suffix;
        name << ".nxs";
        std::string path = m_directory;
        if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/')
            path += '\\';
        path += name.str();
#ifdef _WIN32
        const int fd = _open(path.c_str(), _O_CREAT | _O_EXCL | _O_WRONLY | _O_BINARY,
                             _S_IREAD | _S_IWRITE);
#else
        const int fd = open(path.c_str(), O_CREAT | O_EXCL | O_WRONLY, 0666);
#endif
        if (fd >= 0)
        {
#ifdef _WIN32
            const int result = _close(fd);
#else
            const int result = close(fd);
#endif
            m_path = path;
            m_fileName = name.str();
            if (result)
                throw std::runtime_error("Cannot close reserved NeXus file: " + path);
            return;
        }
        if (errno != EEXIST)
            throw std::runtime_error("Cannot reserve NeXus file " + path + ": " + std::strerror(errno));
        if (suffix == ULONG_MAX)
            throw std::runtime_error("NeXus filename suffix exhausted");
    }
}

/**
 * @brief Create the private NeXus file, metadata and datasets for the available history.
 * The file starts incomplete and remains separate from LImA's saving pipeline.
 */
void PcoRingBufferControl::beginExport(const lima::Pco::RingBufferInfo& info)
{
    lima::AutoMutex lock(m_mutex);
    if (!m_active || m_file)
        throw std::runtime_error("Invalid PCO NeXus export lifecycle");
    m_info = info;
    reserveFile();
    try
    {
        nxcpp::NexusFile::Initialize();
        m_file = new nxcpp::NexusFile();
        m_file->Create(m_path.c_str());
        m_file->OpenReadWrite(m_path.c_str());
        m_file->CreateGroup("entry", "NXentry");
        std::string model;
        m_camera->getCameraNameBase(model);
        m_file->WriteData("camera_model", model.c_str());
        m_file->CloseDataSet();
        m_file->WriteData("acquisition_mode", "pco_dimax_ring_buffer");
        m_file->CloseDataSet();
        scalar(*m_file, "complete", 0);
        scalar(*m_file, "written_frames", 0);
        m_metadataReady = true;
        scalar(*m_file, "requested_frames", info.requestedFrames);
        scalar(*m_file, "available_frames", info.frames);
        scalar(*m_file, "double_image", info.doubleImage ? 1 : 0);
        scalar(*m_file, "timestamp_mode", info.timestampMode);
        scalar(*m_file, "bit_alignment", info.bitAlignment);
        scalar(*m_file, "dynamic_bits", info.dynamicBits);
        scalar(*m_file, "ram_indices_assumed_chronological", 1);
        m_file->WriteData("exposure_time", info.exposure);
        m_file->PutAttr("units", "s");
        m_file->CloseDataSet();
        m_file->WriteData("latency_time", info.latency);
        m_file->PutAttr("units", "s");
        m_file->CloseDataSet();
        m_file->WriteData("camera_frame_period", info.framePeriod);
        m_file->PutAttr("units", "s");
        m_file->CloseDataSet();
        m_file->CreateGroup("scan_data", "NXdata");
        if (info.frames)
        {
            int shape[3] = {info.frames, info.height, info.width};
            m_file->CreateDataSet("image", nxcpp::NX_UINT16, 3, shape);
            m_file->PutAttr("signal", 1L);
            m_file->PutAttr("interpretation", "image");
            m_file->CloseDataSet();
            int count = info.frames;
            m_file->CreateDataSet("pco_ram_index", nxcpp::NX_UINT32, 1, &count);
            m_file->CloseDataSet();
            if ((info.timestampMode == 1 || info.timestampMode == 2) &&
                size_t(info.width) * info.height >= 14)
            {
                int timestampShape[2] = {info.frames, 14};
                m_file->CreateDataSet("pco_timestamp_raw", nxcpp::NX_UINT16, 2, timestampShape);
                m_file->PutAttr("description", "First 14 camera pixels, original BCD and bit alignment");
                m_file->CloseDataSet();
            }
        }
        m_file->CloseGroup();
    }
    catch (const yat::Exception& error)
    {
        throw nexusError(error);
    }
}

/**
 * @brief Synchronously write the next image, RAM index and optional raw timestamp.
 * Pixels are borrowed from the SDK; written_frames advances only after these writes.
 */
void PcoRingBufferControl::writeFrame(unsigned short* pixels, int index,
                                     unsigned long ramIndex)
{
    lima::AutoMutex lock(m_mutex);
    if (!m_file || index != m_written || index >= m_info.frames)
        throw std::runtime_error("Invalid PCO NeXus image index");
    try
    {
        m_file->OpenGroup("scan_data", "NXdata");
        int start[3] = {index, 0, 0};
        int size[3] = {1, m_info.height, m_info.width};
        m_file->OpenDataSet("image");
        m_file->PutDataSubSet(pixels, start, size);
        m_file->CloseDataSet();
        unsigned int ram = static_cast<unsigned int>(ramIndex);
        int one = 1;
        m_file->OpenDataSet("pco_ram_index");
        m_file->PutDataSubSet(&ram, &index, &one);
        m_file->CloseDataSet();
        if ((m_info.timestampMode == 1 || m_info.timestampMode == 2) &&
            size_t(m_info.width) * m_info.height >= 14)
        {
            int timestampStart[2] = {index, 0}, timestampSize[2] = {1, 14};
            m_file->OpenDataSet("pco_timestamp_raw");
            m_file->PutDataSubSet(pixels, timestampStart, timestampSize);
            m_file->CloseDataSet();
        }
        m_file->CloseGroup();
        ++m_written;
        scalar(*m_file, "written_frames", m_written, false);
    }
    catch (const yat::Exception& error)
    {
        throw nexusError(error);
    }
}

/**
 * @brief Update completion metadata and close the file; the caller provides synchronization.
 * A close failure propagates and leaves the file pointer available for cleanup.
 */
void PcoRingBufferControl::closeFile(bool complete)
{
    if (!m_file)
        return;
    if (m_metadataReady)
    {
        m_file->OpenGroupPath("/entry<NXentry>");
        scalar(*m_file, "written_frames", m_written, false);
        scalar(*m_file, "complete", complete ? 1 : 0, false);
    }
    m_file->Close();
    delete m_file;
    m_file = 0;
}

/** @brief Close the export, marking it complete only if all images were written without cancellation. */
void PcoRingBufferControl::endExport(bool cancelled)
{
    lima::AutoMutex lock(m_mutex);
    try
    {
        closeFile(!cancelled && m_written == m_info.frames);
    }
    catch (const yat::Exception& error)
    {
        throw nexusError(error);
    }
}

/**
 * @brief Close a leftover export as incomplete, stop LImA and restore the Snap history.
 * Additional close errors are propagated to the worker instead of hiding them.
 */
void PcoRingBufferControl::completed(bool cancelled, const std::string& error)
{
    lima::AutoMutex lock(m_mutex);
    std::string failure = error;
    try
    {
        if (m_file)
            closeFile(false);
    }
    catch (const yat::Exception& closeError)
    {
        failure += std::string("; closing incomplete NeXus file: ") + nexusError(closeError).what();
    }
    if (m_control && m_active)
    {
        try
        {
            m_control->stopAcq();
        }
        catch (...)
        {
            m_control->acquisition()->setAcqNbFrames(m_history);
            m_active = false;
            m_history = 0;
            throw;
        }
        m_control->acquisition()->setAcqNbFrames(m_history);
    }
    m_active = false;
    m_history = 0;
    if (failure != error)
        throw std::runtime_error(failure);
    (void)cancelled;
}
}
