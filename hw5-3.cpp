#include<iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{

	//
	//img_gray = imread("C:/my_images/Fig0911(a)(noisy_fingerprint)", IMREAD_GRAYSCALE);
	Mat srcImage = imread("C:/my_images/Fig0938(a)(cygnusloop_Xray_original).tif", IMREAD_GRAYSCALE);
	//Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Size size(3, 3);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);
	cout << "rectKernel=" << rectKernel << endl;

	int iterations = 1;
	Point anchor(1, 1);
	Mat openImage;
	morphologyEx(srcImage, openImage, MORPH_OPEN, rectKernel, anchor, iterations);
	imshow("openImage", openImage);
	iterations = 3;
	Mat openImage2;
	morphologyEx(srcImage, openImage2, MORPH_OPEN, rectKernel, anchor, iterations);
	imshow("openImage2", openImage2);
	iterations = 5;


	


	/*Mat closeImage;
	morphologyEx(srcImage, closeImage, MORPH_CLOSE, rectKernel, anchor, iterations);
	imshow("closeImage", closeImage);*/

	

	waitKey();
	return 0;
}