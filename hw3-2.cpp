/////////////////////////////////////////////////////////////////
//                                                             //
//               medianBlur, blur, GaussianBlur 필터           //
//                                                             //
/////////////////////////////////////////////////////////////////

// void medianBlur(InputArray src, OutputArray dst, int ksize)l, 
// 
// src 영상에서 ksize x ksize의 필터 윈도우를 사용하여 미디언/중위 수를 계산하여 dst에 저장
// 미디언 필터링의 결과값은 원본 src에 있는 값이며, salt and pepper 잡음에 효과적.
//
// src		: 1,3,4채널 영상
//                ksize가 3,또는 5보다 크면 CV_8U만 가능
// 경계처리방식 : BORDER_REPLICATE


// void blur(InputArray src, OutputArray dst, Size ksize, int d, double sigmaColor, 
//           Point Anchor=Point(-1,-1), int borderType=BORDER_DEFAULT);
// 
// 커널 크기 ksize 내의 합계를 계산하는, 커널 크기로 정규화된 박스 필터임.
//     == boxFilter(src, dst, 01, ksize, anchor, true, borderType);
//
// src		: 모든 채널, CV_8U, CV_16U, CV_16S, CV_32F, CV_64F 가능


// void getGuassianKernel(int ksize, double sigma, int ktype=CV_64F);
// 
// ksize x 1의 1D 가우시안 커널을 행렬로 반환
//
// ksize	: 커널 크기. 3,5,7,9 등의 홀수
// sigma	: 가우시안 표준편차.	
//	sigma<=0 이면, sigma=0.3*(ksize-1)*0.5-1)+0.8로 계산
// ktype	: 필터의 자료형. CV_32F 또는 CV_64F



// void GuassianBlur(InputArray src, OutputArray dst, Size ksize, 
//		double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
// 
// ksize 크기의 2차원 가우시안 커널과 회선(convolution) 수행.
//
// sigmaX	: X축 방향으로의 가우시안 커널 표준편차
// sigmaY	: Y축 방향으로의 가우시안 커널 표준편차 
//
//	sigmaX != 0, sigmaY != 0이면 sigmaX = sigmaY
//	sigmaX=0, sigmaY=0이먄 ksize.width, ksize.height를 가지고 계산
//
//		sigmaX = 0.3((ksize.width-1)/2-1)+0.8		
//		sigmaY = 0.3((ksize.height-1)/2-1)+0.8	
//
//	커널크기 n = 2 x sigma + 1
//


#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/my_images/blur.png", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	int ksize ;	// 필터 윈도우의 크기
	
	ksize = 11;
	Mat dstImage4;
	GaussianBlur(srcImage, dstImage4, Size(ksize, ksize), 0.0);
	imshow("GaussianBlur", dstImage4);

	Mat kx = getGaussianKernel(ksize, 0.0);   // 11 x 1 가우시안 커널
	Mat ky = getGaussianKernel(ksize, 0.0);
	Mat kxy = kx * ky.t();  // 11 x 11 2D 가우시안 커널 생성

	Mat dstImage5;
	filter2D(srcImage, dstImage5, -1, kxy);
	imshow("GaussianKernel", dstImage5);

	waitKey();
	return 0;
}
