#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat srcImage = imread("C:/my_images/HW4-2.jpg", IMREAD_GRAYSCALE);
    Mat dstImage45, dstImageNeg45;

    // 이미지 크기 반으로 조정
    Size newSize(srcImage.cols / 2, srcImage.rows / 2);
    resize(srcImage, srcImage, newSize);

    // -45도 방향의 대각선 엣지 검출
    Mat kernelNeg45 = (Mat_<char>(2, 2) << -1, 0, 0, 1);
    filter2D(srcImage, dstImageNeg45, CV_8U, kernelNeg45);

    // 45도 방향의 대각선 엣지 검출
    Mat kernel45 = (Mat_<char>(2, 2) << 0, -1, 1, 0);
    filter2D(srcImage, dstImage45, CV_8U, kernel45);

    // 결과 이미지를 밝게 만들기
    normalize(dstImageNeg45, dstImageNeg45, 0, 255, NORM_MINMAX);
    normalize(dstImage45, dstImage45, 0, 255, NORM_MINMAX);

    // 결과 이미지 출력
    imshow("Result (-45 degrees)", dstImageNeg45);
    imshow("Result (45 degrees)", dstImage45);
    waitKey(0);

    return 0;
}