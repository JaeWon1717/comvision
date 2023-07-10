//////////////////////////////////////////////////////////////
//                                                          //
//                    �⺻ �迭 �Լ�                        //
//                                                          //
//////////////////////////////////////////////////////////////



// flip()  : ������       repeat() : ����        transpose() : ��� ��ġ
//
// void flip(InputArray src, OutputArray dst, int flipCode);  // ���� �������� ������ �Լ�
//
//      src	: �Է�
//	dst 	: ���
//	flipcode =  0�̸�, ����������� ������.
//	flipcode =  1(���)�̸�, ������������ ������.
//	flipcode = -1(����)�̸�, ����, �������� ��� ������.	
//
//	
// void repeat(InputArray src, int ny, int nx, OutputArray dst);  
// Mat repeat(Mat& src, int ny, int nx); 
//
//      �Է� src�� �������� nx��, �������� ny�� �����Ͽ� ��� dst ����




#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("flip_test.jpg", IMREAD_COLOR);
	CV_Assert(image.data);                  // ���� ó��

	Mat x_axis, y_axis, xy_axis, rep_img, trans_img;

	flip(image, x_axis, 0);                // x�� ���� ���� ������
	flip(image, y_axis, 1);                // y�� ���� �¿� ������
	flip(image, xy_axis, -1);

	repeat(image, 1, 2, rep_img);          // ���� ���� 2�� �ݺ� ����
	transpose(image, trans_img);           // ��� ��ġ 

	imshow("image", image);                // ����� �������� ǥ�� 
	imshow("x_axis", x_axis);
	imshow("y_axis", y_axis);
	imshow("xy_axis", xy_axis);
	imshow("rep_img", rep_img);
	imshow("trans_img", trans_img);

	waitKey();
	return 0;
}