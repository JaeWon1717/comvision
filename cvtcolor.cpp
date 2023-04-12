/////////////////////////////////////////////////////////////////
//                                                             //
//             cvtColor에 의한 컬러 모델 변환                  //
//                                                             //
/////////////////////////////////////////////////////////////////

// void cvtColor(const CvArr* src, const CvArr* dst, int code, int dstCn=0);
// 
// src		: 입력영상. CV_8U, CV_8S, CV_16U, CV_16S 또는 CV_32
// dst		: 출력영상. src와 같은 크기, 같은 깊이.채널의 수는 다를 수 있음.
// code		: src의 컬러인 src_color에서 출력 dst의 컬러 dst_color로의 변환 명시
// dstCn	: dst 영상의 채널 수. 0인 경우 src와 code에 의해 자동 계산

// RGB 영상의 값의 범위
// 	8비트 	: 0~255
//	16비트 	: 0~65535 
//	실수영상: 0~1사이의 값



#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg");
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("grayImage", grayImage);

	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	imshow("hsvImage", hsvImage);

	Mat yCrCbImage;
	cvtColor(srcImage, yCrCbImage, COLOR_BGR2YCrCb);
	imshow("yCrCbImage", yCrCbImage);

	Mat luvImage;
	cvtColor(srcImage, luvImage, COLOR_BGR2Luv);
	imshow("luvImage", luvImage);
	waitKey();

	return 0;
}
