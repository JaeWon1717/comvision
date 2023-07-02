#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// ��ö� ���� �˰��� : ����Ʈ���� �⺻ �з���� ���, ���̴��ν�Ʈ�� �н����� �� ����
// OpenCV�� �� DB�� �н��� ����� XML ���Ͽ� ��� �н���.
//
// �� ���⿡ ���Ǵ� XML ���� : haarcascade_frontalface_alt2
// �� ���⿡ ���Ǵ� XML ���� : haarcascade_eye
// 
// ��Ÿ : ���� �����(haarcascade_profileface)
//        �� �����(haarcascade_mcs_mouth) ���
//////////////////////////////////////////////////////////////////////////////////////////////

String face_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";  // ���� �� �����
String eye_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_eye.xml";  // �� �����	

CascadeClassifier face;   // ���� �����ϱ� ���� CascadeClassifier Ŭ���� ���� ����
CascadeClassifier eye;    // ���� �����ϱ� ���� CascadeClassifier Ŭ���� ���� ����


void FaceAndEyeDetect(Mat);

int main()
{
	Mat  image = imread("../image/girl.jpg", IMREAD_COLOR);	// �� ���� �ε�
	CV_Assert(image.data);

	CV_Assert(face.load(face_cascade));   // �� �з��� �ε� �� ����ó��, �ش� XML������ �о� ������ �غ�
	CV_Assert(eye.load(eye_cascade));     // �� �з��� �ε� �� ����ó��

	FaceAndEyeDetect(image);

	waitKey();
	return 0;
}

void FaceAndEyeDetect(Mat img)
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
	face.detectMultiScale(gray, face_pos, 1.1, 2, 0, Size(10, 10));


	// ������ ���� ���� �÷����� ���簢���� ǥ��
	//for (int i = 0; i<face_pos.size(); i++)
	//	rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // �� ���� �簢�� �׸���


	for (int i = 0; i < face_pos.size(); i++) {
		// ������ ���� ���� �÷����� ���簢���� ǥ��
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // �� ���� �簢�� �׸���

		// �� ������ ���Ͽ� �� ����
		vector<Rect> eye_pos;                   // ������ �� ������ �����ϴ� Rect ���� vector   
		Mat roi = gray(face_pos[i]);            // �� ������ ROI�� ����

		eye.detectMultiScale(roi, eye_pos, 1.1, 2, 0, Size(20, 20));    // �� ���� ����

		// ����� ���� �߽��� center�� ������radius�� ����� �� circle() �Լ��� �̿��Ͽ� ���� �׸�
		for (int j = 0; j < eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].x + eye_pos[j].width * 0.5, face_pos[i].y + eye_pos[j].y + eye_pos[j].height * 0.5);
			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.25);
			circle(img, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		}
	}

	imshow("�󱼰� �� ����", img);
}
