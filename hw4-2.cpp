#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat srcImage = imread("C:/my_images/HW4-2.jpg", IMREAD_GRAYSCALE);
    Mat dstImage45, dstImageNeg45;

    // �̹��� ũ�� ������ ����
    Size newSize(srcImage.cols / 2, srcImage.rows / 2);
    resize(srcImage, srcImage, newSize);

    // -45�� ������ �밢�� ���� ����
    Mat kernelNeg45 = (Mat_<char>(2, 2) << -1, 0, 0, 1);
    filter2D(srcImage, dstImageNeg45, CV_8U, kernelNeg45);

    // 45�� ������ �밢�� ���� ����
    Mat kernel45 = (Mat_<char>(2, 2) << 0, -1, 1, 0);
    filter2D(srcImage, dstImage45, CV_8U, kernel45);

    // ��� �̹����� ��� �����
    normalize(dstImageNeg45, dstImageNeg45, 0, 255, NORM_MINMAX);
    normalize(dstImage45, dstImage45, 0, 255, NORM_MINMAX);

    // ��� �̹��� ���
    imshow("Result (-45 degrees)", dstImageNeg45);
    imshow("Result (45 degrees)", dstImage45);
    waitKey(0);

    return 0;
}