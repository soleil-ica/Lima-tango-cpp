
#include "FitTask.h"
#include <FitGaussian.h>

namespace FitGaussian_ns
{ 
    //-----------------------------------------------
    //ctor
    //-----------------------------------------------
    FitTask::FitTask(const std::string& opType, Tango::DeviceImpl* dev): 
    LinkTask(true), Tango::LogAdapter(dev),
    m_device(static_cast<FitGaussian*>(dev)),
    m_operation_type(opType)
    {         
        INFO_STREAM<<"FitTask::FitTask("<<opType<<")"<<std::endl;
        transform(m_operation_type.begin(), m_operation_type.end(), m_operation_type.begin(), ::toupper);
        m_x.clear();
        m_y.clear();
        m_fitted_x.clear();
        m_fitted_y.clear();
        m_auto_roi_enabled = false; //default value
        m_auto_roi_factor_x = 5.0; //default value
        m_auto_roi_factor_y = 1.5; //default value    
        m_pixel_size_x = 1.0; //default value
        m_pixel_size_y = 1.0; //default value
        m_optical_magnification = 1.0; //default value
        m_fit_nb_iterations_max = 100; //default value 
        m_fit_tolerance = 1e-6; //default value            
        m_xproj_enabled = true; //default value
        m_yproj_enabled = true; //default value
        m_map_params.clear();
        m_map_shared_params.clear();
    }

    //-----------------------------------------------
    //dtor
    //-----------------------------------------------
    FitTask::~FitTask()
    {
        INFO_STREAM<<"FitTask::~FitTask("")"<<std::endl;
    }

    //-----------------------------------------------
    //define the operation type (FIT)
    //-----------------------------------------------    
    void FitTask::set_operation_type(const std::string& op_type)
    {            
        INFO_STREAM<< "FitTask::set_operation_type("<<op_type<<")"<<std::endl;
        m_operation_type = op_type;
        transform(m_operation_type.begin(), m_operation_type.end(), m_operation_type.begin(), ::toupper);
    }

    //-----------------------------------------------
    //get the operation type (FIT)
    //-----------------------------------------------
    const std::string& FitTask::get_operation_type()
    {
        return m_operation_type;
    }

    //-----------------------------------------------
    //define if AutoROI is enabled or not         
    //-----------------------------------------------
    void FitTask::set_auto_roi_enabled(bool is_auto_roi)
    {            
        INFO_STREAM<< "FitTask::set_auto_roi_enabled("<<is_auto_roi<<")"<<std::endl;
        m_auto_roi_enabled = is_auto_roi;        
    }

    //-----------------------------------------------
    //define if X/Y Proj is enabled or not 
    //-----------------------------------------------
    void FitTask::set_proj_enabled(bool is_proj_enabled, bool is_along_x)
    {
        INFO_STREAM<< "FitTask::set_proj_enabled("<<is_proj_enabled<<" , "<<is_along_x<<")"<<std::endl;
        if(is_along_x)
            m_xproj_enabled = is_proj_enabled;
        else        
            m_yproj_enabled = is_proj_enabled;
    }

    //-----------------------------------------------
    // Define the AutoROI factor along X      
    //-----------------------------------------------
    void FitTask::set_auto_roi_factor_x(double factor_x)
    {
        INFO_STREAM<< "FitTask::set_auto_roi_factorx("<<factor_x<<")"<<std::endl;
        m_auto_roi_factor_x = factor_x;        
    }

    //-----------------------------------------------
    // Define the AutoROI factor along Y
    //-----------------------------------------------
    void FitTask::set_auto_roi_factor_y(double factor_y)
    {
        INFO_STREAM<< "FitTask::set_auto_roi_factory("<<factor_y<<")"<<std::endl;
        m_auto_roi_factor_y = factor_y;        
    }

    //-----------------------------------------------
    // Set pixel size in microns
    //-----------------------------------------------
    void FitTask::set_pixel_size_x(double pixel_size_x)
    {
        INFO_STREAM<< "FitTask::set_pixel_size_x("<<pixel_size_x<<")"<<std::endl;
        m_pixel_size_x = pixel_size_x;        
    }

    //-----------------------------------------------
    // Set pixel size in microns
    //-----------------------------------------------
    void FitTask::set_pixel_size_y(double pixel_size_y)
    {
        INFO_STREAM<< "FitTask::set_pixel_size_y("<<pixel_size_y<<")"<<std::endl;
        m_pixel_size_y = pixel_size_y;   
    }

    //-----------------------------------------------
    // Set optical magnification
    //-----------------------------------------------
    void FitTask::set_optical_magnification(double optical_magnification)
    {
        INFO_STREAM<< "FitTask::set_optical_magnification("<<optical_magnification<<")"<<std::endl;
        m_optical_magnification = optical_magnification;   
    }

    //-----------------------------------------------
    // Set max number of iterations for the fit
    //-----------------------------------------------
    void FitTask::set_fit_nb_iterations_max(int fit_nb_iterations_max)
    {
        INFO_STREAM<< "FitTask::set_fit_nb_iterations_max("<<fit_nb_iterations_max<<")"<<std::endl;
        m_fit_nb_iterations_max = fit_nb_iterations_max;   
    }

    //-----------------------------------------------
    // Set tolerance for the fit
    //-----------------------------------------------
    void FitTask::set_fit_tolerance(double fit_tolerance)
    {
        INFO_STREAM<< "FitTask::set_fit_tolerance("<<fit_tolerance<<")"<<std::endl;
        m_fit_tolerance = fit_tolerance;   
    }

    //-----------------------------------------------
    // Get input spectrum values
    //-----------------------------------------------
    const std::vector<double>& FitTask::get_spectrum(const std::string& name)
    {
        yat::MutexLock scoped_lock(m_data_lock);
        if(name == "XProj")
            return m_x;
        else if(name == "XProjFitted")
            return m_fitted_x;
        else if(name == "YProj")
            return m_y;
        else if(name == "YProjFitted")
            return m_fitted_y;          
    }

    //-----------------------------------------------
    // Get the image of the ROI as cv::Mat
    //-----------------------------------------------
    const cv::Mat& FitTask::get_img_roi()
    {        
        yat::MutexLock scoped_lock(m_data_lock);
        return m_mat_img_roi;
    }

    //-----------------------------------------------
    // Get the image of the ROI as vector of unsigned long
    //-----------------------------------------------
    const std::vector<unsigned short>& FitTask::get_img_roi_data()
    {
        yat::MutexLock scoped_lock(m_data_lock);
        if(!m_mat_img_roi.empty())
        {
            size_t total_elements = m_mat_img_roi.total() * m_mat_img_roi.channels();      
            m_mat_img_roi_data.resize(total_elements);
            if(!m_mat_img_roi.isContinuous())
            {
                ERROR_STREAM<<"[Error] FitTask::get_img_roi_data() : m_mat_img_roi is not continuous in memory!"<<std::endl;
                m_mat_img_roi = m_mat_img_roi.clone();
            }            
            m_mat_img_roi_data.assign(m_mat_img_roi.begin<unsigned short>(),m_mat_img_roi.end<unsigned short>());
        }
        return m_mat_img_roi_data;
    }

    //-----------------------------------------------
    //get parameter value by name
    //-----------------------------------------------
    double FitTask::get_param(const std::string param_name)
    { 
        yat::MutexLock scoped_lock(m_data_lock);
        if(m_map_shared_params.find(param_name) == m_map_shared_params.end())
        {
            //std::cerr<<"[Error] FitTask::get_param() : unknown parameter name : "<<param_name<<std::endl;
            return std::nan("");
        }

        return m_map_shared_params[param_name]; 
    }    

    //-----------------------------------------------
    // Get current time in nanoseconds as string
    //-----------------------------------------------
    std::string FitTask::get_time_ns_to_str()
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);

        long long ns = static_cast<long long>(ts.tv_sec) * 1000000000LL + ts.tv_nsec;

        std::ostringstream oss;
        oss << ns;
        return oss.str();
    }
    
    //-----------------------------------------------
    // Process AutoROI
    //-----------------------------------------------
    void FitTask::process_auto_roi(const cv::Mat& mat_origin_16u)
    {
        yat::Timer t_roi;
        t_roi.restart();

        AutoROI auto_roi(m_auto_roi_factor_x, m_auto_roi_factor_y);
        cv::Rect roi = auto_roi.compute(mat_origin_16u);

        // Check convergence and adjust ROI bounds
        if (!auto_roi.has_converged())
        {
            INFO_STREAM << "[Warning] AutoROI did not converge. Using full image as ROI." << std::endl;
            roi = cv::Rect(0, 0, mat_origin_16u.cols, mat_origin_16u.rows);
            m_map_params["AutoROIConverged"] = 0.0;
        }
        else
        {
            INFO_STREAM << "[Info] AutoROI converged." << std::endl;
            m_map_params["AutoROIConverged"] = 1.0;

            // Clip ROI within image bounds
            roi.x      = std::max(0, roi.x);
            roi.y      = std::max(0, roi.y);
            roi.width  = std::min(roi.width,  mat_origin_16u.cols - roi.x);
            roi.height = std::min(roi.height, mat_origin_16u.rows - roi.y);
        }

        // Store ROI parameters
        m_map_params["AutoROIOriginX"] = roi.x;
        m_map_params["AutoROIOriginY"] = roi.y;
        m_map_params["AutoROIWidth"]   = roi.width;
        m_map_params["AutoROIHeight"]  = roi.height;

        // Copy ROI region into m_mat_img_roi (deep copy for contiguous memory)
        {
            yat::MutexLock scoped_lock(m_data_lock);
            mat_origin_16u(roi).copyTo(m_mat_img_roi);
        }

        INFO_STREAM << "[Elapsed time (AutoROI): " << t_roi.elapsed_msec() << " (ms)]" << std::endl;
        INFO_STREAM << "------------------------" << std::endl;
    }


    //-----------------------------------------------
    // Push event
    //-----------------------------------------------
    void FitTask::push_event(const std::string& name, std::string value)
    {
        try
        {
            Tango::AutoTangoMonitor mon(m_device);
            std::vector<Tango::DevString> data;
            data.push_back(const_cast<char*>(value.c_str()));
            std::vector<std::string> dummy1;
            std::vector<double> dummy2;

            m_device->push_event(   name,
                                    dummy1,
                                    dummy2,
                                    data.data(),
                                    data.size(),
                                    0,
                                    false
                                );
        }
        catch (Tango::DevFailed &e)
        {
            ERROR_STREAM << "push_event() failed: " << e.errors[0].desc << std::endl;
        }
    }

    //-----------------------------------------------
    // Push event
    //-----------------------------------------------
    void FitTask::push_event(const std::string& name, double value)
    {
        try
        {
            Tango::AutoTangoMonitor mon(m_device);
            std::vector<Tango::DevDouble> data;
            data.push_back(value);

            std::vector<std::string> dummy1;
            std::vector<double> dummy2;

            m_device->push_event(   name,
                                    dummy1,
                                    dummy2,
                                    data.data(),
                                    data.size(),
                                    0,
                                    false
                                );
        }
        catch (Tango::DevFailed &e)
        {
            ERROR_STREAM << "push_event(" << name << ") failed: " << e.errors[0].desc << std::endl;
        }
    }


    //-----------------------------------------------
    // Process projection along X or Y
    //-----------------------------------------------
    void FitTask::process_projection(const cv::Mat& img, bool is_along_x)
    {
        yat::Timer t_fit;
        t_fit.restart();

        const std::string axis = is_along_x ? "X" : "Y";
        int reduce_dim = is_along_x ? 0 : 1;

        cv::Mat proj_mat;
        cv::reduce(img, proj_mat, reduce_dim, CV_REDUCE_AVG, CV_64F);

        std::vector<double> proj_vec(proj_mat.begin<double>(), proj_mat.end<double>());

        double pixel_size = (is_along_x ? m_pixel_size_x : m_pixel_size_y) / m_optical_magnification;

        FitGaussLM fit(axis + "Proj", proj_vec, pixel_size);
        fit.fit(m_fit_nb_iterations_max, m_fit_tolerance);

        // Store fit results
        {
            yat::MutexLock scoped_lock(m_data_lock);

            m_map_params[axis + "ProjFitConverged"] = fit.has_converged() ? 1.0 : 0.0;
            m_map_params[axis + "ProjFitCenter"]    = (fit.get_mu() + m_map_params["AutoROIOrigin"+axis])*pixel_size;
            m_map_params[axis + "ProjFitMag"]       = fit.get_amplitude();
            m_map_params[axis + "ProjFitMu"]        = fit.get_mu();
            m_map_params[axis + "ProjFitSigma"]     = fit.get_sigma();
            m_map_params[axis + "ProjFitFWHM"]      = fit.get_fwhm();
            m_map_params[axis + "ProjFitBG"]        = fit.get_bg();
            m_map_params[axis + "ProjFitChi2"]      = fit.get_chi2();
            m_map_params[axis + "ProjFitRMS"]       = fit.get_rms();
            m_map_params[axis + "ProjFitR2"]        = fit.get_r2();

            if (is_along_x)
            {
                m_x = fit.get_input_spectrum();
                m_fitted_x = fit.get_fitted_spectrum();
            }
            else
            {
                m_y = fit.get_input_spectrum();
                m_fitted_y = fit.get_fitted_spectrum();
            }
        }

    #ifdef PUSH_EVENT_PROJ_ENABLED
        DEBUG_STREAM << "Pushing " << axis << " Proj fit event..." << std::endl;
        push_event(axis + "ProjFitSigma", fit.get_sigma());
    #endif
        
        print_results(fit);
        INFO_STREAM << "[Elapsed time (fit_" << axis << "): " << t_fit.elapsed_msec() << " (ms)]" << std::endl;        
    }


    //-----------------------------------------------
    //process every new frame arrived
    //-----------------------------------------------
    Data FitTask::process(Data& aSrc)
    {
        INFO_STREAM << "FitTask::process() ..." << std::endl;
        INFO_STREAM << "************************" << std::endl;

        //----------------------------------------------------------------------
        // initialisation
        //----------------------------------------------------------------------
        {
            yat::MutexLock scoped_lock(m_data_lock);
            m_map_params.clear();
            m_x.clear();
            m_y.clear();
            m_fitted_x.clear();
            m_fitted_y.clear();
            m_mat_img_roi.release();
            m_mat_img_roi_data.clear();
        }

        yat::Timer t_total;
        t_total.restart();

        //----------------------------------------------------------------------
        // Convert Data to cv::Mat
        //----------------------------------------------------------------------
        Data my_image = aSrc;
        cv::Mat mat_origin_16u(my_image.dimensions[1], my_image.dimensions[0], CV_16UC1, (unsigned short*) my_image.data() );
        cv::Rect roi = cv::Rect(0, 0, mat_origin_16u.cols, mat_origin_16u.rows); //default ROI is full image
        if (mat_origin_16u.empty())
        {
            ERROR_STREAM << "[Error]: empty image!" << std::endl;
            return aSrc;
        }

        {
            yat::MutexLock scoped_lock(m_data_lock);
            m_mat_img_roi = mat_origin_16u;
        }

        // Store initial ROI parameters, will be updated if AutoROI is enabled
        m_map_params["AutoROIOriginX"] = roi.x;
        m_map_params["AutoROIOriginY"] = roi.y;
        m_map_params["AutoROIWidth"]   = roi.width;
        m_map_params["AutoROIHeight"]  = roi.height;

        //----------------------------------------------------------------------
        // AUTO ROI
        //----------------------------------------------------------------------
        if (m_auto_roi_enabled)
            process_auto_roi(mat_origin_16u);

        //----------------------------------------------------------------------
        // PROJECTION & FIT on X
        //----------------------------------------------------------------------
        if (m_xproj_enabled)
            process_projection(m_mat_img_roi, true);

        //----------------------------------------------------------------------
        // PROJECTION & FIT on Y
        //----------------------------------------------------------------------            
        if (m_yproj_enabled)
            process_projection(m_mat_img_roi, false);

        //----------------------------------------------------------------------
        // Push time event
        //----------------------------------------------------------------------
#ifdef PUSH_EVENT_MYPUSHTIME_ENABLED
        DEBUG_STREAM << "Pushing myPushTime event..." << std::endl;
        m_time_ns = get_time_ns_to_str();
        push_event("myPushTime", m_time_ns);
#endif

        // Update shared parameters
        {
            yat::MutexLock scoped_lock(m_data_lock);
            m_map_shared_params = m_map_params;
        }

        INFO_STREAM << "************************" << std::endl;
        INFO_STREAM << "[Elapsed time (Process): " << t_total.elapsed_msec() << " (ms)]" << std::endl;
        INFO_STREAM << "************************\n" << std::endl;

        return aSrc;
    }


    //-----------------------------------------------
    // Print all fitted parameters
    //-----------------------------------------------
    void FitTask::print_results(const FitGaussLM& fit)
    {
        DEBUG_STREAM << "Fitted parameters for :"   << fit.get_label()      << std::endl;
        DEBUG_STREAM << "Amplitude: "               << fit.get_amplitude()  << std::endl;
        DEBUG_STREAM << "Mu: "                      << fit.get_mu()         << std::endl;
        DEBUG_STREAM << "Sigma: "                   << fit.get_sigma()      << std::endl;
        DEBUG_STREAM << "FWHM: "                    << fit.get_fwhm()       << std::endl;
        DEBUG_STREAM << "Background: "              << fit.get_bg()         << std::endl;
        DEBUG_STREAM << "Slope: "                   << fit.get_slope()      << std::endl;
        DEBUG_STREAM << "Chi2: "                    << fit.get_chi2()       << std::endl;
        DEBUG_STREAM << "RMS: "                     << fit.get_rms()        << std::endl;
        DEBUG_STREAM << "R²: "                      << fit.get_r2()         << std::endl;
        DEBUG_STREAM << "Number of iterations: "    << fit.get_nb_iter()    << std::endl;
    }    
}
