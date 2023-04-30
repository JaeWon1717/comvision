#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat srcImage = imread("C:/my_images/Fig0939(a)(headCT-Vandy).tif", IMREAD_GRAYSCALE);
    if (srcImage.empty())
        return -1;
    imshow("srcImage", srcImage);

    Size size(3, 3);
    Mat rectKernel = getStructuringElement(MORPH_RECT, size);
    cout << "rectKernel=" << rectKernel << endl;

    int iterations = 3;
    Point anchor(1, 1);
    Mat erodeImage;

    Mat ellipseKernel = getStructuringElement(MORPH_ELLIPSE, size);
    cout << "ellipseKernel=" << ellipseKernel << endl;

    Mat crossKernel = getStructuringElement(MORPH_CROSS, size);
    cout << "crossKernel=" << crossKernel << endl;

    Mat erodeImage3;
    erode(srcImage, erodeImage3, crossKernel, anchor, iterations);
    imshow("erodeImage3 C", erodeImage3);

    Mat dilateImage3;
    dilate(srcImage, dilateImage3, crossKernel, anchor, iterations);
    imshow("dilateImage3 B", dilateImage3);

    Mat gradientImage;
    subtract(dilateImage3, erodeImage3, gradientImage);
    imshow("gradientImage", gradientImage);

    Mat sobelImage;
    Sobel(srcImage, sobelImage, CV_16S, 1, 1);
    convertScaleAbs(sobelImage, sobelImage);
    imshow("sobelImage", sobelImage);

    Mat laplacianImage;
    Laplacian(srcImage, laplacianImage, CV_16S);
    convertScaleAbs(laplacianImage, laplacianImage);
    imshow("laplacianImage", laplacianImage);
<<<<<<< HEAD
    /*
     if ((center > 0 && top < 0) || (center > 0 && bottom < 0) ||
                (center > 0 && left < 0) || (center > 0 && right < 0) ||
                (center < 0 && top > 0) || (center < 0 && bottom > 0) ||
                (center < 0 && left > 0) || (center < 0 && right > 0))*/ //log연산 필요시 추가 
=======

>>>>>>> 18b0b3d4c1ae335d2756eefeba6a59816c007e2b
    waitKey();
    return 0;
}