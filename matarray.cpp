//////////////////////////////////////////////////////////////
//                                                          //
//                    기본 배열 함수                        //
//                                                          //
//////////////////////////////////////////////////////////////



// flip()  : 뒤집기       repeat() : 복사        transpose() : 행렬 전치
//
// void flip(InputArray src, OutputArray dst, int flipCode);  // 수평 수직으로 뒤집는 함수
//
//      src	: 입력
//	dst 	: 출력
//	flipcode =  0이면, 수평방향으로 뒤집음.
//	flipcode =  1(양수)이면, 수직방향으로 뒤집음.
//	flipcode = -1(음수)이면, 수평, 수직방향 모두 뒤집음.	
//
//	
// void repeat(InputArray src, int ny, int nx, OutputArray dst);  
// Mat repeat(Mat& src, int ny, int nx); 
//
//      입력 src를 수평으로 nx번, 수직으로 ny번 복사하여 출력 dst 생성




#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("flip_test.jpg", IMREAD_COLOR);
	CV_Assert(image.data);                  // 예외 처리

	Mat x_axis, y_axis, xy_axis, rep_img, trans_img;

	flip(image, x_axis, 0);                // x축 기준 상하 뒤집기
	flip(image, y_axis, 1);                // y축 기준 좌우 뒤집기
	flip(image, xy_axis, -1);

	repeat(image, 1, 2, rep_img);          // 가로 방향 2번 반복 복사
	transpose(image, trans_img);           // 행렬 전치 

	imshow("image", image);                // 행렬을 영상으로 표시 
	imshow("x_axis", x_axis);
	imshow("y_axis", y_axis);
	imshow("xy_axis", xy_axis);
	imshow("rep_img", rep_img);
	imshow("trans_img", trans_img);

	waitKey();
	return 0;
}