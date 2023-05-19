/////////////////////////////////////////////////////////////////
//                                                             //
//                   ���󿡼��� Sobel ���� 		       //
//                                                             //
/////////////////////////////////////////////////////////////////



// void getDerivKernels(OutputArray kx, OutputArray ky, int dx, int dy, 
//		        int ksize, bool normalize=false, int ktype=CV_32F); 
// 
// ���󿡼� �̺��� ����ϱ� ���� 1D �������� ��ȯ
// sepFilter2D �Լ����� ������ Ŀ���� ����Ͽ� ���͸���.
//
// kx, ky	: dx, dy �̺� ���Ͱ���� ���� ��� ���
// 	normalize = true�̸� ����ȭ
// ktype	: kx, ky�� �ڷ���. CV_32F �Ǵ� CV_64F
// ksize	: Ŀ���� ũ��
//	ksize = CV_SCHARR(-1)�̸� Scharr 3x3 Ŀ�� ����
//	ksize = 1,3,5 �Ǵ� 7�̸� Sobel Ŀ�� ����



// void Sobel(OutputArray src, OutputArray dst, int ddepth, int dx, int ksize=3,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// �Է¿��� src�� ���� Sobel �̺��� �����Ͽ� ��¿��� dst�� ����.
//
// ddepth = -1�̸�, dst.depth() = src.depth() ���� �̷� ��� ���͸� �� ������ ���� �Ǿ� �߸� ������ �Ͼ.
// ddepth�� �ڷ����� CV_16S�� �ٲپ��� �ʿ䰡 ����. // int ddepth = CV_32F; 
// dx, dy	: ���� x�� �̺� ����, y�� �̺� ����
// ksize	: �Һ� ������ Ŀ���� ũ��  1,3,5,7
//	ksize =1�̸� 3 x 1 �Ǵ� 1 x 3 Ŀ�� ����. x�� �Ǵ� y�������� 1�� �Ǵ� 2�� �̺и��� ���� ����.
//	ksize!=1�̸� ksize x ksize Ŀ�� ����
//	ksize=-1�̸� Scharr 3 x 3 Ŀ�� ����


// void Scharr(OutputArray src, OutputArray dst, int ddepth, int dx, int dy,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// �Է¿��� src�� ���� Scharr �����ڸ� ����� x��, y�� ���������� �̺��� �����Ͽ� ��¿��� dst�� ����.
// �̺� ����ϰ�, �����ϱ� ���� scale�� ���� �����ϸ��� delta�� ���� ������ ����Ͽ� dst�� ����.
// Sobel �Լ����� ksize = -1�� ���͸��� �Ͱ� ������ ȿ���� ����.



#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/my_images/HW4-1.jpg", IMREAD_GRAYSCALE);
	//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	int ksize = 3;
	int ddepth = CV_32F;	// ���̿� ���� �ڷ��� ����
	Mat dstGx, dstGy;
	Sobel(srcImage, dstGx, ddepth, 1, 0, ksize);    // dx
	Sobel(srcImage, dstGy, ddepth, 0, 1, ksize);	// dy

	int dtype = CV_8U;
	Mat dstImageGx;
	normalize(abs(dstGx), dstImageGx, 0, 255, NORM_MINMAX, dtype);    // |dstGx|

	//	int thresh = 100;
	//	threshold(abs(dstGx), dstImageGx, thresh, 255, THRESH_BINARY);
	imshow("dstImageGx", dstImageGx);

	Mat dstImageGy;
	normalize(abs(dstGy), dstImageGy, 0, 255, NORM_MINMAX, dtype);	// |dstGy|	
	//	threshold(abs(dstGy), dstImageGy, thresh, 255, THRESH_BINARY);
	imshow("dstImageGy", dstImageGy);

	Mat dstMag;
	magnitude(dstGx, dstGy, dstMag);  // �ܼ�ȭ�ϸ�.. |dstGx| + |dstGy|
	Mat dstImageGxy;
	normalize(dstMag, dstImageGxy, 0, 255, NORM_MINMAX, dtype);
	//	threshold(dstMag, dstImageGxy, thresh, 255, THRESH_BINARY);
	imshow("dstImageGxy", dstImageGxy);

	waitKey();
	return 0;
}
