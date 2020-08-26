#pragma once
#include "Color.h"

/// <summary>
/// 提供基本绘图支持。
/// </summary>
struct IBaseDrawable
{
	//Properties
	/// <summary>
	/// 获取图面行数。
	/// </summary>
	/// <returns>无符号整型，表示图面的行数。</returns>
	virtual const size_t Rows() = 0;

	/// <summary>
	/// 获取图面列数。
	/// </summary>
	/// <returns>无符号整型，表示图面的列数。</returns>
	virtual const size_t Cols() = 0;

	//Methods
	/// <summary>
	/// 绘制点。
	/// </summary>
	/// <param name="x">横坐标（列数）。</param>
	/// <param name="y">纵坐标（行数）</param>
	/// <param name="color">点的颜色。</param>
	virtual void DrawPixel(int x, int y, Color color) = 0;

	/// <summary>
	/// 获取点颜色。
	/// </summary>
	/// <param name="x">横坐标（列数）。</param>
	/// <param name="y">纵坐标（行数）</param>
	/// <returns>点的颜色。</returns>
	virtual Color GetPixel(int x, int y) = 0;
};

