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

	// XOR ���� ����
	double alpha = 0.5, beta = 10;
	Mat xor_img;
	bitwise_xor(image1, image2, xor_img); //XOR
	// ���� �̹��� ���� (DIFF)
	Mat diff_img;//DIFF
	absdiff(image1, image2, diff_img);
	
	// AND ���� ����
	Mat AND;//AND 
	bitwise_and(image1, image2, AND);
	Mat OR;//OR
	bitwise_or(image1, image2, OR);

	// ���ϱ� ���� (ADD)
	Mat add_img1 = image1 + image2;
	Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	Mat add_img3 = image1 * alpha + image2 * (1 - alpha);
	Mat sub_img = abs(image2  *alpha - image1 *(1-alpha));
	// ������׷� ��Ȱȭ ����
	Mat histEqA, histEqB;
	equalizeHist(image1, histEqA);
	equalizeHist(image2, histEqB);
	// �̹��� ���� ���� ���� �� ����
	Mat diff = abs(image1 - image2);
	diff = 255 - diff;
	// �� �̹����� ������׷� ���� ���� ����
	absdiff(histEqA, histEqB, diff);


	imshow("Histogram Equalization of A", histEqA);
   imshow("Histogram Equalization of B", histEqB);
	imshow("Difference between A and B", diff);
	//Mat add_img4, sub_img1, sub_img2;;
	//addWeighted(image1, alpha, image2, beta, 0, add_img4);  // OpenCV�Լ� �̿��Ͽ� ���ϱ�

  imshow("image1", image1), imshow("image2", image2);
	imshow("add_img1", add_img1);
	imshow("add_img2", add_img2);
	imshow("add_img3", add_img3);
	imshow("sub_img", sub_img);
	imshow("xor_img", xor_img);
	imshow("diff_img", diff_img);
	imshow("AND", AND);
	imshow("OR", OR);
//	imshow("add_img4", add_img4);
	waitKey(0);
}