/////////////////////////////////////////////////////////////////
//                                                             //
//               medianBlur, blur, GaussianBlur ����           //
//                                                             //
/////////////////////////////////////////////////////////////////

// void medianBlur(InputArray src, OutputArray dst, int ksize)l, 
// 
// src ���󿡼� ksize x ksize�� ���� �����츦 ����Ͽ� �̵��/���� ���� ����Ͽ� dst�� ����
// �̵�� ���͸��� ������� ���� src�� �ִ� ���̸�, salt and pepper ������ ȿ����.
//
// src		: 1,3,4ä�� ����
//                ksize�� 3,�Ǵ� 5���� ũ�� CV_8U�� ����
// ���ó����� : BORDER_REPLICATE


// void blur(InputArray src, OutputArray dst, Size ksize, int d, double sigmaColor, 
//           Point Anchor=Point(-1,-1), int borderType=BORDER_DEFAULT);
// 
// Ŀ�� ũ�� ksize ���� �հ踦 ����ϴ�, Ŀ�� ũ��� ����ȭ�� �ڽ� ������.
//     == boxFilter(src, dst, 01, ksize, anchor, true, borderType);
//
// src		: ��� ä��, CV_8U, CV_16U, CV_16S, CV_32F, CV_64F ����


// void getGuassianKernel(int ksize, double sigma, int ktype=CV_64F);
// 
// ksize x 1�� 1D ����þ� Ŀ���� ��ķ� ��ȯ
//
// ksize	: Ŀ�� ũ��. 3,5,7,9 ���� Ȧ��
// sigma	: ����þ� ǥ������.	
//	sigma<=0 �̸�, sigma=0.3*(ksize-1)*0.5-1)+0.8�� ���
// ktype	: ������ �ڷ���. CV_32F �Ǵ� CV_64F



// void GuassianBlur(InputArray src, OutputArray dst, Size ksize, 
//		double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
// 
// ksize ũ���� 2���� ����þ� Ŀ�ΰ� ȸ��(convolution) ����.
//
// sigmaX	: X�� ���������� ����þ� Ŀ�� ǥ������
// sigmaY	: Y�� ���������� ����þ� Ŀ�� ǥ������ 
//
//	sigmaX != 0, sigmaY != 0�̸� sigmaX = sigmaY
//	sigmaX=0, sigmaY=0�̐� ksize.width, ksize.height�� ������ ���
//
//		sigmaX = 0.3((ksize.width-1)/2-1)+0.8		
//		sigmaY = 0.3((ksize.height-1)/2-1)+0.8	
//
//	Ŀ��ũ�� n = 2 x sigma + 1
//


#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize ;	// ���� �������� ũ��
	
	ksize = 11;
	Mat dstImage4;
	GaussianBlur(srcImage, dstImage4, Size(ksize, ksize), 0.0);
	imshow("GaussianBlur", dstImage4);

	Mat kx = getGaussianKernel(ksize, 0.0);   // 11 x 1 ����þ� Ŀ��
	Mat ky = getGaussianKernel(ksize, 0.0);
	Mat kxy = kx * ky.t();  // 11 x 11 2D ����þ� Ŀ�� ����

	Mat dstImage5;
	filter2D(srcImage, dstImage5, -1, kxy);
	imshow("GaussianKernel", dstImage5);

	waitKey();
	return 0;
}
