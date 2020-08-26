#pragma once
#include "IBaseDrawable.h"
#include "IBrush1D.h"
#include "IBrush2D.h"
#include "Point.h"

/// <summary>
/// 提供基本绘图及各类形状绘图支持。
/// </summary>
struct IShapeDrawable : public IBaseDrawable
{
	//Methods
	/// <summary>
	/// 获取基本绘图依赖。
	/// </summary>
	/// <returns>指向基本绘图实例的指针。</returns>
	virtual IBaseDrawable* BaseDrawable() = 0;

	/// <summary>
	/// 绘制线条。
	/// </summary>
	/// <param name="p1">起始点。</param>
	/// <param name="p2">终止点。</param>
	/// <param name="brush">线条填充样式。</param>
	virtual void Line(Point p1, Point p2, const IBrush1D& brush) = 0;

	/// <summary>
	/// 绘制封闭凸多边形。
	/// </summary>
	/// <param name="ps">封闭顶点集。顺时针首尾相连的顶点数组。</param>
	/// <param name="ps_num">顶点数。封闭顶点集数组长度，若不匹配可能造成越界访问。</param>
	/// <param name="brush">线条填充样式。</param>
	virtual void Polygon(Point ps[], int ps_num, const IBrush1D& brush) = 0;

	/// <summary>
	/// 绘制填充封闭凸多边形。
	/// </summary>
	/// <param name="ps">封闭顶点集。顺时针首尾相连的顶点数组。</param>
	/// <param name="ps_num">顶点数。封闭顶点集数组长度，若不匹配可能造成越界访问。</param>
	/// <param name="brush">形状面填充样式。</param>
	virtual void FillPolygon(Point ps[], int ps_num, const IBrush1D& brush) = 0;

};