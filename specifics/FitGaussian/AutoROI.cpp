#include "AutoROI.h"
#include "FitGaussLM.h" // Make sure this class is included
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <yat/time/Timer.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor: initialize magnification factors
/////////////////////////////////////////////////////////////////////////////////////////////////////////
AutoROI::AutoROI(double factor_x, double factor_y)
    : m_factor_x(factor_x), m_factor_y(factor_y)
{
    m_has_converged = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute the auto ROI based on Gaussian fits along X and Y
/////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Rect AutoROI::compute(const cv::Mat& image)
{
    CV_Assert(image.channels() == 1); // Only single-channel images
    CV_Assert(image.type() == CV_8UC1 || image.type() == CV_16UC1);

    /////////////////////////////////////////////////////////////////////////////
    // Roi X based on FIT on X
    /////////////////////////////////////////////////////////////////////////////
    // Average over rows -> projection along X
    cv::Mat proj_x_mat;
    cv::reduce(image, proj_x_mat, 0, CV_REDUCE_AVG, CV_64F); // 0 = reduce rows
 
    // --- Gaussian fit along X ---
    std::vector<double> proj_x(proj_x_mat.begin<double>(), proj_x_mat.end<double>());
    FitGaussLM fitX("along X", proj_x);
    fitX.fit(100, 1e-6);
    bool x_has_converged = fitX.has_converged();
    double mean_x  = fitX.get_mu();
    double sigma_x = fitX.get_sigma();

    int roi_x     = std::max(0, (int)std::floor(mean_x - sigma_x * m_factor_x));
    int roi_width = std::min(image.cols - roi_x, (int)std::ceil(2 * sigma_x * m_factor_x));
    
    /////////////////////////////////////////////////////////////////////////////
    // Roi Y based on FIT on Y
    /////////////////////////////////////////////////////////////////////////////    
    // Average over columns -> projection along Y
    cv::Mat proj_y_mat;
    cv::reduce(image, proj_y_mat, 1, CV_REDUCE_AVG, CV_64F); // 1 = reduce cols

    // --- Gaussian fit along Y ---    
    std::vector<double> proj_y(proj_y_mat.begin<double>(), proj_y_mat.end<double>());
    FitGaussLM fitY("along Y", proj_y);
    fitY.fit(100, 1e-6);
    bool y_has_converged = fitY.has_converged();
    double mean_y = fitY.get_mu();
    double sigma_y = fitY.get_sigma();

    int roi_y      = std::max(0, (int)std::floor(mean_y - sigma_y * m_factor_y));
    int roi_height = std::min(image.rows - roi_y, (int)std::ceil(2 * sigma_y * m_factor_y));

    // --- Construct the ROI rectangle ---
    m_has_converged = x_has_converged && y_has_converged;
    return cv::Rect(roi_x, roi_y, roi_width, roi_height);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Check if AutoROI has converged
/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AutoROI::has_converged() const
{
    return m_has_converged; //true if AutoROI converged
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////