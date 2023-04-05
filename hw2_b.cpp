//������������������
//////////////////////////////////////////////////////////////
//                                                          //
//        ������꿡 ���� ��ϴ�� ���� ȿ��                //
//                                                          //    
//////////////////////////////////////////////////////////////

#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("C:/my_images/Fig0310(b)(washed_out_pollen_image).tif", 0);	// ��ϵ� Ÿ�� �б�
	CV_Assert(image.data);				// ����ó��

	Scalar avg = mean(image) / 2.0;			// ���� ���� ȭ�� ����� ����
	Mat dst1 = image * 0.5;				// ��ϴ�� ���� : 1���� ������ ���� ��� ����
	Mat dst2 = image * 2.0;				// ��ϴ�� ����
	Mat dst3 = image * 0.5 + avg[0];		// ���� ��� �̿� ��� ����
	Mat dst4 = image * 2.0 - avg[0];		// ���� ��� �̿� ��� �߰�

	imshow("image", image);
	imshow("dst1-��񰨼�", dst1),
	
	waitKey();
	return 0;
}