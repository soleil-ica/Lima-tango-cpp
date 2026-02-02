
#pragma once
//- Tango
#include <tango.h>

//- Standard C++
#include <map>

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace FitGaussian_ns
{  
    class FitGaussian; //forward declaration
    //-----------------------------------------------
    class FitTask : public LinkTask, public Tango::LogAdapter
    {
        public:
            //ctor
            FitTask(const std::string& opType, Tango::DeviceImpl* dev);

            //dtor
            ~FitTask();
            
            // Define the operation type (FIT)            
            void set_operation_type(const std::string& op_type);

            // Get the operation type (FIT)
            const std::string& get_operation_type();

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
            void set_fit_nb_iterations_max(int fit_nb_iterations_max);  // Set tolerance for the fit

            // Set tolerance for the fit
            void set_fit_tolerance(double fit_tolerance);

            // Check if parameter exists
            bool is_param_exist(const std::string& param_name);

            // Get parameter value by name
            yat::Any get_param(const std::string& param_name);

            // Get current time in nanoseconds as string formatted to human-readable time
            std::string get_time_ns_to_human_time(long long ns);

            // Get current time in nanoseconds
            long long get_time_ns();

            // Get all parameters as map
            void print_results(const FitGaussLM& fit);

            // Process every new frame arrived
            Data process(Data&);
        private:
            
            // Process AutoROI
            void process_auto_roi(const cv::Mat& mat_origin_16u);

            // Process projection along X or Y
            void process_projection(const cv::Mat& img, const std::string& axis_name);
            
            // Push event std::string value
            void push_event(const std::string& name, std::string value);

            // Push event double value
            void push_event(const std::string& name, double value);
            
            //Data members
        private:
            FitGaussian*                        m_device; // pointer to the FitGaussian device
            yat::Mutex                          m_data_lock; // mutex to protect access to shared parameters map
            std::string                         m_operation_type; // operation type (FIT/NONE)          
            std::vector<double>                 m_x; // x data points
            std::vector<double>                 m_fitted_x; // x fitted data points
            std::vector<double>                 m_y; // y data points
            std::vector<double>                 m_fitted_y; // y fitted data points              
            cv::Mat                             m_mat_img_roi; // image of the ROI
            bool                                m_auto_roi_enabled; // AutoROI enabled or not
            double                              m_auto_roi_factor_x; // AutoROI factor along X
            double                              m_auto_roi_factor_y; // AutoROI factor along Y            
            double                              m_pixel_size_x; // pixel size in microns along X
            double                              m_pixel_size_y; // pixel size in microns along Y
            double                              m_optical_magnification; // optical magnification
            int                                 m_fit_nb_iterations_max; // max number of iterations for the fit
            double                              m_fit_tolerance; // tolerance for the fit
            bool                                m_xproj_enabled; // XProj enabled or not
            bool                                m_yproj_enabled; // YProj enabled or not
            std::string                         m_time_ns_to_human; // current time in nanoseconds as string formatted to human-readable time            
            std::map<std::string, yat::Any>     m_map_params; //map of parameters , this map is filled during the processing of each frame

            //map of shared parameters , this map is the swap of m_map_params done in protected SECTION
            //each tango attribute (READ Only) can access this map to get the latest value of the parameter
            //the key is the tango attribute name and the value is of type yat::Any
            //client can use yat::any_cast to extract the real type of the parameter
            //client shall check first if the parameter exists using is_param_exist() method
            //client can get the parameter value using get_param() method
            std::map<std::string, yat::Any>     m_map_shared_params;            
    };
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////