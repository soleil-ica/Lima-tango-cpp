#include "FitGaussLM.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <numeric>

const double SIGMA2FWHM_SCALE_FACTOR = ::sqrt(8.0 * ::log(2.0));

///////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////
FitGaussLM::FitGaussLM(const std::string& label,
                       const std::vector<double>& y,
                       double pixel_size,
                       bool fixed_bg,
                       double fixed_bg_value)
: m_label(label),
  m_pixel_size(pixel_size),
  m_x(),
  m_y(y),
  m_params(),
  m_fixed_bg(fixed_bg),
  m_fixed_bg_value(fixed_bg_value),
  m_nb_iter(0),
  m_chi2(0.0),
  m_rms(0.0),
  m_r2(0.0),
  m_has_converged(false)
{
    if (m_y.empty())
        throw std::invalid_argument("Input data vector y must not be empty");

    m_x.resize(m_y.size());
    std::iota(m_x.begin(), m_x.end(), 0.0);

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
// Estimate background from profile edges, mimicking ISL::GaussianFit1D::initial_guess()
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::estimate_bg_edges() const
{
    const int kBG_FINDING_N = 5;
    const int n = static_cast<int>(m_y.size());

    if (n == 0)
        return 0.0;

    if (n < 2 * kBG_FINDING_N)
        return std::min(m_y.front(), m_y.back());

    double bg_begin = 0.0;
    double bg_end = 0.0;

    for (int i = 0; i < kBG_FINDING_N; ++i)
    {
        bg_begin += m_y[i];
        bg_end   += m_y[n - 1 - i];
    }

    bg_begin /= static_cast<double>(kBG_FINDING_N);
    bg_end   /= static_cast<double>(kBG_FINDING_N);

    return std::min(bg_begin, bg_end);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute Gaussian function:
// f(x) = bg + A * exp(-((x - mu)^2) / (2 * sigma^2))
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::compute_gaussian(double x, double A, double mu, double sigma, double bg) const
{
    return bg + A * std::exp(-((x - mu) * (x - mu)) / (2.0 * sigma * sigma));
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute Jacobian and residuals
//
// Parameters:
//   [A, mu, sigma, bg]
//
// If fixed_bg == true, bg is frozen and taken from m_fixed_bg_value
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_jacobian(const std::vector<double>& params,
                                  cv::Mat& J,
                                  cv::Mat& residuals) const
{
    const double A     = params[0];
    const double mu    = params[1];
    const double sigma = params[2];
    const double bg    = m_fixed_bg ? m_fixed_bg_value : params[3];

    const int N = static_cast<int>(m_x.size());

    for (int i = 0; i < N; ++i)
    {
        const double xi = m_x[i];
        const double yi = m_y[i];

        const double dx = xi - mu;
        const double sigma2 = sigma * sigma;
        const double exp_term = std::exp(-(dx * dx) / (2.0 * sigma2));

        const double fi = bg + A * exp_term;

        residuals.at<double>(i, 0) = yi - fi;

        J.at<double>(i, 0) = exp_term;                                 // df/dA
        J.at<double>(i, 1) = A * exp_term * dx / sigma2;              // df/dmu
        J.at<double>(i, 2) = A * exp_term * (dx * dx) / (sigma2 * sigma); // df/dsigma
        J.at<double>(i, 3) = m_fixed_bg ? 0.0 : 1.0;                  // df/dbg
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute L2 norm of a vector
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::compute_norm(const cv::Mat& mat) const
{
    double sum_sq = 0.0;
    for (int i = 0; i < mat.rows; ++i)
    {
        const double val = mat.at<double>(i, 0);
        sum_sq += val * val;
    }
    return std::sqrt(sum_sq);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute reduced chi-squared statistic
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_reduced_chi_squared()
{
    const int N = static_cast<int>(m_x.size());
    int p = m_fixed_bg ? 3 : 4;

    double ssr = 0.0;
    const double bg = m_fixed_bg ? m_fixed_bg_value : m_params[3];

    for (int i = 0; i < N; ++i)
    {
        const double fi = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], bg);
        const double residual = m_y[i] - fi;
        ssr += residual * residual;
    }

    const int dof = N - p;
    m_chi2 = (dof > 0) ? (ssr / static_cast<double>(dof)) : 0.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute root-mean-square (RMS) error
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_rms_error()
{
    double sum_sq = 0.0;
    const double bg = m_fixed_bg ? m_fixed_bg_value : m_params[3];

    for (size_t i = 0; i < m_x.size(); ++i)
    {
        const double y_fit = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], bg);
        const double diff = m_y[i] - y_fit;
        sum_sq += diff * diff;
    }

    m_rms = std::sqrt(sum_sq / static_cast<double>(m_x.size()));
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Compute R-squared
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::compute_r_squared()
{
    double mean_y = 0.0;
    for (double val : m_y)
        mean_y += val;
    mean_y /= static_cast<double>(m_y.size());

    double ss_tot = 0.0;
    double ss_res = 0.0;

    const double bg = m_fixed_bg ? m_fixed_bg_value : m_params[3];

    for (size_t i = 0; i < m_x.size(); ++i)
    {
        const double y_fit = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], bg);
        const double diff_res = m_y[i] - y_fit;
        const double diff_tot = m_y[i] - mean_y;

        ss_res += diff_res * diff_res;
        ss_tot += diff_tot * diff_tot;
    }

    m_r2 = (ss_tot > 0.0) ? (1.0 - (ss_res / ss_tot)) : 1.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Automatic initial parameter estimation, mimicking ISL::GaussianFit1D::initial_guess()
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::initialize_params()
{
    const int n = static_cast<int>(m_y.size());

    if (n < 3)
    {
        const double bg = m_fixed_bg ? m_fixed_bg_value : 0.0;
        m_params = { m_y[0], 0.0, 1.0, bg };
        return;
    }

    //-----------------------
    // BACKGROUND
    //-----------------------
    double background = m_fixed_bg ? m_fixed_bg_value : estimate_bg_edges();

    //-----------------------
    // CENTER
    //-----------------------
    int maxima_pos = 0;
    double maxima_val = m_y[0];
    for (int i = 1; i < n; ++i)
    {
        if (m_y[i] > maxima_val)
        {
            maxima_val = m_y[i];
            maxima_pos = i;
        }
    }
    const double mean = static_cast<double>(maxima_pos);

    //-----------------------
    // SIGMA
    //-----------------------
    double sigma = 0.0;
    {
        double val = m_y[maxima_pos];
        int pos = maxima_pos;

        const double half_top_mag = 0.5 * (background + val);

        if (maxima_pos < n / 2)
        {
            while (pos < n - 1 && val > half_top_mag)
                val = m_y[++pos];
        }
        else
        {
            while (pos > 0 && val > half_top_mag)
                val = m_y[--pos];
        }

        if (pos != maxima_pos)
            sigma = std::fabs(static_cast<double>(pos - maxima_pos));
        else
            sigma = static_cast<double>(n) / 6.0;
    }

    if (sigma <= 0.0)
        sigma = 1.0;

    //-----------------------
    // MAGNITUDE
    //-----------------------
    const double magnitude = maxima_val; // ISL behavior

    m_params = { magnitude, mean, sigma, background };
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Levenberg-Marquardt fitting
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::fit(int max_iterations, double tol)
{
    const int N = static_cast<int>(m_x.size());
    const int M = 4; // [A, mu, sigma, bg]

    double lambda = 1e-3;
    m_nb_iter = 0;

    for (m_nb_iter = 0; m_nb_iter < static_cast<unsigned int>(max_iterations); ++m_nb_iter)
    {
        cv::Mat J(N, M, CV_64F, cv::Scalar(0));
        cv::Mat residuals(N, 1, CV_64F, cv::Scalar(0));
        compute_jacobian(m_params, J, residuals);

        cv::Mat JTJ = J.t() * J;
        cv::Mat JTRes = J.t() * residuals;

        for (int i = 0; i < M; ++i)
            JTJ.at<double>(i, i) += lambda;

        if (m_fixed_bg)
            JTJ.at<double>(3, 3) += 1e12;

        cv::Mat delta;
        cv::solve(JTJ, JTRes, delta, cv::DECOMP_SVD);

        std::vector<double> new_params = m_params;

        for (int i = 0; i < M; ++i)
        {
            if (m_fixed_bg && i == 3)
                continue;

            new_params[i] += delta.at<double>(i, 0);
        }

        if (new_params[2] <= 0.0)
        {
            lambda *= 10.0;
            continue;
        }

        const double error = compute_norm(residuals);

        cv::Mat dummyJ(N, M, CV_64F, cv::Scalar(0));
        cv::Mat new_residuals(N, 1, CV_64F, cv::Scalar(0));
        compute_jacobian(new_params, dummyJ, new_residuals);
        const double new_error = compute_norm(new_residuals);

        if (new_error < error)
        {
            lambda *= 0.1;
            m_params = new_params;

            if (std::fabs(error - new_error) < tol)
                break;
        }
        else
        {
            lambda *= 10.0;
        }
    }

    m_has_converged = (m_nb_iter < static_cast<unsigned int>(max_iterations));

    if (m_fixed_bg)
        m_params[3] = m_fixed_bg_value;

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
    const double bg = m_fixed_bg ? m_fixed_bg_value : m_params[3];

    for (size_t i = 0; i < m_x.size(); ++i)
    {
        y_fit[i] = compute_gaussian(m_x[i], m_params[0], m_params[1], m_params[2], bg);
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
// Get Standard deviation
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_sigma() const
{
    return m_params[2] * m_pixel_size;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Full Width at Half Maximum (FWHM)
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_fwhm() const
{
    return SIGMA2FWHM_SCALE_FACTOR * m_params[2] * m_pixel_size;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get Constant background offset
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_bg() const
{
    return m_fixed_bg ? m_fixed_bg_value : m_params[3];
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get reduced chi2
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_chi2() const
{
    return m_chi2;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get RMS
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_rms() const
{
    return m_rms;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get R²
///////////////////////////////////////////////////////////////////////////////////////////////
double FitGaussLM::get_r2() const
{
    return m_r2;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Get number of iterations
///////////////////////////////////////////////////////////////////////////////////////////////
unsigned int FitGaussLM::get_nb_iter() const
{
    return m_nb_iter;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Check convergence
///////////////////////////////////////////////////////////////////////////////////////////////
bool FitGaussLM::has_converged() const
{
    return m_has_converged;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Generate a BMP plot of the Gaussian fit and experimental points
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::save_to_bmp(const std::vector<double>& y_in,
                             const std::string& filename,
                             int w,
                             int h) const
{
    std::vector<double> x_in(y_in.size());
    std::iota(x_in.begin(), x_in.end(), 0.0);

    cv::Mat x = vector_to_mat(x_in);
    cv::Mat y = vector_to_mat(y_in);

    double min_x, max_x, min_y, max_y;
    cv::minMaxLoc(x, &min_x, &max_x);
    cv::minMaxLoc(y, &min_y, &max_y);

    cv::Mat canvas(h, w, CV_8UC3, cv::Scalar(255, 255, 255));

    auto to_canvas = [&](double xv, double yv)
    {
        int X = static_cast<int>((xv - min_x) / (max_x - min_x) * (w - 1));
        int Y = h - 1 - static_cast<int>((yv - min_y) / (max_y - min_y) * (h - 1));
        return cv::Point(X, Y);
    };

    for (int i = 0; i < x.rows; ++i)
    {
        cv::circle(canvas,
                   to_canvas(x.at<double>(i, 0), y.at<double>(i, 0)),
                   2,
                   cv::Scalar(255, 0, 0),
                   -1);
    }

    std::vector<cv::Point> fit_curve;
    const int n_samples = 200;
    const double A = m_params[0];
    const double mu = m_params[1];
    const double sigma = m_params[2];
    const double b = get_bg();

    for (int i = 0; i < n_samples; ++i)
    {
        const double xv = min_x + (max_x - min_x) * i / (n_samples - 1);
        const double z = (xv - mu) / sigma;
        const double yv = A * std::exp(-0.5 * z * z) + b;
        fit_curve.push_back(to_canvas(xv, yv));
    }

    for (size_t i = 1; i < fit_curve.size(); ++i)
    {
        cv::line(canvas, fit_curve[i - 1], fit_curve[i], cv::Scalar(0, 0, 255), 2);
    }

    int y0 = 20;
    const double fwhm = SIGMA2FWHM_SCALE_FACTOR * sigma * m_pixel_size;

    const double chi2 = get_chi2();
    const double rms  = get_rms();
    const double r2   = get_r2();

    std::vector<std::string> texts =
    {
        "A = " + std::to_string(A),
        "mu = " + std::to_string(mu),
        "sigma = " + std::to_string(sigma * m_pixel_size),
        "FWHM = " + std::to_string(fwhm),
        "BG = " + std::to_string(b),
        "Reduced Chi2 = " + std::to_string(chi2),
        "RMS error = " + std::to_string(rms),
        "R^2 = " + std::to_string(r2),
    };

    for (size_t i = 0; i < texts.size(); ++i)
    {
        cv::putText(canvas,
                    texts[i],
                    cv::Point(10, y0 + 20 * static_cast<int>(i)),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    cv::Scalar(0, 0, 0),
                    1,
                    CV_AA);
    }

    cv::imwrite(filename, canvas);
    std::cout << "FitGaussianLM Results saved to : " << filename << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Ensure that input vector is a column vector of type CV_64F
///////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat FitGaussLM::sanitize_vector(const cv::Mat& v) const
{
    cv::Mat v_out;

    if (v.cols == 1 && v.type() == CV_64F)
        return v;

    if (v.rows == 1 && v.type() == CV_64F)
        cv::transpose(v, v_out);
    else
        v.convertTo(v_out, CV_64F);

    return v_out;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// from std::vector to cv::Mat
///////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat FitGaussLM::vector_to_mat(const std::vector<double>& vec) const
{
    return cv::Mat(vec).clone().reshape(1, static_cast<int>(vec.size()));
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Print fitting results to console
///////////////////////////////////////////////////////////////////////////////////////////////
void FitGaussLM::print_results() const
{
    std::cout << "Fit results ("    << get_label()      << ") :"      << std::endl;
    std::cout << "--------------------"                                << std::endl;
    std::cout << "A : "             << get_amplitude()                << std::endl;
    std::cout << "mu : "            << get_mu()                       << std::endl;
    std::cout << "sigma : "         << get_sigma()                    << std::endl;
    std::cout << "FWHM : "          << get_fwhm()                     << std::endl;
    std::cout << "BG : "            << get_bg()                       << std::endl;
    std::cout << "Reduced Chi2 : "  << get_chi2()                     << std::endl;
    std::cout << "RMS : "           << get_rms()                      << std::endl;
    std::cout << "R² : "            << get_r2()                       << std::endl;
    std::cout << "Nb iterations : " << get_nb_iter()                  << std::endl;
    std::cout << ""                                                    << std::endl;
}