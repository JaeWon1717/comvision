#include <opencv.hpp>

using namespace cv;

int main()
{
    Mat srcImage = imread("C:/my_images/Fig0309(a)(washed_out_aerial_image).tif", 0);
    Mat fImage;
    srcImage.convertTo(fImage, CV_32F);

    double powerB = 1.5;//Figure(b)�� ���� ��⸦ ã������ �����ؾ��ϴ� �� 
    Mat powImageB;
    pow(fImage, powerB, powImageB);//pow�Լ��� ����Ͽ� fimage�� ���� ������������,�����powimage�� ����
    normalize(powImageB, powImageB, 0, 1.0, NORM_MINMAX);   // 0~1���̷� ����ȭ,
    
    //1���� ���� ��������ϸ� ��ο� �κ��� ��� �������� , 1���� ū ���� ����ϸ� ���� �κ��� ��� ������ 
    double powerC = 2.5;//Figure(c)�� ���� ��⸦ ã������ �����ؾ��ϴ� �� 
    Mat powImageC;
    pow(powImageB, powerC, powImageC);   // ����Ϳ� ��Ÿ���� ���
    normalize(powImageC, powImageC, 0, 1.0, NORM_MINMAX);

    double powerD = 4.0;//Figure(d)�� ���� ��⸦ ã������ �����ؾ��ϴ� �� 
    Mat powImageD;
    pow(powImageB, powerD, powImageD);
    normalize(powImageD, powImageD, 0, 1.0, NORM_MINMAX);

    Mat resizedSrc, resizedPowB, resizedPowC, resizedPowD;//�̹����� �ʹ�ũ�Ƿ� ������ �������ֱ����� ��������

    resize(srcImage, resizedSrc, Size(srcImage.cols / 2, srcImage.rows / 2)); // 1/2�� ũ�� ����
    resize(powImageB, resizedPowB, Size(powImageB.cols / 2, powImageB.rows / 2)); // 1/2�� ũ�� ����
    resize(powImageC, resizedPowC, Size(powImageC.cols / 2, powImageC.rows / 2)); // 1/2�� ũ�� ����
    resize(powImageD, resizedPowD, Size(powImageD.cols / 2, powImageD.rows / 2)); // 1/2�� ũ�� ����


    imshow("original", resizedSrc);
    imshow("Fig3.9(B)", resizedPowB);
    imshow("Fig3.9(C)", resizedPowC);
    imshow("Fig3.9(D)", resizedPowD);

    waitKey(0);
    return 0;
}