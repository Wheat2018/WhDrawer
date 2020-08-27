#pragma once
#include "Line.h"
#include "Plane.h"
#include "Math.h"
#include "VectorAlgorithm.h"
#include "Debug.h"

/// <summary>
/// ���������࣬�ṩ���༸���㷨��
/// </summary>
class Geometry
{
public:
	template<typename VectorTy> using _V2 = Vector2D<VectorTy>;
	template<typename VectorTy> using _V3 = Vector3D<VectorTy>;
	template<typename PointTy> using _P2 = Point2D<PointTy>;
	template<typename PointTy> using _P3 = Point3D<PointTy>;
	template<typename LineTy> using _L2 = Line2D<LineTy>;
	template<typename LineTy> using _L3 = Line3D<LineTy>;
	template<typename PlaneTy> using _E = Plane3D<PlaneTy>;

	using _Rel = GeometryRelation;

	//Operator
#define Operator2D(p1, p2, opt) {p1.x opt p2.x, p1.y opt p2.y};
#define Operator3D(p1, p2, opt) {p1.x opt p2.x, p1.y opt p2.y, p1.z opt p2.z};

	template<typename T1, typename T2> static constexpr _P2<upper_t<T1, T2>> Add(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, +); }
	template<typename T1, typename T2> static constexpr _P2<upper_t<T1, T2>> Sub(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, -); }
	template<typename T1, typename T2> static constexpr _P2<upper_t<T1, T2>> Mul(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, *); }
	template<typename T1, typename T2> static constexpr _P2<upper_t<T1, T2>> Div(_P2<T1> p1, _P2<T2> p2) { return Operator2D(p1, p2, /); }

	template<typename T1, typename T2> static constexpr _P3<upper_t<T1, T2>> Add(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, +); }
	template<typename T1, typename T2> static constexpr _P3<upper_t<T1, T2>> Sub(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, -); }
	template<typename T1, typename T2> static constexpr _P3<upper_t<T1, T2>> Mul(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, *); }
	template<typename T1, typename T2> static constexpr _P3<upper_t<T1, T2>> Div(_P3<T1> p1, _P3<T2> p2) { return Operator3D(p1, p2, /); }

	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename T1, typename T2> static constexpr auto Dot(_V2<T1> v1, _V2<T2> v2) { return v1.x * v2.x + v1.y * v2.y; }
	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename T1, typename T2> static constexpr auto Dot(_V3<T1> v1, _V3<T2> v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	/// <summary>
	/// ����ģ����
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> static constexpr auto Mop(_V2<T1> v1, _V2<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }
	/// <summary>
	/// ����ģ����
	/// </summary>
	/// <typeparam name="T1">����1�������͡�</typeparam>
	/// <typeparam name="T2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> static constexpr auto Mop(_V3<T1> v1, _V3<T2> v2) { return sqrt(Dot(v1, v1) * Dot(v2, v2)); }

	/// <summary>
	/// ������˻������������������
	/// </summary>
	/// <typeparam name="T">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ģ�ĳ˻���</returns>
	template<typename T1, typename T2> static constexpr _V3<upper_t<T1, T2>> Cro(_V3<T1> v1, _V3<T2> v2)
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
	static _Rel VectorRelation(_V<T1> vector1, _V<T2> vector2)
	{
		/*
			ʵ���߼���1���������Ϊ0ʱ��ֱ��2�������������ֵ������ģ�������н�����Ϊ��1��ʱ���ߡ�3������Ϊ�ޡ�
		*/
		auto dot = Dot(vector1, vector2);
		if (Math::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (Math::Equal(Math::Abs(Math::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

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
	template<typename T1, typename T2> static _Rel Relation(_P2<T1> point1, _P2<T2> point2)
	{
		if (Math::Equal(point1.x, point2.x) && Math::Equal(point1.y, point2.y))
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
	template<typename T1, typename T2> static _Rel Relation(_P3<T1> point1, _P3<T2> point2)
	{
		if (Math::Equal(point1.x, point2.x) && Math::Equal(point1.y, point2.y) && Math::Equal(point1.z, point2.z))
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
	template<typename PT, typename LT> static _Rel Relation(_P2<PT> point, _L2<LT> line)
	{
		/*
			ʵ���߼�������һ��ʽ��
		*/
		if (Math::IsZero(line.A * point.x + line.B * point.y + line.C))
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
	template<typename PT, typename LT> static _Rel Relation(_P3<PT> point, _L3<LT> line)
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
	template<typename T1, typename T2> static _Rel Relation(_L2<T1> line1, _L2<T2> line2)
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
	template<typename T1, typename T2> static _Rel Relation(_L3<T1> line1, _L3<T2> line2)
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
		_Rel n_line3v = VectorRelation(Cro(line1v, line2v), line3v); //����ƽ��ʱ��������Ϊ�㣬��������/�����ߴ�ֱ��

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
	template<typename PT, typename ET> static _Rel Relation(_P3<PT> point, _E<ET> plane)
	{
		/*
			ʵ���߼�������һ��ʽ��
		*/
		if (Math::IsZero(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D))
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
	template<typename LT, typename ET> static _Rel Relation(_L3<LT> line, _E<ET> plane)
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
	/// <typeparam name=T2">����������2��</typeparam>
	/// <param name="plane1">��άƽ��1��</param>
	/// <param name="plane2">��άƽ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Paralled��Intersectant��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> static _Rel Relation(_E<T1> plane1, _E<T2> plane2)
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

		using _T = upper_t<T1, T2>;
		using _V4 = VectorNd<_T, 4>;
		_Rel abcdRel = VecAlgo::Relation(
			_V4{ (_T)plane1.A, (_T)plane1.B, (_T)plane1.C, (_T)plane1.D }, 
			_V4{ (_T)plane2.A, (_T)plane2.B, (_T)plane2.C, (_T)plane2.D });
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
	/// <typeparam name=T2">����������2��</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> static auto Distance(_P2<T1> point1, _P2<T2> point2)
	{
		return sqrt(Math::Pow2(point1.x - point2.x) + Math::Pow2(point1.y - point2.y));
	}
	/// <summary>
	/// ��ά��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name=T2">����������2��</typeparam>
	/// <param name="point1">��1��</param>
	/// <param name="point2">��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> static auto Distance(_P3<T1> point1, _P3<T2> point2)
	{
		return sqrt(Math::Pow2(point1.x - point2.x) + Math::Pow2(point1.y - point2.y) + Math::Pow2(point1.z - point2.z));
	}

	//������
	/// <summary>
	/// ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename LT> static auto Distance(_P2<PT> point, _L2<LT> line)
	{
		/*
			ʵ���߼���
				|A * x_0 + B * y_0 + C|
			d = -----------------------
					sqrt(A^2 + B^2)
		*/
		return Math::Abs(line.A * point.x + line.B * point.y + line.C) / sqrt(Math::Pow2(line.A) + Math::Pow2(line.B));
	}
	/// <summary>
	/// ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <param name="point">�㡣</param>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename LT> static auto Distance(_P3<PT> point, _L3<LT> line)
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
	/// ֱ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> static auto Distance(_L2<T1> line1, _L2<T2> line2)
	{
		/*
			ʵ���߼��������߲�ƽ�У�����Ϊ0������ʹ�þ��빫ʽ
					|C_1 - C_2|
			d = -----------------------
					sqrt(A^2 + B^2)

		*/
		_Rel dRel = VectorRelation(DirectionVector(line1), DirectionVector(line2));
		if (!(dRel & _Rel::Collinear))
			return upper_t<T1, T2>(0);

		upper_t<T1, T2> k;
		if (line1.A >= line1.B) k = line1.A / line2.A;
		else k = line1.B / line2.B;
		
		return Math::Abs(line1.C - k * line2.C) / sqrt(Math::Pow2(line1.A) + Math::Pow2(line1.B));
	}
	/// <summary>
	/// ֱ����ֱ��ŷ�Ͼ��롣
	/// </summary>	
	/// <typeparam name="T1">��1�������͡�</typeparam>
	/// <typeparam name="T2">��2�������͡�</typeparam>
	/// <param name="line1">ֱ��1��</param>
	/// <param name="line2">ֱ��2��</param>
	/// <returns>���ι�ϵö�١�Coincident��Intersectant��Paralled��DifferentPlane��(Perpendicular|DifferentPlane)��(Perpendicular|Intersectant)��</returns>
	template<typename T1, typename T2> static _Rel Distance(_L3<T1> line1, _L3<T2> line2)
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
		_Rel n_line3v = VectorRelation(Cro(line1v, line2v), line3v); //����ƽ��ʱ��������Ϊ�㣬��������/�����ߴ�ֱ��

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
	/// ����ƽ��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="PT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="point">��ά�㡣</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename PT, typename ET> static _Rel Distance(_P3<PT> point, _E<ET> plane)
	{
		/*
			ʵ���߼�������һ��ʽ��
		*/
		if (Math::IsZero(plane.A * point.x + plane.B * point.y + plane.C * point.z + plane.D))
			return _Rel::Contained;
		return _Rel::None;
	}

	//������
	/// <summary>
	/// ����ƽ��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="LT">���������͡�</typeparam>
	/// <typeparam name="ET">���������͡�</typeparam>
	/// <param name="line">��άֱ�ߡ�</param>
	/// <param name="plane">��άƽ�档</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename LT, typename ET> static _Rel Distance(_L3<LT> line, _E<ET> plane)
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
	/// ƽ����ƽ��ŷ�Ͼ��롣
	/// </summary>
	/// <typeparam name="T1">����������1��</typeparam>
	/// <typeparam name=T2">����������2��</typeparam>
	/// <param name="plane1">��άƽ��1��</param>
	/// <param name="plane2">��άƽ��2��</param>
	/// <returns>ŷ�Ͼ��롣</returns>
	template<typename T1, typename T2> static _Rel Distance(_E<T1> plane1, _E<T2> plane2)
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

		using _T = upper_t<T1, T2>;
		using _V4 = VectorNd<_T, 4>;
		_Rel abcdRel = VecAlgo::Relation(
			_V4{ (_T)plane1.A, (_T)plane1.B, (_T)plane1.C, (_T)plane1.D },
			_V4{ (_T)plane2.A, (_T)plane2.B, (_T)plane2.C, (_T)plane2.D });
		if (abcdRel & _Rel::Collinear)
			return _Rel::Coincident;
		return _Rel::Paralled;
	}


	//Others
	/// <summary>
	/// ��ȡֱ�ߵķ���������
	/// </summary>
	/// <typeparam name="T">ֱ���������͡�</typeparam>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ֱ�ߵķ���������</returns>
	template<typename T>
	static constexpr _V2<T> DirectionVector(_L2<T>line) { return { line.A, line.B }; }

	/// <summary>
	/// ��ȡֱ�ߵķ���������
	/// </summary>
	/// <typeparam name="T">ֱ���������͡�</typeparam>
	/// <param name="line">ֱ�ߡ�</param>
	/// <returns>ֱ�ߵķ���������</returns>
	template<typename T>
	static constexpr _V3<T> DirectionVector(_L3<T>line) { return line.direction; }

	/// <summary>
	/// ��ȡƽ��ķ�������
	/// </summary>
	/// <typeparam name="T">ƽ���������͡�</typeparam>
	/// <param name="plane">ƽ�档</param>
	/// <returns>ƽ��ķ�������</returns>
	template<typename T>
	static constexpr _V3<T> NormalVector(_E<T>plane) { return { plane.A, plane.B, plane.C}; }


};

