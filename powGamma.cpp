#include <opencv.hpp>

using namespace cv;


void main()
{
	Mat srcImage = imread("Fig0307(a)(intensity_ramp).tif");
	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);

	double power = 0.4;  // 0.4 = 1/2.5

	Mat powImage;
	pow(fImage, power, powImage);
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);   // 0~1���̷� ����ȭ


	double power1 = 2.5;
	Mat powImage1;
	pow(powImage, power1, powImage1);   // ����Ϳ� ��Ÿ���� ���

	normalize(powImage1, powImage1, 0, 1.0, NORM_MINMAX);

	imshow("src", srcImage);
	imshow("pow", powImage);
	imshow("pow1", powImage1);

	waitKey(0);
}