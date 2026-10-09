#include "AutoROI.h"
#include "FitGaussLM.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor: initialize magnification factors
/////////////////////////////////////////////////////////////////////////////////////////////////////////
AutoROI::AutoROI(double factor_x, double factor_y)
    : m_factor_x(factor_x), m_factor_y(factor_y), m_has_converged(false)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute the auto ROI based on Gaussian fits along X and Y
/////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Rect AutoROI::compute(const cv::Mat& image)
{
    // Validate input image
    CV_Assert(!image.empty());
    CV_Assert(image.channels() == 1);
    CV_Assert(image.type() == CV_8UC1 || image.type() == CV_16UC1);

    //--------------------------------------------------------------------------
    // X projection (average over rows)
    //--------------------------------------------------------------------------
    cv::Mat proj_x_mat;
    cv::reduce(image, proj_x_mat, 0, CV_REDUCE_AVG, CV_64F);

    std::vector<double> proj_x(proj_x_mat.begin<double>(), proj_x_mat.end<double>());
    FitGaussLM fitX("along X", proj_x);
    fitX.fit(100, 1e-6);
    bool x_has_converged = fitX.has_converged();
    double mean_x  = fitX.get_mu();
    double sigma_x = fitX.get_sigma();

    // Safety: avoid negative/zero sigma producing weird widths
    if (!std::isfinite(sigma_x) || sigma_x < 1.0) sigma_x = 1.0;

    //--------------------------------------------------------------------------
    // Y projection (average over columns)
    //--------------------------------------------------------------------------
    cv::Mat proj_y_mat;
    cv::reduce(image, proj_y_mat, 1, CV_REDUCE_AVG, CV_64F);

    std::vector<double> proj_y(proj_y_mat.begin<double>(), proj_y_mat.end<double>());
    FitGaussLM fitY("along Y", proj_y);
    fitY.fit(100, 1e-6);
    bool y_has_converged = fitY.has_converged();
    double mean_y  = fitY.get_mu();
    double sigma_y = fitY.get_sigma();

    if (!std::isfinite(sigma_y) || sigma_y < 1.0) sigma_y = 1.0;

    //--------------------------------------------------------------------------
    // Build ROI "raw" (can be outside image), then intersect like ISL does
    //--------------------------------------------------------------------------
    int x0 = (int)std::floor(mean_x - sigma_x * m_factor_x);
    int w  = (int)std::ceil (2.0 * sigma_x * m_factor_x);

    int y0 = (int)std::floor(mean_y - sigma_y * m_factor_y);
    int h  = (int)std::ceil (2.0 * sigma_y * m_factor_y);

    cv::Rect roi_raw(x0, y0, w, h);

    // ISL's intersect(Rectangle(0,0,W,H)) equivalent:
    cv::Rect bounds(0, 0, image.cols, image.rows);
    cv::Rect roi = roi_raw & bounds;   // intersection / clipping

    // Convergence flag
    m_has_converged = x_has_converged && y_has_converged;

    // Optional fallback if ROI becomes empty (no overlap with image)
    // If you prefer a different behavior (return last ROI, whole image, etc.), change here.
    if (roi.empty())
        roi = bounds;

    return roi;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check if AutoROI has converged
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AutoROI::has_converged() const
{
    return m_has_converged;
}
///////////////////////////////////////////////////////////////////////////////////////////