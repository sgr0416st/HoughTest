#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <opencv2/opencv.hpp>


int main() {
	//--------------------------------------�p�����[�^--------------------------------------
	//���ɂ��ݒ�
	const int AREA_WIDTH = 10001;
	const int AREA_HEIGHT = 10001;

#if 0
	int N = 4;
	int RECTANGLE[4][4] = {
		{ 0 ,0 , 1, 1 },
		{ 9999 ,0 , 1, 1 },
		{ 0 ,9999 , 1, 1 },
		{ 9999 ,9999 , 1, 1 }
	};

#endif // 0

#if 1
	int N = 6;
	int RECTANGLE[6][4] = {
		{ 2 ,1 , 4, 3 },
		{ 1 ,10 , 1, 3 },
		{ 5 ,7 , 5, 4 },
		{ 8 ,8 , 3, 2 },
		{ 13 ,4 , 3, 1 },
		{ 17 ,1 , 1, 14 }
	};

#endif // 0

	//�����Őݒ�
	const int RHO_MAX = sqrt(pow(AREA_WIDTH, 2) + pow(AREA_HEIGHT, 2)); //�Ίp���̒����Fr^2 = x^2 + y^2
	const int THETA_MAX = 1024; //������
	const float PIK = M_PI / (float)THETA_MAX;

	//--------------------------------------�e�[�u��--------------------------------------
	//�O�p�֐��e�[�u���i�T�C���j
	float sn[THETA_MAX];
	//�O�p�֐��e�[�u���i�R�T�C���j
	float cs[THETA_MAX];
	//���a�v�Z�p�ΐ����e�[�u��
	std::vector < std::vector<short> > diagonal;
	diagonal.resize(AREA_HEIGHT);		// ()���̐������v�f���ɂȂ�
	for (int i = 0; i<AREA_HEIGHT; i++) {
		diagonal[i].resize(AREA_WIDTH);
	}


	//--------------------------------------�������E�ݒ�--------------------------------------
	//�O�p�֐��e�[�u�����쐬
	for (int i = 0; i<THETA_MAX; i++) {
		sn[i] = (float)sin(PIK*i);
		cs[i] = (float)cos(PIK*i);
	}

#if 0
	//�ΐ����e�[�u�����쐬
	for (int y = 0; y < AREA_HEIGHT; y++)
		for (int x = 0; x < AREA_WIDTH; x++)
			diagonal[y][x] = (short)(sqrt(y*y + x*x) + 0.5);
#endif // 0

	// ---------------------- Hough�ϊ� --------------------------

	int theta, rho, rho_high, rho_low;
	//hough���
	//int hough_spase[THETA_MAX][RHO_MAX];
	std::vector < std::vector<short> > hough_spase;
	hough_spase.resize(THETA_MAX);		// ()���̐������v�f���ɂȂ�
	for (int i = 0; i<THETA_MAX; i++) {
		hough_spase[i].resize(RHO_MAX*2);
	}

	// 1.�n�t�ϊ�
	for (int n = 0; n < N; n++) {

		for (theta = 0; theta < (THETA_MAX / 2); theta++) {
			//���_�P��Hough�ϊ�
			rho_low = (int)(RECTANGLE[n][0] * cs[theta] + RECTANGLE[n][1] * sn[theta] + 0.5);
			//���_3��Hough�ϊ�
			rho_high = (int)((RECTANGLE[n][0] + RECTANGLE[n][2]) * cs[theta] + (RECTANGLE[n][1] + RECTANGLE[n][3]) * sn[theta] + 0.5);
			//theta = theta[i] �̎��CHough��ԏ�� rho[x1] <=  rho[x] <=  rho[x3]�@�ƂȂ�_x��h��Ԃ�
			//�t�ɁC����𖞂��������irho, theta�j�͕K�����̒����`������ʉ߂���
			for (rho = rho_low; rho <= rho_high; rho++) {
				hough_spase[theta][rho + RHO_MAX]++;
			}
		}
		
		for (theta = (THETA_MAX / 2); theta< THETA_MAX; theta++) {
			//���_2��Hough�ϊ�
			rho_low = (int)((RECTANGLE[n][0] + RECTANGLE[n][2]) * cs[theta] + RECTANGLE[n][1] * sn[theta] + 0.5);
			//���_4��Hough�ϊ�
			rho_high = (int)(RECTANGLE[n][0] * cs[theta] + (RECTANGLE[n][1] + RECTANGLE[n][3]) * sn[theta] + 0.5);
			//theta = theta[i] �̎��CHough��ԏ�� rho[x2] <=  rho[x] <=  rho[x4]�@�ƂȂ�_x��h��Ԃ�
			//�t�ɁC����𖞂��������irho, theta�j�͕K�����̒����`������ʉ߂���
			for (rho = rho_low; rho <= rho_high; rho++) {
				hough_spase[theta][rho + RHO_MAX]++;
			}
		}
	}

	//�J�[
	int count_max = 0;
	for (theta = 0; theta < THETA_MAX; theta++) {
		for (rho = -RHO_MAX; rho < RHO_MAX; rho++) {
			if (count_max < hough_spase[theta][rho + RHO_MAX]) {
				count_max = hough_spase[theta][rho + RHO_MAX];
			}
		}
	}

	printf("count_max = %d", count_max);

	printf("finish");
}

