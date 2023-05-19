/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                        erode, dilate 모폴로지 연산  	                       //
//									       //	
//									       //
// 모폴로지 연산 : 구조요소를 이용하여 반복적으로 영역을 확장시켜 떨어진 부분  //
// 또는 구멍을 메꾼거나, 잡음을 축소하여 제거하는 등의 연산		       //
//									       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////



#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/my_images/Fig0911(a)(noisy_fingerprint).tif", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Size size(3, 3);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size); 
	cout << "rectKernel=" << rectKernel << endl;

	int iterations = 1;
	Point anchor(1, 1);
	Mat erodeImage;
	erode(srcImage, erodeImage, rectKernel, anchor, iterations);  
	imshow("erodeImage", erodeImage);	

	Mat ellipseKernel = getStructuringElement(MORPH_ELLIPSE, size);
	cout << "ellipseKernel=" << ellipseKernel << endl;

	

	Mat crossKernel = getStructuringElement(MORPH_CROSS, size);
	cout << "crossKernel=" << crossKernel << endl;


	
	waitKey();
	return 0;
}
