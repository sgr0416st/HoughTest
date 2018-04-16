#include <stdio.h>
#include "rect_spase.h"
#include "data_read.h"


int main()
{

	//問題による設定
	const int AREA_WIDTH = 10001;
	const int AREA_HEIGHT = 10001;
	//自分で設定
	const int THETA_RESOLUTION = 1024; //偶数で

	int N;
	std::vector<cv::Rect> RECTANGLE;
	//初期化
	DataRead reader;
	RectSpase r_spase(AREA_WIDTH, AREA_HEIGHT, THETA_RESOLUTION);


	/*------------------------------------------データの読み込み------------------------------------------*/
	reader.read(N, RECTANGLE);
	std::cout << "N = " << N << std::endl;

	/*------------------------------------------計算------------------------------------------*/
	for (int n = 0; n < N; n++) {
		r_spase.calclateLineThroughRectangle(RECTANGLE[n], 1024);
	}
	
	/*------------------------------------------表示------------------------------------------*/
	printf("answer = %d\n", r_spase.countMaxOnHoughSpase());
	r_spase.displayHoughSpase();

	return 0;
}