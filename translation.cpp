/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//            	행렬에서 DFT 주파수 중심을 F(M/2, N/2)로 이동                  //
//                                                                             //
// (DFT : flags = DFT_REAL_OUTPUT, IDFT : flags = DFT_REAL_OUTPUT)             //
//									       //	
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// void dft(OutputArray src, OutputArray dst, int flags-0, inr nonzeroRows=0);
//
// 1D 또는 2D 영상의 정방향 푸리에 변환(DFT) 및 역방향(inverse) 푸리에 변환(IDEF) 수행
//
// 입력 src	: 1채널로 표현되는 실수 또는 2채널로 표현되는 복소수
//		  2채널의 경우 : 채널 1에 실수부, 채널 2에 허수부가 따로 모든 u, v에 대하여 저장됨
// 출력 dst	: 크기와 자료형은 flag에 의존
//            dft 함수 내부에서 임시로 메모리를 할당해서 사용하므로 메모리 할당을 최소화하기 위하여 
//            src와 dst를 같은 행렬 또는 영상으로 사용가능		
//
//  flags = 0   : 정방향 푸리에 변환(디폴트)
//  flags = DFT_INVERSE : 역방향 푸리에 변환
//  flags = DFT_SCALE : 결과를 1/MN로 스케일링하여 반환. 일반적으로 역방향 푸리에 변환관 같이 UDFT_SCALE
//  flags = DFT_ROWS  : 각 행단위로 정방향 푸리에 변환과 역방향 푸리에 변환 사용
//  flags = DFT_COMPLEX_OUTPUT : 결과는 2채널의 복소수
//  flags = DFT_REAL_OUTPUT : 출력 행렬이 1채널의 실수 행렬

/////////////////////////////////////////////////////////////////////////////////
// void idft(OutputArray src, OutputArray dst, int flags-0, inr nonzeroRows=0);
//
// 역방향 푸리에 변환
//
// dft(src, dst, flags | DFT_INVERSE)와 같음.


/////////////////////////////////////////////////////////////////////////////////
// int getOptimalDFTSize(int vecsize);
//
// vecsize와 같거나 큰 정수 중에 DFT를 계산하기에 최적의 크기인 N을 계산하여 반환
// 대부분의 FFT 알고리즘의 최적의 크기는 N=2^n인 경우이지만, OpenCV의 dft 함수는 
// 임의의 정수 p,q,r에 대하여 N=2^pX3^qX5^r인 vecsize와 같거나 큰 정수 중에 만족하는
// 최소 정수로 계산함.



#include <iomanip>
#include <opencv.hpp>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);   // 주파수 영역의 원점 변경
// 푸리에 변환의 이동(translation/shift) 특성인 A(x,y)(-1)^(x+y)에 의한 변경
// (x+y)가 홀수인 위치에서만 부호를 반대로 변경

void Printmat(const char* strName, Mat m);

int main()
{
	float dataA[] = { 1, 2, 4, 5, 2, 1,
						3, 6, 6, 9, 0, 3,
						1, 8, 3, 7, 2, 5,
						2, 9, 8, 9, 9, 1,
						3, 9, 8, 8, 7, 2,
						4, 9, 9, 9, 9, 3 };
	Mat A(6, 6, CV_32F, dataA);
	cout << "A=" << A << endl;

	ChangeSignOddPositionInXY(A); 		// centering
	Mat dftA;
	dft(A, dftA, DFT_COMPLEX_OUTPUT);	// centering 된 영상에 대해 정방향 푸리에 변환 수행
	// dftA(3,3)dl 주파수 영역의 원점이 되어 가장 저주파가 되고, 원점에서 멀어질 수록 고주파 영역이 됨.

	Mat dftA2[2];
	split(dftA, dftA2); // dftA2[0] : 실수부		dftA2[1] : 허수부

	cout << "dftA.channels()=" << dftA.channels() << endl;  // 2채널
	Printmat("dftA2[0](Re)=", dftA2[0]);
	Printmat("dftA2[1](Im)=", dftA2[1]);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT); // 역방향 푸리에 변환
	ChangeSignOddPositionInXY(dftB); 	// centering	

	cout << "dftB.channels()=" << dftB.channels() << endl;	// 1-채널 실수 행렬
	Printmat("dftB=", dftB);

	return 0;
}

void ChangeSignOddPositionInXY(Mat& m)
{
	int x, y;
	float fValue;

	for (x = 0; x < m.rows; x++)
	{
		for (y = 0; y < m.cols; y++)
		{
			fValue = m.at<float>(x, y);
			//			if((x+y)%2==1) // odd number
			if ((x + y) % 2 == 1 && fValue != 0)
				m.at<float>(x, y) = -fValue;
		}
	}
}

void Printmat(const char* strName, Mat m)
{
	int x, y;
	float fValue;
	cout << endl << strName << endl;
	cout << setiosflags(ios::fixed);

	for (x = 0; x < m.rows; x++)
	{
		for (y = 0; y < m.cols; y++)
		{
			fValue = m.at<float>(x, y);
			cout << setprecision(2) << setw(8) << fValue;
		}
		cout << endl;
	}
	cout << endl;
}