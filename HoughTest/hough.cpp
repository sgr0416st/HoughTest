#include "hough.h"

Hough::Hough()
{
}

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


void Hough::houghTransform_Point(cv::Point p, std::vector<float> &rho, int theta_res, float theta_min, float theta_max)
{
	double theta, theta_unit;
	int theta_index;
	if (!doInit) {
		init(theta_res);
	}

	theta_unit = M_PI / theta_res;
	theta_index = theta_min / M_PI * theta_res;

	//Hough�ϊ�
	for (theta = theta_min; theta < theta_max && theta_index < theta_res; theta+=theta_unit, theta_index++) {
		rho[theta_index] = (int)(p.x * table.cos_t(theta_index) + p.y * table.sin_t(theta_index) + 0.5);
	}
}

Hough::~Hough()
{

}
