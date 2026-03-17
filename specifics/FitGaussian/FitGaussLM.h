#pragma once

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class to fit a 1D Gaussian peak with constant background using Levenberg-Marquardt algorithm
//
// Model:
//     f(x) = bg + A * exp( - (x - mu)^2 / (2 * sigma^2) )
//
// Parameters stored in m_params:
//     [A, mu, sigma, bg]
//
// Notes:
// - fixed_bg = false : bg is optimized
// - fixed_bg = true  : bg is imposed and not optimized
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class FitGaussLM
{
public:

    // Constructor
    FitGaussLM(const std::string& label,
               const std::vector<double>& y,
               double pixel_size = 1.0,
               bool fixed_bg = false,
               double fixed_bg_value = 0.0);

    // Fit Gaussian using Levenberg-Marquardt algorithm
    void fit(int max_iterations = 256, double tol = 1e-9);

    // Get label
    const std::string& get_label() const;

    // Get input spectrum values
    std::vector<double> get_input_spectrum() const;

    // Get fitted spectrum values
    std::vector<double> get_fitted_spectrum() const;

    // Plot results into bmp file
    void save_to_bmp(const std::vector<double>& y_in,
                     const std::string& filename,
                     int w = 800,
                     int h = 600) const;

    // Get Amplitude of the Gaussian peak
    double get_amplitude() const;

    // Get Center (mean) of the peak
    double get_mu() const;

    // Get Standard deviation
    double get_sigma() const;

    // Get Full Width at Half Maximum (FWHM)
    double get_fwhm() const;

    // Get Constant background offset
    double get_bg() const;

    // Get reduced chi2
    double get_chi2() const;

    // Get Root Mean Square error of residuals
    double get_rms() const;

    // Get coefficient of determination R²
    double get_r2() const;

    // Get number of iterations in LM algo needed to converge
    unsigned int get_nb_iter() const;

    // Check if fit is valid
    bool has_converged() const;

    // Debug: print parameters
    void print_results() const;

private:

    // Estimate initial parameters automatically
    void initialize_params();

    // Estimate background from profile edges, ISL-like
    double estimate_bg_edges() const;

    // Compute Gaussian model value at x
    double compute_gaussian(double x, double A, double mu, double sigma, double bg) const;

    // Compute residuals and Jacobian for LM fitting
    void compute_jacobian(const std::vector<double>& params, cv::Mat& J, cv::Mat& residuals) const;

    // Compute Euclidean norm of vector
    double compute_norm(const cv::Mat& mat) const;

    // Compute reduced chi-squared
    void compute_reduced_chi_squared();

    // Compute Root Mean Square error of residuals
    void compute_rms_error();

    // Compute coefficient of determination R²
    void compute_r_squared();

    // Sanitize vectors
    cv::Mat sanitize_vector(const cv::Mat& v) const;

    // Transform vector to cv::Mat
    cv::Mat vector_to_mat(const std::vector<double>& vec) const;

private:

    // Label for the fit (e.g., "XProj" or "YProj")
    std::string m_label;

    // Pixel size in physical units (e.g., microns)
    double m_pixel_size;

    // Data points
    std::vector<double> m_x;
    std::vector<double> m_y;

    // Fitting parameters: [A, mu, sigma, bg]
    std::vector<double> m_params;

    // Fixed background mode
    bool m_is_fixed_bg;
    double m_fixed_bg_value;

    // Fitting metrics
    unsigned int m_nb_iter;
    double m_chi2;
    double m_rms;
    double m_r2;

    // Convergence flag
    bool m_has_converged;
};