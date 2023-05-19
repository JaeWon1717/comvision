/////////////////////////////////////////////////////////////////
// //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                 ���󿡼� ����þ� ���͸�, ���ö�þ�, 0������ ����	       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////



// void Laplacian(OutputArray src, OutputArray dst, int ddepth, int ksize=1,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// src�� ���Ͽ� ���ö��̻��� ������ �Ŀ� scale�� �������ϰ�, delta ���� ���� ddepth ������ dst�� ����
// 
// ksize	: ���ö�þ��� ũ��
// ksize = 1 �Ǵ� ksize = 3�϶� 3 x 3 ���ö�þ� ������.
//
// ���ö�þ� ���͸� �Ŀ� ������ 0-�����ϴ� ��ġ��.

// LoG ����
// ������ Ŀ���� ũ�� n = 2 x 3 x sigma + 1 �Ǵ�  sigma = 0.3(n/2 - 1)+0.8�� ���


#include <opencv.hpp>
using namespace cv;
using namespace std;

void ZeroCrossing(Mat& src, Mat& dst, int threshold);  // 0 ������ üũ


int main()
{
	Mat srcImage = imread("C:/my_images/HW4-1.jpg", IMREAD_GRAYSCALE);
	//	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize = 15;
	Mat blurImage;
	GaussianBlur(srcImage, blurImage, Size(ksize, ksize), 0.0);  // srcImage�� 15 x 15�� ����þ� ���ͷ� ������

	Mat lapImage;
	Laplacian(blurImage, lapImage, CV_32F, ksize);  // ����þ� ������ �� ���� ���� ���ö�þ� ���͸� ����

	Mat dstImage;
	ZeroCrossing(lapImage, dstImage, 10);  // ���ö�þ� ����� ���� �������� üũ

	imshow("dstImage", dstImage);

	waitKey();

	return 0;
}

// ���ö�þ� ���͸��� �Է� ���� src���� ���ι���� ���� ������ �̿��� �����Ͽ� ��ȣ�� ����Ǵ� 0-���� ��ġ�� �����ϰ�
// ����Ǵ� ���̸� ���밪���� ������ ����, threshold �Լ��� �Ӱ谪 �̻��� ū ������ ��ȣ�� ����Ǵ� ��ġ�� ������ dst ���� �ݿ�

void ZeroCrossing(Mat& src, Mat& dst, int th)
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

	threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}