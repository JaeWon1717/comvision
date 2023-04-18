/*******************************************************/
/*             HW#2-2. Piecewise-Linear Transform      */
/*  �ۼ��� : �����          ��¥ : 2023�� 4�� 17�� */
/*                                                                           */
/* ���� ���� : �����̹����� low-contrast,stretching,threshodingó������� �̿��Ͽ�
�� �������� ��� ��µǴ��� ���� ����.* /
/*                - - - - - - -                                            */
/*******************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("C:/my_images/Fig0310(b)(washed_out_pollen_image).tif", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "�̹����� ã���� �����ϴ�" << endl;
        return -1;
    }

    // Low-contrast image
    Mat low_contrast = image * 0.75;

    // Histogram stretching
    Mat stretched;
    double minVal, maxVal;//�Է� �̹����� �ּҰ��� �ִ밪����
    minMaxLoc(image, &minVal, &maxVal);////�Է� �̹����� �ּҰ��� �ִ밪�� ���ؼ� 
    image.convertTo(stretched, CV_8U, 255.0 / (maxVal - minVal), -255.0 * minVal / (maxVal - minVal));
    //55.0 / (maxVal - minVal)�� �����ϸ� ����� �̿��Ͽ� �Է� �̹����� ���� ������ [0, 255] ������ �����ϰ�
    // -255.0 * minVal / (maxVal - minVal)�� �̵� ����� �̿�

    // Thresholding
    Mat thresholded;//otsu�˰����� �̿��Ͽ� ����ȭ ���� 
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