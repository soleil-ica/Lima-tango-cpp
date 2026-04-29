#include "FitTask.h"
#include <FitGaussian.h>

#include <chrono>
#include <cstdio>
#include <stdexcept>
#include <thread>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace FitGaussian_ns
{
    namespace
    {
        ///////////////////////////////////////////////////////////////////////////////
        // Helper function to convert string to uppercase
        ///////////////////////////////////////////////////////////////////////////////
        static std::string to_upper_copy(std::string s)
        {
            std::transform(s.begin(), s.end(), s.begin(), ::toupper);
            return s;
        }

        ///////////////////////////////////////////////////////////////////////////////
        // Estimate image background like ISL::Image::estimate_background(5)
        ///////////////////////////////////////////////////////////////////////////////
        static double estimate_background_isl_like(const cv::Mat& img, int border_size = 5)
        {
            if (img.empty())
                return 0.0;

            cv::Mat img64;
            if (img.type() != CV_64F)
                img.convertTo(img64, CV_64F);
            else
                img64 = img;

            const int width  = img64.cols;
            const int height = img64.rows;

            if (height > 2 * border_size && width > 2 * border_size)
            {
                const cv::Rect upper_rect(0, 0, width, border_size);
                const cv::Rect lower_rect(0, height - border_size, width, border_size);
                const cv::Rect left_rect (0, 0, border_size, height);
                const cv::Rect right_rect(width - border_size, 0, border_size, height);

                const double mean_upper = cv::mean(img64(upper_rect))[0];
                const double mean_lower = cv::mean(img64(lower_rect))[0];
                const double mean_left  = cv::mean(img64(left_rect))[0];
                const double mean_right = cv::mean(img64(right_rect))[0];

                return std::min(std::min(mean_upper, mean_lower),
                                std::min(mean_left,  mean_right));
            }
            else
            {
                double min_val = 0.0;
                cv::minMaxLoc(img64, &min_val, 0);
                return min_val;
            }
        }
    }

    //-----------------------------------------------
    // ctor
    //-----------------------------------------------
    FitTask::FitTask(const std::string& opType, Tango::DeviceImpl* dev)
        : LinkTask(true),
          Tango::LogAdapter(dev),
          m_device(static_cast<FitGaussian*>(dev)),
          m_operation_type(to_upper_copy(opType)),
          m_fit_enabled(false),
          m_auto_roi_enabled(false),
          m_auto_roi_factor_x(5.0),
          m_auto_roi_factor_y(1.5),
          m_pixel_size_x(1.0),
          m_pixel_size_y(1.0),
          m_optical_magnification(1.0),
          m_fit_nb_iterations_max(100),
          m_fit_tolerance(1e-6),
          m_xproj_enabled(true),
          m_yproj_enabled(true),
          m_profilefit_fixedbg(false),
          m_use_rotation(false),
          m_rotation_angle_cv_code(cv::ROTATE_90_CLOCKWISE),
          m_rotation_angle(0),
          m_display_rotated_image(false)
    {
        INFO_STREAM << "FitTask::FitTask(" << opType << ")" << std::endl;
    }

    //-----------------------------------------------
    // dtor
    //-----------------------------------------------
    FitTask::~FitTask()
    {
        INFO_STREAM << "FitTask::~FitTask()" << std::endl;
    }

    //-----------------------------------------------
    // snapshot config
    //-----------------------------------------------
    FitTask::ConfigSnapshot FitTask::get_config_snapshot()
    {
        yat::MutexLock scoped_lock(m_data_lock);

        ConfigSnapshot cfg;
        cfg.operation_type            = m_operation_type;
        cfg.fit_enabled               = m_fit_enabled;
        cfg.auto_roi_enabled          = m_auto_roi_enabled;
        cfg.auto_roi_factor_x         = m_auto_roi_factor_x;
        cfg.auto_roi_factor_y         = m_auto_roi_factor_y;
        cfg.pixel_size_x              = m_pixel_size_x;
        cfg.pixel_size_y              = m_pixel_size_y;
        cfg.optical_magnification     = m_optical_magnification;
        cfg.fit_nb_iterations_max     = m_fit_nb_iterations_max;
        cfg.fit_tolerance             = m_fit_tolerance;
        cfg.xproj_enabled             = m_xproj_enabled;
        cfg.yproj_enabled             = m_yproj_enabled;
        cfg.profilefit_fixedbg        = m_profilefit_fixedbg;
        // Rotation parameters
        cfg.use_rotation              = m_use_rotation;
        cfg.rotation_angle_cv_code    = m_rotation_angle_cv_code;
        cfg.rotation_angle            = m_rotation_angle;
        cfg.display_rotated_image     = m_display_rotated_image;
        return cfg;
    }

    //-----------------------------------------------
    // define the operation type (FIT)
    //-----------------------------------------------
    void FitTask::set_operation_type(const std::string& op_type)
    {
        INFO_STREAM << "FitTask::set_operation_type(" << op_type << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_operation_type = to_upper_copy(op_type);
    }

    //-----------------------------------------------
    // get the operation type (FIT)
    //-----------------------------------------------
    std::string FitTask::get_operation_type()
    {
        yat::MutexLock scoped_lock(m_data_lock);
        return m_operation_type;
    }

    //-----------------------------------------------
    // define if Fit is enabled or not
    //-----------------------------------------------
    void FitTask::set_fit_enabled(bool is_fit_enabled)
    {
        INFO_STREAM << "FitTask::set_fit_enabled(" << is_fit_enabled << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_fit_enabled = is_fit_enabled;
    }

    //-----------------------------------------------
    // define if AutoROI is enabled or not
    //-----------------------------------------------
    void FitTask::set_auto_roi_enabled(bool is_auto_roi)
    {
        INFO_STREAM << "FitTask::set_auto_roi_enabled(" << is_auto_roi << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_auto_roi_enabled = is_auto_roi;
    }

    //-----------------------------------------------
    // define if X/Y Proj is enabled or not
    //-----------------------------------------------
    void FitTask::set_proj_enabled(bool is_proj_enabled, bool is_along_x)
    {
        INFO_STREAM << "FitTask::set_proj_enabled(" << is_proj_enabled << " , " << is_along_x << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        if (is_along_x)
            m_xproj_enabled = is_proj_enabled;
        else
            m_yproj_enabled = is_proj_enabled;
    }

    //-----------------------------------------------
    // Define the AutoROI factor along X
    //-----------------------------------------------
    void FitTask::set_auto_roi_factor_x(double factor_x)
    {
        INFO_STREAM << "FitTask::set_auto_roi_factor_x(" << factor_x << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_auto_roi_factor_x = factor_x;
    }

    //-----------------------------------------------
    // Define the AutoROI factor along Y
    //-----------------------------------------------
    void FitTask::set_auto_roi_factor_y(double factor_y)
    {
        INFO_STREAM << "FitTask::set_auto_roi_factor_y(" << factor_y << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_auto_roi_factor_y = factor_y;
    }

    //-----------------------------------------------
    // Set pixel size in microns
    //-----------------------------------------------
    void FitTask::set_pixel_size_x(double pixel_size_x)
    {
        INFO_STREAM << "FitTask::set_pixel_size_x(" << pixel_size_x << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_pixel_size_x = pixel_size_x;
    }

    //-----------------------------------------------
    // Set pixel size in microns
    //-----------------------------------------------
    void FitTask::set_pixel_size_y(double pixel_size_y)
    {
        INFO_STREAM << "FitTask::set_pixel_size_y(" << pixel_size_y << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_pixel_size_y = pixel_size_y;
    }

    //-----------------------------------------------
    // Set optical magnification
    //-----------------------------------------------
    void FitTask::set_optical_magnification(double optical_magnification)
    {
        INFO_STREAM << "FitTask::set_optical_magnification(" << optical_magnification << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_optical_magnification = optical_magnification;
    }

    //-----------------------------------------------
    // Set max number of iterations for the fit
    //-----------------------------------------------
    void FitTask::set_fit_nb_iterations_max(int fit_nb_iterations_max)
    {
        INFO_STREAM << "FitTask::set_fit_nb_iterations_max(" << fit_nb_iterations_max << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_fit_nb_iterations_max = fit_nb_iterations_max;
    }

    //-----------------------------------------------
    // Set tolerance for the fit
    //-----------------------------------------------
    void FitTask::set_fit_tolerance(double fit_tolerance)
    {
        INFO_STREAM << "FitTask::set_fit_tolerance(" << fit_tolerance << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_fit_tolerance = fit_tolerance;
    }

    //-----------------------------------------------
    // Enable/disable fixed background mode for profile fit
    //-----------------------------------------------
    void FitTask::set_profilefit_fixedbg(bool enabled)
    {
        INFO_STREAM << "FitTask::set_profilefit_fixedbg(" << enabled << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_profilefit_fixedbg = enabled;
    }

    //-----------------------------------------------
    // Enable/disable rotation for profile fit
    //-----------------------------------------------
    void FitTask::set_rotation_angle(int angle)
    {
        INFO_STREAM << "FitTask::set_rotation_angle(" << angle << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);

        int a = angle % 360;
        if (a < 0)
            a += 360;

        m_rotation_angle = a;

        // Set rotation parameters based on angle
        switch (a)
        {
            case 0:
                m_use_rotation = false;
                m_rotation_angle_cv_code = cv::ROTATE_90_CLOCKWISE; // dummy, never used
                break;

            case 90:
                m_use_rotation = true;
                m_rotation_angle_cv_code = cv::ROTATE_90_CLOCKWISE;
                break;

            case 180:
                m_use_rotation = true;
                m_rotation_angle_cv_code = cv::ROTATE_180;
                break;

            case 270:
                m_use_rotation = true;
                m_rotation_angle_cv_code = cv::ROTATE_90_COUNTERCLOCKWISE;
                break;

            default:
                Tango::Except::throw_exception( "PARAM_ERROR",
                                                "Rotation angle must be one of: 0, 90, -90, 180, -180, 270, -270",
                                                "FitTask::set_rotation_angle");
        }
    }    

    //-----------------------------------------------
    // Enable/disable display rotated image 
    //-----------------------------------------------
    void FitTask::set_display_rotated_image(bool enabled)
    {
        INFO_STREAM << "FitTask::set_display_rotated_image(" << enabled << ")" << std::endl;
        yat::MutexLock scoped_lock(m_data_lock);
        m_display_rotated_image = enabled;
    }    
    //-----------------------------------------------
    // get parameter value by name
    //-----------------------------------------------
    yat::Any FitTask::get_param(const std::string& param_name)
    {
        yat::MutexLock scoped_lock(m_data_lock);

        std::map<std::string, yat::Any>::const_iterator it = m_map_shared_params.find(param_name);
        if (it == m_map_shared_params.end())
        {
            Tango::Except::throw_exception("PARAM_ERROR",
                                           "Unknown parameter",
                                           "FitTask::get_param");
        }

        return it->second;
    }

    //-----------------------------------------------
    // Check if parameter exists
    //-----------------------------------------------
    bool FitTask::is_param_exist(const std::string& param_name)
    {
        yat::MutexLock scoped_lock(m_data_lock);
        return (m_map_shared_params.find(param_name) != m_map_shared_params.end());
    }

    //---------------------------------------------------------------
    // get time now in human readable format
    //---------------------------------------------------------------
    std::string FitTask::now_human_time()
    {
        using clock = std::chrono::system_clock;

        const auto now = clock::now();
        const auto sec = clock::to_time_t(now);

        std::tm tm_time;
        localtime_r(&sec, &tm_time);

        const auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % 1000000000LL;

        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_time);

        std::ostringstream oss;
        oss << buffer << "." << std::setfill('0') << std::setw(9) << nsec;

        return oss.str();
    }

    //-----------------------------------------------
    // Check if ROI is valid and adjust it if necessary to fit within image bounds
    //-----------------------------------------------
    bool FitTask::sanitize_roi(cv::Rect& roi, const cv::Mat& img)
    {
        if (img.empty())
            return false;

        const cv::Rect bounds(0, 0, img.cols, img.rows);
        roi &= bounds;
        return (roi.width > 0 && roi.height > 0);
    }

    //-----------------------------------------------
    // validate input image and extract width, height and raw pointer
    //-----------------------------------------------
    bool FitTask::validate_image(const Data& src, int& width, int& height, const void*& raw_ptr)
    {
        if (src.dimensions.size() < 2)
        {
            ERROR_STREAM << "[Error] Invalid image dimensions count: " << src.dimensions.size() << std::endl;
            return false;
        }

        if (src.type != Data::UINT16)
        {
            ERROR_STREAM << "[Error] Unsupported image type: expected UINT16, got type=" << src.type << std::endl;
            return false;
        }

        width  = static_cast<int>(src.dimensions[0]);
        height = static_cast<int>(src.dimensions[1]);

        if (width <= 0 || height <= 0)
        {
            ERROR_STREAM << "[Error] Invalid image size: " << width << "x" << height << std::endl;
            return false;
        }

        raw_ptr = src.data();
        if (!raw_ptr)
        {
            ERROR_STREAM << "[Error] Null image buffer!" << std::endl;
            return false;
        }

        return true;
    }

    //-----------------------------------------------
    // Process AutoROI
    //-----------------------------------------------
    void FitTask::process_auto_roi(const cv::Mat& mat_origin,
                                   const ConfigSnapshot& cfg,
                                   cv::Mat& mat_img_roi,
                                   std::map<std::string, yat::Any>& params)
    {
        ////auto begin_auto_roi = std::chrono::steady_clock::now();

        if (mat_origin.empty())
        {
            ERROR_STREAM << "[Error] Input image is empty. Aborting AutoROI." << std::endl;
            return;
        }

        AutoROI auto_roi(cfg.auto_roi_factor_x, cfg.auto_roi_factor_y);
        cv::Rect roi = auto_roi.compute(mat_origin);

        const bool converged = auto_roi.has_converged();
        if (!converged)
        {
            std::cerr << "[Warning] AutoROI did not converge. Using full image as ROI. Skip projections" << std::endl;
            roi = cv::Rect(0, 0, mat_origin.cols, mat_origin.rows);
        }
        else
        {
            ////INFO_STREAM << "[Info] AutoROI converged." << std::endl;

            if (!sanitize_roi(roi, mat_origin))
            {
                std::cerr << "[Warning] Invalid ROI after sanitization. Using full image as ROI" << std::endl;
                roi = cv::Rect(0, 0, mat_origin.cols, mat_origin.rows);
            }
        }

        mat_origin(roi).copyTo(mat_img_roi);

        params["AutoROIConverged"] = yat::Any(converged);
        params["AutoROIOriginX"]   = yat::Any(roi.x);
        params["AutoROIOriginY"]   = yat::Any(roi.y);
        params["AutoROIWidth"]     = yat::Any(roi.width);
        params["AutoROIHeight"]    = yat::Any(roi.height);
        params["ROIImage"]         = yat::Any(mat_img_roi.clone());

        ////auto end_auto_roi = std::chrono::steady_clock::now();
        ////auto ms = std::chrono::duration<double, std::milli>(end_auto_roi - begin_auto_roi).count();
        ////std::cerr   << "AutoROI"
        ////            << " frame=" << yat::any_cast<long long>(params["FrameNumber"])
        ////            << " tid=" << std::this_thread::get_id()
        ////            << " total_ms=" << ms
        ////            << std::endl;
    }

    //-----------------------------------------------
    // Push event std::string
    //-----------------------------------------------
    void FitTask::push_event(const std::string& name, const std::string& value)
    {
        Tango::DevString data = 0;

        try
        {
            Tango::AutoTangoMonitor mon(m_device);

            std::vector<std::string> dummy1;
            std::vector<double> dummy2;
            data = Tango::string_dup(value.c_str());

            m_device->push_event(name,
                                 dummy1,
                                 dummy2,
                                 &data,
                                 1,
                                 0,
                                 false);

            Tango::string_free(data);
            data = 0;
        }
        catch (Tango::DevFailed& e)
        {
            ERROR_STREAM << "push_event(" << name << ") failed: " << e.errors[0].desc << std::endl;
            if (data)
                Tango::string_free(data);
            return;
        }
        catch (...)
        {
            ERROR_STREAM << "push_event(" << name << ") failed: unknown exception" << std::endl;
            if (data)
                Tango::string_free(data);
            return;
        }
    }

    //-----------------------------------------------
    // Push event double
    //-----------------------------------------------
    void FitTask::push_event(const std::string& name, double value)
    {
        try
        {
            Tango::AutoTangoMonitor mon(m_device);

            Tango::DevDouble data = value;
            std::vector<std::string> dummy1;
            std::vector<double> dummy2;

            m_device->push_event(name,
                                 dummy1,
                                 dummy2,
                                 &data,
                                 1,
                                 0,
                                 false);
        }
        catch (Tango::DevFailed& e)
        {
            ERROR_STREAM << "push_event(" << name << ") failed: " << e.errors[0].desc << std::endl;
            return;
        }
        catch (...)
        {
            ERROR_STREAM << "push_event(" << name << ") failed: unknown exception" << std::endl;
            return;
        }
    }

    //-----------------------------------------------
    // Process projection along X or Y
    //-----------------------------------------------
    void FitTask::process_projection(const cv::Mat& img,
                                     const std::string& axis_name,
                                     const ConfigSnapshot& cfg,
                                     std::map<std::string, yat::Any>& params)
    {
        std::string axis = to_upper_copy(axis_name);

        if (axis != "X" && axis != "Y")
        {
            ERROR_STREAM << "[Error] FitTask::process_projection() : unknown axis name : " << axis << std::endl;
            std::string msg = "unknown axis name : " + axis;
            Tango::Except::throw_exception("PARAM_ERROR", msg.c_str(), "FitTask::process_projection");
        }

        if (img.empty())
        {
            Tango::Except::throw_exception("DATA_ERROR", "Empty ROI image", "FitTask::process_projection");
        }

        // Same spirit as ISL projections: sum along the orthogonal axis
        const int reduce_dim = (axis == "X") ? 0 : 1;

        cv::Mat proj_mat;
        cv::reduce(img, proj_mat, reduce_dim, CV_REDUCE_AVG, CV_64F);

        std::vector<double> proj_vec;
        proj_vec.assign((double*)proj_mat.datastart, (double*)proj_mat.dataend);

        const double magnification = (cfg.optical_magnification != 0.0) ? cfg.optical_magnification : 1.0;
        const double pixel_size = ((axis == "X") ? cfg.pixel_size_x : cfg.pixel_size_y) / magnification;

        double fixed_bg_value = 0.0;        
        if (cfg.profilefit_fixedbg)
        {
            // Minimal adaptation to mirror ISL behavior:
            // estimate image background using the same method as ISL::Image::estimate_background(5)
            const double bg_pixel = estimate_background_isl_like(img, 5);    
            fixed_bg_value = bg_pixel;
        }

        FitGaussLM fit(axis + "Proj",
                       proj_vec,
                       pixel_size,
                       cfg.profilefit_fixedbg,
                       fixed_bg_value);

        fit.fit(cfg.fit_nb_iterations_max, cfg.fit_tolerance);

        int roi_origin = 0;
        auto it = params.find("AutoROIOrigin" + axis);
        if (it != params.end())
            roi_origin = yat::any_cast<int>(it->second);

        const std::string push_time = now_human_time();

        params[axis + "ProjFitConverged"] = yat::Any(fit.has_converged());
        params[axis + "ProjFitCenter"]    = yat::Any((fit.get_mu() + roi_origin) * pixel_size);
        params[axis + "ProjFitMag"]       = yat::Any(fit.get_amplitude());
        params[axis + "ProjFitMu"]        = yat::Any(fit.get_mu());
        params[axis + "ProjFitSigma"]     = yat::Any(fit.get_sigma());
        params[axis + "ProjFitFWHM"]      = yat::Any(fit.get_fwhm());
        params[axis + "ProjFitBG"]        = yat::Any(fit.get_bg());
        params[axis + "ProjFitChi2"]      = yat::Any(fit.get_chi2());
        params[axis + "ProjFitRMS"]       = yat::Any(fit.get_rms());
        params[axis + "ProjFitR2"]        = yat::Any(fit.get_r2());
        params[axis + "ProjFitNbIter"]    = yat::Any(fit.get_nb_iter());
        params[axis + "ProjPushTime"]     = yat::Any(push_time);
        params[axis + "Proj"]             = yat::Any(fit.get_input_spectrum());
        params[axis + "ProjFitted"]       = yat::Any(fit.get_fitted_spectrum());

        if (fit.has_converged())
        {
#ifdef PUSH_EVENT_PROJ_ENABLED
            DEBUG_STREAM << "Pushing " << axis << "ProjFitSigma event..." << std::endl;
            push_event(axis + "ProjFitSigma", fit.get_sigma());
#endif

#ifdef PUSH_EVENT_MYPUSHTIME_ENABLED
            DEBUG_STREAM << "Pushing " << axis << "ProjPushTime event..." << std::endl;
            push_event(axis + "ProjPushTime", push_time);
#endif
        }
    }

    //-----------------------------------------------
    // Publish parameters to be read by the main device class
    //-----------------------------------------------
    void FitTask::publish_params(std::map<std::string, yat::Any>& params)
    {
        yat::MutexLock scoped_lock(m_data_lock);
        m_map_shared_params.swap(params);
    }

    //-----------------------------------------------
    // process every new frame arrived
    //-----------------------------------------------
    Data FitTask::process(Data& aSrc)
    {        
        const auto begin_process = std::chrono::steady_clock::now();        
        std::map<std::string, yat::Any> local_params;
        cv::Mat mat_origin_rotated;// in order to be in the same scope as out
        local_params["FrameNumber"]      = yat::Any(aSrc.frameNumber);

        // Get a snapshot of the current configuration, this ensures consistency in case the configuration is changed while processing
        const ConfigSnapshot cfg = get_config_snapshot();
        try
        {
            // If Fit is not enabled, we skip directly
            if (!cfg.fit_enabled)
            {                
                std::cerr << "[Info] FIT disabled, skip processing frame=" << aSrc.frameNumber << " tid=" << std::this_thread::get_id()<< std::endl;
                publish_params(local_params);
                return aSrc;
            }

            std::cerr << "BEGIN Process "<< " tid=" << std::this_thread::get_id()<<" | frame=" << aSrc.frameNumber  << std::endl;          


            int width = 0;
            int height = 0;
            const void* raw_ptr = 0;

            if (!validate_image(aSrc, width, height, raw_ptr))
            {
                ERROR_STREAM << "[Error] Failed to validate image!" << std::endl;
                publish_params(local_params);
                return aSrc;
            }

            cv::Mat mat_view(height, width, CV_16UC1, const_cast<void*>(raw_ptr));
            if (mat_view.empty())
            {
                ERROR_STREAM << "[Error] Empty image view!" << std::endl;
                publish_params(local_params);
                return aSrc;
            }

            cv::Mat mat_origin = mat_view.clone();
            if (mat_origin.empty())
            {
                ERROR_STREAM << "[Error] Failed to clone image!" << std::endl;
                publish_params(local_params);
                return aSrc;
            }

            // Rotate the image if rotation is enabled
            if (cfg.use_rotation)
                cv::rotate(mat_origin, mat_origin_rotated, cfg.rotation_angle_cv_code);
            else
                mat_origin_rotated = mat_origin.clone();// deep copy, independent buffer

            // This will hold the ROI image after AutoROI processing, to be used for projections if enabled
            cv::Mat mat_img_roi;

            // Store the original image parameters in case we need to use them for projections if AutoROI fails, this ensures that projections will always have an image to work with, even if it's not cropped            
            local_params["AutoROIOriginX"]      = yat::Any(0);
            local_params["AutoROIOriginY"]      = yat::Any(0);
            local_params["AutoROIWidth"]        = yat::Any(mat_origin_rotated.cols);
            local_params["AutoROIHeight"]       = yat::Any(mat_origin_rotated.rows);
            local_params["ROIImage"]            = yat::Any(mat_origin_rotated.clone());

            // Process AutoROI: if enabled, we compute the ROI and update local_params with the results, if not enabled we just use the full image as ROI and set the corresponding parameters
            if(!cfg.auto_roi_enabled)
            {
                // If AutoROI is not enabled, we consider it as converged with the full image as ROI
                local_params["AutoROIConverged"]    = yat::Any(true);
                // If AutoROI is not enabled, we just use the full image as ROI
                mat_origin_rotated.copyTo(mat_img_roi);
            }
            else
            {
                // If AutoROI is enabled, we initialize the convergence status to false in case the processing fails
                local_params["AutoROIConverged"]    = yat::Any(false);
                // If AutoROI is enabled, we process it and update the local_params with the results (convergence status, ROI coordinates and size, ROI image)
                process_auto_roi(mat_origin_rotated, cfg, mat_img_roi, local_params);
            }

            // We check if AutoROI converged by looking at the local_params
            bool auto_roi_converged = false;
            std::map<std::string, yat::Any>::const_iterator it = local_params.find("AutoROIConverged");
            if (it != local_params.end())
                auto_roi_converged = yat::any_cast<bool>(it->second);

            // Process projections X if enabled and if AutoROI converged, as they depend on the ROI being valid
            if (cfg.xproj_enabled && auto_roi_converged)
                process_projection(mat_img_roi, "X", cfg, local_params);

            // Process projections Y if enabled and if AutoROI converged, as they depend on the ROI being valid
            if (cfg.yproj_enabled && auto_roi_converged)
                process_projection(mat_img_roi, "Y", cfg, local_params);
        }
        catch (const Tango::DevFailed& e)
        {
            ERROR_STREAM << "FitTask::process(" << aSrc.frameNumber << ") Tango exception: " << e.errors[0].desc << std::endl;
        }
        catch (const cv::Exception& e)
        {
            ERROR_STREAM << "FitTask::process(" << aSrc.frameNumber << ") OpenCV exception: " << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            ERROR_STREAM << "FitTask::process(" << aSrc.frameNumber << ") std::exception: " << e.what() << std::endl;
        }
        catch (const lima::Exception& e)
        {
            ERROR_STREAM << "FitTask::process(" << aSrc.frameNumber << ") lima exception: " << e.getErrMsg() << std::endl;
        }
        catch (...)
        {
            ERROR_STREAM << "FitTask::process(" << aSrc.frameNumber << ") unknown exception" << std::endl;
        }

        // Publish the parameters to be read by the main device class and possibly pushed as events
        // Note: we publish all parameters at the end of processing to ensure consistency, as some parameters depend on the results of previous steps (e.g. projections depend on AutoROI results)        
        publish_params(local_params);

        // Prepare out Data
        Data out = aSrc;

        // If display rotation is enabled and the rotated image is not empty, we replace the output buffer with the rotated image data
        if (cfg.display_rotated_image && !mat_origin_rotated.empty())
        {
            out.type = aSrc.type;
            out.frameNumber = aSrc.frameNumber;
            out.timestamp = aSrc.timestamp;
            out.header = aSrc.header;

            out.dimensions.resize(2);
            out.dimensions[0] = mat_origin_rotated.cols;
            out.dimensions[1] = mat_origin_rotated.rows;

            out.buffer = new Buffer(out.size());
            std::memcpy(out.data(), mat_origin_rotated.data, out.size());
        }

        // Log processing time
        const auto ms = std::chrono::duration<double, std::milli>( std::chrono::steady_clock::now() - begin_process).count();        
        std::cerr << "END   Process "<< " tid=" << std::this_thread::get_id()<<" | frame=" << aSrc.frameNumber<< " | total_ms=" << (int)ms  <<std::endl <<std::endl;                       
        return out;
    }

    //-----------------------------------------------
    // Print all fitted parameters
    //-----------------------------------------------
    void FitTask::print_results(const FitGaussLM& fit)
    {
        DEBUG_STREAM << "Fitted parameters for :" << fit.get_label()     << std::endl;
        DEBUG_STREAM << "Amplitude: "             << fit.get_amplitude() << std::endl;
        DEBUG_STREAM << "Mu: "                    << fit.get_mu()        << std::endl;
        DEBUG_STREAM << "Sigma: "                 << fit.get_sigma()     << std::endl;
        DEBUG_STREAM << "FWHM: "                  << fit.get_fwhm()      << std::endl;
        DEBUG_STREAM << "Background: "            << fit.get_bg()        << std::endl;
        DEBUG_STREAM << "Chi2: "                  << fit.get_chi2()      << std::endl;
        DEBUG_STREAM << "RMS: "                   << fit.get_rms()       << std::endl;
        DEBUG_STREAM << "R²: "                    << fit.get_r2()        << std::endl;
        DEBUG_STREAM << "Nb. iter: "              << fit.get_nb_iter()   << std::endl;
    }
}
