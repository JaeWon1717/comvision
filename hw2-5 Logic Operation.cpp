/*******************************************************/
/*            HW#2-5. Logic Operation    */
/*  작성자 : 박재원          날짜 : 2023년 4월 17일 */
/*                                                                           */
/* 문제 정의 : 두 개의 그레이 스케일을 불러온후 , 비트연산자를 
사용하여 두 이미지를 AND연산하여 결과값을 내는 실험.
특정부분을 강조할때나 노이즈제거하는 작업에 유용함.* /
/*                - - - - - - -                                            */
/*******************************************************/
#include <opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	Mat image1 = imread("C:/my_images/Fig0230(a)(dental_xray).tif", IMREAD_GRAYSCALE);
	Mat image2 = imread("C:/my_images/Fig0230(b)(dental_xray_mask).tif", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.5, beta = 10;


	Mat AND;//AND 
	bitwise_and(image1, image2, AND);

	// 이미지 크기를 0.5배로 조절
	resize(AND, AND, Size(), 0.5, 0.5, INTER_LINEAR);

	imshow("AND", AND);

	waitKey(0);
}