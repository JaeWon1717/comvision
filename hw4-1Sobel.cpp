/////////////////////////////////////////////////////////////////
//                                                             //
//                   영상에서의 Sobel 연산 		       //
//                                                             //
/////////////////////////////////////////////////////////////////



// void getDerivKernels(OutputArray kx, OutputArray ky, int dx, int dy, 
//		        int ksize, bool normalize=false, int ktype=CV_32F); 
// 
// 영상에서 미분을 계산하기 위한 1D 선형필터 반환
// sepFilter2D 함수에서 생성된 커널을 사용하여 필터링함.
//
// kx, ky	: dx, dy 미분 필터계수를 위한 출력 행렬
// 	normalize = true이면 정규화
// ktype	: kx, ky의 자료형. CV_32F 또는 CV_64F
// ksize	: 커널의 크기
//	ksize = CV_SCHARR(-1)이면 Scharr 3x3 커널 생성
//	ksize = 1,3,5 또는 7이면 Sobel 커널 생성



// void Sobel(OutputArray src, OutputArray dst, int ddepth, int dx, int ksize=3,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// 입력영상 src에 대해 Sobel 미분을 적용하여 출력영상 dst에 저장.
//
// ddepth = -1이면, dst.depth() = src.depth() 따라서 이런 경우 필터링 후 음수가 없게 되어 잘림 현상이 일어남.
// ddepth의 자료형을 CV_16S로 바꾸어줄 필요가 있음. // int ddepth = CV_32F; 
// dx, dy	: 각각 x축 미분 차수, y축 미분 차수
// ksize	: 소벨 윈도우 커널의 크기  1,3,5,7
//	ksize =1이면 3 x 1 또는 1 x 3 커널 적용. x축 또는 y축으로의 1차 또는 2차 미분만을 위해 사용됨.
//	ksize!=1이면 ksize x ksize 커널 생성
//	ksize=-1이면 Scharr 3 x 3 커널 적용


// void Scharr(OutputArray src, OutputArray dst, int ddepth, int dx, int dy,
//	      double scale=1, double delta=0, int borderType=BORDER_DEFAULT); 
// 
// 입력영상 src에 대해 Scharr 연산자를 사용한 x축, y축 방향으로의 미분을 적용하여 출력영상 dst에 저장.
// 미분 계산하고, 저장하기 전에 scale에 의한 스케일링과 delta에 이한 덧셈을 계산하여 dst에 저장.
// Sobel 함수에서 ksize = -1로 필터링한 것과 동일한 효과를 가짐.



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
	int ddepth = CV_32F;	// 깊이에 대한 자료형 변경
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
	magnitude(dstGx, dstGy, dstMag);  // 단순화하면.. |dstGx| + |dstGy|
	Mat dstImageGxy;
	normalize(dstMag, dstImageGxy, 0, 255, NORM_MINMAX, dtype);
	//	threshold(dstMag, dstImageGxy, thresh, 255, THRESH_BINARY);
	imshow("dstImageGxy", dstImageGxy);

	waitKey();
	return 0;
}
