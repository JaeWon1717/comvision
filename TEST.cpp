#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // �� �̹��� �о����
    Mat img1 = imread("C:/my_images/Fig0228(a)(angiography_mask_image).tif", IMREAD_COLOR);
    Mat img2 = imread("C:/my_images/Fig0228(b)(angiography_live_ image).tif", IMREAD_COLOR);

    // �̹����� �� �о������� Ȯ��
    if (img1.empty() || img2.empty())
    {
        cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
        return -1;
    }

    // �̹��� ũ�Ⱑ �ٸ� ���, ũ�⸦ ������
    if (img1.size() != img2.size())
    {
        resize(img1, img1, img2.size(), 0, 0, INTER_LINEAR);
    }

    // �� �̹����� ���Ͽ� ���� �̹��� ����
    Mat diff;
    absdiff(img1, img2, diff);

    // ���� �̹����� �׷��̽����Ϸ� ��ȯ
    cvtColor(diff, diff, COLOR_BGR2GRAY);

    // �Ӱ谪�� �̿��Ͽ� ����ȭ ó��
    threshold(diff, diff, 30, 255, THRESH_BINARY);

    // ��� �̹��� ���
    imshow("diff", diff);
    waitKey(0);

    return 0;
}