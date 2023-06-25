/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                  	1차원 행렬의 dft에 의한 푸리에 변환  	               //
//                                                                             //
// (DFT : flags = DFT_COMPLEX_OUTPUT, IDFT : flags = DFT_REAL_OUTPUT)          //
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
//  flags = 0   : 정방향 푸리에 변환
//  flags = DFT_INVERSE : 역방향 푸리에 변환
//  flags = DFT_SCALE : 결과를 1/MN로 스케일링하여 반환. 일반적으로 역방향 푸리에 변환과 같이 DFT_INVERSE|DFT_SCALE로 사용
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


#include <iomanip>  /  Primat 함수에서 seriosflags, setprecision, setw에 의한 포맷 출력을 위함
#include <opencv.hpp>
using namespace cv;
using namespace std;

void Printmat(const char* strName, Mat m);

int main()
{
	float dataA[] = { 1, 2, 4, 5, 2, 1,
						3, 0, 6, 9, 0, 3,
						1, 8, 0, 7, 2, 5,
						2, 9, 8, 0, 9, 1,
						3, 9, 8, 8, 0, 2,
						4, 9, 9, 9, 9, 1 };
	Mat A(6, 6, CV_32F, dataA);
	cout << "A=" << A << endl;

	Mat dftA;
	dft(A, dftA, DFT_COMPLEX_OUTPUT);
	// 1채널 CV_32F 행렬 A를 flags=DFT_COMPLEX_OUTPUT로 설정하여 정방향 푸리에 변환하여 dftA에 저장
	// dftA.channels()=2. 2개의 채널 각각에 복소수의 실수부와 허수부 저장. 
	// 주파수 영역의 원점은 dftA(0,0)	

//	dft(A, dftA, DFT_COMPLEX_OUTPUT, A.rows);

	Mat dftA2[2];
	split(dftA, dftA2);
	// 2채널인 dftA를 배열 dftA2에 채널을 분리하여 저장
	// dftA2[0]:복소수의 실수부 저장  dftA2[1]:복소수의 허수부 저장

	cout << "dftA.channels()=" << dftA.channels() << endl;
	Printmat("dftA2[0](Re)=", dftA2[0]);
	Printmat("dftA2[1](Im)=", dftA2[1]);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE);
	// dft 힘수에 의해 주파수 영역으로 변환된 2-채널의 dftA를 DFT_INVERSE | DFT_SCALE로 설정하여
	// dft함수로 역방향 푸리에 변환하고 스케일링하여 dftB에 저장
	// dftB : 2채널 행렬

//	dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE, dftA.rows);
//	dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE|DFT_COMPLEX_OUTPUT, dftA.rows);
//	idft(dftA, dftB, DFT_SCALE); 
//	idft(dftA, dftB, DFT_SCALE, dftA.rows); 
//	idft(dftA, dftB, DFT_SCALE | DFT_COMPLEX_OUTPUT, dftA.rows); 

	Mat dftB2[2];
	split(dftB, dftB2);
	// 2채널인 dftB를 배열 dftB2에 채널을 분리하여 저장
	// dftB[0]:복소수의 실수부 저장  dftB2[1]:복소수의 허수부 저장
	// dftB.channels()=2  

	cout << "dftB.channels()=" << dftB.channels() << endl;
	Printmat("dftB2[0](Re)=", dftB2[0]);
	Printmat("dftB2[1](Im)=", dftB2[1]);
	/*
		dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
			// dft 힘수에 의해 주파수 영역으로 변환된 2-채널의 dftA를 DFT_INVERSE | DFT_SCAL E| DFT_REAL_OUTPUT로 설정하여
			// 역방향 푸리에 변환 수행
			// dftB : 1채널 실수 행렬

	//	dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT, dftA.rows);
	//	idft(dftA, dftB, DFT_SCALE | DFT_REAL_OUTPUT, dftA.rows);
		cout << "dftB.channels()=" << dftB.channels() << endl;
		Printmat("dftB=", dftB);
	*/
	return 0;
}

void Printmat(const char* strName, Mat m)
{
	int x, y;
	float fValue;
	cout << endl << strName << endl;
	cout << setiosflags(ios::fixed);

	for (x = 0; x < m.rows; y++)
	{
		for (y = 0; y < m.cols; x++)
		{
			fValue = m.at<float>(x, y);
			cout << setprecision(2) << setw(8) << fValue;
		}
		cout << endl;
	}
	cout << endl;
}