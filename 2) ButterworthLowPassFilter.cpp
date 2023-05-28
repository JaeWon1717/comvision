/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                       버터워스 저주파 통과 필터링                          //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
// 저주파 통과 필터 F(u,v) : 저주파 영역은 통과시키고, 고주파 영역은 0으로 만들어
//			     통과시키지 않는 필터
//
//
//  1) 이상적인(Ideal) 저주파 통과 필터
//
// 주파수 영역의 원점 F(M/2, N/2)로부터의 거리 D(u,v)가 절단(cut-off) 주파수 D0미만이면 통과시키고,
// 그렇지 않으면 통과시키지 않도록 함.
//
// D(u,v) <= D0이면 : H(u,v) = 1이 되어 H(u,v)F(u,v) = 1 x F(u,v) = F(u,v)가 되어, F(u,v)가 통과됨
// D(u,v) > D0이면  : H(u,v) = 0이 되어 H(u,v)F(u,v) = 0 x F(u,v) = 0이 되어 F(u,v)가 통과되지 못함.
//
//
//  2) 버터워스(Butterworth) 저주파 통과 필터
//
// 절단 주파스 D0와 정수 n을 사용하여 필터 H(u,v)를 완만하게 0에서 1사이의 실수 값을 갖도록 함.
// 영상의 중심에서는 H(u,v) = 1을 갖고, 멀어질수록 0에 가까운 값을 가짐.
//
//
//  3) 가우시안(Gaussian) 저주파 통과 필터
// 
// D0를 표준편가로 갖는 가우시안 함수에 의해 H(u,v)가 완만하게 0에서 1사이의 실수값을 가짐.
// 영상의 중심에서는 H(u,v) = 1을 갖고, 멀어질수록 0에 가까운 값을 가짐.
//
/////////////////////////////////////////////////////////////////////////////////
// 울림 현상을 없애기 위해 필터의 전달함수 D(u,v)를 연속적으로 완만하게 감소시키는 필터를 사용
// 매개 변수 n 은 경계선을 중심으로 D(u, v)의 값이 완만하게 변화하게 할 것인지 급격하게 변화하게 할 것인지를 조절




#include <opencv.hpp>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);
void ButterworthLowpassFilteringH(Mat F, double D0, int n);

int main()
{
	Mat srcImage = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);
	ChangeSignOddPositionInXY(fImage); // centering

	Mat dftA;
	dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

	double D0 = 30.0; //30, 80, 200   cut-off(절단) 주파수
	int n = 2;
	ButterworthLowpassFilteringH(dftA, D0, n);  // D0와 n에 의해 버터워스 저주파 통과 필터링 수행

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);	// 역변환
	ChangeSignOddPositionInXY(dftB);  // 다시 원래대로 중심 이동

	Mat dstImage;
	dftB.convertTo(dstImage, CV_8U);
	imshow("dstImage", dstImage);

	waitKey();
	return 0;
}

void ButterworthLowpassFilteringH(Mat F, double D0, int n)
{
	int u, v;
	double D;   // 원점에서의 거리
	double H;
	double centerU = F.rows / 2;   // 중심
	double centerV = F.cols / 2;
	Vec2f cmplxValue;

	// filter H
	for (u = 0; u < F.rows; u++)
	{
		for (v = 0; v < F.cols; v++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));  // 원점에서의 거리 계산
			H = 1.0 / (1.0 + pow(D / D0, 2 * n));   // 버터워스 필터 H 구현

			// 푸리에 변환에 이한 주파수 공간의 값과 필터 H를 곱하여 다시 저장
			cmplxValue = F.at<Vec2f>(u, v);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(u, v) = cmplxValue;
		}
	}
}

void ChangeSignOddPositionInXY(Mat& m)
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