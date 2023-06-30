#include "histo.hpp"
#include "utils.hpp"

/////////////////////////////////////////////////////////////////////////////////////
// 검색하려는 2개의 영상의 색상 히스토그램이 얼마나 유사한지 비교하여 영상검색     //
/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Vec3i bins(30, 42, 0);
	Vec3f ranges(180, 256, 0);

	vector<Mat> DB_hists = load_histo(bins, ranges, 100);
	Mat query = query_img();

	Mat hsv, query_hist;
	cvtColor(query, hsv, COLOR_BGR2HSV);					// HSV 컬러 변환
	calc_histo(hsv, query_hist, bins, ranges, 2);
	Mat hist_img = draw_histo(query_hist);

	Mat DB_similaritys = calc_similarity(query_hist, DB_hists);

	//  기준 유사도를 입력 받아 이 값보다 유사도가 큰 영상들을 윈도우에 출력
	double  sinc;
	cout << "   기준 유사도 입력: ";
	cin >> sinc;
	select_view(sinc, DB_similaritys);

	imshow("image", query);
	imshow("hist_img", hist_img);
	waitKey();

	return 0;
}