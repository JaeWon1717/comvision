//////////////////////////////////////////////////////////////
//                                                          //
//                  직선, 사각형 그리기                     //
//                                                          //
//////////////////////////////////////////////////////////////

// 직선 그리기
//
// void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0);
//
// 영상 img에 Point 좌표점 pt1에서 pt2까지 연결하는 라인을 color 색상, thickness 두께로 라인을 그림.
//       lineType : 4 또는 8의 경우 - 4픽셀 이웃 또는 8픽셀 이웃을 사용하는 라인 알고리즘
//                  CV_AA - 안티에일리징 라인 
//       shift    : pt1과 pt2의 각 좌표의 비트 이동
//                  shift=1인 경우 pt1과 pt2의 x,y 좌표를 오른쪽으로 1비트 시프트 연산을 한 결과(즉, 2로 나눈 효과)
//
// 사각형 그리기
//
// void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, 
//              int lineType=8, int shift=0);
//
// void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, 
//              int lineType=8, int shift=0);
// 
//    thickness = -1이면 color 색상으로 채운 사각형을 그림.



#include <opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
    // 512 x 512 크기의 3채널 컬러 영상 dstImage를 Mat 행렬로 생성하고,
    // Scalar(255, 255, 255) 백색으로 초기화함.


    rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);
    // 영상 dstImage에 좌표점 Point(100, 100), Point(400, 400)를 모서리로 갖는 사각형을 
    // Color=Scalar(0,0,255) 색상, thickness= 2 두께로 그림.
        // thickness=-1이면 color 색상으로 채운 사각형을 그림.   


    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));
    // 영상 dstImage에 양 끝점이  Point(400, 100), Point(100, 400)인 직선을 color=Scalar(0, 255, 0), 
        // thickness= 1 두께로 그림.

    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);
    // 영상 dstImage에 양 끝점이  Point(400, 100), Point(100, 400)인 직선을 color=Scalar(0, 255, 0), 
        // thickness= 2 두께, lineType=8, shift=1로 그림.
        // lineType=8, lineType=4이면 8 도는 4 픽셀 이웃을 사용하는 라인 알고리즘을, lineType-CV_AA이면
        // 안티에일리징 라인을 생성
        // shift : pt1과 pt2의 각 좌표의 비트 이동
        // 예) shift=1이면 pt1과 pt2의 x,y좌표를 오른쪽으로 1비트 시프트연산(>>)을 한 결과(즉, 2로 나눈 효과)의
        // 좌표에 직선을 그림.  


        //  line(dstImage,Point(400/2, 100/2),Point(100/2, 400/2), Scalar(0, 255, 0), 2);

    rectangle(dstImage, Point(200 / 2, 100 / 2), Point(200 / 2, 400 / 2), Scalar(255, 0, 0));
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
}
