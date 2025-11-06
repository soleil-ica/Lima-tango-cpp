#pragma once

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>

//ImageBeamAnalyzer CONSTANT
//#define IBA_PX_SIZE 5.86/2.55 //(pixel size X)/(optical magnification)
//#define IBA_PY_SIZE 5.86/2.55 //(pixel size Y)/(optical magnification)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class to fit a Gaussian peak with linear background using Levenberg-Marquardt algorithm
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class FitGaussLM
{
    public:

        // Constructor: initialize with data points
        FitGaussLM(const std::string& label, const std::vector<double>& y, double pixel_size=1);
        
        // Fit Gaussian using Levenberg-Marquardt algorithm
        void fit(int max_iterations = 256, double tol = 1e-9);

        // Get label
        const std::string& get_label() const;

        // Get input spectrum values
        std::vector<double> get_input_spectrum() const;

        // Get fitted spectrum values
        std::vector<double> get_fitted_spectrum() const;

        // Plot results into bmp file
        void save_to_bmp(const std::vector<double>& y_in,  const std::string& filename, int w = 800, int h = 600) const;

        // Get Amplitude of the Gaussian peak
        double get_amplitude() const;

        // Get Center (mean) of the peak
        double get_mu() const;

        // Get Standard deviation (controls width)
        double get_sigma() const;   

        // Get Full Width at Half Maximum (FWHM)
        double get_fwhm() const;

        // Get Constant background offset
        double get_bg() const;

        // Get Linear background slope
        double get_slope() const;

        // Get reduced chi2 squared
        double get_chi2() const;

        // Get Root Mean Square error of residuals
        double get_rms() const;

        // Get coefficient of determination R²
        double get_r2() const;

        // Get number of iteration in LM algo needed to converge
        int get_nb_iter() const;

        // Check if fit is valid
        bool has_converged() const;

        // Debug: print parameters
        void print_results() const;

    private:

        // Estimate initial parameters automatically
        void initialize_params();

        // Compute Gaussian model value at x
        double compute_gaussian(double x, double A, double mu, double sigma, double bg, double slope) const;

        // Compute residuals and Jacobian for LM fitting
        void compute_jacobian(const std::vector<double>& params, cv::Mat& J, cv::Mat& residuals) const;

        // Compute Euclidean norm of vector
        double compute_norm(const cv::Mat& mat) const;	

        // Compute reduced chi-squared
        void compute_reduced_chi_squared();

        // Compute Root Mean Square error of residuals
        void  compute_rms_error();

        // Compute coefficient of determination R²
        void  compute_r_squared();	

        // Sanitize vectors 
        cv::Mat sanitize_vector(const cv::Mat& v) const;

        // Transform vector to cv::Mat
        cv::Mat vector_to_mat(const std::vector<double>& vec) const;

        // Label for the fit (e.g., "XProj" or "YProj")
        std::string m_label;
        
        // Data members
        double m_pixel_size; // pixel size in physical units (e.g., microns)
        // Data points  
        std::vector<double> m_x;
        std::vector<double> m_y;
        // Fitting parameters
        // m_params = [A, mu, sigma, bg, slope]
        std::vector<double> m_params; // [A, mu, sigma, bg, slope]
        // Fitting metrics        
        double m_nb_iter;
        // Reduced chi2
        double m_chi2;
        // RMS error
        double m_rms;
        // Coefficient of determination R²
        double m_r2;
        // Convergence flag
        bool m_has_converged;
};
