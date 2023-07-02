#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// ��ö� ���� �˰��� : ����Ʈ���� �⺻ �з���� ���, ���̴��ν�Ʈ�� �н����� �� ����
// OpenCV�� �� DB�� �н��� ����� XML ���Ͽ� ��� �н���.
//
// �� ���⿡ ���Ǵ� XML ���� : haarcascade_frontalface_alt2
// 
// ��Ÿ : �� �����(haarcascade_eye)
//        ���� �����(haarcascade_profileface)
//        �� �����(haarcascade_mcs_mouth) ���
//////////////////////////////////////////////////////////////////////////////////////////////

String face_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml";  // ���� �� �����

CascadeClassifier face;   // ���� �����ϱ� ���� CascadeClassifier Ŭ���� ���� ����


void FaceDetect(Mat);

int main()
{
	Mat  image = imread("../image/girl.jpg", IMREAD_COLOR);	// �� ���� �ε�
	CV_Assert(image.data);

	CV_Assert(face.load(face_cascade));   // �� �з��� �ε� �� ����ó��, �ش� XML������ �о� ������ �غ�

	FaceDetect(image);

	waitKey();
	return 0;
}

void FaceDetect(Mat img)
{
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);  // ��ϵ� ����ȯ : ��ö� ���� �˰����� ��ϵ� ������ ������� �����.

	vector<Rect> face_pos;	// �� ���� ����� ǥ���ϴ� ���簢��

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// void CascadeClassifier::detectMultiScale(InputArray image, CV_OUT vector<Rect>& objects, 
	//                                          double scaleFactor=1.1, int minNeighbors=3,
	//                                          int flags=0, Size minsize=Size(), Size maxSize = Size());
	// 1. ��ü��������� 2. ��ȯ�Ǵ� ���ⰴü�簢�� 3. ���� ũ�� ���ҿ� ���� ����
	// 4. �̿� �ĺ� �簢���� ����    5.�����Լ����� ����ϴ� �÷���
	// 6. ������ ��ü �ּ� ũ�� : �̺��� ���� ��ü ����
	// 7. ������ ��ü �ִ� ũ�� : �̺��� ū ��ü ����
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// ù��° �Ű������� gray ���󿡼� ���� �����Ͽ� �ι�° �Ű������� Rect���� vector�� ����
	face.detectMultiScale(gray, face_pos, 1.5, 2, 0, Size(10, 10));


	// ������ ���� ���� �÷����� ���簢���� ǥ��
	for (int i = 0; i < face_pos.size(); i++)
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // �� ���� �簢�� �׸���

	imshow("�� ����", img);
}
