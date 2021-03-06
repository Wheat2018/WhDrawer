#pragma once
#include "Line.h"
#include "Plane.h"
#include "Math.h"
#include "VectorAlgorithm.h"
#include "Debug.h"

/// <summary>
/// 几何算术类，提供各类几何算法。
/// <para>注：使用类静态算法需提供浮点判零方法。</para>
/// <para>浮点判零方法：要求一个包含静态方法IsZero(T)的类，方法返回所给数字是否为0的布尔值。</para>
/// </summary>
template<typename FloatZeroJudger = DefaultFloatZeroJudger>
class _Geometry
{
public:
#define _StaInCst static inline constexpr
#define _StaIn static inline

	template<typename VectorTy> using _V2 = Vector2D<VectorTy>;
	template<typename VectorTy> using _V3 = Vector3D<VectorTy>;
	template<typename PointTy> using _P2 = Point2D<PointTy>;
	template<typename PointTy> using _P3 = Point3D<PointTy>;
	template<typename LineTy> using _L2 = Line2D<LineTy>;
	template<typename LineTy> using _L3 = Line3D<LineTy>;
	template<typename PlaneTy> using _E = Plane3D<PlaneTy>;

	using _Rel = GeometryRelation;
	using _Mth = _Math<FloatZeroJudger>;

	//Operator
#define Operator2D(p1, p2, opt) {p1.x opt p2.x, p1.y opt p2.y};
#define Operator3D(p1, p2, opt) {p1.x opt p2.x, p1.y opt p2.y, p1.z opt p2.z};

	template<typename T1, typename T2> _StaInCst _P2<upper_t<T1, T2>> Add(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, +); }
	template<typename T1, typename T2> _StaInCst _P2<upper_t<T1, T2>> Sub(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, -); }
	template<typename T1, typename T2> _StaInCst _P2<upper_t<T1, T2>> Mul(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, *); }
	template<typename T1, typename T2> _StaInCst _P2<upper_t<T1, T2>> Div(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, /); }

	template<typename T1, typename T2> _StaInCst _P3<upper_t<T1, T2>> Add(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, +); }
	template<typename T1, typename T2> _StaInCst _P3<upper_t<T1, T2>> Sub(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, -); }
	template<typename T1, typename T2> _StaInCst _P3<upper_t<T1, T2>> Mul(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, *); }
	template<typename T1, typename T2> _StaInCst _P3<upper_t<T1, T2>> Div(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, /); }

	/// <summary>
	/// 向量点积。（内积）
	/// </summary>
	/// <typeparam name="T1">向量1数据类型。</typeparam>
	/// <typeparam name="T2">向量2数据类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度乘积的和。</returns>
	template<typename T1, typename T2> _StaInCst auto Dot(_V2<T1> v1, _V2<T2> v2) { return v1.x * v2.x + v1.y * v2.y; }
	/// <summary>
	/// 向量点积。（内积）
	/// </summary>
	/// <typeparam name="T1">向量1数据类型。</typeparam>
	/// <typeparam name="T2">向量2数据类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度乘积的和。</returns>
	template<typename T1, typename T2> _StaInCst auto Dot(_V3<T1> v1, _V3<T2> v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	/// <summary>
	/// 向量模积。
	/// </summary>
	/// <typeparam name="T1">向量1数据类型。</typeparam>
	/// <typeparam name="T2">向量2数据类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量的模的乘积。</returns>
	template<typename T1, typename T2> _StaInCst auto Mop(_V2<T1> v1, _V2<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }
	/// <summary>
	/// 向量模积。
	/// </summary>
	/// <typeparam name="T1">向量1数据类型。</typeparam>
	/// <typeparam name="T2">向量2数据类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量的模的乘积。</returns>
	template<typename T1, typename T2> _StaInCst auto Mop(_V3<T1> v1, _V3<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }

	/// <summary>
	/// 向量叉乘积。（向量积、外积）
	/// </summary>
	/// <typeparam name="T">向量数据类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量的模的乘积。</returns>
	template<typename T1, typename T2> _StaInCst _V3<upper_t<T1, T2>> Cro(_V3<T1> v1, _V3<T2> v2)
	{
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	//Relation
	//向量与向量
	/// <summary>
	/// 向量与向量关系：无或正交或共线。
	/// 注：零向量与任意向量正交。
	/// </summary>
	/// <typeparam name="T1">向量1数据类型。</typeparam>
	/// <typeparam name="T2">向量2数据类型。</typeparam>
	/// <param name="vector1">向量1。</param>
	/// <param name="vector2">向量2。</param>
	/// <returns>几何关系枚举。None或Perpendicular或Collinear。</returns>
	template<typename T1, typename T2, template<typename> typename _V>
	_StaInCst _Rel VectorRelation(_V<T1> vector1, _V<T2> vector2)
	{
		/*
			实现逻辑：1、向量点积为0时垂直。2、向量点积绝对值等于其模积（即夹角余弦为±1）时共线。3、其余为无。
		*/
		auto dot = Dot(vector1, vector2);
		if (_Mth::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (_Mth::Equal(_Mth::Abs(_Mth::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
	}

	//点与点
	/// <summary>
	/// 点与点关系：无或重合。
	/// </summary>	
	/// <typeparam name="T1">点1数据类型。</typeparam>
	/// <typeparam name="T2">点2数据类型。</typeparam>
	/// <param name="point1">点1。</param>
	/// <param name="point2">点2。</param>
	/// <returns>几何关系枚举。None或Coincident。</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_P2<T1> point1, _P2<T2> point2)
	{
		if (_Mth::Equal(point1.x, point2.x) && _Mth::Equal(point1.y, point2.y))
			return _Rel::Coincident;
		return _Rel::None;
	}
	/// <summary>
	/// 点与点关系：无或重合。
	/// </summary>	
	/// <typeparam name="T1">点1数据类型。</typeparam>
	/// <typeparam name="T2">点2数据类型。</typeparam>
	/// <param name="point1">点1。</param>
	/// <param name="point2">点2。</param>
	/// <returns>几何关系枚举。None或Coincident。</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_P3<T1> point1, _P3<T2> point2)
	{
		if (_Mth::Equal(point1.x, point2.x) && _Mth::Equal(point1.y, point2.y) && _Mth::Equal(point1.z, point2.z))
			return _Rel::Coincident;
		return _Rel::None;
	}

	//点与线
	/// <summary>
	/// 点与直线关系：无或包含。
	/// </summary>	
	/// <typeparam name="PT">点数据类型。</typeparam>
	/// <typeparam name="LT">线数据类型。</typeparam>
	/// <param name="point">点。</param>
	/// <param name="line">直线。</param>
	/// <returns>几何关系枚举。None或Contained。</returns>
	template<typename PT, typename LT> _StaInCst _Rel Relation(_P2<PT> point, _L2<LT> line)
	{
		/*
			实现逻辑：代入一般式。
		*/
		if (_Mth::IsZero(line.A * point.x + line.B * point.y + line.C))
			return _Rel::Contained;
		return _Rel::None;
	}
	/// <summary>
	/// 点与直线关系：无或包含。
	/// </summary>	
	/// <typeparam name="PT">点数据类型。</typeparam>
	/// <typeparam name="LT">线数据类型。</typeparam>
	/// <param name="point">点。</param>
	/// <param name="line">直线。</param>
	/// <returns>几何关系枚举。None或Contained。</returns>
	template<typename PT, typename LT> _StaInCst _Rel Relation(_P3<PT> point, _L3<LT> line)
	{
		/*
			实现逻辑：若点与直线上定点重合或构成的向量与直线方向向量共线，则点在直线上。
		*/
		if (Relation(point, line.fixed) & _Rel::Coincident)
			return _Rel::Contained;
		auto vec = Sub(point, line.fixed);
		if (VectorRelation(vec, line.direction) & _Rel::Collinear)
			return _Rel::Contained;
		return _Rel::None;
	}

	//线与线
	/// <summary>
	/// 二维直线与二维直线关系：重合、相交、平行、垂直（且相交）。
	/// </summary>	
	/// <typeparam name="T1">线1数据类型。</typeparam>
	/// <typeparam name="T2">线2数据类型。</typeparam>
	/// <param name="line1">直线1。</param>
	/// <param name="line2">直线2。</param>
	/// <returns>几何关系枚举。Coincident或Intersectant或Paralled或(Perpendicular|Intersectant)。</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_L2<T1> line1, _L2<T2> line2)
	{
		/*
			实现逻辑：若两线的方向向量 1、正交，则两线垂直相交，2、既不正交也不共线，则两线相交，
			3、共线，若两线方程系数等比，则两线重合，4、共线，两线方程系数不等比，两线平行。
		*/
		_Rel dRel = VectorRelation(DirectionVector(line1), DirectionVector(line2));
		if (dRel & _Rel::Perpendicular)
			return _Rel::Intersectant | _Rel::Perpendicular;
		if (dRel & _Rel::None)
			return _Rel::Intersectant;

		_Rel abcRel = VectorRelation(_V3<T1>{ line1.A, line1.B, line1.C }, _V3<T2>{ line2.A, line2.B, line2.C });
		if (abcRel & _Rel::Collinear)
			return _Rel::Coincident;
		return _Rel::Paralled;
	}
	/// <summary>
	/// 三维直线与三维直线关系：重合、相交、平行、异面、异面垂直、垂直相交。
	/// </summary>	
	/// <typeparam name="T1">线1数据类型。</typeparam>
	/// <typeparam name="T2">线2数据类型。</typeparam>
	/// <param name="line1">直线1。</param>
	/// <param name="line2">直线2。</param>
	/// <returns>几何关系枚举。Coincident或Intersectant或Paralled或DifferentPlane或(Perpendicular|DifferentPlane)或(Perpendicular|Intersectant)。</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_L3<T1> line1, _L3<T2> line2)
	{
		/*
			实现逻辑：第三线指两线定点构成的向量。两线外积向量与第三线内积为零，则两线共面，否则两线异面。
			注意两线外积向量可能为零向量，此时两线平行，上述内积仍然为零，两线共面亦成立。
			两线共面时，若两线方向向量 1、正交，则两线垂直相交，2、既不正交也不共线，则两线相交，3、共线，
			若第三线为零向量或与两线任意一线共线，则两线重合，4、共线，剩余情况下两线平行。
			两线异面时，若两线方向向量 1、正交，则两线异面垂直，2、既不正交也不共线，则两线异面，3、不可
			能共线，若共线，其外积向量为零向量，应属两线共面分支。
		*/
		_V3<T1> line1v = DirectionVector(line1);
		_V3<T2> line2v = DirectionVector(line2);
		auto line3v = Sub(line1.fixed, line2.fixed);

		_Rel line1v_line2v = VectorRelation(line1v, line2v);
		_Rel n_line3v = VectorRelation(Cro(line1v, line2v), line3v); //若两线平行，法向量为零，与任意线/第三线垂直。

		if (n_line3v & _Rel::Perpendicular)	//两线共面
		{
			if (line1v_line2v & _Rel::Perpendicular)
				return _Rel::Intersectant | _Rel::Perpendicular;
			if (line1v_line2v & _Rel::None)
				return _Rel::Intersectant;
			if (VectorRelation(line1v, line3v) & _Rel::Collinear)
				return _Rel::Coincident;
			if (Relation(line1.fixed, line2.fixed) & _Rel::Coincident) //两定点重合
				return _Rel::Coincident;
			return _Rel::Paralled;
		}
		else											//两线异面
		{
			if (line1v_line2v & _Rel::Perpendicular)
				return _Rel::DifferentPlane | _Rel::Perpendicular;
			if (line1v_line2v & _Rel::None)
				return _Rel::DifferentPlane;
			//异面直线不可能平行。
			Debug::Assert(!(line1v_line2v & _Rel::Collinear), "Geometry::Relation(_L3<T>, _L3<T>): 内部逻辑错误！");
		}
		return _Rel();
	}

	//点与面
	/// <summary>
	/// 三维点与三维平面关系：无或包含。
	/// </summary>
	/// <typeparam name="PT">点数据类型。</typeparam>
	/// <typeparam name="ET">面数据类型。</typeparam>
	/// <param name="point">三维点。</param>
	/// <param name="plane">三维平面。</param>
	/// <returns>几何关系枚举。None或Contained。</returns>
	template<typename PT, typename ET> _StaInCst _Rel Relation(_P3<PT> point, _E<ET> plane)
	{
		/*
			实现逻辑：代入一般式。
		*/
		if (_Mth::IsZero(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D))
			return _Rel::Contained;
		return _Rel::None;
	}

	//线与面
	/// <summary>
	/// 三维直线与三维平面关系：包含、平行、相交、垂直（且相交）。
	/// </summary>
	/// <typeparam name="LT">线数据类型。</typeparam>
	/// <typeparam name="ET">面数据类型。</typeparam>
	/// <param name="line">三维直线。</param>
	/// <param name="plane">三维平面。</param>
	/// <returns>几何关系枚举。Contained或Paralled或Intersectant或(Perpendicular|Intersectant)。</returns>
	template<typename LT, typename ET> _StaInCst _Rel Relation(_L3<LT> line, _E<ET> plane)
	{
		/*
			实现逻辑：若直线方向向量与平面法向量 1、共线，则线垂直于面，2、正交，若直线定点在面上，则线含于面，
			3、正交，直线定点不在面上，则线平行于面，4、既不正交也不共线，则线与面相交。
		*/
		_Rel n_direc = VectorRelation(NormalVector(plane), line.direction);
		
		if (n_direc & _Rel::Collinear)
			return _Rel::Intersectant | _Rel::Perpendicular;

		if (n_direc & _Rel::Perpendicular)
			if (Relation(line.fixed, plane) & _Rel::Contained) 
				return _Rel::Contained;
			else return _Rel::Paralled;

		return _Rel::Intersectant;
	}

	//面与面
	/// <summary>
	/// 三维平面与三维平面关系：重合、平行、相交、垂直（且相交）。
	/// </summary>
	/// <typeparam name="T1">面数据类型1。</typeparam>
	/// <typeparam name="T2">面数据类型2。</typeparam>
	/// <param name="plane1">三维平面1。</param>
	/// <param name="plane2">三维平面2。</param>
	/// <returns>几何关系枚举。Coincident或Paralled或Intersectant或(Perpendicular|Intersectant)。</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_E<T1> plane1, _E<T2> plane2)
	{
		/*
			实现逻辑：若两面的法向量 1、正交，则两面垂直，2、既不正交也不共线，则两面相交，3、共线，
			若两面方程系数等比，则两面重合，4、共线，两面方程系数不等比，则两面平行。
		*/
		_V3<T1> n1 = NormalVector(plane1);
		_V3<T2> n2 = NormalVector(plane2);
		_Rel nRel = VectorRelation(n1, n2);

		if (nRel & _Rel::Perpendicular)
			return _Rel::Intersectant | _Rel::Perpendicular;
		if (nRel & _Rel::None)
			return _Rel::Intersectant;

		_Rel abcdRel = VecAlgo::Relation(
			VectorNd<T1, 4>{ plane1.A, plane1.B, plane1.C, plane1.D },
			VectorNd<T2, 4>{ plane2.A, plane2.B, plane2.C, plane2.D });
		if (abcdRel & _Rel::Collinear)
			return _Rel::Coincident;
		return _Rel::Paralled;
	}

	//Distance
	//点与点
	/// <summary>
	/// 二维点欧氏距离。
	/// </summary>
	/// <typeparam name="T1">点数据类型1。</typeparam>
	/// <typeparam name="T2">点数据类型2。</typeparam>
	/// <param name="point1">点1。</param>
	/// <param name="point2">点2。</param>
	/// <returns>欧氏距离。</returns>
	template<typename T1, typename T2> _StaIn double Distance(_P2<T1> point1, _P2<T2> point2)
	{
		return sqrt(_Mth::Pow2(point1.x - point2.x) + _Mth::Pow2(point1.y - point2.y));
	}
	/// <summary>
	/// 三维点欧氏距离。
	/// </summary>
	/// <typeparam name="T1">点数据类型1。</typeparam>
	/// <typeparam name="T2">点数据类型2。</typeparam>
	/// <param name="point1">点1。</param>
	/// <param name="point2">点2。</param>
	/// <returns>欧氏距离。</returns>
	template<typename T1, typename T2> _StaIn double Distance(_P3<T1> point1, _P3<T2> point2)
	{
		return sqrt(_Mth::Pow2(point1.x - point2.x) + _Mth::Pow2(point1.y - point2.y) + _Mth::Pow2(point1.z - point2.z));
	}

	//点与线
	/// <summary>
	/// 点与直线欧氏距离。
	/// </summary>	
	/// <typeparam name="PT">点数据类型1。</typeparam>
	/// <typeparam name="LT">直线数据类型2。</typeparam>
	/// <param name="point">点。</param>
	/// <param name="line">直线。</param>
	/// <returns>欧氏距离。</returns>
	template<typename PT, typename LT> _StaIn double Distance(_P2<PT> point, _L2<LT> line)
	{
		/*
			实现逻辑：
				|A * x_0 + B * y_0 + C|
			d = -----------------------
					sqrt(A^2 + B^2)
		*/
		return _Mth::Abs(line.A * point.x + line.B * point.y + line.C) / sqrt(_Mth::Pow2(line.A) + _Mth::Pow2(line.B));
	}
	/// <summary>
	/// 点与直线欧氏距离。
	/// </summary>	
	/// <typeparam name="PT">点数据类型1。</typeparam>
	/// <typeparam name="LT">直线数据类型2。</typeparam>
	/// <param name="point">点。</param>
	/// <param name="line">直线。</param>
	/// <returns>欧氏距离。</returns>
	template<typename PT, typename LT> _StaIn double Distance(_P3<PT> point, _L3<LT> line)
	{
		/*
			实现逻辑：点与直线上定点构成的向量为A，直线方向向量为B，距离d=|A|sinθ=|A×B|/|B|。
		*/
		auto A = Sub(point, line.fixed);
		auto B = line.direction;
		auto cro = Cro(A, B);
		return sqrt(Dot(cro, cro) / Dot(B, B));
	}

	//线与线
	/// <summary>
	/// 直线与直线欧氏距离。相交直线距离为0。
	/// </summary>	
	/// <typeparam name="T1">线1数据类型。</typeparam>
	/// <typeparam name="T2">线2数据类型。</typeparam>
	/// <param name="line1">直线1。</param>
	/// <param name="line2">直线2。</param>
	/// <returns>欧氏距离。</returns>
	template<typename T1, typename T2> _StaIn double Distance(_L2<T1> line1, _L2<T2> line2)
	{
		/*
			实现逻辑：若两线不平行，距离为0。否则使用距离公式
					|C_1 - C_2|
			d = -----------------------
					sqrt(A^2 + B^2)

		*/
		_Rel dRel = VectorRelation(DirectionVector(line1), DirectionVector(line2));
		if (!(dRel & _Rel::Collinear))
			return 0.0;

		double k = (_Mth::Abs(line1.A) + _Mth::Abs(line1.B)) / (_Mth::Abs(line2.A) + _Mth::Abs(line2.B));
		return _Mth::Abs(line1.C - k * line2.C) / sqrt(_Mth::Pow2(line1.A) + _Mth::Pow2(line1.B));
	}
	/// <summary>
	/// 直线与直线欧氏距离。相交直线距离为0。
	/// </summary>	
	/// <typeparam name="T1">线1数据类型。</typeparam>
	/// <typeparam name="T2">线2数据类型。</typeparam>
	/// <param name="line1">直线1。</param>
	/// <param name="line2">直线2。</param>
	/// <returns>几何关系枚举。Coincident或Intersectant或Paralled或DifferentPlane或(Perpendicular|DifferentPlane)或(Perpendicular|Intersectant)。</returns>
	template<typename T1, typename T2> _StaIn double Distance(_L3<T1> line1, _L3<T2> line2)
	{
		/*
			实现逻辑：第三线指两线定点构成的向量。两线外积向量（法向量）与第三线内积为零，则两线共面，否则两线异面。
			两线异面时，距离等于单位法向量与第三线内积；两线共面时，若方向向量共线，距离等于一线定点到另一线距离，
			否则距离为0.
		*/
		_V3<T1> line1v = DirectionVector(line1);
		_V3<T2> line2v = DirectionVector(line2);
		auto line3v = Sub(line1.fixed, line2.fixed);
		auto n = Cro(line1v, line2v);

		auto dot_n_line3v = Dot(line3v, n);

		if (!_Mth::IsZero(dot_n_line3v))
			return dot_n_line3v / sqrt(Dot(n, n));

		_Rel line1v_line2v = VectorRelation(line1v, line2v);
		
		if (line1v_line2v & _Rel::Collinear)
			return Distance(line1.fixed, line2);
		return 0;
	}

	//点与面
	/// <summary>
	/// 点与平面欧氏距离。
	/// </summary>
	/// <typeparam name="PT">点数据类型。</typeparam>
	/// <typeparam name="ET">面数据类型。</typeparam>
	/// <param name="point">三维点。</param>
	/// <param name="plane">三维平面。</param>
	/// <returns>欧氏距离。</returns>
	template<typename PT, typename ET> _StaIn double Distance(_P3<PT> point, _E<ET> plane)
	{
		/*
			实现逻辑：
				|A * x_0 + B * y_0 + C * z_0 + D|
			d = ---------------------------------
					sqrt(A^2 + B^2 + C^2)
		*/
		return _Mth::Abs(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D) /
			sqrt(_Mth::Pow2(plane.A) + _Mth::Pow2(plane.B) + _Mth::Pow2(plane.C));
	}

	//线与面
	/// <summary>
	/// 线与平面欧氏距离。线与面相交时距离为0。
	/// </summary>
	/// <typeparam name="LT">线数据类型。</typeparam>
	/// <typeparam name="ET">面数据类型。</typeparam>
	/// <param name="line">三维直线。</param>
	/// <param name="plane">三维平面。</param>
	/// <returns>欧氏距离。</returns>
	template<typename LT, typename ET> _StaIn double Distance(_L3<LT> line, _E<ET> plane)
	{
		/*
			实现逻辑：若直线与平面平行，则距离等于直线上定点到平面距离，否则距离为0.
		*/
		_Rel n_direc = VectorRelation(NormalVector(plane), line.direction);

		if (n_direc & _Rel::Perpendicular)
			return Distance(line.fixed, plane);
		return 0;
	}

	//面与面
	/// <summary>
	/// 平面与平面欧氏距离。相交平面距离为0。
	/// </summary>
	/// <typeparam name="T1">面数据类型1。</typeparam>
	/// <typeparam name=T2">面数据类型2。</typeparam>
	/// <param name="plane1">三维平面1。</param>
	/// <param name="plane2">三维平面2。</param>
	/// <returns>欧氏距离。</returns>
	template<typename T1, typename T2> _StaIn double Distance(_E<T1> plane1, _E<T2> plane2)
	{
		/*
			实现逻辑：若两线不平行，距离为0。否则使用距离公式
						|C_1 - C_2|
			d = ----------------------------
					sqrt(A^2 + B^2 + C^2)

		*/
		_Rel dRel = VectorRelation(NormalVector(plane1), NormalVector(plane2));
		if (!(dRel & _Rel::Collinear))
			return 0.0;

		double k = (_Mth::Abs(plane1.A) + _Mth::Abs(plane1.B) + _Mth::Abs(plane1.C)) / 
			(_Mth::Abs(plane2.A) + _Mth::Abs(plane2.B) + _Mth::Abs(plane2.C));
		return _Mth::Abs(plane1.C - k * plane2.C) / sqrt(_Mth::Pow2(plane1.A) + _Mth::Pow2(plane1.B) + _Mth::Pow2(plane1.C));
	}


	//Others
	/// <summary>
	/// 获取直线的方向向量。
	/// </summary>
	/// <typeparam name="T">直线数据类型。</typeparam>
	/// <param name="line">直线。</param>
	/// <returns>直线的方向向量。</returns>
	template<typename T>
	_StaIn constexpr _V2<T> DirectionVector(_L2<T>line) { return { line.A, line.B }; }

	/// <summary>
	/// 获取直线的方向向量。
	/// </summary>
	/// <typeparam name="T">直线数据类型。</typeparam>
	/// <param name="line">直线。</param>
	/// <returns>直线的方向向量。</returns>
	template<typename T>
	_StaIn constexpr _V3<T> DirectionVector(_L3<T>line) { return line.direction; }

	/// <summary>
	/// 获取平面的法向量。
	/// </summary>
	/// <typeparam name="T">平面数据类型。</typeparam>
	/// <param name="plane">平面。</param>
	/// <returns>平面的法向量。</returns>
	template<typename T>
	_StaIn constexpr _V3<T> NormalVector(_E<T>plane) { return { plane.A, plane.B, plane.C}; }

};

/// <summary>
/// 几何算术类，提供各类几何算法。
/// </summary>
typedef _Geometry<> Geometry;
