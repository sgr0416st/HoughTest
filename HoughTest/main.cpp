#include <stdio.h>
#include "hough.h"
#include "data_read.h"


int main()
{

	//���ɂ��ݒ�
	const int AREA_WIDTH = 10001;
	const int AREA_HEIGHT = 10001;

	//�����Őݒ�
	const int RHO_MAX = sqrt(pow(AREA_WIDTH, 2) + pow(AREA_HEIGHT, 2)); //�Ίp���̒����Fr^2 = x^2 + y^2
	const int RHO_RANGE = RHO_MAX * 2 + 1;
	const int THETA_RESOLUTION = 1024; //������

	int N;
	std::vector<cv::Rect> RECTANGLE;
	DataRead reader;

	//������
	Mat hough_spase = Mat::zeros(RHO_RANGE, THETA_RESOLUTION, CV_16UC1);
	Hough hough(THETA_RESOLUTION);

	/*------------------------------------------�f�[�^�̓ǂݍ���------------------------------------------*/
	reader.read(N, RECTANGLE);
	std::cout << "N = " << N << std::endl;

	/*------------------------------------------�v�Z------------------------------------------*/
	for (int n = 0; n < N; n++) {
		hough.calclateLineThroughRectangle(RECTANGLE[n], hough_spase, 1024);
	}
	
	/*------------------------------------------�\���i�J�����j------------------------------------------*/
	printf("answer = %d\n", hough.countMaxValue(hough_spase));
	hough.disp(hough_spase);

	return 0;
}