//////////////////////////////////////////////////////////////
//                                                          //
//                      라벨링 영상                         //
//                                                          //   
//////////////////////////////////////////////////////////////

#include <opencv.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat img_gray, img_color, img_binary;

	img_gray = imread("../image/logo.jpg", IMREAD_GRAYSCALE);

	//adaptiveThreshold(img_gray, img_binary, 255,ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 5);
	threshold(img_gray, img_binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	imshow("binary image", img_binary);
	cvtColor(img_gray, img_color, COLOR_GRAY2BGR);


	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
		stats, centroids, 8, CV_32S);


	//라벨링된 이미지중 특정 라벨을 컬러로 표현해주기  
	for (int y = 0; y < img_labels.rows; ++y) {

		int* label = img_labels.ptr<int>(y);
		Vec3b* pixel = img_color.ptr<Vec3b>(y);


		for (int x = 0; x < img_labels.cols; ++x) {

			if (label[x] == 1) {
				pixel[x][0] = 0;
				pixel[x][1] = 255;
				pixel[x][2] = 0;
			}
		}
	}


	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
	for (int j = 1; j < numOfLables; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0); //중심좌표
		int y = centroids.at<double>(j, 1);

		circle(img_color, Point(x, y), 5, Scalar(255, 0, 0), 1);

		rectangle(img_color, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);

		putText(img_color, to_string(j), Point(left + 10, top + 10),
			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
	}

	imshow("labeled image", img_color);
	waitKey(0);
}
