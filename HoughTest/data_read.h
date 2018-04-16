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
	/// 文字列がInt型かどうかを判定する
	/// </summary>
	/// <param name="s">文字列</param>
	/// <returns>与えられた文字列がInt型に変換可能ならtrue,それ以外はfalse</returns>
	bool checkInt(std::string s);

	/// <summary>
	/// 最初にファイルが与えられればそのファイルから，
	/// 与えられなければ標準入力からデータを読み込み，
	/// 長方形の数を引数 n に，各長方形の座標情報を rect に取り込む．
	/// </summary>
	/// <param name="n">長方形の数</param>
	/// <param name="rect">各長方形の座標情報</param>
	void read(int &n, std::vector<cv::Rect> &rect);

	~DataRead();
};

