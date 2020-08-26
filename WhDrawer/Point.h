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
/// ��ά���͵㡣
/// </summary>
typedef Point2D<int> Point;
/// <summary>
/// ��ά�㡣
/// </summary>
typedef Point2D<float> PointF;

template<typename Ty> using Vector2D = Point2D<Ty>;
/// <summary>
/// ��ά����������
/// </summary>
typedef Vector2D<int> Vector;
/// <summary>
/// ��ά������
/// </summary>
typedef Vector2D<float> VectorF;

template<typename Ty>
struct Point3D
{
	//Fields
	Ty x, y, z;

};

/// <summary>
/// ��ά���͵㡣
/// </summary>
typedef Point3D<int> Point3;
/// <summary>
/// ��ά�㡣
/// </summary>
typedef Point3D<float> Point3F;

template<typename Ty> using Vector3D = Point3D<Ty>;
/// <summary>
/// ��ά����������
/// </summary>
typedef Vector3D<int> Vector3;
/// <summary>
/// ��ά������
/// </summary>
typedef Vector3D<float> Vector3F;
