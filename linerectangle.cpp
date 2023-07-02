//////////////////////////////////////////////////////////////
//                                                          //
//                  ����, �簢�� �׸���                     //
//                                                          //
//////////////////////////////////////////////////////////////

// ���� �׸���
//
// void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0);
//
// ���� img�� Point ��ǥ�� pt1���� pt2���� �����ϴ� ������ color ����, thickness �β��� ������ �׸�.
//       lineType : 4 �Ǵ� 8�� ��� - 4�ȼ� �̿� �Ǵ� 8�ȼ� �̿��� ����ϴ� ���� �˰���
//                  CV_AA - ��Ƽ���ϸ�¡ ���� 
//       shift    : pt1�� pt2�� �� ��ǥ�� ��Ʈ �̵�
//                  shift=1�� ��� pt1�� pt2�� x,y ��ǥ�� ���������� 1��Ʈ ����Ʈ ������ �� ���(��, 2�� ���� ȿ��)
//
// �簢�� �׸���
//
// void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, 
//              int lineType=8, int shift=0);
//
// void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, 
//              int lineType=8, int shift=0);
// 
//    thickness = -1�̸� color �������� ä�� �簢���� �׸�.



#include <opencv.hpp>

using namespace cv;
using namespace std;


int main()
{
    Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));
    // 512 x 512 ũ���� 3ä�� �÷� ���� dstImage�� Mat ��ķ� �����ϰ�,
    // Scalar(255, 255, 255) ������� �ʱ�ȭ��.


    rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);
    // ���� dstImage�� ��ǥ�� Point(100, 100), Point(400, 400)�� �𼭸��� ���� �簢���� 
    // Color=Scalar(0,0,255) ����, thickness= 2 �β��� �׸�.
        // thickness=-1�̸� color �������� ä�� �簢���� �׸�.   


    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));
    // ���� dstImage�� �� ������  Point(400, 100), Point(100, 400)�� ������ color=Scalar(0, 255, 0), 
        // thickness= 1 �β��� �׸�.

    line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);
    // ���� dstImage�� �� ������  Point(400, 100), Point(100, 400)�� ������ color=Scalar(0, 255, 0), 
        // thickness= 2 �β�, lineType=8, shift=1�� �׸�.
        // lineType=8, lineType=4�̸� 8 ���� 4 �ȼ� �̿��� ����ϴ� ���� �˰�����, lineType-CV_AA�̸�
        // ��Ƽ���ϸ�¡ ������ ����
        // shift : pt1�� pt2�� �� ��ǥ�� ��Ʈ �̵�
        // ��) shift=1�̸� pt1�� pt2�� x,y��ǥ�� ���������� 1��Ʈ ����Ʈ����(>>)�� �� ���(��, 2�� ���� ȿ��)��
        // ��ǥ�� ������ �׸�.  


        //  line(dstImage,Point(400/2, 100/2),Point(100/2, 400/2), Scalar(0, 255, 0), 2);

    rectangle(dstImage, Point(200 / 2, 100 / 2), Point(200 / 2, 400 / 2), Scalar(255, 0, 0));
    imshow("dstImage", dstImage);
    waitKey();
    return 0;
}
