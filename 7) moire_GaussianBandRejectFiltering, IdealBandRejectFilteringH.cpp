#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);
void GaussianLowpassFilteringH(Mat F, double D0);
void GaussianBandRejectFilteringH(Mat F, double D0, double W);
void IdealLowpassFilteringH(Mat F, double D0);
void IdealBandRejectFilteringH(Mat F, double D0, double W);


int main()
{
	Mat srcImage = imread("Fig0516.tif", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);
	ChangeSignOddPositionInXY(fImage); // centering

	Mat dftA;
	dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

	double	D0 = 40;
	double W = 10;
	GaussianLowpassFilteringH(dftA, D0);
	//GaussianBandRejectFilteringH(dftA, D0, W);
	//IdealLowpassFilteringH(dftA, D0);
	//IdealBandRejectFilteringH(dftA, D0, W);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(dftB);

	Mat dstImage;
	dftB.convertTo(dstImage, CV_8U);
	imshow("dstImage", dstImage);


	waitKey();
	return 0;
}


void IdealLowpassFilteringH(Mat F, double D0)
{
	int u, v;
	double D; // distance
	double H;
	double centerU = F.cols / 2;
	double centerV = F.rows / 2;
	Vec2f cmplxValue;

	// ideal filter H
	for (v = 0; v < F.rows; v++)
		for (u = 0; u < F.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			if (D <= D0)
				H = 1.0;
			else
				H = 0.0;
			cmplxValue = F.at<Vec2f>(v, u);

			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(v, u) = cmplxValue;
		}
}


void IdealBandRejectFilteringH(Mat F, double D0, double W)
{
	int u, v;
	double D; // distance
	double H;
	double centerU = F.cols / 2;
	double centerV = F.rows / 2;
	Vec2f cmplxValue;

	// ideal filter H
	for (v = 0; v < F.rows; v++)
		for (u = 0; u < F.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			if ((D <= (D0 + W / 2)) && (D >= (D0 - W / 2)))
				H = 0.0;
			else
				H = 1.0;
			cmplxValue = F.at<Vec2f>(v, u);

			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(v, u) = cmplxValue;
		}
}


void GaussianLowpassFilteringH(Mat F, double D0)
{
	int u, v;
	double D; // distance
	double H;
	double centerU = F.cols / 2;
	double centerV = F.rows / 2;
	Vec2f cmplxValue;

	// filter H
	for (v = 0; v < F.rows; v++)
		for (u = 0; u < F.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			H = exp(-D * D / (2.0 * D0 * D0));
			cmplxValue = F.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(v, u) = cmplxValue;
		}
}

void GaussianBandRejectFilteringH(Mat F, double D0, double W)
{
	int u, v;
	double D2;
	double DW;

	double D; // distance
	double H;
	double centerU = F.cols / 2;
	double centerV = F.rows / 2;
	Vec2f cmplxValue;

	// filter H
	for (v = 0; v < F.rows; v++)
		for (u = 0; u < F.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			D2 = D * D - D0 * D0;
			DW = D2 / (D * W);
			H = 1.0 - exp(-(DW * DW));
			cmplxValue = F.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(v, u) = cmplxValue;
		}
}

void ChangeSignOddPositionInXY(Mat& m)
{
	int x, y;
	float fValue;
	for (y = 0; y < m.rows; y++)
		for (x = 0; x < m.cols; x++)
		{
			fValue = m.at<float>(y, x);
			//		if((x+y)%2==1 && fValue != 0)
			if ((x + y) % 2 == 1) // odd number
				m.at<float>(y, x) = -fValue;
		}
}

/*
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;


void ChangeSignOddPositionInXY(Mat &m);
void ChangeSignOddPositionInXY(Mat &m);
int main()
{
	Mat srcImage = imread("Fig0516.tif", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);
	ChangeSignOddPositionInXY(fImage); // centering

	Mat dftA;
	dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

	Mat dftA2[2];
	split(dftA, dftA2);

	Mat magF;
	magnitude(dftA2[0], dftA2[1], magF);
	magF += Scalar(1);
	log(magF, magF);

	double   minValue, maxValue;
	minMaxLoc(magF, &minValue, &maxValue);
	cout << "minValue=" << minValue << endl;
	cout << "maxValue=" << maxValue << endl;

	Mat magImage;
	normalize(magF, magImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("magImage", magImage);

	Mat angleF;
	phase(dftA2[0], dftA2[1], angleF);

	Mat angleImage;
	normalize(angleF, angleImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("angleImage", angleImage);
	waitKey();

	return 0;
}
void ChangeSignOddPositionInXY(Mat &m)
{
	int x, y;
	float fValue;
	for (y = 0; y<m.rows; y++)
		for (x = 0; x<m.cols; x++)
		{
			fValue = m.at<float>(y, x);
			//		if((x+y)%2==1) // odd number
			if ((x + y) % 2 == 1 && fValue != 0)
				m.at<float>(y, x) = -fValue;
		}
}*/