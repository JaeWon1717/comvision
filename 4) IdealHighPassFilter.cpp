/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                      이상적인 고주파 통과 필터링                            //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
// 고주파 통과 필터 F(u,v) : 고주파 영역은 통과시키고, 저주파 영역은 0으로 만들어
//			     통과시키지 않는 필터
//
// 
//
//  1) 이상적인(Ideal) 고주파 통과 필터
//
// 주파수 영역의 원점 F(M/2, N/2)로부터의 거리 D(u,v)가 절단(cut-off) 주파수 D0 이상이면 통과시키고,
// 그렇지 않으면 통과시키지 않도록 함.
//
//
//  2) 버터워스(Butterworth) 저주파 통과 필터
//
// 절단 주파스 D0와 정수 n을 사용하여 필터 H(u,v)를 완만하게 0에서 1사이의 실수 값을 갖도록 함.
// 영상의 중심에서 멀어질수록 D(u,v)가 커지면 H(u,v)=1에 가까운 값을 가짐.
// 주파수 영역의 원점인 중심에서는 D(u,v)이 되므로 0으로 나누는 것을 방지하기 해야 함.
// 이 예에서는 D(u,v)를 인위적으로 0.1로 정함.
//
//
//  3) 가우시안(Gaussian) 저주파 통과 필터
// 
// 1에서 가우시안 저주파 통과 필터를 뺄셈하여 계산
// 영상의 중심에서는 낮은 값을 갖고, 중심에서 멀어질수록 1에 가까운 값을 가짐.
//
/////////////////////////////////////////////////////////////////////////////////



#include <opencv.hpp>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);
void IdealHighpassFilteringH(Mat F, double D0);

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

	double D0 = 5.0; //30, 80, 200
	IdealHighpassFilteringH(dftA, D0);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(dftB);

	Mat dstImage;
	dftB.convertTo(dstImage, CV_8U);
	imshow("dstImage", dstImage);

	waitKey();
	return 0;
}


void IdealHighpassFilteringH(Mat F, double D0)
{
	int u, v;
	double D; // 원점에서의 거리
	double H;
	double centerU = F.rows / 2;   // 중심
	double centerV = F.cols / 2;
	Vec2f cmplxValue;

	// ideal filter H
	for (u = 0; u < F.rows; u++)
	{
		for (v = 0; v < F.cols; v++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));  // 원점에서의 거리 계산
			if (D >= D0)
				H = 2.0;
			else
				H = 1.0;


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