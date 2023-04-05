#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:/my_images/Fig0310(b)(washed_out_pollen_image).tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Low-contrast image
    Mat low_contrast = image * 0.5;

    // Histogram stretching
    Mat stretched;
    double minVal, maxVal;
    minMaxLoc(image, &minVal, &maxVal);
    image.convertTo(stretched, CV_8U, 255.0 / (maxVal - minVal), -255.0 * minVal / (maxVal - minVal));

    // Thresholding
    Mat thresholded;
    double thresh = threshold(image, thresholded, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // Display the results
    namedWindow("Original Image", WINDOW_NORMAL);
    namedWindow("Low-Contrast Image", WINDOW_NORMAL);
    namedWindow("Stretched Image", WINDOW_NORMAL);
    namedWindow("Thresholded Image", WINDOW_NORMAL);

    imshow("Original Image", image);
    imshow("Low-Contrast Image", low_contrast);
    imshow("Stretched Image", stretched);
    imshow("Thresholded Image", thresholded);

    waitKey(0);
    return 0;
}