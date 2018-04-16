#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "table.h"

/// <summary>
/// Hough�ϊ��Ƃ���Ɋ֘A���鎩�색�C�u����
/// </summary>
class Hough
{
private:
	bool doInit;
	Table table;
public:
	Hough();
	Hough(int theta_res);
	void init(int theta_res);

	/// <summary>
	/// <para>�^����ꂽ�_�ɑ΂��Č��_����_�Ƃ���Hough�ϊ����s���C���̌��ʂ�Ԃ��D</para>
	/// <para>��ʂɁCHough�ϊ��͓_ p(x, y) �ɑ΂���</para>
	/// 
	/// <para>�� = x�Ecos(��) + y�Esin(��)</para>
	/// 
	/// <para>�ŗ^������D</para>
	/// ������,�Ƃ́i�_p��ʂ�j�����Ɖ������Ȃ��p�i��`��F0�`�΁j,
	/// �� �͒����ɂ��낵�������̒�����\���D
	/// 
	/// �����ŁC�v�Z�������ʂ͔z��rho�Ɋi�[�����D
	/// </summary>
	/// <param name="p">hough�ϊ����s���_</param>
	/// <param name="hough_spase">�v�Z����</param>
	/// <param name="theta_res">�ϊ����̊p�x����\(��������\�͂P�Œ�)</param>
	/// <param name="theta_min">�p�x�̉����l�D�f�t�H���g�͂O</param>
	/// <param name="theta_max">�p�x�̏���l�D�f�t�H���g�̓�</param>
	void houghTransform_Point(cv::Point p, std::vector<float> &rho, int theta_res, float theta_min=0,float theta_max=M_PI);

	~Hough();
};

