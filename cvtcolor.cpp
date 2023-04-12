/////////////////////////////////////////////////////////////////
//                                                             //
//             cvtColor�� ���� �÷� �� ��ȯ                  //
//                                                             //
/////////////////////////////////////////////////////////////////

// void cvtColor(const CvArr* src, const CvArr* dst, int code, int dstCn=0);
// 
// src		: �Է¿���. CV_8U, CV_8S, CV_16U, CV_16S �Ǵ� CV_32
// dst		: ��¿���. src�� ���� ũ��, ���� ����.ä���� ���� �ٸ� �� ����.
// code		: src�� �÷��� src_color���� ��� dst�� �÷� dst_color���� ��ȯ ���
// dstCn	: dst ������ ä�� ��. 0�� ��� src�� code�� ���� �ڵ� ���

// RGB ������ ���� ����
// 	8��Ʈ 	: 0~255
//	16��Ʈ 	: 0~65535 
//	�Ǽ�����: 0~1������ ��



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
