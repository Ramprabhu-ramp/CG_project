#include "ImageQuality.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/quality.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>

ImageQuality::ImageQuality() {

}

cv::Mat ImageQuality::applyVDP(const cv::Mat& image1, const cv::Mat& image2) {
    // Preprocessing the images to ensure they are in the right format
    cv::Mat preprocessedImage1 = preprocessImage(image1);
    cv::Mat preprocessedImage2 = preprocessImage(image2);

    // Computing the difference map
    cv::Mat differenceMap = computeDifferenceMap(preprocessedImage1, preprocessedImage2);

    // Applying the contrast sensitivity function (a part of Daly's method)
    cv::Mat cfsImage1 = applyContrastSensitivityFunction(preprocessedImage1);
    cv::Mat cfsImage2 = applyContrastSensitivityFunction(preprocessedImage2);

    // Applying masking function on frequency channels (part of VDP)
    std::vector<cv::Mat> freqChannels1 = splitFrequencyChannels(cfsImage1);
    std::vector<cv::Mat> freqChannels2 = splitFrequencyChannels(cfsImage2);
    cv::Mat maskedImage1 = applyMaskingFunction(freqChannels1[0]);
    cv::Mat maskedImage2 = applyMaskingFunction(freqChannels2[0]);

    // Returning the final difference map after applying VDP methods (just a basic approach here)
    return computeDifferenceMap(maskedImage1, maskedImage2);
}

double ImageQuality::calculatePercentageDifference(const cv::Mat& differenceMap, double threshold) {
    // Counting pixels that exceed the threshold in the difference map
    int totalPixels = differenceMap.total();
    int countAboveThreshold = cv::countNonZero(differenceMap > threshold);
    return 100 - ((countAboveThreshold / double(totalPixels)) * 100);
}

double ImageQuality::calculateMeanVisualDifference(const cv::Mat& differenceMap) {
    double sum = cv::sum(differenceMap)[0]; // Sum of pixel differences
    return ((sum / differenceMap.total())/1000);
}

double ImageQuality::calculateMaximumVisualDifference(const cv::Mat& differenceMap) {
    double minVal, maxVal;
    cv::minMaxLoc(differenceMap, &minVal, &maxVal);
    return maxVal;
}

double ImageQuality::calculateSSIM(const cv::Mat& image1, const cv::Mat& image2) {
    cv::Mat ssimMap;
    cv::quality::QualitySSIM::compute(image1, image2, ssimMap);
    return cv::mean(ssimMap)[0]; // Return average SSIM value
}

cv::Mat ImageQuality::generateHeatmap(const cv::Mat& differenceMap, double threshold) {
    // Normalizing the difference map for better visualization
    cv::Mat normalizedMap;
    cv::normalize(differenceMap, normalizedMap, 0, 255, cv::NORM_MINMAX);
    normalizedMap.convertTo(normalizedMap, CV_8U);

    // Inverting the normalized map to reverse the heatmap coverage
    cv::Mat invertedMap = 255 - normalizedMap; // Invert pixel intensities

    // Using the inverted map directly without applying any color map
    return invertedMap;
}


cv::Mat ImageQuality::preprocessImage(const cv::Mat& image) {
    cv::Mat processedImage = image.clone();

    // Printing the original image size and channels for debugging
    std::cout << "Original Image size: " << image.size() << ", Channels: " << image.channels() << std::endl;

    // Resizing if the images are not the same size (You can choose to resize to image1's size)
    if (image.size() != processedImage.size()) {
        std::cout << "Resizing Image..." << std::endl;
        cv::resize(processedImage, processedImage, cv::Size(256, 256));  // Resize to 256x256 (or another size)
    }

    // Converting to grayscale if the image has 3 channels (color)
    if (processedImage.channels() == 3) {
        cv::cvtColor(processedImage, processedImage, cv::COLOR_BGR2GRAY);  // Convert to grayscale if needed
    }

    // Printing the processed image size and channels for debugging
    std::cout << "Processed Image size: " << processedImage.size() << ", Channels: " << processedImage.channels() << std::endl;

    return processedImage;
}

cv::Mat ImageQuality::computeDifferenceMap(const cv::Mat& image1, const cv::Mat& image2) {

    // Resizing image1 to match image2's size
    if (image1.size() != image2.size()) {
        cv::resize(image1, image1, image2.size());
    }
    // Computing the absolute difference between two images
    cv::Mat differenceMap;
    cv::absdiff(image1, image2, differenceMap);
    return differenceMap;
}

cv::Mat ImageQuality::applyContrastSensitivityFunction(const cv::Mat& image) {
    // Placeholder for the actual contrast sensitivity function application
    // In Daly's VDP, this involves frequency domain processing
    cv::Mat cfsImage = image.clone();  // Apply some contrast enhancement (if required)
    return cfsImage;
}

std::vector<cv::Mat> ImageQuality::splitFrequencyChannels(const cv::Mat& image) {
    // Using Fourier Transform or other techniques to split the image into frequency channels
    cv::Mat imageFloat;
    image.convertTo(imageFloat, CV_32F);  // Converting to 32-bit floating point

    // Performing the DFT
    cv::Mat dftImage;
    cv::dft(imageFloat, dftImage, cv::DFT_COMPLEX_OUTPUT);

    // Returning the real and imaginary components
    std::vector<cv::Mat> channels;
    cv::split(dftImage, channels);  // Spliting into real and imaginary parts
    return channels;
}

cv::Mat ImageQuality::applyMaskingFunction(const cv::Mat& frequencyChannel) {
    // Applying a simple mask on the frequency channel
    cv::Mat maskedChannel = frequencyChannel.clone();
    // Implementing masking logic here, for now just returning the unmodified channel
    return maskedChannel;
}
//PSNR calculation
double ImageQuality::calculatePSNR(const cv::Mat& img1, const cv::Mat& img2) {
    if (img1.empty() || img2.empty()) {
        std::cerr << "Error: One or both images are empty." << std::endl;
        return -1.0;
    }

    if (img1.size() != img2.size() || img1.type() != img2.type()) {
        std::cerr << "Error: Images must have the same size and type." << std::endl;
        return -1.0;
    }

    // Computing Mean Squared Error (MSE)
    cv::Mat diff;
    cv::absdiff(img1, img2, diff); // Computing absolute difference
    diff.convertTo(diff, CV_32F); // Converting to float to avoid precision loss

    cv::Mat squaredDiff;
    cv::multiply(diff, diff, squaredDiff); // Squaring the differences

    double mse = cv::sum(squaredDiff)[0] / (double)(img1.total()); // Computing Mean

    if (mse == 0) {
        return 100.0; // If images are identical, PSNR is maximum
    }

    double psnr = 10.0 * log10((255 * 255) / mse);
    return psnr;
}