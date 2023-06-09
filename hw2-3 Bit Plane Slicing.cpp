/*******************************************************/
/*             HW#2-3. Bit Plane Slicing      */
/*  작성자 : 박재원          날짜 : 2023년 4월 17일 */
/*                                                                           */
/* 문제 정의 :영상에서 각 비트의 값들이 어떤영향을 미치는지 알아보기 위해 
각각의 비트들로만 이루어진 영상을 만들어 보고 특정 bit-plane을 이용하여 
영상을 다시 만들어보는 실험 .* /
/*                - - - - - - -                                            */
/*******************************************************/
#include <opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

char print(int i) {
    char temp = (char)(i + '0');
    return temp;
}

int main()
{
    Mat m1 = imread("C:/my_images/Fig0314(a)(100-dollars).tif", IMREAD_GRAYSCALE);
    resize(m1, m1, Size(), 0.5, 0.5); // 이미지 크기 1/4로 축소
    imshow("Original", m1);
    int cols, rows, x, y;
    cols = m1.cols;
    rows = m1.rows;
    printf("%d %d \n", m1.rows, m1.cols);
    Mat out[9], dst(rows, cols, CV_8UC1, Scalar(0));

    // 비트 평면 분리
    for (int i = 0; i <= 8; i++) {
        out[i] = Mat(rows, cols, CV_8UC1, Scalar(0));
    }
    for (int i = 0; i <= 8; i++) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                out[i].at<uchar>(x, y) = (m1.at<uchar>(x, y) & uchar(pow(2, i))) ? uchar(255) : uchar(0);
            }
        }
        string s = "dstImage";
        s += print(i);
        namedWindow(s, WINDOW_NORMAL);
        resizeWindow(s, cols / 2, rows / 2); // 윈도우 크기 1/4로 축소
        imshow(s, out[i]);
    }

    // 비트 평면 다시 합성
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            uchar sum = 0;
            for (int i = 0; i <= 8; i++) {
                if (out[i].at<uchar>(x, y) == 255) {
                    sum |= uchar(pow(2, i));
                }
            }
            dst.at<uchar>(x, y) = sum;
        }
    }
    imshow("Reconstructed", dst);
    waitKey(0);

    return 0;
}