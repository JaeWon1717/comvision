/////////////////////////////////////////////////////////////////
//                                                             //
//                     ������׷� ������                       //
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
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);   // ������׷� hist ����
	// ������׷� ����� �Է¿���=A, ������ ���� nimage=1,  channels[0]=0�� ä��,
	// mask=Mat():���ȭ�Ұ� ������׷���꿡 ����, ���������׷� hist, 
	// dims=1����, histSize=���� ���� 4��, uniform=true:���
	cout << "hist=" << hist << endl;

	Mat backProject;    // ������ ��� 
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	// ��� A�� ������׷� hist�� �̿��Ͽ� ��������� backProject ���

	cout << "backProject=" << backProject << endl;
	return 0;
}