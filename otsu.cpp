//////////////////////////////////////////////////////////////
//                                                          //
//                        감마 조절                         //
//                                                          //
//      지수의 값에 의해 다양하게 입력영상을 변환           //
//                                                          // 
//                   s= T(r) = (r)^p                        //
//                                                          //   
//////////////////////////////////////////////////////////////

// p=1 : 입력 r과 s가 동일
// p<1 : 로그변환과 유사
// p>1 : 역로그(inverse log) 변환과 유사


#include <opencv.hpp>

using namespace cv;


void main()
{
	Mat srcImage = imread("C:/my_images/Fig0309(a)(washed_out_aerial_image).tif", 0);
	Mat fImage;
	srcImage.convertTo(fImage, CV_32F);

	double power = 0.4;  // 0.4 = 1/2.5

	Mat powImage;
	pow(fImage, power, powImage);
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);   // 0~1사이로 정규화


	double power1 = 2.5;
	Mat powImage1;
	pow(powImage, power1, powImage1);   // 모니터에 나타나는 밝기

	normalize(powImage1, powImage1, 0, 1.0, NORM_MINMAX);

	imshow("src", srcImage);
	imshow("pow", powImage);
	imshow("pow1", powImage1);

	waitKey(0);
} 