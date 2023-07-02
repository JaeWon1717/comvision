#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String face_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String eye_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_eye.xml";
CascadeClassifier face;
CascadeClassifier eye;

void FaceAndEyeDetect(Mat);

int main()
{
	VideoCapture v(0);  // �⺻���� 0�� ī�޶� ���� ���� v�� ����
	assert(v.isOpened());

	CV_Assert(face.load(face_cascade));   // �� �з��� �ε� �� ����ó��, �ش� XML������ �о� ������ �غ�
	CV_Assert(eye.load(eye_cascade));     // �� �з��� �ε� �� ����ó��


	Mat frame;     // ī�޶󿡼� �ԷµǴ� ������ �����Ͽ� ���� frame�� ����

	while (true) {
		v.read(frame);
		FaceAndEyeDetect(frame);

		if ((char)waitKey(20) == 27) break;
	}

	return 0;

}

void FaceAndEyeDetect(Mat img)
{
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);  // ��ϵ� ����ȯ : ��ö� ���� �˰����� ��ϵ� ������ ������� �����.

	vector<Rect> face_pos;	// �� ���� ����� ǥ���ϴ� ���簢��

	// �� ����
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

		eye.detectMultiScale(roi, eye_pos, 1.1, 2, 0, Size(10, 10));    // �� ���� ����

		// ����� ���� �߽��� center�� ������radius�� ����� �� circle() �Լ��� �̿��Ͽ� ���� �׸�
		for (int j = 0; j < eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].x + eye_pos[j].width * 0.5, face_pos[i].y + eye_pos[j].y + eye_pos[j].height * 0.5);
			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.25);
			circle(img, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		}
	}

	imshow("�󱼰� �� ����", img);
}
