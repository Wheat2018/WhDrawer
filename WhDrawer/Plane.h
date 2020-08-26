#pragma once

/// <summary>
/// 三维平面。
/// </summary>
/// <typeparam name="Ty">平面数据类型。</typeparam>
template<typename Ty>
struct Plane3D
{
	//Fields
	Ty A, B, C, D;
};

typedef Plane3D<float> Plane;
