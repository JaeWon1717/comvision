//////////////////////////////////////////////////////////////
//                                                          //
//                         반전 영상                        //
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
	Mat_<uchar>dstImage(srcImage.size());     // 출력영상 dstImage를 srcImage.size() 크기로 생성

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
