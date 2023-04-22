//////////////////////////////////////////////////////////////
//                                                          //
//                      트랙바 처리                         //
//                                                          //
//////////////////////////////////////////////////////////////

// createTrackbar() : winname의 윈도우에 trackbarname의 트랙바 생성.
//
// void createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0,  
void* userdata = 0);
// value : 트랙바가 생성될때의 슬라이더의 위치
// count : 트랙바 슬라이더의 최대 위치, 최소값은 항상 0.
// onChange : 트랙배 슬라이더가 변경될때마다 자동 호출되는 핸들러 함수
//
// 
// onChange() : 트랙바 슬라이더가 변경될때마다 자동 호출되는 함수.
//
// void onChange(int pos,void* userdata=0);
// pos : 트랙바의 슬라이더 위치
//
//
// getTrackbarPos() : 트랙바의 슬라이더 위치 반환.
//
// int getTrackbarPos((const string& trackbarname, const string& winname);
// winname의 윈도우의 trackbarname 트랙바의 슬라이더 위치 반환
//
//
// setTrackbarPos() : 트랙바의 슬라이더 위치 변경.
//
// int setTrackbarPos((const string& trackbarname, const string& winname, int pos);
// winname의 윈도우의 trackbarname 트랙바의 슬라이더 위치를 pos로 변경.



#include <opencv.hpp>

using namespace cv;
using namespace std;

void onChange(int  pos, void* param);
// 트랙바 슬라이더가 변경될때마다 자동 호출
// pos : 트략바의 슬라이더 위치
// param : 사용자 정의인수

int main()
{
	Mat image[2];
	image[0] = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (image[0].empty())
		return -1;
	image[1].create(image[0].size(), CV_8U);  // image[1]에 입력영상과 같은 크기, 8비트 1채널로 생성함.

	//	namedWindow("image"); 
	imshow("image", image[0]);  // "image" 윈도우에 image[0] 영상출력

	int pos = 128;
	onChange(pos, (void*)image);
	// 프로그램을 실행하자 마자, onChange 트랙바 핸들러 함수를 호출하기 위하여 트랙바 핸들러 함수 onChange호출

	createTrackbar("threshold", "image", &pos, 255, onChange, (void*)image);
	// "threshold" 트랙바를 "image" 윈도우에 생성
	// 트랙바가 생성될 때의 슬라이더 위치 : pos, 트랙바 슬라이더의 최대위치값 : 255, 최소값은 항상 0
	// 트랙바 핸들러 함수는 onChange 함수로 설정(트랙바 슬라이더가 변경될 때마다 자동 호출되는 핸들러 함수)
	// 사용자 데이터는 (void*)image를 전달.

	waitKey();

	return 0;
}


// trackbar callback to threshold the image gray value
void onChange(int  pos, void* param)
{
	Mat* pMat = (Mat*)param;   // 사용자 데이터인수 param을 (Mat *)param으로 형변환하여 행렬 포인터 pMat에 저장
	Mat srcImage = Mat(pMat[0]);
	Mat dstImage = Mat(pMat[1]);

	// Direct Thresholding 
	int x, y, s, r;
	int nThreshold = pos;
	for (y = 0; y < srcImage.rows; y++)
	{
		for (x = 0; x < srcImage.cols; x++)
		{
			r = srcImage.at<uchar>(y, x);   // srcImage 영상의 (y,x)의 화소의 값을 r에 저장
			if (r > nThreshold)
				s = 255;
			else
				s = 0;
			dstImage.at<uchar>(y, x) = s;
		}
		imshow("image", dstImage);
	}
}
