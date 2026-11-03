#ifndef PCO_TANGO_RING_BUFFER_CONTROL_H
#define PCO_TANGO_RING_BUFFER_CONTROL_H

#include "PcoCamera.h"

#if !defined(LIMA_PCO_RING_BUFFER_API_VERSION) || LIMA_PCO_RING_BUFFER_API_VERSION < 1
#error PCO ring buffer API missing: rebuild and install the updated LimaPco plugin, then clean and rebuild LimaDetector with its matching headers and library.
#endif

#include "PcoRingBuffer.h"
#include "lima/CtControl.h"

namespace nxcpp { class NexusFile; }

namespace Pco_ns
{

class PcoRingBufferControl : public lima::Pco::RingBufferControl
{
public:
    PcoRingBufferControl(lima::Pco::Camera& camera, lima::CtControl& control,
                         const std::string& directory);
    ~PcoRingBufferControl();
    void detach();
    void setFileName(const std::string& name);
    std::string getFileName();
    void prepare(int history);
    void start();
    void beginExport(const lima::Pco::RingBufferInfo& info);
    void writeFrame(unsigned short* pixels, int index, unsigned long ramIndex);
    void endExport(bool cancelled);
    void completed(bool cancelled, const std::string& error);
    void cameraDestroyed();

private:
    lima::Pco::Camera* m_camera;
    lima::CtControl* m_control;
    lima::Mutex m_mutex;
    std::string m_directory;
    std::string m_requestedName;
    std::string m_fileName;
    std::string m_path;
    nxcpp::NexusFile* m_file;
    lima::Pco::RingBufferInfo m_info;
    int m_history;
    int m_written;
    bool m_active;
    bool m_metadataReady;

    void closeFile(bool complete);
    void reserveFile();
};

}
#endif
