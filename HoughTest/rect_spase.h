#pragma once

#include <opencv2/opencv.hpp>
#include "hough.h""

class RectSpase
{
private:
	bool doInit;
	Hough hough;
	cv::Mat hough_spase;
	int rho_max;
	int rho_range;

public:
	RectSpase();
	RectSpase(int width, int height, int theta_res);

	void init(int width, int height, int theta_res);

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
	void calclateLineThroughRectangle(cv::Rect rec, int theta_res);

	/// <summary>
	/// �^����ꂽ��Ԃōł��傫�Ȑ��������l�𒊏o���C�����Ԃ��D
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <returns></returns>
	int countMaxOnHoughSpase();

	/// <summary>
	/// Hough��Ԃ�\������D
	/// �f�t�H���g�ł͍ł��傫���������K�������D
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <param name="Normalization"></param>
	void displayHoughSpase(bool Normalization = true);

	~RectSpase();
};

