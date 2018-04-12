#pragma once
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <opencv2/opencv.hpp>


int main() {
	//--------------------------------------パラメータ--------------------------------------
	//問題による設定
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

	//自分で設定
	const int RHO_MAX = sqrt(pow(AREA_WIDTH, 2) + pow(AREA_HEIGHT, 2)); //対角線の長さ：r^2 = x^2 + y^2
	const int THETA_MAX = 1024; //偶数で
	const float PIK = M_PI / (float)THETA_MAX;

	//--------------------------------------テーブル--------------------------------------
	//三角関数テーブル（サイン）
	float sn[THETA_MAX];
	//三角関数テーブル（コサイン）
	float cs[THETA_MAX];
	//半径計算用斜線長テーブル
	std::vector < std::vector<short> > diagonal;
	diagonal.resize(AREA_HEIGHT);		// ()内の数字が要素数になる
	for (int i = 0; i<AREA_HEIGHT; i++) {
		diagonal[i].resize(AREA_WIDTH);
	}


	//--------------------------------------初期化・設定--------------------------------------
	//三角関数テーブルを作成
	for (int i = 0; i<THETA_MAX; i++) {
		sn[i] = (float)sin(PIK*i);
		cs[i] = (float)cos(PIK*i);
	}

#if 0
	//斜線長テーブルを作成
	for (int y = 0; y < AREA_HEIGHT; y++)
		for (int x = 0; x < AREA_WIDTH; x++)
			diagonal[y][x] = (short)(sqrt(y*y + x*x) + 0.5);
#endif // 0

	// ---------------------- Hough変換 --------------------------

	int theta, rho, rho_high, rho_low;
	//hough空間
	//int hough_spase[THETA_MAX][RHO_MAX];
	std::vector < std::vector<short> > hough_spase;
	hough_spase.resize(THETA_MAX);		// ()内の数字が要素数になる
	for (int i = 0; i<THETA_MAX; i++) {
		hough_spase[i].resize(RHO_MAX*2);
	}

	// 1.ハフ変換
	for (int n = 0; n < N; n++) {

		for (theta = 0; theta < (THETA_MAX / 2); theta++) {
			//頂点１のHough変換
			rho_low = (int)(RECTANGLE[n][0] * cs[theta] + RECTANGLE[n][1] * sn[theta] + 0.5);
			//頂点3のHough変換
			rho_high = (int)((RECTANGLE[n][0] + RECTANGLE[n][2]) * cs[theta] + (RECTANGLE[n][1] + RECTANGLE[n][3]) * sn[theta] + 0.5);
			//theta = theta[i] の時，Hough空間上で rho[x1] <=  rho[x] <=  rho[x3]　となる点xを塗りつぶす
			//逆に，これを満たす直線（rho, theta）は必ずこの長方形内部を通過する
			for (rho = rho_low; rho <= rho_high; rho++) {
				hough_spase[theta][rho + RHO_MAX]++;
			}
		}
		
		for (theta = (THETA_MAX / 2); theta< THETA_MAX; theta++) {
			//頂点2のHough変換
			rho_low = (int)((RECTANGLE[n][0] + RECTANGLE[n][2]) * cs[theta] + RECTANGLE[n][1] * sn[theta] + 0.5);
			//頂点4のHough変換
			rho_high = (int)(RECTANGLE[n][0] * cs[theta] + (RECTANGLE[n][1] + RECTANGLE[n][3]) * sn[theta] + 0.5);
			//theta = theta[i] の時，Hough空間上で rho[x2] <=  rho[x] <=  rho[x4]　となる点xを塗りつぶす
			//逆に，これを満たす直線（rho, theta）は必ずこの長方形内部を通過する
			for (rho = rho_low; rho <= rho_high; rho++) {
				hough_spase[theta][rho + RHO_MAX]++;
			}
		}
	}

	//開票
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

