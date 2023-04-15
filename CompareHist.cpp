/////////////////////////////////////////////////////////////////
//                                                             //
//                     히스토그램 비교                         //
//                                                             //
/////////////////////////////////////////////////////////////////

// double compareHist(InputArray H1, OutputArray H2, int method);
// 
// 2개의 히스토그램 H1과 H2를 method 방법으로 비교하여 d(H1, H2)를 반환



#include <opencv.hpp>
using namespace cv;
using namespace std;

void drawHistogram(Mat& image, Mat hist);  //히스토그램 그리기 함수
int main()
{
	Mat srcImage1 = imread("C:/my_images/Fig0228(a)(angiography_mask_image).tif", IMREAD_GRAYSCALE);
	if (srcImage1.empty())
		return -1;
	Mat srcImage2 = imread("C:/my_images/Fig0228(b)(angiography_live_ image).tif", IMREAD_GRAYSCALE);
	if (srcImage2.empty())
		return -1;

	int histSize = 256;
	float  valueRange[] = { 0, 256 };
	const  float* ranges[] = { valueRange };
	int channels = 0;
	int dims = 1;

	Mat H1;
	calcHist(&srcImage1, 1, &channels, Mat(), H1, dims, &histSize, ranges);
	normalize(H1, H1, 1, 0, NORM_L1, CV_32F);
	// 히스토그램 H1의 값이 1의 확률이 되도록 정규화
//	cout << "H1 = " << H1 << endl;

	Mat H2;
	calcHist(&srcImage2, 1, &channels, Mat(), H2, dims, &histSize, ranges);
	normalize(H2, H2, 1, 0, NORM_L1, CV_32F);
	// 히스토그램 H2의 값이 1의 확률이 되도록 정규화
//	cout << "H2 = " << H2 << endl;

	double distl = compareHist(H1, H2, HISTCMP_CORREL); //CV_COMP_CORREL방법으로 비교
	cout << "distl=" << distl << endl;

	double dist2 = compareHist(H1, H2, HISTCMP_CHISQR); //CV_COMP_CHISQR방법으로 비교
	cout << "dist2=" << dist2 << endl;

	double dist3 = compareHist(H1, H2, HISTCMP_INTERSECT); //CV_COMP_INTERSECT방법으로 비교
	cout << "dist3=" << dist3 << endl;

	double dist4 = compareHist(H1, H2, HISTCMP_BHATTACHARYYA);//CV_COMP_BHATTACHARYYA방법으로 비교
	cout << "dist4=" << dist4 << endl;

	Mat histImage1;
	drawHistogram(histImage1, H1);
	imshow("histImage1", histImage1);

	Mat histImage2;
	drawHistogram(histImage2, H2);
	imshow("histImage2", histImage2);

	//	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}

// 히스토그램 그리기 함수
void drawHistogram(Mat& image, Mat hist)
{
	if (image.empty())
		image.create(512, 512, CV_8U);

	normalize(hist, hist, 0, image.rows, NORM_MINMAX, CV_32F);

	image = Scalar(255);
	int binW = cvRound((double)image.cols / hist.rows);
	int x1, y1, x2, y2;
	for (int i = 0; i < hist.rows; i++)
	{
		x1 = i * binW;
		y1 = image.rows;
		x2 = (i + 1) * binW;
		y2 = image.rows - cvRound(hist.at<float>(i));
		rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(0), -1); // fill black
	}
}