//////////////////////////////////////////////////////////////
//                                                          //
//                       임계값 영상                        //
//                                                          //
//    threshold(src, dst, thresh, maxval, type)             //
//                                                          //   
//////////////////////////////////////////////////////////////

#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);  // 1채널의 그레이레벨 영상으로 입력
	if (srcImage.empty())
		return -1;

	Mat dstImage1;
	double th1 = threshold(srcImage, dstImage1, 100, 255, THRESH_BINARY);
	// thresh = 100. maxval = 255, type= THRESH_BINARY
	// 임계값은 th1으로 반환. 이 케이스에서는 100임.	

	cout << "th1 = " << th1 << endl;

	Mat dstImage2;
	double th2 = threshold(srcImage, dstImage2, 100, 255, THRESH_BINARY + THRESH_OTSU);
	// thresh = 100. maxval = 255, type= THRESH_BINARY+THRESH_OTSU
	// THRESH_OTSU가 지정되면 thresh와 상관없이 임계값을 Otsu 알고리즘을 적용하여 계산하여 계산된 임계값을 th2로 반환
	// 이 케이스에서는 117

	cout << "th2 = " << th2 << endl;

	imshow("dstImage1", dstImage1);
	imshow("dstImage2", dstImage2);
	waitKey();

	return 0;
}
