/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                      �̻����� ������ ��� ���͸�                            //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
// ������ ��� ���� F(u,v) : ������ ������ �����Ű��, ������ ������ 0���� �����
//			     �����Ű�� �ʴ� ����
//
//
//  1) �̻�����(Ideal) ������ ��� ����
//
// ���ļ� ������ ���� F(M/2, N/2)�κ����� �Ÿ� D(u,v)�� ����(cut-off) ���ļ� D0�̸��̸� �����Ű��,
// �׷��� ������ �����Ű�� �ʵ��� ��.
//
// D(u,v) <= D0�̸� : H(u,v) = 1�� �Ǿ� H(u,v)F(u,v) = 1 x F(u,v) = F(u,v)�� �Ǿ�, F(u,v)�� �����
// D(u,v) > D0�̸�  : H(u,v) = 0�� �Ǿ� H(u,v)F(u,v) = 0 x F(u,v) = 0�� �Ǿ� F(u,v)�� ������� ����.
//
//
//  2) ���Ϳ���(Butterworth) ������ ��� ����
//
// ���� ���Ľ� D0�� ���� n�� ����Ͽ� ���� H(u,v)�� �ϸ��ϰ� 0���� 1������ �Ǽ� ���� ������ ��.
// ������ �߽ɿ����� H(u,v) = 1�� ����, �־������� 0�� ����� ���� ����.
//
//
//  3) ����þ�(Gaussian) ������ ��� ����
// 
// D0�� ǥ����ck�� ���� ����þ� �Լ��� ���� H(u,v)�� �ϸ��ϰ� 0���� 1������ �Ǽ����� ����.
// ������ �߽ɿ����� H(u,v) = 1�� ����, �־������� 0�� ����� ���� ����.
//
/////////////////////////////////////////////////////////////////////////////////
//������ ����� �帲������ ��Ÿ�� ,Ư���� �뿪���� �ް��ϰ� ���� �����ϱ� ������ ��� ������ ȭ�� ����
//��ü�� ���κ� ������ �ܹ��� ���� ����(ringing pattern) ��Ÿ��
//�ذ���
// ���� ���Ұ��� ���� ���ļ����� �ް��ϰ� 0�������� �ʰ� �ϸ��� ��� �̷絵�� ����
// ���Ϳ��� ����(Butterworth filter)�� ����þ� ����(Gaussian filter)


#include <opencv.hpp>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);
void IdealLowpassFilteringH(Mat F, double D0);

int main()
{
	//Mat srcImage = imread("C:/my_images/universe.jpg", IMREAD_GRAYSCALE);
	Mat srcImage = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);
	ChangeSignOddPositionInXY(fImage); // centering

	Mat dftA;
	dft(fImage, dftA, DFT_COMPLEX_OUTPUT);

	double D0 = 30.0; //30, 80, 200   cut-off(����) ���ļ�
	IdealLowpassFilteringH(dftA, D0); // D0�� ���� �̻����� ������ ��� ���͸� ����

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT); // ����ȯ
	ChangeSignOddPositionInXY(dftB);   // �ٽ� ������� �߽� �̵�

	Mat dstImage;
	dftB.convertTo(dstImage, CV_8U);
	imshow("dstImage", dstImage);
	waitKey();

	return 0;
}

void IdealLowpassFilteringH(Mat F, double D0)
{
	int u, v;
	double D; // ���������� �Ÿ�
	double H;
	double centerU = F.rows / 2;   // �߽�
	double centerV = F.cols / 2;
	Vec2f cmplxValue;

	// ideal filter H
	for (u = 0; u < F.rows; u++)
	{
		for (v = 0; v < F.cols; v++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));  // ���������� �Ÿ� ���
			if (D <= D0)   // ���� ���ļ� �ȿ� ������ ���
				H = 1.0;
			else
				H = 0.0;


			// Ǫ���� ��ȯ�� ���� ���ļ� ������ ���� ���� H�� ���Ͽ� �ٽ� ����
			cmplxValue = F.at<Vec2f>(u, v);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			F.at<Vec2f>(u, v) = cmplxValue;
		}
	}
}

void ChangeSignOddPositionInXY(Mat& m)
{
	int x, y;
	float fValue;

	for (x = 0; x < m.rows; x++)
	{
		for (y = 0; y < m.cols; y++)
		{
			fValue = m.at<float>(x, y);
			//			if((x+y)%2==1) // odd number
			if ((x + y) % 2 == 1 && fValue != 0)
				m.at<float>(x, y) = -fValue;
		}
	}
}