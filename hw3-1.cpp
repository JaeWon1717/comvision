#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);
    imshow("srcImage", srcImage);

    int border = 3; // 7x7
    Size ksize(border * 2 + 1, border * 2 + 1);

    Mat dstImage0;
    boxFilter(srcImage, dstImage0, -1, ksize);  // 박스 필터, normalize=true이므로 평균필터와 같음.
    imshow("box", dstImage0);

    Mat dstImage7;
    int d = ksize.width;  // 7
    double sigmaColor = 10.0;
    double sigmaSpace = 10.0;
    bilateralFilter(srcImage, dstImage7, d, sigmaColor, sigmaSpace);
    imshow("가우시안", dstImage7);

    // Sharpening
    Mat dstImage1;
    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(srcImage, dstImage1, -1, kernel);
    imshow("Sharpening", dstImage1);

    // Vertical edges
    Mat dstImage2;
    Mat kernel2 = (Mat_<float>(3, 3) << 1, 0, -1, 1, 0, -1, 1, 0, -1);
    filter2D(srcImage, dstImage2, -1, kernel2);
    imshow("Vertical Edges", dstImage2);

    // Horizontal edges
    Mat dstImage3;
    Mat kernel3 = (Mat_<float>(3, 3) << 1,1,1, 0, 0, 0, -1,-1,-1);
    filter2D(srcImage, dstImage3, -1, kernel3);
    imshow("Horizontal Edges", dstImage3);

    // Motion effect
    Mat dstImage4;
    Mat kernel4 = (Mat_<float>(5, 5) << 0.304, 0.501, 0, 0, 0,
        0.501, 0.1771, 0.519, 0, 0,
        0,0.519, 0.1771, 0.519, 0,
        0, 0, 0.519, 0.1771, 0.501,
        0, 0, 0, 0.501, 0.304);
    filter2D(srcImage, dstImage4, -1, kernel4);
    imshow("Motion Effect", dstImage4);
    waitKey();
    return 0;
}