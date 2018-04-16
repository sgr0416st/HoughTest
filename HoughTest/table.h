#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

/// <summary>
/// �O�p�֐��̃e�[�u�����쐬�E�ێ�����N���X�D�������̂��߁D
/// �Ȃ��Ă��悢�D
/// </summary>
class Table
{
private:
	bool doInit;
	//�O�p�֐��̃e�[�u��
	float *sn, *cs;


public:
	Table();
	Table(int theta_res);
	void init(int theta_res);

	float cos_t(int theta);
	float sin_t(int theta);

	~Table();
};

