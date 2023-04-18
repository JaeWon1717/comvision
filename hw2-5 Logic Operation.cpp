/*******************************************************/
/*            HW#2-5. Logic Operation    */
/*  �ۼ��� : �����          ��¥ : 2023�� 4�� 17�� */
/*                                                                           */
/* ���� ���� : �� ���� �׷��� �������� �ҷ����� , ��Ʈ�����ڸ� 
����Ͽ� �� �̹����� AND�����Ͽ� ������� ���� ����.
Ư���κ��� �����Ҷ��� �����������ϴ� �۾��� ������.* /
/*                - - - - - - -                                            */
/*******************************************************/
#include <opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	Mat image1 = imread("C:/my_images/Fig0230(a)(dental_xray).tif", IMREAD_GRAYSCALE);
	Mat image2 = imread("C:/my_images/Fig0230(b)(dental_xray_mask).tif", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.5, beta = 10;


	Mat AND;//AND 
	bitwise_and(image1, image2, AND);

	// �̹��� ũ�⸦ 0.5��� ����
	resize(AND, AND, Size(), 0.5, 0.5, INTER_LINEAR);

	imshow("AND", AND);

	waitKey(0);
}