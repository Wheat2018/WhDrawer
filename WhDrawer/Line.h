#pragma once
#include "Point.h"

/// <summary>
/// ��άֱ�ߡ�
/// </summary>
/// <typeparam name="Ty">ֱ���������͡�</typeparam>
template<typename Ty>
struct Line2D
{
	//Fields
	Ty A, B, C;
};

typedef Line2D<float> Line;

/// <summary>
/// ��άֱ�ߡ�
/// </summary>
/// <typeparam name="Ty">ֱ���������͡�</typeparam>
template<typename Ty>
struct Line3D
{
	//Fields
	/// <summary>
	/// ֱ���ϵĶ��㡣
	/// </summary>
	Point3D<Ty> fixed;

	/// <summary>
	/// ֱ�ߵķ���������
	/// </summary>
	Vector3D<Ty> direction;
};

typedef Line3D<float> Line3;
