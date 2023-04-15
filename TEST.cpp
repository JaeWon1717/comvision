#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 두 이미지 읽어오기
    Mat img1 = imread("C:/my_images/Fig0228(a)(angiography_mask_image).tif", IMREAD_COLOR);
    Mat img2 = imread("C:/my_images/Fig0228(b)(angiography_live_ image).tif", IMREAD_COLOR);

    // 이미지가 잘 읽어졌는지 확인
    if (img1.empty() || img2.empty())
    {
        cout << "이미지 파일을 읽을 수 없습니다." << endl;
        return -1;
    }

    // 이미지 크기가 다른 경우, 크기를 맞춰줌
    if (img1.size() != img2.size())
    {
        resize(img1, img1, img2.size(), 0, 0, INTER_LINEAR);
    }

    // 두 이미지를 비교하여 차이 이미지 생성
    Mat diff;
    absdiff(img1, img2, diff);

    // 차이 이미지를 그레이스케일로 변환
    cvtColor(diff, diff, COLOR_BGR2GRAY);

    // 임계값을 이용하여 이진화 처리
    threshold(diff, diff, 30, 255, THRESH_BINARY);

    // 결과 이미지 출력
    imshow("diff", diff);
    waitKey(0);

    return 0;
}