#pragma once

/// <summary>
/// ��άƽ�档
/// </summary>
/// <typeparam name="Ty">ƽ���������͡�</typeparam>
template<typename Ty>
struct Plane3D
{
	//Fields
	Ty A, B, C, D;
};

typedef Plane3D<float> Plane;
