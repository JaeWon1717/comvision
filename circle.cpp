#include <opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
	// 512 x 512 ũ���� 3ä�� �÷� ���� dstImage�� Mat ��ķ� �����ϰ�, 
	// Scalar(255, 255, 255)�� �ʱ�ȭ


	rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));
	// dstImage ����  Point(100, 100), Point(400, 400)�� ���� ���ǵǴ� �簢����
	// Scalar(0, 0, 255) �������� �׸�.

	line(dstImage, Point(250, 100), Point(250, 400) Scalar(0, 0, 255));
	line(dstImage, Point(100, 250), Point(400, 250), Scalar(0, 0, 255));
	// dstImage ����  �簢���� ���� ���� �̵���ϴ� ������ Scalar(0, 0, 255) �������� �׸�.


	circle(dstImage, Point(250, 250), 150, Scalar(255, 0, 0));
	// dstImage ����  �߽��� Point(250, 250), ������ 150�� ���� �׸� �簢���� ������ ���� Scalar(255, 0, 0) �������� �׸�.

	circle(dstImage, Point(250, 250), 50, Scalar(0, 255, 0), -1);
	// dstImage ����  �߽��� Point(250, 250), ������ 50�� ���� Scalar(0, 255, 0) �������� ä��

	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}
