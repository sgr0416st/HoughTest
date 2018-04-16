#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

/// <summary>
/// 三角関数のテーブルを作成・保持するクラス．高速化のため．
/// なくてもよい．
/// </summary>
class Table
{
private:
	bool doInit;
	//三角関数のテーブル
	float *sn, *cs;


public:
	Table();
	Table(int theta_res);
	void init(int theta_res);

	float cos_t(int theta);
	float sin_t(int theta);

	~Table();
};

