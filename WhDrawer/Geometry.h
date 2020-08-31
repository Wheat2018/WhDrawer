#pragma once
#include "Line.h"
#include "Plane.h"
#include "Math.h"
#include "VectorAlgorithm.h"
#include "Debug.h"

/// <summary>
/// ���������࣬�ṩ���༸���㷨��
/// <para>ע��ʹ���ྲ̬�㷨���ṩ�������㷽����</para>
/// <para>�������㷽����Ҫ��һ��������̬����IsZero(T)���࣬�����������������Ƿ�Ϊ0�Ĳ���ֵ��</para>
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
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename T1, typename T2> _StaInCst auto Dot(_V2<T1> v1, _V2<T2> v2) { return v1.x * v2.x + v1.y * v2.y; }
	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename T1, typename T2> _StaInCst auto Dot(_V3<T1> v1, _V3<T2> v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	/// <summary>
	/// ����ģ����
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> _StaInCst auto Mop(_V2<T1> v1, _V2<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }
	/// <summary>
	/// ����ģ����
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> _StaInCst auto Mop(_V3<T1> v1, _V3<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }

	/// <summary>
	/// ������˻������������������
	/// </summary>
	/// <typeparam name="T">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> _StaInCst _V3<upper_t<T1, T2>> Cro(_V3<T1> v1, _V3<T2> v2)
	{
		return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	//Relation
	//����������
	/// <summary>
	/// ������������ϵ���޻��������ߡ�
	/// ע������������������������
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="vector1">����1��</param>
	/// <param name="vector2">����2��</param>
	/// <returns>���ι�ϵö�١�None��Perpendicular��Collinear��</returns>
	template<typename T1, typename T2, template<typename> typename _V>
	_StaInCst _Rel VectorRelation(_V<T1> vector1, _V<T2> vector2)
	{
		/*
			ʵ���߼���1���������Ϊ0ʱ��ֱ��2�������������ֵ������ģ�������н�����Ϊ��1��ʱ���ߡ�3������Ϊ�ޡ�
		*/
		auto dot = Dot(vector1, vector2);
		if (_Mth::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (_Mth::Equal(_Mth::Abs(_Mth::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
	}

	//�����
	/// <summary>
	/// ������ϵ���޻��غϡ�
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>���ι�ϵö�١�None��Coincident��</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_P2<T1> point1, _P2<T2> point2)
	{
		if (_Mth::Equal(point1.x, point2.x) && _Mth::Equal(point1.y, point2.y))
			return _Rel::Coincident;
		return _Rel::None;
	}
	/// <summary>
	/// ������ϵ���޻��غϡ�
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>���ι�ϵö�١�None��Coincident��</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_P3<T1> point1, _P3<T2> point2)
	{
		if (_Mth::Equal(point1.x, point2.x) && _Mth::Equal(point1.y, point2.y) && _Mth::Equal(point1.z, point2.z))
			return _Rel::Coincident;
		return _Rel::None;
	}

	//������
	/// <summary>
	/// ����ֱ�߹�ϵ���޻������
	/// </summary>	
	/// <typeparam name="PT">���������͡�</typeparam>
	/// <typeparam name="LT">���������͡�</typeparam>
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>���ι�ϵö�١�None��Contained��</returns>
	template<typename PT, typename LT> _StaInCst _Rel Relation(_P2<PT> point, _L2<LT> line)
	{
		/*
			ʵ���߼�������һ��ʽ��
		*/
		if (_Mth::IsZero(line.A * point.x + line.B * point.y + line.C))
			return _Rel::Contained;
		return _Rel::None;
	}
	/// <summary>
	/// ����ֱ�߹�ϵ���޻������
	/// </summary>	
	/// <typeparam name="PT">���������͡�</typeparam>
	/// <typeparam name="LT">���������͡�</typeparam>
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>���ι�ϵö�١�None��Contained��</returns>
	template<typename PT, typename LT> _StaInCst _Rel Relation(_P3<PT> point, _L3<LT> line)
	{
		/*
			ʵ���߼���������ֱ���϶����غϻ򹹳ɵ�������ֱ�߷����������ߣ������ֱ���ϡ�
		*/
		if (Relation(point, line.fixed) & _Rel::Coincident)
			return _Rel::Contained;
		auto vec = Sub(point, line.fixed);
		if (VectorRelation(vec, line.direction) & _Rel::Collinear)
			return _Rel::Contained;
		return _Rel::None;
	}

	//������
	/// <summary>
	/// ��άֱ�����άֱ�߹�ϵ���غϡ��ཻ��ƽ�С���ֱ�����ཻ����
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Intersectant��Paralled��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_L2<T1> line1, _L2<T2> line2)
	{
		/*
			ʵ���߼��������ߵķ������� 1�������������ߴ�ֱ�ཻ��2���Ȳ�����Ҳ�����ߣ��������ཻ��
			3�����ߣ������߷���ϵ���ȱȣ��������غϣ�4�����ߣ����߷���ϵ�����ȱȣ�����ƽ�С�
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
	/// ��άֱ������άֱ�߹�ϵ���غϡ��ཻ��ƽ�С����桢���洹ֱ����ֱ�ཻ��
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Intersectant��Paralled��DifferentPlane��(Perpendicular|DifferentPlane)��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_L3<T1> line1, _L3<T2> line2)
	{
		/*
			ʵ���߼���������ָ���߶��㹹�ɵ��������������������������ڻ�Ϊ�㣬�����߹��棬�����������档
			ע�����������������Ϊ����������ʱ����ƽ�У������ڻ���ȻΪ�㣬���߹����������
			���߹���ʱ�������߷������� 1�������������ߴ�ֱ�ཻ��2���Ȳ�����Ҳ�����ߣ��������ཻ��3�����ߣ�
			��������Ϊ������������������һ�߹��ߣ��������غϣ�4�����ߣ�ʣ�����������ƽ�С�
			��������ʱ�������߷������� 1�����������������洹ֱ��2���Ȳ�����Ҳ�����ߣ����������棬3������
			�ܹ��ߣ������ߣ����������Ϊ��������Ӧ�����߹����֧��
		*/
		_V3<T1> line1v = DirectionVector(line1);
		_V3<T2> line2v = DirectionVector(line2);
		auto line3v = Sub(line1.fixed, line2.fixed);

		_Rel line1v_line2v = VectorRelation(line1v, line2v);
		_Rel n_line3v = VectorRelation(Cro(line1v, line2v), line3v); //������ƽ�У�������Ϊ�㣬��������/�����ߴ�ֱ��

		if (n_line3v & _Rel::Perpendicular)	//���߹���
		{
			if (line1v_line2v & _Rel::Perpendicular)
				return _Rel::Intersectant | _Rel::Perpendicular;
			if (line1v_line2v & _Rel::None)
				return _Rel::Intersectant;
			if (VectorRelation(line1v, line3v) & _Rel::Collinear)
				return _Rel::Coincident;
			if (Relation(line1.fixed, line2.fixed) & _Rel::Coincident) //�������غ�
				return _Rel::Coincident;
			return _Rel::Paralled;
		}
		else											//��������
		{
			if (line1v_line2v & _Rel::Perpendicular)
				return _Rel::DifferentPlane | _Rel::Perpendicular;
			if (line1v_line2v & _Rel::None)
				return _Rel::DifferentPlane;
			//����ֱ�߲�����ƽ�С�
			Debug::Assert(!(line1v_line2v & _Rel::Collinear), "Geometry::Relation(_L3<T>, _L3<T>): �ڲ��߼�����");
		}
		return _Rel();
	}

	//������
	/// <summary>
	/// ��ά������άƽ���ϵ���޻������
	/// </summary>
	/// <typeparam name="PT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="point">��ά�㡣</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>���ι�ϵö�١�None��Contained��</returns>
	template<typename PT, typename ET> _StaInCst _Rel Relation(_P3<PT> point, _E<ET> plane)
	{
		/*
			ʵ���߼�������һ��ʽ��
		*/
		if (_Mth::IsZero(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D))
			return _Rel::Contained;
		return _Rel::None;
	}

	//������
	/// <summary>
	/// ��άֱ������άƽ���ϵ��������ƽ�С��ཻ����ֱ�����ཻ����
	/// </summary>
	/// <typeparam name="LT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="line">��άֱ�ߡ�</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>���ι�ϵö�١�Contained��Paralled��Intersectant��(Perpendicular|Intersectant)��</returns>
	template<typename LT, typename ET> _StaInCst _Rel Relation(_L3<LT> line, _E<ET> plane)
	{
		/*
			ʵ���߼�����ֱ�߷���������ƽ�淨���� 1�����ߣ����ߴ�ֱ���棬2����������ֱ�߶��������ϣ����ߺ����棬
			3��������ֱ�߶��㲻�����ϣ�����ƽ�����棬4���Ȳ�����Ҳ�����ߣ����������ཻ��
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

	//������
	/// <summary>
	/// ��άƽ������άƽ���ϵ���غϡ�ƽ�С��ཻ����ֱ�����ཻ����
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name="T2">����������2��</typeparam>
	/// <param name="plane1">��άƽ��1��</param>
	/// <param name="plane2">��άƽ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Paralled��Intersectant��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> _StaInCst _Rel Relation(_E<T1> plane1, _E<T2> plane2)
	{
		/*
			ʵ���߼���������ķ����� 1�������������洹ֱ��2���Ȳ�����Ҳ�����ߣ��������ཻ��3�����ߣ�
			�����淽��ϵ���ȱȣ��������غϣ�4�����ߣ����淽��ϵ�����ȱȣ�������ƽ�С�
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
	//�����
	/// <summary>
	/// ��ά��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name="T2">����������2��</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> _StaIn double Distance(_P2<T1> point1, _P2<T2> point2)
	{
		return sqrt(_Mth::Pow2(point1.x - point2.x) + _Mth::Pow2(point1.y - point2.y));
	}
	/// <summary>
	/// ��ά��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name="T2">����������2��</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> _StaIn double Distance(_P3<T1> point1, _P3<T2> point2)
	{
		return sqrt(_Mth::Pow2(point1.x - point2.x) + _Mth::Pow2(point1.y - point2.y) + _Mth::Pow2(point1.z - point2.z));
	}

	//������
	/// <summary>
	/// ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <typeparam name="PT">����������1��</typeparam>
	/// <typeparam name="LT">ֱ����������2��</typeparam>
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename LT> _StaIn double Distance(_P2<PT> point, _L2<LT> line)
	{
		/*
			ʵ���߼���
				|A * x_0 + B * y_0 + C|
			d = -----------------------
					sqrt(A^2 + B^2)
		*/
		return _Mth::Abs(line.A * point.x + line.B * point.y + line.C) / sqrt(_Mth::Pow2(line.A) + _Mth::Pow2(line.B));
	}
	/// <summary>
	/// ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <typeparam name="PT">����������1��</typeparam>
	/// <typeparam name="LT">ֱ����������2��</typeparam>
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename LT> _StaIn double Distance(_P3<PT> point, _L3<LT> line)
	{
		/*
			ʵ���߼�������ֱ���϶��㹹�ɵ�����ΪA��ֱ�߷�������ΪB������d=|A|sin��=|A��B|/|B|��
		*/
		auto A = Sub(point, line.fixed);
		auto B = line.direction;
		auto cro = Cro(A, B);
		return sqrt(Dot(cro, cro) / Dot(B, B));
	}

	//������
	/// <summary>
	/// ֱ����ֱ��ŷ�Ͼ��롣�ֱཻ�߾���Ϊ0��
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> _StaIn double Distance(_L2<T1> line1, _L2<T2> line2)
	{
		/*
			ʵ���߼��������߲�ƽ�У�����Ϊ0������ʹ�þ��빫ʽ
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
	/// ֱ����ֱ��ŷ�Ͼ��롣�ֱཻ�߾���Ϊ0��
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Intersectant��Paralled��DifferentPlane��(Perpendicular|DifferentPlane)��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> _StaIn double Distance(_L3<T1> line1, _L3<T2> line2)
	{
		/*
			ʵ���߼���������ָ���߶��㹹�ɵ������������������������������������ڻ�Ϊ�㣬�����߹��棬�����������档
			��������ʱ��������ڵ�λ��������������ڻ������߹���ʱ���������������ߣ��������һ�߶��㵽��һ�߾��룬
			�������Ϊ0.
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

	//������
	/// <summary>
	/// ����ƽ��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="PT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="point">��ά�㡣</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename ET> _StaIn double Distance(_P3<PT> point, _E<ET> plane)
	{
		/*
			ʵ���߼���
				|A * x_0 + B * y_0 + C * z_0 + D|
			d = ---------------------------------
					sqrt(A^2 + B^2 + C^2)
		*/
		return _Mth::Abs(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D) /
			sqrt(_Mth::Pow2(plane.A) + _Mth::Pow2(plane.B) + _Mth::Pow2(plane.C));
	}

	//������
	/// <summary>
	/// ����ƽ��ŷ�Ͼ��롣�������ཻʱ����Ϊ0��
	/// </summary>
	/// <typeparam name="LT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="line">��άֱ�ߡ�</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename LT, typename ET> _StaIn double Distance(_L3<LT> line, _E<ET> plane)
	{
		/*
			ʵ���߼�����ֱ����ƽ��ƽ�У���������ֱ���϶��㵽ƽ����룬�������Ϊ0.
		*/
		_Rel n_direc = VectorRelation(NormalVector(plane), line.direction);

		if (n_direc & _Rel::Perpendicular)
			return Distance(line.fixed, plane);
		return 0;
	}

	//������
	/// <summary>
	/// ƽ����ƽ��ŷ�Ͼ��롣�ཻƽ�����Ϊ0��
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name=T2">����������2��</typeparam>
	/// <param name="plane1">��άƽ��1��</param>
	/// <param name="plane2">��άƽ��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> _StaIn double Distance(_E<T1> plane1, _E<T2> plane2)
	{
		/*
			ʵ���߼��������߲�ƽ�У�����Ϊ0������ʹ�þ��빫ʽ
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
	/// ��ȡֱ�ߵķ���������
	/// </summary>
	/// <typeparam name="T">ֱ���������͡�</typeparam>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ֱ�ߵķ���������</returns>
	template<typename T>
	_StaIn constexpr _V2<T> DirectionVector(_L2<T>line) { return { line.A, line.B }; }

	/// <summary>
	/// ��ȡֱ�ߵķ���������
	/// </summary>
	/// <typeparam name="T">ֱ���������͡�</typeparam>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ֱ�ߵķ���������</returns>
	template<typename T>
	_StaIn constexpr _V3<T> DirectionVector(_L3<T>line) { return line.direction; }

	/// <summary>
	/// ��ȡƽ��ķ�������
	/// </summary>
	/// <typeparam name="T">ƽ���������͡�</typeparam>
	/// <param name="plane">ƽ�档</param>
	/// <returns>ƽ��ķ�������</returns>
	template<typename T>
	_StaIn constexpr _V3<T> NormalVector(_E<T>plane) { return { plane.A, plane.B, plane.C}; }

};

/// <summary>
/// ���������࣬�ṩ���༸���㷨��
/// </summary>
typedef _Geometry<> Geometry;
