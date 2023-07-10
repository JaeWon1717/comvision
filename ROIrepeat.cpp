//////////////////////////////////////////////////////////////
//                                                          //
//                     ROI, repeat �Լ�                     //
//                                                          //
//////////////////////////////////////////////////////////////


// void repeat(InputArray src, int ny, int nx, OutputArray dst);  
// Mat repeat(Mat& src, int ny, int nx); 
//
//      �Է� src�� �������� nx��, �������� ny�� �����Ͽ� ��� dst ����



#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Rect rtROI(0, 0, 256, 256);  // ���ɿ��� (0,0,256,256)�� �簢�� rtROI�� �ʱ�ȭ
	Mat roi = srcImage(rtROI);   // srcImage���� ���ɿ����� rtROI �κи��� Mat ��� roi�� ����
	rectangle(srcImage, rtROI, Scalar::all(0));  // ���ɿ������� �簢������ ǥ��
	imshow("srcImage", srcImage);

	Mat dstImage = repeat(roi, 2, 2); // ���ɿ��� roi ����� �������� 2��, �������� 2�� �ݺ� �����Ͽ� ��� dstImage�� ����
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}
