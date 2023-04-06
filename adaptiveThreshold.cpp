//////////////////////////////////////////////////////////////
//                                                          //
//                적응적 임계값 영상                        //
//                                                          //
//    adaptivethreshold(src, dst, thresh, maxval,           //
//                      apativeMethod, thresholdtype,      //
//                      blocksize, C)                       //
//                                                          //   
//////////////////////////////////////////////////////////////


// 하나의 임계값이 영상 전체 화소에 동이랗게 적용하는 것이 아니라, 각각의 화소마다 이웃을 고려하여 
// 개별적으로 임계값을 계산하여 적용

// 입력 src 영상 : 8비트 단일 채널
// blockSize x bloxkSize 크기의 이웃에서 계산한 평균 또는 가중평균에서 C값을 뺄셈하여 임계값 계산
//    blockSize : 이웃의 크기. 일반적으로 3, 5, 7, 9등과 같은 홀수
// thresholdType에 따라 출력 dst 계산

// adaptiveMethod : 적응형임계값의 종류
//   ADAPTIVE_THRESH_MEAN_C :  blockSize x bloxkSize 크기의 이웃에서 평균을 계산한 다음 C를 뺄셈한 값이 임계값
//   ADAPTIVE_THRESH_GAUSSIAN_C : blockSize x bloxkSize 크기의 이웃에서 가우시안 가중평균을 계산한 다음 C를 뺄셈한 값이 임계값



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
