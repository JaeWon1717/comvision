#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// 비올라 존스 알고리즘 : 결정트리를 기본 분류기로 사용, 에이더부스트를 학습시켜 얼굴 검출
// OpenCV는 얼굴 DB로 학습한 결과를 XML 파일에 담아 학습함.
//
// 얼굴 검출에 사용되는 XML 파일 : haarcascade_frontalface_alt2
// 
// 기타 : 눈 검출기(haarcascade_eye)
//        옆얼굴 검출기(haarcascade_profileface)
//        입 검출기(haarcascade_mcs_mouth) 등등
//////////////////////////////////////////////////////////////////////////////////////////////

String face_cascade = "c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml";  // 정면 얼굴 검출기

CascadeClassifier face;   // 얼굴을 검출하기 위한 CascadeClassifier 클래스 형의 변수


void FaceDetect(Mat);

int main()
{
	Mat  image = imread("../image/girl.jpg", IMREAD_COLOR);	// 얼굴 영상 로드
	CV_Assert(image.data);

	CV_Assert(face.load(face_cascade));   // 얼굴 분류기 로드 및 예외처리, 해당 XML파일을 읽어 검출할 준비

	FaceDetect(image);

	waitKey();
	return 0;
}

void FaceDetect(Mat img)
{
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);  // 명암도 영상변환 : 비올라 존스 알고리즘은 명암도 영상을 대상으로 수행됨.

	vector<Rect> face_pos;	// 얼굴 검출 결과를 표시하는 직사각형

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// void CascadeClassifier::detectMultiScale(InputArray image, CV_OUT vector<Rect>& objects, 
	//                                          double scaleFactor=1.1, int minNeighbors=3,
	//                                          int flags=0, Size minsize=Size(), Size maxSize = Size());
	// 1. 객체검출대상행렬 2. 반환되는 검출객체사각형 3. 영상 크기 감소에 대한 규정
	// 4. 이웃 후보 사각형의 개수    5.과거함수에서 사용하던 플래그
	// 6. 가능한 객체 최소 크기 : 이보다 작은 객체 무시
	// 7. 가능한 객체 최대 크기 : 이보다 큰 객체 무시
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// 첫번째 매개변수인 gray 영상에서 얼굴을 검출하여 두번째 매개변수인 Rect형의 vector에 저장
	face.detectMultiScale(gray, face_pos, 1.5, 2, 0, Size(10, 10));


	// 검출한 얼굴을 원해 컬러영상에 직사각형에 표시
	for (int i = 0; i < face_pos.size(); i++)
		rectangle(img, face_pos[i], Scalar(255, 0, 0), 2); // 얼굴 검출 사각형 그리기

	imshow("얼굴 검출", img);
}
