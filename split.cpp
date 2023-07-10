//////////////////////////////////////////////////////////////
//                                                          //
//                    ä�� �и� �� �ռ�                     //
//                                                          //
//////////////////////////////////////////////////////////////


// void merge(const Mat*mv, size_t count, OutputArray dst);  
// void merge(InputArrayOfArrays mv, OutputArray dst);  
//
//      �������� ���� ä�� �Է� mv�� ���� ä�� ��� dst��ķ� ����.
//	mv : �Է����� ��ĵ��� ���� �Ǵ� �迭
//	dst�� ä�μ��� mv�� ä�μ��� ����.
//
//
// void split(const Mat& src, Mat* mvbegin);  
// void split(InputArray m, OutputArrayOfArrays mv);  
//
//      ����ä���� �Է� ��� src �Ǵ� m�� 1���� ����� �迭 mvbegin �Ǵ� ����� ������ ��� mv�� �и���.


#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("lena.jpg"); // BGR-Color
	if (srcImage.empty())
		return -1;

	vector<Mat> planes;   // Mat ����� ���� planes ����
	split(srcImage, planes);   // srcImage �÷� ������ ä���� �и��� planes�� ����
	// ����ä�� srcImage�� 1���� ����� �迭 �Ǵ� ����� ���ͷ� �����.

//	imshow("srcImage", srcImage);
	imshow("planes[0]", planes[0]); //Blue
	imshow("planes[1]", planes[1]); //Green
	imshow("planes[2]", planes[2]); //Red

	//	planes[0] = 0;     // planes[0]�� ��� ȭ�Ҹ� 0���� ����
	//	Mat dstImage(srcImage.rows, srcImage.cols, srcImage.type());
	Mat dstImage;
	merge(planes, dstImage);
	// planes�� ���� �������� ���� ä�� �Է��� ����ä�� ��� dstImage�� ����.
	// �������� ���� ä�� �Է��� ��ĵ��� ���� �Ǵ� �迭�̾�� �ϸ�
	// �Էµ� ����� ��� ���� ����, ũ�⸦ ������ ��.  

	imshow("dstImage", dstImage);

	waitKey();

	return 0;
}
