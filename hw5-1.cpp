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
