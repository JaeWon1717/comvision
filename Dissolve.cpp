//////////////////////////////////////////////////////////////
//                                                          //
//                       ������ ����                        //
//                                                          //   
//////////////////////////////////////////////////////////////

#include <opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	Mat image1 = imread("C:/my_images/Fig0228(a)(angiography_mask_image).tif", IMREAD_GRAYSCALE);
	Mat image2 = imread("C:/my_images/Fig0228(b)(angiography_live_ image).tif", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.6, beta = 0.7;

	Mat add_img1 = image1 + image2;
	Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	Mat add_img3 = image1 * alpha + image2 * (1 - alpha);

	Mat add_img4, sub_img1, sub_img2;;
	addWeighted(image1, alpha, image2, beta, 0, add_img4);  // OpenCV�Լ� �̿��Ͽ� ���ϱ�

	imshow("image1", image1), imshow("image2", image2);
	imshow("add_img1", add_img1), imshow("add_img2", add_img2);
	imshow("add_img3", add_img3), imshow("add_img4", add_img4);
	waitKey(0);
}
