#pragma once
#include "DebugString.hpp"

/// <summary>
/// 仅当配置为Debug编译时，该类函数才生效。
/// </summary>
class Debug
{
public:
	inline static void Assert(bool expression, DebugString description)
	{
		if (expression) return;
#ifdef _DEBUG
		std::cout << description << std::endl;
		throw;
#endif // _DEBUG
	}
};


//Print Operator
#include "Point.h"

inline std::ostream& operator<<(std::ostream& o, Size size)
{
	return o << DEBUG_STR_STRUCT_2(size, width, height);
}


template<typename Ty>
inline std::ostream& operator<<(std::ostream& o, Point2D<Ty> p)
{
	return o << DEBUG_STR_STRUCT_2(p, x, y);;
}

template<typename Ty>
inline std::ostream& operator<<(std::ostream& o, Point3D<Ty> p)
{
	return o << DEBUG_STR_STRUCT_3(p, x, y, z);
}

#include "Line.h"

template<typename Ty>
inline std::ostream& operator<<(std::ostream& o, Line2D<Ty> l)
{
	return o << DEBUG_STR_STRUCT_3(l, A, B, C);
}

template<typename Ty>
inline std::ostream& operator<<(std::ostream& o, Line3D<Ty> l)
{
	return o << DEBUG_STR_STRUCT_2(l, fixed, direction);
}

#include "Plane.h"

template<typename Ty>
inline std::ostream& operator<<(std::ostream& o, Plane3D<Ty> e)
{
	return o << DEBUG_STR_STRUCT_4(e, A, B, C, D);
}

#include "GeometryRelation.h"

inline std::ostream& operator<<(std::ostream& o, GeometryRelation relation)
{
	DebugString str;
	o << "{ ";
	if (relation & GeometryRelation::None)			str.Append("None ");
	if (relation & GeometryRelation::Coincident)	str.Append("Coincident ");
	if (relation & GeometryRelation::Contained)		str.Append("Contained ");
	if (relation & GeometryRelation::Intersectant)	str.Append("Intersectant ");
	if (relation & GeometryRelation::Paralled)		str.Append("Paralled ");
	if (relation & GeometryRelation::Perpendicular)	str.Append("Perpendicular ");
	if (relation & GeometryRelation::DifferentPlane)str.Append("DifferentPlane ");
	if (relation & GeometryRelation::Collinear)		str.Append("Collinear ");
	if (((std::string)(str)).empty()) str.Append("Error ");
	return o << str << "}";
}

#include "VectorNd.h"

template<typename Ty, size_t dim>
inline std::ostream& operator<<(std::ostream& o, VectorNd<Ty, dim> vec)
{
	o << "{ ";
	for (int i = 0; i < vec.size; i++) o << "["<< i << "]:" << vec.elem[i] << " ";
	return o << "}";
}
