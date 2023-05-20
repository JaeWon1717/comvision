/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                   ����þ� �Լ��� Ǫ���� ��ȯ�� �̿��� LoG                  //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

// ## ����þ� �Լ� g(x,y)�� Ǫ���� ��ȯ G(u,v) ���� ����þ� �Լ���.
// ## ����þ� �Լ��� Ǫ���� ��ȯ��  DFT(g(x,y)) = G(u,v)�� �̿��� ���͸� ����
//
// 1) ����þ� �Լ��� Ǫ���� ��ȯ G(u,v)�� �̿��� ������
// 2) ����þ� �Լ��� Ǫ���� ��ȯ G(u,v)�� �̿��� �̺�(gradient)
// 3) ����þ� �Լ��� Ǫ���� ��ȯ G(u,v)�� �̿��� LoG ���͸�



#include <opencv.hpp>
using namespace cv;
using namespace std;

void LOG_DFT(Mat& src, Mat& dst, double sigma);
void ZeroCrossing(Mat& src, Mat& dst, int th);
void ChangeSignOddPositionInXY(Mat& m);

int main()
{
	Mat srcImage = imread("rect.jpg", IMREAD_GRAYSCALE);
	//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;
	imshow("srcImage", srcImage);

	Mat src32f;
	srcImage.convertTo(src32f, CV_32F);

	double sigma = 0.01; // 0.05, 0.01
	Mat logDst;
	LOG_DFT(src32f, logDst, sigma);   // LoG ���͸�

	Mat zeroDest;
	ZeroCrossing(logDst, zeroDest, 1);   // �������� üũ, thresold �� : 1

	imshow("zeroDest", zeroDest);

	waitKey();

	return 0;
}

void LOG_DFT(Mat& src, Mat& dst, double sigma)
{

	// src ������ dft�� ���� ������ ũ�� ���
	int nW = getOptimalDFTSize(src.cols);
	int nH = getOptimalDFTSize(src.rows);

	Mat A;
	copyMakeBorder(src, A, 0, nH - (src.rows), 0, nW - (src.cols), BORDER_CONSTANT, 0);  // src�� ��� A�� 0 �е��Ͽ� Ȯ��

	ChangeSignOddPositionInXY(A); // centering  : �߽� �̵�

	Mat dftA;
	dft(A, dftA, DFT_COMPLEX_OUTPUT);  // 0-�е��Ͽ� Ȯ��� ��� A�� DFT ��ȯ

	int u, v;
	Vec2f cValue;
	const double phi4 = -4 * CV_PI * CV_PI;  // CV_PI : ����

	double centerU = dftA.rows / 2;
	double centerV = dftA.cols / 2;

	double D, G;
	double d = -2 * (CV_PI * CV_PI) * sigma * sigma;   // CV_PI : ����
	double U, V;

	for (u = 0; u < dftA.rows; u++)
	{
		for (v = 0; v < dftA.cols; v++)
		{
			U = (u - centerU);
			V = (v - centerV);

			D = U * U + V * V;

			G = phi4 * D * exp(d * D);

			// dftA(u,v)�� LoG �Լ��� Ǫ���� ��ȯ G(u,v)�� ���ļ� ���������� ������ �Ͽ� dftA(u,v)�� ����
			cValue = dftA.at<Vec2f>(u, v);
			cValue[0] *= G;
			cValue[1] *= G;
			dftA.at<Vec2f>(v, u) = cValue;
		}

		dst.create(src.size(), CV_32F);  // dst�� src�� ���� ũ���� ����� CV_32F�� ����

		idft(dftA, dst, DFT_SCALE | DFT_REAL_OUTPUT, dftA.rows);   // dftA�� ����ȯ�Ͽ� dst�� ����

		ChangeSignOddPositionInXY(dst); // centering �߽��� ������� ����
	}

	void ZeroCrossing(Mat & src, Mat & dst, int th)
	{
		int x, y;
		double a, b;

		Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));  // ���� ������ 0-���� ����
		// src�� ������ ũ����, CV_32F�� �ڷ����� 0���� �ʱ�ȭ�� ��� ����

		Mat_<float> _src(src);	// src�� �����Ͽ� _src ����

		for (x = 1; x < src.rows - 1; x++)
		{
			for (y = 1; y < src.cols - 1; y++)
			{

				// (+.-), (-,+), (+,0,-), (-,0,+) �� ��츦 �����Ͽ� �����ϴ� ������ zeroCrossH�� ����

				a = _src(x, y);     		// ���� ������ ������ �� �ȼ� ����
				b = _src(x, y + 1);

				if (a == 0)   			// �ش� �ȼ��� ���� 0 �̸� �� ������ �ȼ��� �ٽ� ����.
					// (+,0,-) �Ǵ� (-,0,+)�� ��츦 �����ϱ� ����
					a = _src(x, y - 1);

				if (a * b < 0)			// ���� ������ ������ �� �ȼ��� ��ȣ�� �ٸ��ٸ�
					// �� �ȼ��� ���밪�� ���� ����
					zeroCrossH.at<float>(x, y) = fabs(a) + fabs(b);

				else				// ���� ������ ������ �� �ȼ��� ��ȣ�� ������ 0 ����
					zeroCrossH.at<float>(x, y) = 0;

			}
		}

		Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));  // ���� ������ 0-���� ����
		for (x = 1; x < src.rows - 1; x++)
		{
			for (y = 1; y < src.cols - 1; y++)
			{
				a = _src(x, y);
				b = _src(x + 1, y);

				if (a == 0)
					a = _src(x - 1, y);
				if (a * b < 0)
					zeroCrossV.at<float>(x, y) = fabs(a) + fabs(b);
				else
					zeroCrossV.at<float>(x, y) = 0;
			}
		}

		Mat zeroCross(src.size(), CV_32F, Scalar::all(0));

		add(zeroCrossH, zeroCrossV, zeroCross);  // zeroCross = zeroCrossH + zeroCrossV

		dst.create(src.size(), CV_8U);  // Mat::create() �޼ҵ� : ������ ������ Mat Ŭ���� ��İ� ũ�� �� �ڷ����� �����ϸ� ���� �����͸� ���� �޸𸮸� �Ҵ����� ����. 
		threshold(zeroCross, dst, th, 255, THRESH_BINARY);
	}

	void ChangeSignOddPositionInXY(Mat & m)
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