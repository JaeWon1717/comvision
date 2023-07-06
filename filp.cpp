//////////////////////////////////////////////////////////////
//                                                          //
//                      flip 함수                           //
//                                                          //
//////////////////////////////////////////////////////////////


//
// void flip(InputArray src, OutputArray dst, int flipCode);  // 수평 수직으로 뒤집는 함수
//
//      src	: 입력
//	dst 	: 출력
//	flipcode =  0이면, 수평방향으로 뒤집음.
//	flipcode =  1(양수)이면, 수직방향으로 뒤집음.
//	flipcode = -1(음수)이면, 수평, 수직방향 모두 뒤집음.	



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
