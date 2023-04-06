//////////////////////////////////////////////////////////////
//                                                          //
//                       �Ӱ谪 ����                        //
//                                                          //
//    threshold(src, dst, thresh, maxval, type)             //
//                                                          //   
//////////////////////////////////////////////////////////////

#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);  // 1ä���� �׷��̷��� �������� �Է�
	if (srcImage.empty())
		return -1;

	Mat dstImage1;
	double th1 = threshold(srcImage, dstImage1, 100, 255, THRESH_BINARY);
	// thresh = 100. maxval = 255, type= THRESH_BINARY
	// �Ӱ谪�� th1���� ��ȯ. �� ���̽������� 100��.	

	cout << "th1 = " << th1 << endl;

	Mat dstImage2;
	double th2 = threshold(srcImage, dstImage2, 100, 255, THRESH_BINARY + THRESH_OTSU);
	// thresh = 100. maxval = 255, type= THRESH_BINARY+THRESH_OTSU
	// THRESH_OTSU�� �����Ǹ� thresh�� ������� �Ӱ谪�� Otsu �˰����� �����Ͽ� ����Ͽ� ���� �Ӱ谪�� th2�� ��ȯ
	// �� ���̽������� 117

	cout << "th2 = " << th2 << endl;

	imshow("dstImage1", dstImage1);
	imshow("dstImage2", dstImage2);
	waitKey();

	return 0;
}
