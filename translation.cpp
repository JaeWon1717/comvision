/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//            	��Ŀ��� DFT ���ļ� �߽��� F(M/2, N/2)�� �̵�                  //
//                                                                             //
// (DFT : flags = DFT_REAL_OUTPUT, IDFT : flags = DFT_REAL_OUTPUT)             //
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
//  flags = 0   : ������ Ǫ���� ��ȯ(����Ʈ)
//  flags = DFT_INVERSE : ������ Ǫ���� ��ȯ
//  flags = DFT_SCALE : ����� 1/MN�� �����ϸ��Ͽ� ��ȯ. �Ϲ������� ������ Ǫ���� ��ȯ�� ���� UDFT_SCALE
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



#include <iomanip>
#include <opencv.hpp>
using namespace cv;
using namespace std;

void ChangeSignOddPositionInXY(Mat& m);   // ���ļ� ������ ���� ����
// Ǫ���� ��ȯ�� �̵�(translation/shift) Ư���� A(x,y)(-1)^(x+y)�� ���� ����
// (x+y)�� Ȧ���� ��ġ������ ��ȣ�� �ݴ�� ����

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
	dft(A, dftA, DFT_COMPLEX_OUTPUT);	// centering �� ���� ���� ������ Ǫ���� ��ȯ ����
	// dftA(3,3)dl ���ļ� ������ ������ �Ǿ� ���� �����İ� �ǰ�, �������� �־��� ���� ������ ������ ��.

	Mat dftA2[2];
	split(dftA, dftA2); // dftA2[0] : �Ǽ���		dftA2[1] : �����

	cout << "dftA.channels()=" << dftA.channels() << endl;  // 2ä��
	Printmat("dftA2[0](Re)=", dftA2[0]);
	Printmat("dftA2[1](Im)=", dftA2[1]);

	Mat dftB;
	dft(dftA, dftB, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT); // ������ Ǫ���� ��ȯ
	ChangeSignOddPositionInXY(dftB); 	// centering	

	cout << "dftB.channels()=" << dftB.channels() << endl;	// 1-ä�� �Ǽ� ���
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