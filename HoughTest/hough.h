#pragma once

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "table.h"

using namespace cv;

/// <summary>
/// Hough変換とそれに関連する自作ライブラリ
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
	void houghTransform_Point(Point p, std::vector<float> &rho, int theta_res, float theta_min=0,float theta_max=M_PI);

	/// <summary>
	/// <para>ある長方形を通る直線の集合をhough変換を用いて計算し，その結果をHough空間上に表現する．</para>
	/// <para>ユークリッド空間上に存在する長方形に対して，頂点を原点に近い点を基準として時計回りにv1,v2,v3,v4とすると，</para>
	/// <para> </para>
	/// <para>(i) 0 &lt;θ&lt;π/2 を満たす∀θにおいて，</para>
	/// <para>この長方形を通る原点から下ろした垂線と横軸のなす角度がθとなるすべての直線は,Hough変換によって</para>
	/// <para>ρ(v1,θ) &lt;ρ(l)&lt;ρ(v3,θ)</para>
	/// <para>を満たし，逆にこの長方形を通る原点から下ろした垂線と横軸のなす角度がθとなる直線のうち，</para>
	/// <para>ρ(v1,θ) &lt;ρ(l)&lt;ρ(v3,θ)</para>
	/// <para>を満たすあらゆる直線はすべてこの長方形を通る．（必要十分条件）</para>
	/// <para> </para>
	/// <para>ただし，頂点v_に対して ρ(v_,θ_) は頂点vのHough変換後のパラメータθ=θ_でのρの値を指し，</para>
	/// <para>直線ｌ_に対してρ(l_)はその直線のHough変換後のρの値を指す．</para>
	/// <para> </para>
	/// <para>(ⅱ)π/2 &lt;θ&lt;πを満たす∀θにおいて，同様に</para>
	/// <para>この長方形を通る原点から下ろした垂線と横軸のなす角度がθとなるすべての直線は,Hough変換によって</para>
	/// <para>ρ(v2,θ) &lt;ρ(l)&lt;ρ(v4,θ)</para>
	/// <para>を満たし，逆にこの長方形を通る原点から下ろした垂線と横軸のなす角度がθとなる直線のうち，</para>
	/// <para>ρ(v2,θ) &lt;ρ(l)&lt;ρ(v4,θ)</para>
	/// <para>を満たすあらゆる直線はすべてこの長方形を通る．（必要十分条件）</para>
	/// <para> </para>
	/// <para>すなわち，この関数は長方形を通る直線の集合を</para>
	/// <para>角度分解能theta_res（距離分解能はfloat型単精度固定）で計算し,</para>
	/// <para>該当領域をHough空間上でインクリメントして返す．</para>
	/// </summary>
	/// <param name="rec">任意の長方形．この長方形を通る直線を計算する</param>
	/// <param name="hough_spase">結果を格納するHough空間</param>
	/// <param name="theta_res">角度分解能</param>
	void calclateLineThroughRectangle(Rect rec, Mat &hough_spase, int theta_res);

	/// <summary>
	/// 与えられた空間で最も大きな数を示す値を抽出し，それを返す．
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <returns></returns>
	int countMaxValue(Mat &hough_spase);

	/// <summary>
	/// Hough空間を表示する．
	/// デフォルトでは最も大きい所が正規化される．
	/// </summary>
	/// <param name="hough_spase"></param>
	/// <param name="Normalization"></param>
	void disp(Mat &hough_spase, bool Normalization=true);
	~Hough();
};

