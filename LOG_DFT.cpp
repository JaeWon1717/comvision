/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                   가우시안 함수의 푸리에 변환을 이용한 LoG                  //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

// ## 가우시안 함수 g(x,y)의 푸리에 변환 G(u,v) 역시 가우시안 함수임.
// ## 가우시안 함수의 푸리에 변환인  DFT(g(x,y)) = G(u,v)를 이용한 필터링 가능
//
// 1) 가우시안 함수의 푸리에 변환 G(u,v)를 이용한 스무딩
// 2) 가우시안 함수의 푸리에 변환 G(u,v)를 이용한 미분(gradient)
// 3) 가우시안 함수의 푸리에 변환 G(u,v)를 이용한 LoG 필터링



#include <opencv.hpp>
using namespace cv;
using namespace std;

void LOG_DFT(Mat& src, Mat& dst, double sigma);
void ZeroCrossing(Mat& src, Mat& dst, int th);
void ChangeSignOddPositionInXY(Mat& m);

int main()
{
	Mat srcImage = imread("rect.jpg", IMREAD_GRAYSCALE);
	//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Mat src32f;
	srcImage.convertTo(src32f, CV_32F);

	double sigma = 0.01; // 0.05, 0.01
	Mat logDst;
	LOG_DFT(src32f, logDst, sigma);   // LoG 필터링

	Mat zeroDest;
	ZeroCrossing(logDst, zeroDest, 1);   // 영교차점 체크, thresold 값 : 1

	imshow("zeroDest", zeroDest);

	waitKey();

	return 0;
}

void LOG_DFT(Mat& src, Mat& dst, double sigma)
{

	// src 영상의 dft를 위한 최적의 크기 계산
	int nW = getOptimalDFTSize(src.cols);
	int nH = getOptimalDFTSize(src.rows);

	Mat A;
	copyMakeBorder(src, A, 0, nH - (src.rows), 0, nW - (src.cols), BORDER_CONSTANT, 0);  // src를 행렬 A로 0 패딩하여 확장

	ChangeSignOddPositionInXY(A); // centering  : 중심 이동

	Mat dftA;
	dft(A, dftA, DFT_COMPLEX_OUTPUT);  // 0-패딩하여 확장된 행렬 A를 DFT 변환

	int u, v;
	Vec2f cValue;
	const double phi4 = -4 * CV_PI * CV_PI;  // CV_PI : 파이

	double centerU = dftA.rows / 2;
	double centerV = dftA.cols / 2;

	double D, G;
	double d = -2 * (CV_PI * CV_PI) * sigma * sigma;   // CV_PI : 파이
	double U, V;

	for (u = 0; u < dftA.rows; u++)
	{
		for (v = 0; v < dftA.cols; v++)
		{
			U = (u - centerU);
			V = (v - centerV);

			D = U * U + V * V;

			G = phi4 * D * exp(d * D);

			// dftA(u,v)와 LoG 함수의 푸리에 변환 G(u,v)의 주파수 영역에서의 곱셈을 하여 dftA(u,v)에 저장
			cValue = dftA.at<Vec2f>(u, v);
			cValue[0] *= G;
			cValue[1] *= G;
			dftA.at<Vec2f>(v, u) = cValue;
		}

		dst.create(src.size(), CV_32F);  // dst에 src와 같은 크기의 행렬을 CV_32F로 생성

		idft(dftA, dst, DFT_SCALE | DFT_REAL_OUTPUT, dftA.rows);   // dftA를 역변환하여 dst에 저장

		ChangeSignOddPositionInXY(dst); // centering 중심을 원래대로 복원
	}

	void ZeroCrossing(Mat & src, Mat & dst, int th)
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

		dst.create(src.size(), CV_8U);  // Mat::create() 메소드 : 이전에 생성된 Mat 클래스 행렬과 크기 및 자료형이 동일하면 새로 데이터를 위한 메모리를 할당하지 않음. 
		threshold(zeroCross, dst, th, 255, THRESH_BINARY);
	}

	void ChangeSignOddPositionInXY(Mat & m)
	{
		int x, y;
		float fValue;

		for (x = 0; x < m.rows; x++)
		{
			for (y = 0; y < m.cols; y++)
			{
				fValue = m.at<float>(x, y);
				//			if((x+y)%2==1) // odd number
				if ((x + y) % 2 == 1 && fValue != 0)
					m.at<float>(x, y) = -fValue;
			}
		}
	}