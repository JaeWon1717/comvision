/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                        erode, dilate �������� ����  	                       //
//									       //	
//									       //
// �������� ���� : ������Ҹ� �̿��Ͽ� �ݺ������� ������ Ȯ����� ������ �κ�  //
// �Ǵ� ������ �޲۰ų�, ������ ����Ͽ� �����ϴ� ���� ����		       //
//									       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////



#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/my_images/Fig0905(a)(wirebond-mask).tif", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Size size(3, 3);
	Mat rectKernel = getStructuringElement(MORPH_RECT, size);
	cout << "rectKernel=" << rectKernel << endl;

	int iterations = 2;
	Point anchor(1, 1);
	Mat erodeImage;
	erode(srcImage, erodeImage, rectKernel, anchor, iterations);
	imshow("erodeImage B", erodeImage);	

	Mat ellipseKernel = getStructuringElement(MORPH_ELLIPSE, size);
	cout << "ellipseKernel=" << ellipseKernel << endl;
	iterations = 10;
	Mat erodeImage2;
	erode(srcImage, erodeImage2, ellipseKernel, anchor, iterations);
	imshow("erodeImage2 C", erodeImage2);
	
	Mat crossKernel = getStructuringElement(MORPH_CROSS, size);
	cout << "crossKernel=" << crossKernel << endl;

	iterations = 25;
	Mat erodeImage3;
	erode(srcImage, erodeImage3, crossKernel, anchor, iterations);
	imshow("erodeImage3 D", erodeImage3);

	
	waitKey();
	return 0;
}
