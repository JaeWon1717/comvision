#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void MarrHildrethEdgeDetection(Mat& src, Mat& dst, double sigma, int kernelSize, double threshold);

int main()
{
    Mat srcImage = imread("C:/my_images/HW4-1.jpg", IMREAD_GRAYSCALE);
   
    Mat dstImage;
    MarrHildrethEdgeDetection(srcImage, dstImage, 1.4, 9, 10);

    imshow("¿øº»", srcImage);
    imshow("Marr-Hildreth Edges", dstImage);
    waitKey(0);

    return 0;
}

void MarrHildrethEdgeDetection(Mat& src, Mat& dst, double sigma, int kernelSize, double threshold)
{
    Mat blurredImage;
    GaussianBlur(src, blurredImage, Size(kernelSize, kernelSize), sigma, sigma, BORDER_DEFAULT);

    Mat_<float> laplacian;
    Laplacian(blurredImage, laplacian, CV_32F, kernelSize, 1, 0, BORDER_DEFAULT);

    dst = Mat::zeros(src.size(), CV_8UC1);

    int y = 1;
    while (y < laplacian.rows - 1)
    {
        int x = 1;
        while (x < laplacian.cols - 1)
        {
            float center = laplacian(y, x);
            float top = laplacian(y - 1, x);
            float bottom = laplacian(y + 1, x);
            float left = laplacian(y, x - 1);
            float right = laplacian(y, x + 1);

            if ((center > 0 && top < 0) || (center > 0 && bottom < 0) ||
                (center > 0 && left < 0) || (center > 0 && right < 0) ||
                (center < 0 && top > 0) || (center < 0 && bottom > 0) ||
                (center < 0 && left > 0) || (center < 0 && right > 0))
            {
                if (abs(center) >= threshold)
                {
                    dst.at<uchar>(y, x) = 255;
                }
            }

            x++;
        }

        y++;
    }
}