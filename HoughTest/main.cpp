#include <stdio.h>
#include "rect_spase.h"
#include "data_read.h"


int main()
{

	//���ɂ��ݒ�
	const int AREA_WIDTH = 10001;
	const int AREA_HEIGHT = 10001;
	//�����Őݒ�
	const int THETA_RESOLUTION = 1024; //������

	int N;
	std::vector<cv::Rect> RECTANGLE;
	//������
	DataRead reader;
	RectSpase r_spase(AREA_WIDTH, AREA_HEIGHT, THETA_RESOLUTION);


	/*------------------------------------------�f�[�^�̓ǂݍ���------------------------------------------*/
	reader.read(N, RECTANGLE);
	std::cout << "N = " << N << std::endl;

	/*------------------------------------------�v�Z------------------------------------------*/
	for (int n = 0; n < N; n++) {
		r_spase.calclateLineThroughRectangle(RECTANGLE[n], 1024);
	}
	
	/*------------------------------------------�\��------------------------------------------*/
	printf("answer = %d\n", r_spase.countMaxOnHoughSpase());
	r_spase.displayHoughSpase();

	return 0;
}