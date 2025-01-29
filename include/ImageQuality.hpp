#ifndef IMAGEQUALITY_HPP
#define IMAGEQUALITY_HPP

#include <opencv2/opencv.hpp>
#include <vector>

class ImageQuality {
public:

    ImageQuality();

    // Scott Daly's Visual Difference Predictor (VDP) Method
    cv::Mat applyVDP(const cv::Mat& image1, const cv::Mat& image2);

    // Metrics Calculation
    double calculatePercentageDifference(const cv::Mat& differenceMap, double threshold);
    double calculateMeanVisualDifference(const cv::Mat& differenceMap);
    double calculateMaximumVisualDifference(const cv::Mat& differenceMap);
    double calculateSSIM(const cv::Mat& image1, const cv::Mat& image2);
    double calculatePSNR(const cv::Mat& image1, const cv::Mat& image2);

    // Heatmap visualization
    cv::Mat generateHeatmap(const cv::Mat& differenceMap, double threshold);

private:
    // Helper functions
    cv::Mat preprocessImage(const cv::Mat& image);
    cv::Mat computeDifferenceMap(const cv::Mat& image1, const cv::Mat& image2);
    cv::Mat applyContrastSensitivityFunction(const cv::Mat& image);
    std::vector<cv::Mat> splitFrequencyChannels(const cv::Mat& image);
    cv::Mat applyMaskingFunction(const cv::Mat& frequencyChannel);
};

#endif
