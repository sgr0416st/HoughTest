#pragma once

#include <opencv2/opencv.hpp>
#include <Math.h>

#include "hough.h""

class RectSpase
{
private:
	const int scale_threshold = 500;
	bool doInit;
	Hough hough;
	cv::Mat hough_spase, rectangles_spase;
	int theta_res, rho_max, rho_range, rectspase_maxlength, max_rectangles_rho, max_rectangles_theta_index;

public:
	RectSpase();
	RectSpase(int width, int height, int theta_res);

	void init(int width, int height, int theta_res);

	/// <summary>
	/// 長方形空間に長方形を描画する．
	/// </summary>
	/// <param name="">描画する長方形</param>
	void drawRect(cv::Rect rect, bool scale = true);
	/// <summary>
	/// 長方形空間に長方形を描画する．
	/// </summary>
	/// <param name=""></param>
	void drawRect(std::vector<cv::Rect> rects, bool scale = true);

	/// <summary>
	/// <para>ある長方形を通る直線の集合をhough変換を用いて計算し，その結果をHough空間上に記憶する．</para>
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
	/// <para>該当領域をHough空間上でインクリメントする．</para>
	/// </summary>
	/// <param name="rec">任意の長方形．この長方形を通る直線を計算する</param>
	/// <param name="theta_res">角度分解能</param>
	void calclateLineThroughRectangle(cv::Rect rec, int theta_res);

	/// <summary>
	/// 与えられた空間で最も大きな数を示す座標を記憶し，その値を返す．
	/// </summary>
	/// <returns>最も大きな値</returns>
	int searchMaxRectanglesOnLine();

	/// <summary>
	/// 保持している長方形空間において，最も多くの長方形を通る直線のうち１つを描画する．
	/// この関数は実行前に必ず searchMaxRectanglesOnLine()　を実行していなければならない．
	/// </summary>
	void drawPrepareLine();

	/// <summary>
	/// Hough空間を表示する．
	/// デフォルトでは最も大きい所が正規化される．
	/// </summary>
	/// <param name="Normalization">空間の最大値をMAXに正規化する場合はtrue,それ以外はfalse．</param>
	void disp(bool Normalization = true);

	~RectSpase();
};

