#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:/my_images/Fig0310(b)(washed_out_pollen_image).tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "이미지를 찾을수 없습니다" << endl;
        return -1;
    }

    // Low-contrast image
    Mat low_contrast = image * 0.75;

    // Histogram stretching
    Mat stretched;
    double minVal, maxVal;//입력 이미지의 최소값과 최대값설정
    minMaxLoc(image, &minVal, &maxVal);////입력 이미지의 최소값과 최대값을 구해서 
    image.convertTo(stretched, CV_8U, 255.0 / (maxVal - minVal), -255.0 * minVal / (maxVal - minVal));
    //55.0 / (maxVal - minVal)을 스케일링 상수로 이용하여 입력 이미지의 동적 범위를 [0, 255] 범위로 변경하고
    // -255.0 * minVal / (maxVal - minVal)를 이동 상수로 이용

    // Thresholding
    Mat thresholded;//otsu알고리즘을 이용하여 이진화 수행 
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