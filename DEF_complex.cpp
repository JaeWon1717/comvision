/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                  	1���� ����� dft�� ���� Ǫ���� ��ȯ  	               //
//                                                                             //
// (DFT : flags = DFT_COMPLEX_OUTPUT, IDFT : flags = DFT_REAL_OUTPUT)          //
//									       //	
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// void dft(OutputArray src, OutputArray dst, int flags-0, inr nonzeroRows=0);
//
// 1D �Ǵ� 2D ������ ������ Ǫ���� ��ȯ(DFT) �� ������(inverse) Ǫ���� ��ȯ(IDEF) ����
//
// �Է� src	: 1ä�η� ǥ���Ǵ� �Ǽ� �Ǵ� 2ä�η� ǥ���Ǵ� ���Ҽ�
//		  2ä���� ��� : ä�� 1�� �Ǽ���, ä�� 2�� ����ΰ� ���� ��� u, v�� ���Ͽ� �����
// ��� dst	: ũ��� �ڷ����� flag�� ����
//            dft �Լ� ���ο��� �ӽ÷� �޸𸮸� �Ҵ��ؼ� ����ϹǷ� �޸� �Ҵ��� �ּ�ȭ�ϱ� ���Ͽ� 
//            src�� dst�� ���� ��� �Ǵ� �������� ��밡��		
//
//  flags = 0   : ������ Ǫ���� ��ȯ
//  flags = DFT_INVERSE : ������ Ǫ���� ��ȯ
//  flags = DFT_SCALE : ����� 1/MN�� �����ϸ��Ͽ� ��ȯ. �Ϲ������� ������ Ǫ���� ��ȯ�� ���� DFT_INVERSE|DFT_SCALE�� ���
//  flags = DFT_ROWS  : �� ������� ������ Ǫ���� ��ȯ�� ������ Ǫ���� ��ȯ ���
//  flags = DFT_COMPLEX_OUTPUT : ����� 2ä���� ���Ҽ�
//  flags = DFT_REAL_OUTPUT : ��� ����� 1ä���� �Ǽ� ���

/////////////////////////////////////////////////////////////////////////////////
// void idft(OutputArray src, OutputArray dst, int flags-0, inr nonzeroRows=0);
//
// ������ Ǫ���� ��ȯ
//
// dft(src, dst, flags | DFT_INVERSE)�� ����.


/////////////////////////////////////////////////////////////////////////////////
// int getOptimalDFTSize(int vecsize);
//
// vecsize�� ���ų� ū ���� �߿� DFT�� ����ϱ⿡ ������ ũ���� N�� ����Ͽ� ��ȯ
// ��κ��� FFT �˰����� ������ ũ��� N=2^n�� ���������, OpenCV�� dft �Լ��� 
// ������ ���� p,q,r�� ���Ͽ� N=2^pX3^qX5^r�� vecsize�� ���ų� ū ���� �߿� �����ϴ�
// �ּ� ������ �����.


#include <iomanip>  /  Primat �Լ����� seriosflags, setprecision, setw�� ���� ���� ����� ����
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
	// 1ä�� CV_32F ��� A�� flags=DFT_COMPLEX_OUTPUT�� �����Ͽ� ������ Ǫ���� ��ȯ�Ͽ� dftA�� ����
	// dftA.channels()=2. 2���� ä�� ������ ���Ҽ��� �Ǽ��ο� ����� ����. 
	// ���ļ� ������ ������ dftA(0,0)	

//	dft(A, dftA, DFT_COMPLEX_OUTPUT, A.rows);

	Mat dftA2[2];
	split(dftA, dftA2);
	// 2ä���� dftA�� �迭 dftA2�� ä���� �и��Ͽ� ����
	// dftA2[0]:���Ҽ��� �Ǽ��� ����  dftA2[1]:���Ҽ��� ����� ����

	cout << "dftA.channels()=" << dftA.channels() << endl;
	Printmat("dftA2[0](Re)=", dftA2[0]);
	Printmat("dftA2[1](Im)=", dftA2[1]);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE);
	// dft ������ ���� ���ļ� �������� ��ȯ�� 2-ä���� dftA�� DFT_INVERSE | DFT_SCALE�� �����Ͽ�
	// dft�Լ��� ������ Ǫ���� ��ȯ�ϰ� �����ϸ��Ͽ� dftB�� ����
	// dftB : 2ä�� ���

//	dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE, dftA.rows);
//	dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE|DFT_COMPLEX_OUTPUT, dftA.rows);
//	idft(dftA, dftB, DFT_SCALE); 
//	idft(dftA, dftB, DFT_SCALE, dftA.rows); 
//	idft(dftA, dftB, DFT_SCALE | DFT_COMPLEX_OUTPUT, dftA.rows); 

	Mat dftB2[2];
	split(dftB, dftB2);
	// 2ä���� dftB�� �迭 dftB2�� ä���� �и��Ͽ� ����
	// dftB[0]:���Ҽ��� �Ǽ��� ����  dftB2[1]:���Ҽ��� ����� ����
	// dftB.channels()=2  

	cout << "dftB.channels()=" << dftB.channels() << endl;
	Printmat("dftB2[0](Re)=", dftB2[0]);
	Printmat("dftB2[1](Im)=", dftB2[1]);
	/*
		dft(dftA, dftB,  DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
			// dft ������ ���� ���ļ� �������� ��ȯ�� 2-ä���� dftA�� DFT_INVERSE | DFT_SCAL E| DFT_REAL_OUTPUT�� �����Ͽ�
			// ������ Ǫ���� ��ȯ ����
			// dftB : 1ä�� �Ǽ� ���

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