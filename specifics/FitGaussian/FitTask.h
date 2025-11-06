
#pragma once
//- Tango
#include <tango.h>

//- Standard C++
#include <map>

//- Yat
#include <yat/threading/Mutex.h>
#include <yat/time/Timer.h>

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

            // Get spectrum values
            const std::vector<double>& get_spectrum(const std::string& name);      

            // Get the image of the ROI as cv::Mat
            const cv::Mat& get_img_roi();


            // Get the image of the ROI as vector of unsigned short
            const std::vector<unsigned short>& get_img_roi_data();

            // Get parameter value by name
            double get_param(const std::string param_name);

            std::string get_time_ns_to_str();
           

            // Get all parameters as map
            void print_results(const FitGaussLM& fit);

            // Process every new frame arrived
            Data process(Data&);
        private:
            
            // Process AutoROI
            void process_auto_roi(const cv::Mat& mat_origin_16u);

            // Process projection along X or Y
            void process_projection(const cv::Mat& img, bool is_along_x);
            
            // Push event std::string value
            void push_event(const std::string& name, std::string value);

            // Push event double value
            void push_event(const std::string& name, double value);
            
            // Pointer to the Tango device
            FitGaussian* m_device;

            //Lock to protect the state of the operation
            yat::Mutex m_data_lock;

            //Operation type (FIT/NONE)
            std::string m_operation_type;

            //map of parameters
            std::map<std::string, double>   m_map_params;//map of parameters 
            std::vector<double>             m_x; // x data points
            std::vector<double>             m_fitted_x; // x fitted data points
            std::vector<double>             m_y; // y data points
            std::vector<double>             m_fitted_y; // y fitted data points              
            cv::Mat                         m_mat_img_roi; // image of the ROI
            std::vector<unsigned short>     m_mat_img_roi_data; // image of the ROI as vector of unsigned short
            bool                            m_auto_roi_enabled; // AutoROI enabled or not
            double                          m_auto_roi_factor_x; // AutoROI factor along X
            double                          m_auto_roi_factor_y; // AutoROI factor along Y            
            double                          m_pixel_size_x; // pixel size in microns along X
            double                          m_pixel_size_y; // pixel size in microns along Y
            double                          m_optical_magnification; // optical magnification
            int                             m_fit_nb_iterations_max; // max number of iterations for the fit
            double                          m_fit_tolerance; // tolerance for the fit
            bool                            m_xproj_enabled;// XProj enabled or not
            bool                            m_yproj_enabled;// YProj enabled or not
            std::map<std::string, double>   m_map_shared_params;//map of parameters 
            std::string m_time_ns;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////