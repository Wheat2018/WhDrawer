#pragma once

struct Size
{
	//Fields
	size_t width, height;
};

template<typename Ty>
struct Point2D
{
	//Fields
	Ty x, y;
};

/// <summary>
/// 二维整型点。
/// </summary>
typedef Point2D<int> Point;
/// <summary>
/// 二维点。
/// </summary>
typedef Point2D<float> PointF;

template<typename Ty> using Vector2D = Point2D<Ty>;
/// <summary>
/// 二维整型向量。
/// </summary>
typedef Vector2D<int> Vector;
/// <summary>
/// 二维向量。
/// </summary>
typedef Vector2D<float> VectorF;

template<typename Ty>
struct Point3D
{
	//Fields
	Ty x, y, z;

};

/// <summary>
/// 三维整型点。
/// </summary>
typedef Point3D<int> Point3;
/// <summary>
/// 三维点。
/// </summary>
typedef Point3D<float> Point3F;

template<typename Ty> using Vector3D = Point3D<Ty>;
/// <summary>
/// 三维整型向量。
/// </summary>
typedef Vector3D<int> Vector3;
/// <summary>
/// 三维向量。
/// </summary>
typedef Vector3D<float> Vector3F;
