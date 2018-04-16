#include <stdio.h>
#include "hough.h"
#include "data_read.h"



int main()
{
	//--------------------------------------パラメータ--------------------------------------
	//問題による設定
	const int AREA_WIDTH = 10001;
	const int AREA_HEIGHT = 10001;

#if 0
	int N = 4;
	Rect RECTANGLE[4] = {
		{ 0 ,0 , 1, 1 },
		{ 9999 ,0 , 1, 1 },
		{ 0 ,9999 , 1, 1 },
		{ 9999 ,9999 , 1, 1 }
	};
#endif
#if 0
	int N = 6;
	Rect RECTANGLE[6] = {
		{ 2 ,1 , 4, 3 },
		{ 1 ,10 , 1, 3 },
		{ 5 ,7 , 5, 4 },
		{ 8 ,8 , 3, 2 },
		{ 13 ,4 , 3, 1 },
		{ 17 ,1 , 1, 14 }
	};

#endif // 
#if 0
	int N = 6;
	Rect RECTANGLE[6] = {
		{ 1 ,1 , 9999, 9999 },
		{ 1 ,1 , 9999, 9999 },
		{ 1 ,1 , 9999, 9999 },
		{ 1 ,1 , 9999, 9999 },
		{ 1 ,1 , 9999, 9999 },
		{ 1 ,1 , 9999, 9999 }
	};

#endif // 0
	int N;
	std::vector<cv::Rect> RECTANGLE;

	DataRead reader;
	reader.read(N, RECTANGLE);

	std::cout << "N = " << N << std::endl;

	//自分で設定
	const int RHO_MAX = sqrt(pow(AREA_WIDTH, 2) + pow(AREA_HEIGHT, 2)); //対角線の長さ：r^2 = x^2 + y^2
	const int RHO_RANGE = RHO_MAX * 2 + 1;
	const int THETA_RESOLUTION = 1024; //偶数で



	Mat hough_spase = Mat::zeros(RHO_RANGE, THETA_RESOLUTION, CV_16UC1);

	Point p = { 9999 ,0 };
	//Rect r{ 0 ,0 , 1, 1 };

	Hough hough(THETA_RESOLUTION);

	for (int n = 0; n < N; n++) {
		hough.calclateLineThroughRectangle(RECTANGLE[n], hough_spase, 1024);
	}
	printf("answer = %d\n", hough.countMaxValue(hough_spase));
	
	hough.disp(hough_spase);

	return 0;
}

bool check_int(std::string str)
{
	if (std::all_of(str.cbegin(), str.cend(), isdigit))
	{
		std::cout << stoi(str) << std::endl;
		return true;
	}
	std::cout << "not int" << std::endl;
	return false;
}