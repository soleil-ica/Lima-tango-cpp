#ifndef AUTOROI_H
#define AUTOROI_H

#include <opencv2/core/core.hpp>     // cv::Mat, cv::Rect

class AutoROI
{
public:
    // Constructor with magnification factors for X and Y
    AutoROI(double factor_x, double factor_y);

    // Method to compute the ROI from a grayscale image
    cv::Rect compute(const cv::Mat& image);

    // Method to check if the AutoROI computation has converged
    bool has_converged() const;

private:
    double  m_factor_x; // Magnification factor along X
    double  m_factor_y; // Magnification factor along Y
    bool    m_has_converged; // Convergence flag
};

#endif // AUTOROI_H
