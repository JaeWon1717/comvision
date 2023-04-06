//////////////////////////////////////////////////////////////
//                                                          //
//                ������ �Ӱ谪 ����                        //
//                                                          //
//    adaptivethreshold(src, dst, thresh, maxval,           //
//                      apativeMethod, thresholdtype,      //
//                      blocksize, C)                       //
//                                                          //   
//////////////////////////////////////////////////////////////


// �ϳ��� �Ӱ谪�� ���� ��ü ȭ�ҿ� ���̶��� �����ϴ� ���� �ƴ϶�, ������ ȭ�Ҹ��� �̿��� ����Ͽ� 
// ���������� �Ӱ谪�� ����Ͽ� ����

// �Է� src ���� : 8��Ʈ ���� ä��
// blockSize x bloxkSize ũ���� �̿����� ����� ��� �Ǵ� ������տ��� C���� �����Ͽ� �Ӱ谪 ���
//    blockSize : �̿��� ũ��. �Ϲ������� 3, 5, 7, 9��� ���� Ȧ��
// thresholdType�� ���� ��� dst ���

// adaptiveMethod : �������Ӱ谪�� ����
//   ADAPTIVE_THRESH_MEAN_C :  blockSize x bloxkSize ũ���� �̿����� ����� ����� ���� C�� ������ ���� �Ӱ谪
//   ADAPTIVE_THRESH_GAUSSIAN_C : blockSize x bloxkSize ũ���� �̿����� ����þ� ��������� ����� ���� C�� ������ ���� �Ӱ谪



#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat dstImage0;
	threshold(srcImage, dstImage0, 0, 255, THRESH_BINARY | THRESH_OTSU

		Mat dstImage1;
	adaptiveThreshold(srcImage, dstImage1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 5);
	// apativeMethod=ADAPTIVE_THRESH_MEAN_C, thresholdtype=THRESH_BINARY, blockSize=21, C=5

	Mat dstImage2;
	adaptiveThreshold(srcImage, dstImage2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);
	//apativeMethod=ADAPTIVE_THRESH_GAUSSIAN_C, thresholdtype=THRESH_BINARY, blockSize=21, C=5

	imshow("Otsu", dstImage0);
	imshow("MEAN_C", dstImage1);
	imshow("GAUSSIAN_C", dstImage2);
	waitKey();

	return 0;
}
