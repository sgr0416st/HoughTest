#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "table.h"

/// <summary>
/// Hough変換とそれに関連する自作ライブラリ
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
	/// <para>与えられた点に対して原点を基準点としたHough変換を行い，その結果を返す．</para>
	/// <para>一般に，Hough変換は点 p(x, y) に対して</para>
	/// 
	/// <para>ρ = x・cos(θ) + y・sin(θ)</para>
	/// 
	/// <para>で与えられる．</para>
	/// ただし,θは（点pを通る）直線と横軸がなす角（定義域：0～π）,
	/// ρ は直線におろした垂線の長さを表す．
	/// 
	/// ここで，計算した結果は配列rhoに格納される．
	/// </summary>
	/// <param name="p">hough変換を行う点</param>
	/// <param name="hough_spase">計算結果</param>
	/// <param name="theta_res">変換時の角度分解能(距離分解能は１固定)</param>
	/// <param name="theta_min">角度の下限値．デフォルトは０</param>
	/// <param name="theta_max">角度の上限値．デフォルトはπ</param>
	void houghTransform_Point(cv::Point p, std::vector<float> &rho, int theta_res, float theta_min=0,float theta_max=M_PI);

	~Hough();
};

