//////////////////////////////////////////////////////////////
//                                                          //
//                     ROI, repeat 함수                     //
//                                                          //
//////////////////////////////////////////////////////////////


// void repeat(InputArray src, int ny, int nx, OutputArray dst);  
// Mat repeat(Mat& src, int ny, int nx); 
//
//      입력 src를 수평으로 nx번, 수직으로 ny번 복사하여 출력 dst 생성



#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Rect rtROI(0, 0, 256, 256);  // 관심영역 (0,0,256,256)을 사각형 rtROI에 초기화
	Mat roi = srcImage(rtROI);   // srcImage에서 관심영역인 rtROI 부분만을 Mat 행렬 roi에 저장
	rectangle(srcImage, rtROI, Scalar::all(0));  // 관심영역만을 사각형으로 표시
	imshow("srcImage", srcImage);

	Mat dstImage = repeat(roi, 2, 2); // 관심영역 roi 행렬을 수평으로 2번, 수직으로 2번 반복 복사하여 출력 dstImage에 저장
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}
