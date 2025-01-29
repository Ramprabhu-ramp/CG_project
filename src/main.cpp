#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageQuality.hpp"

int main() {
    // Loading the images
    cv::Mat image1 = cv::imread("../images/LQ.jpg");
    cv::Mat image2 = cv::imread("../images/HQ.jpg");

    // Checking if images are loaded properly
    if (image1.empty() || image2.empty()) {
        std::cerr << "Error: Could not open or find the images!" << std::endl;
        return -1;
    }

    // Creating an instance of the ImageQuality class
    ImageQuality iq;

    // Applying Daly's Visual Difference Predictor (VDP) method
    cv::Mat differenceMap = iq.applyVDP(image1, image2);

    // Generating a heatmap from the difference map
    cv::Mat heatmap = iq.generateHeatmap(differenceMap, 0.1);

    // Showing the images and heatmap
    cv::imshow("Low Quality Image", image1);
    cv::imshow("High Quality Image", image2);
    cv::imshow("Difference Heatmap", heatmap);

    // Calculating some metrics
    double percentageDiff = iq.calculatePercentageDifference(differenceMap, 50.0);
    double meanDiff = iq.calculateMeanVisualDifference(differenceMap);
    //double maxDiff = iq.calculateMaximumVisualDifference(differenceMap);
    double ssim = iq.calculateSSIM(image1, image2);
    double psnr = iq.calculatePSNR(image1, image2);

    // Metrics output
    std::cout << "Percentage Difference: " << percentageDiff << "%" << std::endl;
    std::cout << "Mean Visual Difference: " << meanDiff << std::endl;
    //std::cout << "Maximum Visual Difference: " << maxDiff << std::endl;
    std::cout << "SSIM: " << ssim << std::endl;
    std::cout << "PSNR: " << psnr << " dB" << std::endl;

    // Waiting until a key is pressed to exit
    cv::waitKey(0);

    return 0;
}