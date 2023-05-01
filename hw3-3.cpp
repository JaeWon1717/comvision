#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//salt pepper noise이미지 
void addSaltAndPepperNoise(Mat& image, float noise_ratio) {
    int rows = image.rows;
    int cols = image.cols;

    int noise_pixels = noise_ratio * rows * cols;

    for (int i = 0; i < noise_pixels; i++) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (rand() % 2 == 0) {
            image.at<uchar>(r, c) = 0; // Pepper noise
        }
        else {
            image.at<uchar>(r, c) = 255; // Salt noise
        }
    }
}

// 가우시안 노이즈 이미지 
void addGaussianNoise(Mat& image, double mean, double stddev) {
    Mat noise = Mat::zeros(image.size(), CV_8UC1);
    randn(noise, mean, stddev);

    Mat noisy_image;
    image.convertTo(noisy_image, CV_32FC1);
    noisy_image += noise;
    noisy_image.convertTo(image, CV_8UC1);
}

int main() {
    // Read input image
    Mat image = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);

    // Add Salt-and-Pepper noise to the image
    addSaltAndPepperNoise(image, 0.1f);
  
    // Display the noisy image
    imshow("saltpepper_noise", image);
   
    // Apply various filters to remove noise
    Mat filtered_image;

    // Box filter
    blur(image, filtered_image, Size(3, 3));
    imshow("Box Filter", filtered_image);

    // Low-pass filter 저주파필터
    Mat kernel = Mat::ones(Size(3, 3), CV_32F) / (float)(3 * 3);
    filter2D(image, filtered_image, -1, kernel);
    imshow("Low-pass Filter", filtered_image);

    // High-pass filter 고주파필터 
    kernel = Mat::zeros(Size(3, 3), CV_32F);
    kernel.at<float>(1, 1) = 2.0;
    kernel -= Mat::ones(Size(3, 3), CV_32F) / (float)(3 * 3);
    filter2D(image, filtered_image, -1, kernel);
    imshow("High-pass Filter", filtered_image);

    // Mean filter
    Mat median_kernel = Mat::ones(Size(3, 3), CV_32F) / (float)(3 * 3);
    medianBlur(image, filtered_image, 3);
    imshow("Mean Filter", filtered_image);

    // Gaussian smoothing filter
    GaussianBlur(image, filtered_image, Size(3, 3), 1);
    imshow("Gaussian Filter", filtered_image);

    // Median filter
    medianBlur(image, filtered_image, 3);
    imshow("Median Filter", filtered_image);

    // Wait for key press
    waitKey(0);

    return 0;
}