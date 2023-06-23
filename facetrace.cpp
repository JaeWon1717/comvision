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
	VideoCapture v(0);  // 기본값인 0번 카메라를 열어 변수 v에 저장
	assert(v.isOpened());

	CV_Assert(face.load(face_cascade));   // 얼굴 분류기 로드 및 예외처리, 해당 XML파일을 읽어 검출할 준비
	CV_Assert(eye.load(eye_cascade));     // 눈 분류기 로드 및 예외처리


	Mat frame;     // 카메라에서 입력되는 영상을 추출하여 변수 frame에 저장

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
	cvtColor(img, gray, COLOR_BGR2GRAY);  // 명암도 영상변환 : 비올라 존스 알고리즘은 명암도 영상을 대상으로 수행됨.

	vector<Rect> face_pos;	// 얼굴 검출 결과를 표시하는 직사각형

	// 얼굴 검출
	face.detectMultiScale(gray, face_pos, 1.1, 2, 0, Size(10, 10));


	// 검출한 얼굴을 원해 컬러영상에 직사각형에 표시
	//for (int i = 0; i<face_pos.size(); i++)
	//	rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // 얼굴 검출 사각형 그리기


	for (int i = 0; i < face_pos.size(); i++) {
		// 검출한 얼굴을 원해 컬러영상에 직사각형에 표시
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // 얼굴 검출 사각형 그리기

		// 얼굴 각각에 대하여 눈 검출
		vector<Rect> eye_pos;                   // 검출한 눈 영역을 저장하는 Rect 형의 vector   
		Mat roi = gray(face_pos[i]);            // 얼굴 영역을 ROI로 지정

		eye.detectMultiScale(roi, eye_pos, 1.1, 2, 0, Size(10, 10));    // 눈 검출 수행

		// 검출된 눈의 중심인 center와 반지름radius를 계산한 후 circle() 함수를 이용하여 눈을 그림
		for (int j = 0; j < eye_pos.size(); j++) {
			Point center(face_pos[i].x + eye_pos[j].x + eye_pos[j].width * 0.5, face_pos[i].y + eye_pos[j].y + eye_pos[j].height * 0.5);
			int radius = cvRound((eye_pos[j].width + eye_pos[j].height) * 0.25);
			circle(img, center, radius, Scalar(0, 0, 255), 2, 8, 0);
		}
	}

	imshow("얼굴과 눈 검출", img);
}
