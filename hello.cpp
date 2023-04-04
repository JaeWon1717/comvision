#include <opencv2/opencv.hpp> // openCV API�� ����ϱ� ���� �⺻ ������� ����
//opencv.hpp �� ��κ��� ��������� ���ԵǾ� ����
using namespace cv;
int main()
{
	Mat img;
	img = imread("C:/my_images/humming_bird.jpg");
	putText(img, "Hello, bird!", Point(60, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA, false);
	// img����, Hello, bird!�� ��ְ�, ���ڸ� �� ��ġ�� (x=60,y=50)�� ����, ������ ���ڴ� ������ �Ӽ� ����
	rectangle(img, Rect(30, 25, 350, 30), Scalar(0, 0, 255));
	// Rect(30, 25, 350, 30) : ���簢���� ���� ��ġ (x=30, y=25)�� ũ�� (width=350, height=30) ����
	namedWindow("Hello"); // Hello��� �̸��� ������ ����
	imshow("Hello", img); // Hello��� �����쿡 img ���� ǥ��
	waitKey(); // Ű���尡 ���� ������ ���
	return 0;
}
