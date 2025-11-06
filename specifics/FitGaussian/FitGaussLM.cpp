#include "FitGaussLM.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////
FitGaussLM::FitGaussLM(const std::string& label, const std::vector<double>& y, double pixel_size)
: m_label(label),
  m_x(),
  m_y(y),
  m_pixel_size(pixel_size)
{
    if (m_y.empty())
    {
        throw std::invalid_argument("Input data vector y must not be empty");
    }
    m_x.clear();
    m_x.resize(m_y.size());
    std::iota(m_x.begin(), m_x.end(), 0.0); // fill m_x with 0, 1, 2, ..., n-1
    m_has_converged = false;
    initialize_params();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get label
///////////////////////////////////////////////////////////////////////////////////////////////
const std::string& FitGaussLM::get_label() const
{
    return m_label;
}   

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute Gaussian function with linear background
// f(x) = bg + slope*x + A * exp(-((x - mu)^2) / (2 * sigma^2))
//
// Parameters:
//   x      : input point
//   A      : amplitude of the Gaussian peak
//   mu     : center (mean) of the peak
//   sigma  : standard deviation (controls width)
//   bg     : constant background offset
//   slope  : linear background slope
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::compute_gaussian(double x, double A, double mu, double sigma, double bg, double slope) const
{
    return bg + slope * x + A * std::exp(-((x - mu) * (x - mu)) / (2 * sigma * sigma));
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute Jacobian and residuals
// For each data point (xi, yi):
// - residual = yi - f(xi, params)
// - J(i, :) = partial derivatives of f(x) w.r.t. each parameter
//
// Parameters: [A, mu, sigma, bg, slope]
// f(x) = bg + slope*x + A * exp(-((x - mu)^2) / (2 * sigma^2))
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_jacobian(const std::vector<double>& params, cv::Mat& J, cv::Mat& residuals) const
{
    // Unpack parameters
    double A     = params[0];
    double mu    = params[1];
    double sigma = params[2];
    double bg    = params[3];
    double slope = params[4];

    int N = static_cast<int>(m_x.size());

    for (int i = 0; i < N; ++i)
    {
        double xi = m_x[i];   // current x data point
        double yi = m_y[i];   // measured y value

        // Gaussian term exp(-(x - mu)^2 / (2*sigma^2))
        double exp_term = std::exp(-((xi - mu) * (xi - mu)) / (2 * sigma * sigma));

        // Model value at xi
        double fi = bg + slope * xi + A * exp_term;

        // Residual: difference between observed and model
        residuals.at<double>(i, 0) = yi - fi;

        // Fill Jacobian row (∂f/∂params)
        J.at<double>(i, 0) = exp_term;                                                      // ∂f/∂A
        J.at<double>(i, 1) = A * exp_term * (xi - mu) / (sigma * sigma);                    // ∂f/∂mu
        J.at<double>(i, 2) = A * exp_term * ((xi - mu)*(xi - mu)) / (sigma*sigma*sigma);    // ∂f/∂sigma
        J.at<double>(i, 3) = 1.0;                                                           // ∂f/∂bg
        J.at<double>(i, 4) = xi;                                                            // ∂f/∂slope
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute L2 norm of a vector
// Input: a column vector (cv::Mat)
// Output: sqrt(sum of squared values)
// Used to measure the magnitude of the residuals.
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::compute_norm(const cv::Mat& mat) const
{
    double sum_sq = 0.0;
    for (int i = 0; i < mat.rows; ++i)
    {
        double val = mat.at<double>(i, 0);
        sum_sq += val * val;
    }
    return std::sqrt(sum_sq);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute reduced chi-squared statistic
// χ²_red = (Σ (residuals²)) / (N - p)
//   N = number of data points
//   p = number of fitted parameters
// This gives a normalized measure of goodness-of-fit.
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_reduced_chi_squared()
{
    int N = static_cast<int>(m_x.size());
    int p = static_cast<int>(m_params.size());
    double ssr = 0.0;

    for (int i = 0; i < N; ++i)
    {
        double fi = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], m_params[3], m_params[4]);
        double residual = m_y[i] - fi;
        ssr += residual * residual;
    }
    m_chi2 =  ssr / (N - p);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute root-mean-square (RMS) error
// RMS = sqrt( Σ(residuals²) / N )
// Measures the average deviation of the fit from the data.
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_rms_error()
{
    double sum_sq = 0.0;
    for (size_t i = 0; i < m_x.size(); ++i)
    {
        double y_fit = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], m_params[3], m_params[4]);
        double diff = m_y[i] - y_fit;
        sum_sq += diff * diff;
    }
    m_rms = std::sqrt(sum_sq / static_cast<double>(m_x.size()));
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute reduced R-squared
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_r_squared()
{
    double mean_y = 0.0;
    for (double val : m_y)
    mean_y += val;
    mean_y /= static_cast<double>(m_y.size());

    double ss_tot = 0.0;
    double ss_res = 0.0;

    for (size_t i = 0; i < m_x.size(); ++i)
    {
        double y_fit = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], m_params[3], m_params[4]);
        double diff_res = m_y[i] - y_fit;
        double diff_tot = m_y[i] - mean_y;

        ss_res += diff_res * diff_res;
        ss_tot += diff_tot * diff_tot;
    }

    m_r2 = 1.0 - (ss_res / ss_tot);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Automatic initial parameter estimation
// This function tries to provide good initial guesses for the Gaussian parameters
// (amplitude, center, width, background, slope) based on the input data (m_x, m_y).
// Good initialization is critical for iterative methods like Levenberg–Marquardt,
// since it helps the optimizer converge faster and avoid local minima.
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::initialize_params()
{
    // Find minimum and maximum values in the data (y-axis values).
    double y_min = *min_element(m_y.begin(), m_y.end());
    double y_max = *max_element(m_y.begin(), m_y.end());

    // Estimate amplitude as the peak height above background.
    double A_init = y_max - y_min;

    // Estimate background as the lowest measured value.
    double bg_init = y_min;

    // Estimate slope of linear background using first and last points.
    double slope_init = (m_y.back() - m_y.front()) / (m_x.back() - m_x.front());

    // Find the index of the maximum y-value (approximate center of Gaussian).
    int mu_index = distance(m_y.begin(), max_element(m_y.begin(), m_y.end()));
    double mu_init = m_x[mu_index];  // Corresponding x-value is initial "mu".

    // Estimate the Full Width at Half Maximum (FWHM).
    double half_max = (y_max + y_min) / 2.0;
    int left = 0, right = static_cast<int>(m_y.size() - 1);

    // Search from the left until signal rises above half maximum.
    for (size_t i = 0; i < m_y.size(); ++i)
    {
        if (m_y[i] > half_max)
        {
            left = static_cast<int>(i);
            break;
        }
    }

    // Search from the right until signal drops below half maximum.
    for (size_t i = m_y.size(); i-- > 0;)
    {
        if (m_y[i] > half_max)
        {
            right = static_cast<int>(i);
            break;
        }
    }

    // If valid left/right bounds were found, estimate FWHM from x-coordinates.
    // Otherwise, fall back to using half the x-range as a crude guess.
    double fwhm = (right > left) ? (m_x[right] - m_x[left]) 
                                 : (m_x.back() - m_x.front()) / 2.0;

    // Convert FWHM to sigma (σ = FWHM / 2.355 for Gaussian).
    double sigma_init = fwhm / 2.355;

    // Store all estimated parameters in the order: [A, mu, sigma, bg, slope].
    m_params = { A_init, mu_init, sigma_init, bg_init, slope_init };
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Levenberg-Marquardt fitting
// Iteratively optimizes Gaussian parameters (A, mu, sigma, bg, slope)
// to minimize residuals between model and data using the LM algorithm.
// - max_iterations: maximum allowed iterations
// - tol: stopping criterion based on error improvement
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::fit(int max_iterations, double tol)
{
    int N = static_cast<int>(m_x.size()); // number of data points
    int M = 5;                            // number of parameters

    double lambda = 1e-3; // damping factor (balances between GD and Gauss-Newton)
    m_nb_iter = 0;

    for (m_nb_iter = 0; m_nb_iter < max_iterations; ++m_nb_iter)
    {
        // Jacobian (N×M) and residuals (N×1) for current parameters
        cv::Mat J(N, M, CV_64F);
        cv::Mat residuals(N, 1, CV_64F);
        compute_jacobian(m_params, J, residuals);

        // Normal equations: (JᵀJ) δ = Jᵀr
        cv::Mat JTJ = J.t() * J;
        cv::Mat JTRes = J.t() * residuals;

        // LM modification: add λ to diagonal
        for (int i = 0; i < M; ++i)
            JTJ.at<double>(i, i) += lambda;

        // Solve for parameter update δ
        cv::Mat delta;
        cv::solve(JTJ, JTRes, delta, cv::SVD::MODIFY_A);

        // Compute candidate new parameters
        std::vector<double> new_params = m_params;
        for (int i = 0; i < M; ++i)
            new_params[i] += delta.at<double>(i, 0);

        // Current error
        double error = compute_norm(residuals);

        // Error with candidate parameters
        cv::Mat new_residuals(N, 1, CV_64F);
        cv::Mat dummyJ(N, M, CV_64F);
        compute_jacobian(new_params, dummyJ, new_residuals);
        double new_error = compute_norm(new_residuals);

        // Accept step if error decreases and sigma > 0
        if (new_error < error && new_params[2] > 0)
        {
            lambda *= 0.1;          // decrease damping (closer to Gauss-Newton)
            m_params = new_params;  // accept new parameters
            if (fabs(error - new_error) < tol) // convergence check
                break;
        }
        else
        {
            lambda *= 10; // increase damping (closer to gradient descent)
        }
    }
    // Set convergence flag
	if(m_nb_iter < max_iterations)
        m_has_converged = true;
    else
        m_has_converged = false;

    // Compute metrics
    compute_reduced_chi_squared();
    compute_rms_error();
    compute_r_squared();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get input spectrum values
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> FitGaussLM::get_input_spectrum() const
{
    return m_y;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get fitted spectrum values
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> FitGaussLM::get_fitted_spectrum() const
{
    std::vector<double> y_fit(m_y.size());
    for (size_t i = 0; i < m_x.size(); ++i)
    {
        y_fit[i] = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], m_params[3], m_params[4]);
    }
    return y_fit;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Get Amplitude of the Gaussian peak
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_amplitude() const
{
    return m_params[0];
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Center (mean) of the peak
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_mu() const
{
    return m_params[1];
}   

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Standard deviation (controls width)
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_sigma() const
{
    return m_params[2]*m_pixel_size;
}   

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Full Width at Half Maximum (FWHM)
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_fwhm() const
{
    return 2.355 * m_params[2]*m_pixel_size;//2*sqrt(ln2)*sigma
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Constant background offset
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_bg() const
{
    return m_params[3];
}   

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Linear background slope
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_slope() const
{
    return m_params[4];
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get number of iteration in LM algo needed to converge
///////////////////////////////////////////////////////////////////////////////////////////////
int FitGaussLM::get_nb_iter() const
{
    return m_nb_iter;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get reduced chi2 squared
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_chi2() const
{
	return m_chi2;
}
		
///////////////////////////////////////////////////////////////////////////////////////////////
// Get Root Mean Square error of residuals
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_rms() const
{
	return m_rms;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get coefficient of determination R²
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_r2() const
{
    return m_r2;
}
		
///////////////////////////////////////////////////////////////////////////////////////////////
// Check if fit is valid
bool FitGaussLM::has_converged() const
{
    return m_has_converged;//true if fit converged
}   


///////////////////////////////////////////////////////////////////////////////////////////////
// Generate a BMP plot of the Gaussian fit and experimental points
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::save_to_bmp(const std::vector<double>& y_in, const std::string& filename, int w , int h) const
{
    // Ensure input vectors are column vectors of type double
    std::vector<double> x_in;//index of y_in
    x_in.resize(y_in.size());
    std::iota(x_in.begin(), x_in.end(), 0.0); // fill x_in with 0, 1, 2, ..., n-1
    cv::Mat x = vector_to_mat(x_in);
    cv::Mat y = vector_to_mat(y_in);
    
    // Determine min/max values for scaling
    double min_x, max_x, min_y, max_y;
    cv::minMaxLoc(x, &min_x, &max_x);
    cv::minMaxLoc(y, &min_y, &max_y);

    // Create white canvas
    cv::Mat canvas(h, w, CV_8UC3, cv::Scalar(255, 255, 255));

    // Lambda function to convert data points to canvas coordinates
    auto to_canvas = [&](double xv, double yv)
    {
        int X = static_cast<int>((xv - min_x) / (max_x - min_x) * (w - 1));
        int Y = h - 1 - static_cast<int>((yv - min_y) / (max_y - min_y) * (h - 1));
        return cv::Point(X, Y);
    };

    // Draw experimental points in black
    for (int i = 0; i < x.rows; ++i)
    {
        cv::circle(canvas, to_canvas(x.at<double>(i, 0), y.at<double>(i, 0)), 2, cv::Scalar(255, 0, 0), -1);
    }

    // Draw Gaussian fit curve in red
    std::vector<cv::Point> fit_curve;
    int n_samples = 200;
    double A = m_params[0];
    double mu = m_params[1];
    double sigma = m_params[2];
    double b = m_params[3];
    double slope = m_params[4];

    for (int i = 0; i < n_samples; ++i)
    {
        double xv = min_x + (max_x - min_x) * i / (n_samples - 1);
        double z = (xv - mu) / sigma;
        double yv = A * std::exp(-0.5 * z * z) + b + slope * xv;
        fit_curve.push_back(to_canvas(xv, yv));
    }

    for (size_t i = 1; i < fit_curve.size(); ++i)
    {
        cv::line(canvas, fit_curve[i - 1], fit_curve[i], cv::Scalar(0, 0, 255), 2);
    }

    // Display fit parameters as text
    int y0 = 20;
    double fwhm = 2.355 * sigma*m_pixel_size;
		
    // get metrics
    double chi2 = get_chi2();
    double rms = get_rms();
    double r2  = get_r2();
		
    std::vector<std::string> texts = 
    {
        "A = " + std::to_string(A),
        "mu = " + std::to_string(mu),
        "sigma = " + std::to_string(sigma*m_pixel_size),
        "FWHM = " + std::to_string(fwhm),
        "BG = " + std::to_string(b),
        "Slope = " + std::to_string(slope),
        "Reduced Chi2 = " + std::to_string(chi2),
        "RMS error = " + std::to_string(rms),
        "R^2 = " + std::to_string(r2),
    };

    for (size_t i = 0; i < texts.size(); ++i)
    {
        cv::putText(canvas, texts[i], cv::Point(10, y0 + 20 * i), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 1, CV_AA);				
    }

    // Save BMP image
    cv::imwrite(filename, canvas);
    std::cout << "FitGaussianLM Results saved to : " << filename <<std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Ensure that input vector is a column vector of type CV_64F (double precision).
// - If input is already CV_64F column → return as is.
// - If input is CV_64F row → transpose to column.
// - Otherwise → convert to CV_64F column.
// This standardization avoids issues when using vectors in OpenCV matrix operations.
///////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat FitGaussLM::sanitize_vector(const cv::Mat& v) const
{
    cv::Mat v_out;

    // Already the correct format: column vector of doubles
    if (v.cols == 1 && v.type() == CV_64F)
        return v;

    // If it's a row vector of doubles → transpose to column
    if (v.rows == 1 && v.type() == CV_64F)
        cv::transpose(v, v_out);
    else // Convert any other type (e.g., int, float) to double precision column
        v.convertTo(v_out, CV_64F);

    return v_out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// from std::vector to cv::Mat
/////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat FitGaussLM::vector_to_mat(const std::vector<double>& vec) const
{
    return cv::Mat(vec).clone().reshape(1, (int)vec.size());
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Print fitting results to console
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::print_results() const
{    
    std::cout<<"Fit results ("      <<get_label()<<") :"        <<std::endl;
    std::cout<<"--------------------"                           <<std::endl;
    std::cout<<"A : "               <<get_amplitude()           <<std::endl;  
    std::cout<<"mu : "              <<get_mu()                  <<std::endl;
    std::cout<<"sigma : "           <<get_sigma()               <<std::endl;
    std::cout<<"FWHM : "            <<get_fwhm()                <<std::endl;
    std::cout<<"BG : "              <<get_bg()                  <<std::endl;
    std::cout<<"Slope : "           <<get_slope()               <<std::endl;
    std::cout<<"Reduced Chi2 : "    <<get_chi2()                <<std::endl;
    std::cout<<"RMS : "             <<get_rms()                 <<std::endl;
    std::cout<<"R² : "              <<get_r2()                  <<std::endl;
    std::cout<<"Nb iterations : "   <<get_nb_iter()             <<std::endl;               
    std::cout<<""                   <<std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
