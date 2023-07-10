//////////////////////////////////////////////////////////////
//                                                          //
//                      flip �Լ�                           //
//                                                          //
//////////////////////////////////////////////////////////////


//
// void flip(InputArray src, OutputArray dst, int flipCode);  // ���� �������� ������ �Լ�
//
//      src	: �Է�
//	dst 	: ���
//	flipcode =  0�̸�, ����������� ������.
//	flipcode =  1(���)�̸�, ������������ ������.
//	flipcode = -1(����)�̸�, ����, �������� ��� ������.	



#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat matA = imread("lena.jpg", -1);

	Mat  matB;
	flip(matA, matB, 0);
	imshow("flip image", matB);

	waitKey();
	return 0;
}
