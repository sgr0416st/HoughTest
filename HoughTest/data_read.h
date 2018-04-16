#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>


class DataRead
{
public:
	DataRead();

	/// <summary>
	/// ������Int�^���ǂ����𔻒肷��
	/// </summary>
	/// <param name="s">������</param>
	/// <returns>�^����ꂽ������Int�^�ɕϊ��\�Ȃ�true,����ȊO��false</returns>
	bool checkInt(std::string s);

	/// <summary>
	/// �ŏ��Ƀt�@�C�����^������΂��̃t�@�C������C
	/// �^�����Ȃ���ΕW�����͂���f�[�^��ǂݍ��݁C
	/// �����`�̐������� n �ɁC�e�����`�̍��W���� rect �Ɏ�荞�ށD
	/// </summary>
	/// <param name="n">�����`�̐�</param>
	/// <param name="rect">�e�����`�̍��W���</param>
	void read(int &n, std::vector<cv::Rect> &rect);

	~DataRead();
};

