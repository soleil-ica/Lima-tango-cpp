#pragma once

//- Tango
#include <tango.h>

//- Standard C++
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

//- POSIX
#include <time.h>

//- Yat
#include <yat/threading/Mutex.h>
#include <yat/time/Timer.h>
#include <yat/any/Any.h>

//- Lima
#include "lima/SoftOpId.h"
#include "lima/SoftOpExternalMgr.h"
#include "processlib/Data.h"
#include "processlib/TaskMgr.h"

//- FitGaussLM
#include "FitGaussLM.h"
#include "AutoROI.h"

//- OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace lima;

namespace FitGaussian_ns
{
    class FitGaussian; // forward declaration

    class FitTask : public LinkTask, public Tango::LogAdapter
    {
    public:
        // ctor
        FitTask(const std::string& opType, Tango::DeviceImpl* dev);

        // dtor
        virtual ~FitTask();

        // Define the operation type (FIT)
        void set_operation_type(const std::string& op_type);

        // Get the operation type (FIT)
        std::string get_operation_type();

        // Define if AutoROI is enabled or not
        void set_auto_roi_enabled(bool is_auto_roi);

        // Define if Proj is enabled or not
        void set_proj_enabled(bool is_proj_enabled, bool is_along_x);

        // Define the AutoROI factor along X
        void set_auto_roi_factor_x(double factor_x);

        // Define the AutoROI factor along Y
        void set_auto_roi_factor_y(double factor_y);

        // Set pixel size in microns
        void set_pixel_size_x(double pixel_size_x);

        // Set pixel size in microns
        void set_pixel_size_y(double pixel_size_y);

        // Set optical magnification
        void set_optical_magnification(double optical_magnification);

        // Set max number of iterations for the fit
        void set_fit_nb_iterations_max(int fit_nb_iterations_max);

        // Set tolerance for the fit
        void set_fit_tolerance(double fit_tolerance);

        // Enable/disable fixed background mode for profile fit
        void set_profilefit_fixedbg(bool enabled);

        // Enable/disable rotation for profile fit
        void set_rotation_angle(int angle);

        // Enable/disable display rotated image 
        void set_display_rotated_image(bool enabled);

        // Check if parameter exists
        bool is_param_exist(const std::string& param_name);

        // Get parameter value by name
        yat::Any get_param(const std::string& param_name);

        // Get current time in human readable format
        std::string now_human_time();

        // Print fit results
        void print_results(const FitGaussLM& fit);

        // Process every new frame arrived
        virtual Data process(Data&);

    private:
        struct ConfigSnapshot
        {
            std::string operation_type;
            bool auto_roi_enabled;
            double auto_roi_factor_x;
            double auto_roi_factor_y;
            double pixel_size_x;
            double pixel_size_y;
            double optical_magnification;
            int fit_nb_iterations_max;
            double fit_tolerance;
            bool xproj_enabled;
            bool yproj_enabled;
            bool profilefit_fixedbg;
            // Rotation parameters
            bool use_rotation;
            int  rotation_angle_cv_code;
            int  rotation_angle;
            bool display_rotated_image;
        };

    private:
        // Snapshot all runtime config under lock
        ConfigSnapshot get_config_snapshot();

        // Publish parameters to be read by the main device class
        void publish_params(std::map<std::string, yat::Any>& params);

        // Check if ROI is valid and adjust it if necessary to fit within image bounds
        static bool sanitize_roi(cv::Rect& roi, const cv::Mat& img);

        // Validate input image and extract width, height and raw pointer
        bool validate_image(const Data& src, int& width, int& height, const void*& raw_ptr);

        // Process AutoROI
        void process_auto_roi(const cv::Mat& mat_origin,
                              const ConfigSnapshot& cfg,
                              cv::Mat& mat_img_roi,
                              std::map<std::string, yat::Any>& params);

        // Process projection along X or Y
        void process_projection(const cv::Mat& img,
                                const std::string& axis_name,
                                const ConfigSnapshot& cfg,
                                std::map<std::string, yat::Any>& params);

        // Push event std::string value
        void push_event(const std::string& name, const std::string& value);

        // Push event double value
        void push_event(const std::string& name, double value);

    private:
        FitGaussian*                    m_device;
        yat::Mutex                      m_data_lock;

        // configuration shared between threads -> setter/getter always under lock
        std::string                     m_operation_type;
        bool                            m_auto_roi_enabled;
        double                          m_auto_roi_factor_x;
        double                          m_auto_roi_factor_y;
        double                          m_pixel_size_x;
        double                          m_pixel_size_y;
        double                          m_optical_magnification;
        int                             m_fit_nb_iterations_max;
        double                          m_fit_tolerance;
        bool                            m_xproj_enabled;
        bool                            m_yproj_enabled;
        bool                            m_profilefit_fixedbg;
        // FitTask results to be read by the main device class, protected by m_data_lock
        std::map<std::string, yat::Any> m_map_shared_params;
        
        // Rotation parameters 
        bool                            m_use_rotation;
        int                             m_rotation_angle_cv_code;
        int                             m_rotation_angle;
        bool                            m_display_rotated_image;

    };
}