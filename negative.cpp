//////////////////////////////////////////////////////////////
//                                                          //
//                         ���� ����                        //
//                                                          //
//////////////////////////////////////////////////////////////


#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("Fig0304(a)(breast_digital_Xray).jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat_<uchar>image(srcImage);
	Mat_<uchar>dstImage(srcImage.size());     // ��¿��� dstImage�� srcImage.size() ũ��� ����

	for (int x = 0; y < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			uchar r = image(x, y);
			dstImage(x, y) = 255 - r;
		}
	}

	imshow("dstImage", dstImage);

	waitKey();
	return 0;
}
