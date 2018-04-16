#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

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

