#include "hough.h"


Hough::Hough(int theta_res)
{
	doInit = false;
	init(theta_res);
}


void Hough::init(int theta_res)
{
	if (!doInit) {
		table.init(theta_res);
		doInit = true;	
	}
}


void Hough::houghTransform_Point(Point p, std::vector<float> &rho, int theta_res, float theta_min, float theta_max)
{
	double theta, theta_unit;
	int theta_index;
	if (!doInit) {
		init(theta_res);
	}

	theta = theta_min;
	theta_unit = theta_max / theta_res;
	theta_index = theta_min / M_PI * theta_res;

	while(theta < theta_max) {
		//Hough変換
		rho[theta_index] = (int)(p.x * table.cos_t(theta_index) + p.y * table.sin_t(theta_index) + 0.5);
		//hough_spase.at<unsigned char>(rho + rho_range, theta_index)++;
		//debug用ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
		//hough_spase.at<char>(rho + (hough_spase.rows-1)/2, theta_index)=255;
		//printf("rho[%d]:%f\n", theta_index, rho[theta_index]);

		theta += theta_unit;
		theta_index++;
		
	}

}

void Hough::calclateLineThroughRectangle(Rect rec,Mat &hough_spase, int theta_res)
{
	std::vector<std::vector<float>> rho(4);
	for (int v = 0; v < 4; v++) {
		rho[v].resize(theta_res, 0);
	}

	//頂点１のHough変換
	Hough::houghTransform_Point(Point(rec.x, rec.y), rho[0], theta_res, 0.0, M_PI/2);
	//頂点３のHough変換
	Hough::houghTransform_Point(Point(rec.x + rec.width, rec.y + rec.height), rho[2], theta_res, 0.0, M_PI / 2);

	//頂点２のHough変換
	Hough::houghTransform_Point(Point(rec.x + rec.width, rec.y), rho[1], theta_res, M_PI / 2, M_PI);
	//頂点４のHough変換
	Hough::houghTransform_Point(Point(rec.x, rec.y + rec.height), rho[3], theta_res, M_PI / 2, M_PI);

	//Hough空間の塗りつぶし
	for (int theta_index = 0; theta_index < theta_res/2; theta_index++) {
		for (int r = rho[0][theta_index]; r <= rho[2][theta_index]; r++) {
			//hough_spase.at<unsigned char>(r + (hough_spase.rows-1)/2, theta_index)=255;
			hough_spase.at<unsigned short>(r + (hough_spase.rows - 1) / 2, theta_index)++;
		}
	}
	for (int theta_index = theta_res / 2; theta_index < theta_res; theta_index++) {
		for (int r = rho[1][theta_index]; r <= rho[3][theta_index]; r++) {
			//hough_spase.at<unsigned char>(r + (hough_spase.rows - 1) / 2, theta_index) = 255;
			hough_spase.at<unsigned short>(r + (hough_spase.rows - 1) / 2, theta_index)++;
		}
	}

}

int Hough::countMaxValue(Mat & hough_spase)
{
	int w,h,count_max = 0;
	for (w = 0; w < hough_spase.cols; w++) {
		for (h = 0; h < hough_spase.rows; h++) {
			if (hough_spase.at<unsigned short>(h, w) > count_max) {
				count_max = hough_spase.at<unsigned short>(h, w);
			}
		}
	}
	return count_max;
}

void Hough::disp(Mat &hough_spase, bool Normalization)
{

	//タイプ cv_u16c1 のみ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int max = countMaxValue(hough_spase);
	float rate = 65535 / max;
	if (Normalization) {
		hough_spase *= rate;
	}
	//表示
	cv::namedWindow("rect image", WINDOW_NORMAL);
	cv::imshow("rect image", hough_spase);
	cv::waitKey(0);
	cv::destroyAllWindows();
}


Hough::~Hough()
{

}
