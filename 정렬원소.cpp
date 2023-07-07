//////////////////////////////////////////////////////////////
//                                                          //
//                   정렬 원소 원본 좌표 반환               //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat_<uchar> m1(3, 5);
	m1 << 21, 15, 10, 9, 14,               // Mat_행렬 초기화
		6, 10, 15, 9, 7,
		7, 12, 8, 14, 1;

	Mat  m_sort_idx1, m_sort_idx2, m_sort_idx3;

	sortIdx(m1, m_sort_idx1, SORT_EVERY_ROW);     // 정렬 원소의 원본 좌표. 
	// 행단위 오름차순
	sortIdx(m1, m_sort_idx2, SORT_EVERY_COLUMN);  // 열단위 오름차순

	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m_sort_idx1] = " << endl << m_sort_idx1 << endl << endl;
	cout << "[m_sort_idx2] = " << endl << m_sort_idx2 << endl << endl;


	return 0;
}