/////////////////////////////////////////////////////////////////
//                                                             //
//                     히스토그램 역투영                       //
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
	uchar dataA[16] = { 0,  0,   0, 0,
					1,  1,   3, 5,
					6,  1,   1, 3,
						4,  3,   1, 7 };
	Mat A(4, 4, CV_8U, dataA);
	cout << "A=" << A << endl;

	int    histSize[] = { 4 };
	float  valueRange[] = { 0, 8 };
	const  float* ranges[] = { valueRange };
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);   // 히스토그램 hist 생성
	// 히스토그램 계산할 입력영상=A, 영상의 갯수 nimage=1,  channels[0]=0번 채널,
	// mask=Mat():모든화소가 히스토그램계산에 참여, 출력히스토그램 hist, 
	// dims=1차원, histSize=빈의 갯수 4개, uniform=true:등간격
	cout << "hist=" << hist << endl;

	Mat backProject;    // 역투영 행렬 
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	// 행렬 A의 히스토그램 hist를 이용하여 역투영행렬 backProject 계산

	cout << "backProject=" << backProject << endl;
	return 0;
}