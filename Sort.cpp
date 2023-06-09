//////////////////////////////////////////////////////////////
//                                                          //
//                   행렬 원소 정렬                         //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat_<uchar> m1(10, 10);
	m1 << 21, 15, 10, 9, 14,                   // Mat_ 행렬 초기화
		6, 10, 15, 9, 7,
		7, 12, 8, 14, 1;

	Mat  m_sort1, m_sort2, m_sort3;

	//std::sort() 함수와 인수구조가 동일하므로 반드시 cv::를 적어야 함.

	cv::sort(m1, m_sort1, SORT_EVERY_ROW);                      // 행단위 정렬 + 오름차순
	cv::sort(m1, m_sort2, SORT_EVERY_ROW + SORT_DESCENDING);    // 행단위 정렬 + 내림차순           
	cv::sort(m1, m_sort3, SORT_EVERY_COLUMN);                  // 열단위 정렬 + 오름차순

	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m_sort1] = " << endl << m_sort1 << endl << endl;
	cout << "[m_sort2] = " << endl << m_sort2 << endl << endl;
	cout << "[m_sort3] = " << endl << m_sort3 << endl;
	return 0;
}