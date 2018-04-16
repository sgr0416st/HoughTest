#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "table.h"

using namespace cv;

/// <summary>
/// Hough�ϊ��Ƃ���Ɋ֘A���鎩�색�C�u����
/// </summary>
class Hough
{
private:
	bool doInit;
	Table table;
public:
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
	void houghTransform_Point(Point p, std::vector<float> &rho, int theta_res, float theta_min=0,float theta_max=M_PI);

	/// <summary>
	/// <para>���钷���`��ʂ钼���̏W����hough�ϊ���p���Čv�Z���C���̌��ʂ�Hough��ԏ�ɕ\������D</para>
	/// <para>���[�N���b�h��ԏ�ɑ��݂��钷���`�ɑ΂��āC���_�����_�ɋ߂��_����Ƃ��Ď��v����v1,v2,v3,v4�Ƃ���ƁC</para>
	/// <para> </para>
	/// <para>(i) 0 &lt;��&lt;��/2 �𖞂����̓Ƃɂ����āC</para>
	/// <para>���̒����`��ʂ錴�_���牺�낵�������Ɖ����̂Ȃ��p�x���ƂƂȂ邷�ׂĂ̒�����,Hough�ϊ��ɂ����</para>
	/// <para>��(v1,��) &lt;��(l)&lt;��(v3,��)</para>
	/// <para>�𖞂����C�t�ɂ��̒����`��ʂ錴�_���牺�낵�������Ɖ����̂Ȃ��p�x���ƂƂȂ钼���̂����C</para>
	/// <para>��(v1,��) &lt;��(l)&lt;��(v3,��)</para>
	/// <para>�𖞂��������钼���͂��ׂĂ��̒����`��ʂ�D�i�K�v�\�������j</para>
	/// <para> </para>
	/// <para>�������C���_v_�ɑ΂��� ��(v_,��_) �͒��_v��Hough�ϊ���̃p�����[�^��=��_�ł̃ς̒l���w���C</para>
	/// <para>������_�ɑ΂��ă�(l_)�͂��̒�����Hough�ϊ���̃ς̒l���w���D</para>
	/// <para> </para>
	/// <para>(�A)��/2 &lt;��&lt;�΂𖞂����̓Ƃɂ����āC���l��</para>
	/// <para>���̒����`��ʂ錴�_���牺�낵�������Ɖ����̂Ȃ��p�x���ƂƂȂ邷�ׂĂ̒�����,Hough�ϊ��ɂ����</para>
	/// <para>��(v2,��) &lt;��(l)&lt;��(v4,��)</para>
	/// <para>�𖞂����C�t�ɂ��̒����`��ʂ錴�_���牺�낵�������Ɖ����̂Ȃ��p�x���ƂƂȂ钼���̂����C</para>
	/// <para>��(v2,��) &lt;��(l)&lt;��(v4,��)</para>
	/// <para>�𖞂��������钼���͂��ׂĂ��̒����`��ʂ�D�i�K�v�\�������j</para>
	/// <para> </para>
	/// <para>���Ȃ킿�C���̊֐��͒����`��ʂ钼���̏W����</para>
	/// <para>�p�x����\theta_res�i��������\��float�^�P���x�Œ�j�Ōv�Z��,</para>
	/// <para>�Y���̈��Hough��ԏ�ŃC���N�������g���ĕԂ��D</para>
	/// </summary>
	/// <param name="rec">�C�ӂ̒����`�D���̒����`��ʂ钼�����v�Z����</param>
	/// <param name="hough_spase">���ʂ��i�[����Hough���</param>
	/// <param name="theta_res">�p�x����\</param>
	void calclateLineThroughRectangle(Rect rec, Mat &hough_spase, int theta_res);

	/// <summary>
	/// �^����ꂽ��Ԃōł��傫�Ȑ��������l�𒊏o���C�����Ԃ��D
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <returns></returns>
	int countMaxValue(Mat &hough_spase);

	/// <summary>
	/// Hough��Ԃ�\������D
	/// �f�t�H���g�ł͍ł��傫���������K�������D
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <param name="Normalization"></param>
	void disp(Mat &hough_spase, bool Normalization=true);
	~Hough();
};

