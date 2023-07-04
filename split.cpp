//////////////////////////////////////////////////////////////
//                                                          //
//                    채널 분리 및 합성                     //
//                                                          //
//////////////////////////////////////////////////////////////


// void merge(const Mat*mv, size_t count, OutputArray dst);  
// void merge(InputArrayOfArrays mv, OutputArray dst);  
//
//      여러개의 단일 채널 입력 mv를 다중 채널 출력 dst행렬로 만듬.
//	mv : 입력으로 행렬들의 벡터 또는 배열
//	dst의 채널수는 mv의 채널수와 같음.
//
//
// void split(const Mat& src, Mat* mvbegin);  
// void split(InputArray m, OutputArrayOfArrays mv);  
//
//      다중채널의 입력 행렬 src 또는 m을 1차원 행렬을 배열 mvbegin 또는 행렬의 벡터인 출력 mv로 분리함.


#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg"); // BGR-Color
	if (srcImage.empty())
		return -1;

	vector<Mat> planes;   // Mat 행렬의 벡터 planes 선언
	split(srcImage, planes);   // srcImage 컬러 영상의 채널을 분리해 planes에 저장
	// 다중채널 srcImage를 1차원 행렬의 배열 또는 행렬의 벡터로 출력함.

//	imshow("srcImage", srcImage);
	imshow("planes[0]", planes[0]); //Blue
	imshow("planes[1]", planes[1]); //Green
	imshow("planes[2]", planes[2]); //Red

	//	planes[0] = 0;     // planes[0]의 모든 화소를 0으로 설정
	//	Mat dstImage(srcImage.rows, srcImage.cols, srcImage.type());
	Mat dstImage;
	merge(planes, dstImage);
	// planes와 같은 여러개의 단일 채널 입력을 다중채널 출력 dstImage로 만듬.
	// 여러개의 단일 채널 입력은 행렬들의 벡터 또는 배열이어야 하며
	// 입력돠 출력은 모두 같은 깊이, 크기를 가져야 함.  

	imshow("dstImage", dstImage);

	waitKey();

	return 0;
}
