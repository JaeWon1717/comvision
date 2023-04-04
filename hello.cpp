#include <opencv2/opencv.hpp> // openCV API를 사용하기 위한 기본 헤더파일 포함
//opencv.hpp 에 대부분의 헤더파일이 포함되어 있음
using namespace cv;
int main()
{
	Mat img;
	img = imread("C:/my_images/humming_bird.jpg");
	putText(img, "Hello, bird!", Point(60, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA, false);
	// img영상에, Hello, bird!를 써넣고, 문자를 쓸 위치는 (x=60,y=50)로 지정, 나머지 인자는 글자의 속성 지정
	rectangle(img, Rect(30, 25, 350, 30), Scalar(0, 0, 255));
	// Rect(30, 25, 350, 30) : 직사각형의 시작 위치 (x=30, y=25)와 크기 (width=350, height=30) 지정
	namedWindow("Hello"); // Hello라는 이름의 윈도우 생성
	imshow("Hello", img); // Hello라는 윈도우에 img 영상 표시
	waitKey(); // 키보드가 눌릴 때까지 대기
	return 0;
}
