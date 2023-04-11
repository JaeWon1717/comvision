/////////////////////////////////////////////////////////////////
//                                                             //
//             2ä�� ����� ������׷� ������                  //
//                                                             //
//  �������� ��Ŀ��� ���� ���� ���� ��Ҵ� �Է���Ŀ��� �ش�  //
//  ��ġ�� ȭ���� ���� ������׷��� �󵵼��� ���� ����.        //
//                                                             //
/////////////////////////////////////////////////////////////////

// void calBackProject(const *Mat images, int nimages, const int* channels, 
//	        const SparseMat& hist, OutputArray backProject, const float**ranges, 
//	        double scale=1, bool uniform=true);
// 
// ������׷� hist �� �������� backProject�� ���.
// �������� ��� backProject���� ���� ���� ���� ��Ҵ� �Է���Ŀ��� �ش� ��ġ�� ȭ���� ���� ������׷��� �󵵼��� ���� ����.
// ������ ��Ŀ� �Ӱ谪�� �����ϸ� ������ ȿ���� ���� �� �ִ�.
//
// calBackProject() ������ ��κ��� �μ��� calHist() �Լ��� �μ��� ����.
//
// images	: �Է¿���. ���� ������ CV_8U �Ǵ� CV_32F �ڷ����� ���� ũ�⸦ ���� ������ �迭
// hist		: �Է����� ���Ǵ� ������׷�, Mat �Ǵ� SparseMat �ڷ���
// backProject	: ������. images �迭�� ����� ���� ũ��, ���� ���̸� ���� 1-ä�� ������ ���
// ranges	: ���� �������� ������׷� �� ��谪�� �迭�� �迭
// scale	: ��� ������ ��ɿ� ����� ������ ��. ����Ʈ scale=1


#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	uchar dataA[16] = { 0, 0,   0, 0,
					1, 1,   1, 1,
					1, 1,   1, 2,
						1, 2,   1, 3 };
	Mat A(4, 2, CV_8UC2, dataA);   // 2ä��, CV_8UC2 �ڷ����� 4 x 2 ��� A
	cout << "A=" << A << endl;

	int    histSize[] = { 4, 4 };
	float  range1[] = { 0, 4 };
	float  range2[] = { 0, 4 };
	const  float* ranges[] = { range1, range2 };
	int channels[] = { 0, 1 };
	int dims = 2;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);  // ������׷� hist ����
	// ������׷� ����� �Է¿���=srcImage, ������ ���� nimage=1,  channels[] = {0, 1},
	// mask=Mat():���ȭ�Ұ� ������׷���꿡 ����, ���������׷� hist, 
	// dims=2����, histSize=���� ����(4, 4), uniform=����Ʈ:���
	//  hist�� 4X4 ���
	//
	// �� ���̽�������..
	//    hist(0,0) = 2 : 0ä�ΰ� 1ä���� ���� (0,0)�� ��찡 ��� 2��
	//    hist(1,1) = 3 : 0ä�ΰ� 1ä���� ���� (1,1)�� ��찡 ��� 3��
	//    hist(1,2) = 2 : 0ä�ΰ� 1ä���� ���� (1,2)�� ��찡 ��� 2��
	//    hist(1,3) = 1 : 0ä�ΰ� 1ä���� ���� (1,3)�� ��찡 ��� 1��
	//    �������� ���� �����Ƿ� ��� 0 
	cout << "hist=" << hist << endl;

	Mat backProject;
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	// ��� A�� ������׷� hist�� �̿��Ͽ� ��������� backProject ���

	cout << "backProject=" << backProject << endl;
	return 0;
}