#include "rect_spase.h"



RectSpase::RectSpase()
{
	doInit = false;
}

RectSpase::RectSpase(int width, int height, int theta_res)
{
	doInit = false;
	init(width, height, theta_res);
	hough.init(theta_res);
	doInit = true;
}

void RectSpase::init(int width, int height, int theta_res) {
	if (width < height) {
		rectspase_maxlength = height;
	}
	else {
		rectspase_maxlength = width;
	}
	RectSpase::theta_res = theta_res;
	rho_max = (int)sqrt(pow(width, 2) + pow(height, 2)); //‘ÎŠpü‚Ì’·‚³Fr^2 = x^2 + y^2
	rho_range = rho_max * 2 + 1;
	rectangles_spase = cv::Mat::zeros(height, width, CV_8UC3);
	hough_spase = cv::Mat::zeros(rho_range, theta_res, CV_16UC1);
	max_rectangles_theta_index = 0;
	max_rectangles_rho = 0;
}

void RectSpase::drawRect(cv::Rect rect, bool scale)
{
	if(scale && rectspase_maxlength > scale_threshold)
		cv::rectangle(rectangles_spase, rect, cv::Scalar(0,255,255), rectspase_maxlength/scale_threshold);
	else
		cv::rectangle(rectangles_spase, rect, cv::Scalar(0, 255, 255));
}

void RectSpase::drawRect(std::vector<cv::Rect> rects, bool scale)
{
	if (scale && rectspase_maxlength > scale_threshold) {
		for (int i = 0; i < rects.size(); i++) {
		cv::rectangle(rectangles_spase, rects[i], cv::Scalar(0, 255, 255), rectspase_maxlength / scale_threshold);
		}
	} else {
		for (int i = 0; i < rects.size(); i++) {
			cv::rectangle(rectangles_spase, rects[i], cv::Scalar(0, 255, 255));
		}
	}
}


void RectSpase::calclateLineThroughRectangle(cv::Rect rec, int theta_res)
{
	std::vector<std::vector<float>> rho(4);
	for (int v = 0; v < 4; v++) {
		rho[v].resize(theta_res, 0);
	}

	//’¸“_‚P‚ÌHough•ÏŠ·
	hough.houghTransform_Point(cv::Point(rec.x, rec.y), rho[0], theta_res, 0.0, M_PI / 2);
	//’¸“_‚R‚ÌHough•ÏŠ·
	hough.houghTransform_Point(cv::Point(rec.x + rec.width, rec.y + rec.height), rho[2], theta_res, 0.0, M_PI / 2);

	//’¸“_‚Q‚ÌHough•ÏŠ·
	hough.houghTransform_Point(cv::Point(rec.x + rec.width, rec.y), rho[1], theta_res, M_PI / 2, M_PI);
	//’¸“_‚S‚ÌHough•ÏŠ·
	hough.houghTransform_Point(cv::Point(rec.x, rec.y + rec.height), rho[3], theta_res, M_PI / 2, M_PI);

	//Hough‹óŠÔ‚Ì“h‚è‚Â‚Ô‚µ
	for (int theta_index = 0; theta_index < theta_res / 2; theta_index++) {
		for (int r = rho[0][theta_index]; r <= rho[2][theta_index]; r++) {
			hough_spase.at<unsigned short>(r + (hough_spase.rows - 1) / 2, theta_index)++;
		}
	}
	for (int theta_index = theta_res / 2; theta_index < theta_res; theta_index++) {
		for (int r = rho[1][theta_index]; r <= rho[3][theta_index]; r++) {
			hough_spase.at<unsigned short>(r + (hough_spase.rows - 1) / 2, theta_index)++;
		}
	}
}

int RectSpase::searchMaxRectanglesOnLine()
{
	int w, h, count_max = 0;
	for (w = 0; w < hough_spase.cols; w++) {
		for (h = 0; h < hough_spase.rows; h++) {
			if (hough_spase.at<unsigned short>(h, w) > count_max) {
				max_rectangles_theta_index = w;
				max_rectangles_rho = h - rho_max;
				count_max = hough_spase.at<unsigned short>(h, w);
			}
		}
	}
	return count_max;
}

void RectSpase::drawPrepareLine()
{
		cv::Point pts[2];
		double theta, x_h, y_h, left, right, bottom, top;
		int thickness, counter;
		
		theta = max_rectangles_theta_index * M_PI / theta_res;
		x_h = max_rectangles_rho * cos(theta);
		y_h = max_rectangles_rho * sin(theta);

		thickness = (rectspase_maxlength) / scale_threshold;
		counter = 0;

		if (theta == 0 || theta == M_PI) {
			pts[0].x = cv::saturate_cast<double>(x_h);
			pts[0].y = cv::saturate_cast<double>(0);
			pts[1].x = cv::saturate_cast<double>(x_h);
			pts[1].y = cv::saturate_cast<double>(rectangles_spase.rows-1);
		}
		else if (theta == M_PI/2) {
			pts[0].x = cv::saturate_cast<double>(0.0);
			pts[0].y = cv::saturate_cast<double>(y_h);
			pts[1].x = cv::saturate_cast<double>(rectangles_spase.cols - 1);
			pts[1].y = cv::saturate_cast<double>(y_h);
		}
		else {
			//•K‚¸‚Q“_’Ê‚é‚Í‚¸(Area‚ÌŽl‹÷‚Ìê‡‚à–â‘è‚È‚µ)
			bottom = x_h + y_h * tan(theta);
			top = x_h - (rectangles_spase.rows - y_h) * tan(theta);
			left = y_h + x_h / tan(theta);
			right = y_h - (rectangles_spase.cols - x_h) / tan(theta);

			if (bottom >= 0 && bottom < rectangles_spase.rows) {
				pts[counter].x = cv::saturate_cast<double>(bottom);
				pts[counter].y = cv::saturate_cast<double>(0);
				counter++;
			}
			if (top >= 0 && top < rectangles_spase.rows) {
				pts[counter].x = cv::saturate_cast<double>(top);
				pts[counter].y = cv::saturate_cast<double>(rectangles_spase.rows);
				counter++;
			}
			if (left >= 0 && left <= rectangles_spase.cols) {
				pts[counter].x = cv::saturate_cast<double>(0);
				pts[counter].y = cv::saturate_cast<double>(left);
				counter++;
			}
			if (right >= 0 && right <= rectangles_spase.cols) {
				pts[counter].x = cv::saturate_cast<double>(rectangles_spase.cols);
				pts[counter].y = cv::saturate_cast<double>(right);
				counter++;
			}
		}
		
		cv::line(rectangles_spase,pts[0], pts[1], cv::Scalar(200, 200, 0), thickness, cv::LINE_AA);

}

void RectSpase::disp(bool Normalization)
{
	int max = searchMaxRectanglesOnLine();
	float rate = 65535 / max;
	if (Normalization) {
		hough_spase *= rate;
	}
	//•\Ž¦
	cv::namedWindow("hough spase", cv::WINDOW_NORMAL);
	cv::imshow("hough spase", hough_spase);
	cv::namedWindow("rect spase", cv::WINDOW_NORMAL);
	cv::imshow("rect spase", rectangles_spase);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

RectSpase::~RectSpase()
{
}
