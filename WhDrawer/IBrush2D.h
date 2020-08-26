#pragma once
#include "Color.h"

/// <summary>
/// 定义二维画刷，指定平面的填充方式。
/// </summary>
struct IBrush2D
{
	/// <summary>
	/// <para>点颜色迭代。</para>
	/// <para>说明：该函数指定了比率点的颜色。比率点即当前绘制任务进度下需要绘制的点。实现该接口方法可关注任务进度率，也可关注迭代次数。</para>
	/// </summary>
	/// <param name="rate_x">水平（列）任务进度率，范围在[0, 1]的浮点数。</param>
	/// <param name="rate_y">垂直（行）任务进度率，范围在[0, 1]的浮点数。</param>
	/// <returns></returns>
	virtual Color PixelIteration(float rate_x, float rate_y) = 0;
};