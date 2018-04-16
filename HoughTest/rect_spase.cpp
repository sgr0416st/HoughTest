#include "rect_spase.h"



RectSpase::RectSpase(int theta_res)
{
	hough.init(theta_res);
}


void RectSpase::calclateLineThroughRectangle(cv::Rect rec, cv::Mat &hough_spase, int theta_res)
{
	std::vector<std::vector<float>> rho(4);
	for (int v = 0; v < 4; v++) {
		rho[v].resize(theta_res, 0);
	}

	//í∏ì_ÇPÇÃHoughïœä∑
	hough.houghTransform_Point(cv::Point(rec.x, rec.y), rho[0], theta_res, 0.0, M_PI / 2);
	//í∏ì_ÇRÇÃHoughïœä∑
	hough.houghTransform_Point(cv::Point(rec.x + rec.width, rec.y + rec.height), rho[2], theta_res, 0.0, M_PI / 2);

	//í∏ì_ÇQÇÃHoughïœä∑
	hough.houghTransform_Point(cv::Point(rec.x + rec.width, rec.y), rho[1], theta_res, M_PI / 2, M_PI);
	//í∏ì_ÇSÇÃHoughïœä∑
	hough.houghTransform_Point(cv::Point(rec.x, rec.y + rec.height), rho[3], theta_res, M_PI / 2, M_PI);

	//HoughãÛä‘ÇÃìhÇËÇ¬Ç‘Çµ
	for (int theta_index = 0; theta_index < theta_res / 2; theta_index++) {
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

int RectSpase::countMaxValue(cv::Mat & hough_spase)
{
	int w, h, count_max = 0;
	for (w = 0; w < hough_spase.cols; w++) {
		for (h = 0; h < hough_spase.rows; h++) {
			if (hough_spase.at<unsigned short>(h, w) > count_max) {
				count_max = hough_spase.at<unsigned short>(h, w);
			}
		}
	}
	return count_max;
}

void RectSpase::disp(cv::Mat &hough_spase, bool Normalization)
{

	//É^ÉCÉv cv_u16c1 ÇÃÇ›!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int max = countMaxValue(hough_spase);
	float rate = 65535 / max;
	if (Normalization) {
		hough_spase *= rate;
	}
	//ï\é¶
	cv::namedWindow("rect image", cv::WINDOW_NORMAL);
	cv::imshow("rect image", hough_spase);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

RectSpase::~RectSpase()
{
}
