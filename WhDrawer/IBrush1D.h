#pragma once
#include "Color.h"

/// <summary>
/// 定义一维画刷，指定线条的填充方式。
/// </summary>
struct IBrush1D
{
	//Properties
	/// <summary>
	/// 获取线条宽度。
	/// </summary>
	/// <returns>无符号整型，表示线条宽度。</returns>
	virtual const size_t LineWidth()const = 0;

	//Methods
	/// <summary>
	/// <para>点颜色迭代。</para>
	/// <para>说明：该函数指定了比率点的颜色。比率点即当前绘制任务进度下需要绘制的点。实现该接口方法可关注任务进度率，也可关注迭代次数。</para>
	/// </summary>
	/// <param name="rate">任务进度率，范围在[0, 1]的浮点数。</param>
	/// <returns></returns>
	virtual Color PixelIteration(float rate) = 0;
};