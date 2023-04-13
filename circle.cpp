#include <opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	// 512 x 512 크기의 3채널 컬러 영상 dstImage를 Mat 행렬로 생성하고, 
	// Scalar(255, 255, 255)로 초기화


	rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));
	// dstImage 영상에  Point(100, 100), Point(400, 400)에 의해 정의되는 사각형을
	// Scalar(0, 0, 255) 색상으로 그림.

	line(dstImage, Point(250, 100), Point(250, 400) Scalar(0, 0, 255));
	line(dstImage, Point(100, 250), Point(400, 250), Scalar(0, 0, 255));
	// dstImage 영상에  사각형을 가로 세로 이등분하는 직선을 Scalar(0, 0, 255) 색상으로 그림.


	circle(dstImage, Point(250, 250), 150, Scalar(255, 0, 0));
	// dstImage 영상에  중심점 Point(250, 250), 반지름 150인 위에 그린 사각형에 내접한 원을 Scalar(255, 0, 0) 색상으로 그림.

	circle(dstImage, Point(250, 250), 50, Scalar(0, 255, 0), -1);
	// dstImage 영상에  중심점 Point(250, 250), 반지름 50인 원을 Scalar(0, 255, 0) 색상으로 채움

	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}
