#pragma once
#include "Point.h"

/// <summary>
/// 二维直线。
/// </summary>
/// <typeparam name="Ty">直线数据类型。</typeparam>
template<typename Ty>
struct Line2D
{
	//Fields
	Ty A, B, C;
};

typedef Line2D<float> Line;

/// <summary>
/// 三维直线。
/// </summary>
/// <typeparam name="Ty">直线数据类型。</typeparam>
template<typename Ty>
struct Line3D
{
	//Fields
	/// <summary>
	/// 直线上的定点。
	/// </summary>
	Point3D<Ty> fixed;

	/// <summary>
	/// 直线的方向向量。
	/// </summary>
	Vector3D<Ty> direction;
};

typedef Line3D<float> Line3;
