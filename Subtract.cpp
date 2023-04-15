//////////////////////////////////////////////////////////////
//                                                          //
//                         »¬¼À ¿¬»ê                        //
//                                                          //
//////////////////////////////////////////////////////////////


#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
Mat image1 = imread("C:/my_images/Fig0228(a)(angiography_mask_image).tif", IMREAD_GRAYSCALE);
Mat image2 = imread("C:/my_images/Fig0228(b)(angiography_live_ image).tif", IMREAD_GRAYSCALE);
CV_Assert(!(image1.empty() || image2.empty()));

double alpha = 0.6, beta = 0.7;

Mat sub_img = abs(image2 - image1);

imshow("image1", image1), imshow("image2", image2);
imshow("sub_img", sub_img);

waitKey(0);
}

