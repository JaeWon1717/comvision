/////////////////////////////////////////////////////////////////
//                                                             //
//             2채널 행렬의 히스토그램 역투영                  //
//                                                             //
//  역투영한 행렬에서 높은 값을 갖는 요소는 입력행렬에서 해당  //
//  위치의 화소의 값이 히스토그램의 빈도수가 높은 값임.        //
//                                                             //
/////////////////////////////////////////////////////////////////

// void calBackProject(const *Mat images, int nimages, const int* channels, 
//	        const SparseMat& hist, OutputArray backProject, const float**ranges, 
//	        double scale=1, bool uniform=true);
// 
// 히스토그램 hist 의 역투영을 backProject에 계산.
// 역투영한 행렬 backProject에서 높은 값을 갖는 요소는 입력행렬에서 해당 위치의 화소의 값이 히스토그램의 빈도수가 높은 값임.
// 역투영 행렬에 임계값을 적용하면 분할의 효과도 얻을 수 있다.
//
// calBackProject() 힘수의 대부분의 인수는 calHist() 함수의 인수와 같음.
//
// images	: 입력영상. 같은 깊이의 CV_8U 또는 CV_32F 자료형의 같은 크기를 갖는 영상의 배열
// hist		: 입력으로 사용되는 히스토그램, Mat 또는 SparseMat 자료형
// backProject	: 출력행렬. images 배열의 영상과 같은 크기, 같은 깊이를 갖는 1-채널 역투영 행렬
// ranges	: 각각 차원에서 히스토그램 빈 경계값의 배열의 배열
// scale	: 출력 역투영 행령에 적용될 스케일 값. 디폴트 scale=1


#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	uchar dataA[16] = { 0, 0,   0, 0,
					1, 1,   1, 1,
					1, 1,   1, 2,
						1, 2,   1, 3 };
	Mat A(4, 2, CV_8UC2, dataA);   // 2채널, CV_8UC2 자료형의 4 x 2 행렬 A
	cout << "A=" << A << endl;

	int    histSize[] = { 4, 4 };
	float  range1[] = { 0, 4 };
	float  range2[] = { 0, 4 };
	const  float* ranges[] = { range1, range2 };
	int channels[] = { 0, 1 };
	int dims = 2;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);  // 히스토그램 hist 생성
	// 히스토그램 계산할 입력영상=srcImage, 영상의 갯수 nimage=1,  channels[] = {0, 1},
	// mask=Mat():모든화소가 히스토그램계산에 참여, 출력히스토그램 hist, 
	// dims=2차원, histSize=빈의 갯수(4, 4), uniform=디폴트:등간격
	//  hist는 4X4 행렬
	//
	// 위 케이스에서는..
	//    hist(0,0) = 2 : 0채널과 1채널의 값이 (0,0)인 경우가 모두 2개
	//    hist(1,1) = 3 : 0채널과 1채널의 값이 (1,1)인 경우가 모두 3개
	//    hist(1,2) = 2 : 0채널과 1채널의 값이 (1,2)인 경우가 모두 2개
	//    hist(1,3) = 1 : 0채널과 1채널의 값이 (1,3)인 경우가 모두 1개
	//    나머지는 값이 없으므로 모두 0 
	cout << "hist=" << hist << endl;

	Mat backProject;
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	// 행렬 A의 히스토그램 hist를 이용하여 역투영행렬 backProject 계산

	cout << "backProject=" << backProject << endl;
	return 0;
}