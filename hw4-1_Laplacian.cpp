/////////////////////////////////////////////////////////////////
// //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                 영상에서 가우시안 필터링, 라플라시안, 0교차점 검출	       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////



// void Laplacian(OutputArray src, OutputArray dst, int ddepth, int ksize=1,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// src에 대하여 라플라이산을 적용한 후에 scale로 스케일하고, delta 값을 더해 ddepth 깊이의 dst에 저장
// 
// ksize	: 라플라시안의 크기
// ksize = 1 또는 ksize = 3일때 3 x 3 라플라시안 필터임.
//
// 라플라시안 필터링 후에 에지는 0-교차하는 위치임.

// LoG 필터
// 윈도우 커널의 크기 n = 2 x 3 x sigma + 1 또는  sigma = 0.3(n/2 - 1)+0.8로 계산


#include <opencv.hpp>
using namespace cv;
using namespace std;

void ZeroCrossing(Mat& src, Mat& dst, int threshold);  // 0 교차점 체크


int main()
{
	Mat srcImage = imread("C:/my_images/HW4-1.jpg", IMREAD_GRAYSCALE);
	//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize = 15;
	Mat blurImage;
	GaussianBlur(srcImage, blurImage, Size(ksize, ksize), 0.0);  // srcImage를 15 x 15의 가우시안 필터로 스무딩

	Mat lapImage;
	Laplacian(blurImage, lapImage, CV_32F, ksize);  // 가우시안 스무딩 된 영상에 대해 라플라시안 필터링 수행

	Mat dstImage;
	ZeroCrossing(lapImage, dstImage, 10);  // 라플라시안 결과에 대해 영교차점 체크

	imshow("dstImage", dstImage);

	waitKey();

	return 0;
}

// 라플라시안 필터링된 입력 영상 src에서 가로방향과 세로 방향의 이웃을 조사하여 부호가 변경되는 0-교차 위치를 검출하고
// 변경되는 차이를 절대값으로 저장한 다음, threshold 함수로 임계값 이상의 큰 값으로 부호가 변경되는 위치를 에지로 dst 영상에 반영

void ZeroCrossing(Mat& src, Mat& dst, int th)
{
	int x, y;
	double a, b;

	Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));  // 가로 방향의 0-교차 검출
	// src와 동일한 크기의, CV_32F의 자료형에 0으로 초기화된 행렬 생성

	Mat_<float> _src(src);	// src를 복사하여 _src 생성

	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{

			// (+.-), (-,+), (+,0,-), (-,0,+) 인 경우를 검출하여 교차하는 정도를 zeroCrossH에 저장

			a = _src(x, y);     		// 가로 방향의 인접한 두 픽셀 선택
			b = _src(x, y + 1);

			if (a == 0)   			// 해당 픽셀의 값이 0 이면 그 왼쪽의 픽셀을 다시 선택.
				// (+,0,-) 또는 (-,0,+)인 경우를 검출하기 위함
				a = _src(x, y - 1);

			if (a * b < 0)			// 가로 방향의 인접한 두 픽셀의 부호가 다르다면
				// 두 픽셀의 절대값의 합을 저장
				zeroCrossH.at<float>(x, y) = fabs(a) + fabs(b);

			else				// 가로 방향의 인접한 두 픽셀의 부호가 같으면 0 저장
				zeroCrossH.at<float>(x, y) = 0;

		}
	}

	Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));  // 세로 방향의 0-교차 검출
	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{
			a = _src(x, y);
			b = _src(x + 1, y);

			if (a == 0)
				a = _src(x - 1, y);
			if (a * b < 0)
				zeroCrossV.at<float>(x, y) = fabs(a) + fabs(b);
			else
				zeroCrossV.at<float>(x, y) = 0;
		}
	}

	Mat zeroCross(src.size(), CV_32F, Scalar::all(0));

	add(zeroCrossH, zeroCrossV, zeroCross);  // zeroCross = zeroCrossH + zeroCrossV

	threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}