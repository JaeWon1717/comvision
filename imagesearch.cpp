#include "histo.hpp"
#include "utils.hpp"

/////////////////////////////////////////////////////////////////////////////////////
// �˻��Ϸ��� 2���� ������ ���� ������׷��� �󸶳� �������� ���Ͽ� ����˻�     //
/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Vec3i bins(30, 42, 0);
	Vec3f ranges(180, 256, 0);

	vector<Mat> DB_hists = load_histo(bins, ranges, 100);
	Mat query = query_img();

	Mat hsv, query_hist;
	cvtColor(query, hsv, COLOR_BGR2HSV);					// HSV �÷� ��ȯ
	calc_histo(hsv, query_hist, bins, ranges, 2);
	Mat hist_img = draw_histo(query_hist);

	Mat DB_similaritys = calc_similarity(query_hist, DB_hists);

	//  ���� ���絵�� �Է� �޾� �� ������ ���絵�� ū ������� �����쿡 ���
	double  sinc;
	cout << "   ���� ���絵 �Է�: ";
	cin >> sinc;
	select_view(sinc, DB_similaritys);

	imshow("image", query);
	imshow("hist_img", hist_img);
	waitKey();

	return 0;
}