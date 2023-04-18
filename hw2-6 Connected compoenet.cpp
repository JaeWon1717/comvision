/*******************************************************/
/*            HW#2-6. Connected Component    */
/*  �ۼ��� : �����          ��¥ : 2023�� 4�� 17�� */
/*                                                                           */
/* ���� ���� : ����ȭ�� �̹����� �󺧸��ϴ� ����,*/
/* connectedComponentsWithStats() �Լ��� �̿��Ͽ� ����ȭ�� �̹����� �󺧸��ϰ�*/
/*�󺧸��� �̹����� img_labels ������,*/
/*�󺧸� ������ stats ������, �߽� ��ǥ�� centroids ������ ����*/
/*                - - - - - - -                                            */
/*******************************************************/

#include <opencv.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat img_gray, img_color, img_binary,img;
	img= imread("C:/my_images/logo.jpg");
	img_gray = imread("C:/my_images/logo.jpg", IMREAD_GRAYSCALE);

	//adaptiveThreshold(img_gray, img_binary, 255,ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 5);
	threshold(img_gray, img_binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	imshow("binary image", img_binary);
	cvtColor(img_gray, img_color, COLOR_GRAY2BGR);


	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
		stats, centroids, 8, CV_32S);


	//�󺧸��� �̹����� Ư�� ���� �÷��� ǥ�����ֱ�  
	for (int y = 0; y < img_labels.rows; ++y) {

		int* label = img_labels.ptr<int>(y);
		Vec3b* pixel = img_color.ptr<Vec3b>(y);


		for (int x = 0; x < img_labels.cols; ++x) {

			if (label[x] == 1) {
				pixel[x][0] = 0;
				pixel[x][1] = 30; //�⺻�� 255
				pixel[x][2] = 0;
			}
		}
	}


	//�󺧸� �� �̹����� ���� ���簢������ �ѷ��α� 
	for (int j = 1; j < numOfLables; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0); //�߽���ǥ
		int y = centroids.at<double>(j, 1);

		circle(img_color, Point(x, y), 5, Scalar(255, 0, 0), 1);

		rectangle(img_color, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);

		putText(img_color, to_string(j), Point(left + 10, top + 10),
			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
	}
	imshow("originalimage", img);
	imshow("labeled image", img_color);
	waitKey(0);
}
