//////////////////////////////////////////////////////////////
//                                                          //
//                      Ʈ���� ó��                         //
//                                                          //
//////////////////////////////////////////////////////////////

// createTrackbar() : winname�� �����쿡 trackbarname�� Ʈ���� ����.
//
// void createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0,  
void* userdata = 0);
// value : Ʈ���ٰ� �����ɶ��� �����̴��� ��ġ
// count : Ʈ���� �����̴��� �ִ� ��ġ, �ּҰ��� �׻� 0.
// onChange : Ʈ���� �����̴��� ����ɶ����� �ڵ� ȣ��Ǵ� �ڵ鷯 �Լ�
//
// 
// onChange() : Ʈ���� �����̴��� ����ɶ����� �ڵ� ȣ��Ǵ� �Լ�.
//
// void onChange(int pos,void* userdata=0);
// pos : Ʈ������ �����̴� ��ġ
//
//
// getTrackbarPos() : Ʈ������ �����̴� ��ġ ��ȯ.
//
// int getTrackbarPos((const string& trackbarname, const string& winname);
// winname�� �������� trackbarname Ʈ������ �����̴� ��ġ ��ȯ
//
//
// setTrackbarPos() : Ʈ������ �����̴� ��ġ ����.
//
// int setTrackbarPos((const string& trackbarname, const string& winname, int pos);
// winname�� �������� trackbarname Ʈ������ �����̴� ��ġ�� pos�� ����.



#include <opencv.hpp>

using namespace cv;
using namespace std;

void onChange(int  pos, void* param);
// Ʈ���� �����̴��� ����ɶ����� �ڵ� ȣ��
// pos : Ʈ������ �����̴� ��ġ
// param : ����� �����μ�

int main()
{
	Mat image[2];
	image[0] = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (image[0].empty())
		return -1;
	image[1].create(image[0].size(), CV_8U);  // image[1]�� �Է¿���� ���� ũ��, 8��Ʈ 1ä�η� ������.

	//	namedWindow("image"); 
	imshow("image", image[0]);  // "image" �����쿡 image[0] �������

	int pos = 128;
	onChange(pos, (void*)image);
	// ���α׷��� �������� ����, onChange Ʈ���� �ڵ鷯 �Լ��� ȣ���ϱ� ���Ͽ� Ʈ���� �ڵ鷯 �Լ� onChangeȣ��

	createTrackbar("threshold", "image", &pos, 255, onChange, (void*)image);
	// "threshold" Ʈ���ٸ� "image" �����쿡 ����
	// Ʈ���ٰ� ������ ���� �����̴� ��ġ : pos, Ʈ���� �����̴��� �ִ���ġ�� : 255, �ּҰ��� �׻� 0
	// Ʈ���� �ڵ鷯 �Լ��� onChange �Լ��� ����(Ʈ���� �����̴��� ����� ������ �ڵ� ȣ��Ǵ� �ڵ鷯 �Լ�)
	// ����� �����ʹ� (void*)image�� ����.

	waitKey();

	return 0;
}


// trackbar callback to threshold the image gray value
void onChange(int  pos, void* param)
{
	Mat* pMat = (Mat*)param;   // ����� �������μ� param�� (Mat *)param���� ����ȯ�Ͽ� ��� ������ pMat�� ����
	Mat srcImage = Mat(pMat[0]);
	Mat dstImage = Mat(pMat[1]);

	// Direct Thresholding 
	int x, y, s, r;
	int nThreshold = pos;
	for (y = 0; y < srcImage.rows; y++)
	{
		for (x = 0; x < srcImage.cols; x++)
		{
			r = srcImage.at<uchar>(y, x);   // srcImage ������ (y,x)�� ȭ���� ���� r�� ����
			if (r > nThreshold)
				s = 255;
			else
				s = 0;
			dstImage.at<uchar>(y, x) = s;
		}
		imshow("image", dstImage);
	}
}
