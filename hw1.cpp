#include <opencv.hpp>

using namespace cv;

int main()
{
    Mat srcImage = imread("C:/my_images/Fig0309(a)(washed_out_aerial_image).tif", 0);
    Mat fImage;
    srcImage.convertTo(fImage, CV_32F);

    double powerB = 1.5;//Figure(b)와 같은 밝기를 찾기위해 수정해야하는 값 
    Mat powImageB;
    pow(fImage, powerB, powImageB);//pow함수를 사용하여 fimage에 대한 감마보정수행,결과를powimage에 저장
    normalize(powImageB, powImageB, 0, 1.0, NORM_MINMAX);   // 0~1사이로 정규화,
    
    //1보다 작은 값을사용하면 어두운 부분의 대비가 높아지고 , 1보다 큰 값을 사용하면 밝은 부분의 대비가 높아짐 
    double powerC = 2.5;//Figure(c)와 같은 밝기를 찾기위해 수정해야하는 값 
    Mat powImageC;
    pow(powImageB, powerC, powImageC);   // 모니터에 나타나는 밝기
    normalize(powImageC, powImageC, 0, 1.0, NORM_MINMAX);

    double powerD = 4.0;//Figure(d)와 같은 밝기를 찾기위해 수정해야하는 값 
    Mat powImageD;
    pow(powImageB, powerD, powImageD);
    normalize(powImageD, powImageD, 0, 1.0, NORM_MINMAX);

    Mat resizedSrc, resizedPowB, resizedPowC, resizedPowD;//이미지가 너무크므로 사이즈 조정해주기위한 변수설정

    resize(srcImage, resizedSrc, Size(srcImage.cols / 2, srcImage.rows / 2)); // 1/2로 크기 조정
    resize(powImageB, resizedPowB, Size(powImageB.cols / 2, powImageB.rows / 2)); // 1/2로 크기 조정
    resize(powImageC, resizedPowC, Size(powImageC.cols / 2, powImageC.rows / 2)); // 1/2로 크기 조정
    resize(powImageD, resizedPowD, Size(powImageD.cols / 2, powImageD.rows / 2)); // 1/2로 크기 조정


    imshow("original", resizedSrc);
    imshow("Fig3.9(B)", resizedPowB);
    imshow("Fig3.9(C)", resizedPowC);
    imshow("Fig3.9(D)", resizedPowD);

    waitKey(0);
    return 0;
}