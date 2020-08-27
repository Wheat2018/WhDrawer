#pragma once
#include <initializer_list>
#include "GeometryRelation.h"
#include "VectorNd.h"
#include "Math.h"


/// <summary>
/// VecAlgorithm��Ĭ������Ԫ��ö�ٷ�����
/// </summary>
struct DefaultVectorIter
{
	template<typename Cont>
	static inline auto& At(Cont& container, int index) { return (iterator_data_t<Cont>&) * (std::begin(container) + index); }

	template<typename Cont>
	static inline size_t Length(Cont& container) { return container.end() - container.begin(); }
};

/// <summary>
/// ���������ࡣ�ṩ���������㷨��
/// <para>ע��ʹ���ྲ̬�㷨��ΪVecAlgorithm�ṩ����Ԫ��ö�ٷ���������Ԫ�������Ƶ�����������ʵ����������֧��Ĭ�Ϲ��졣</para>
/// <para>����Ԫ��ö�ٷ�����Ҫ��һ��������̬����At(T&amp;, int)��Length(T&amp;)���࣬����TΪ�����������͡�</para>
/// <para>����Ԫ�������Ƶ�������Ҫ��һ����������T������ģ�壬����TΪ�����������ͣ�ģ���Ƶ�������������Ԫ�����͡�</para>
/// </summary>
/// <typeparam name="IterTy">
/// ����Ԫ��ö�ٷ�����Ҫ��һ��������̬����At(T&amp;, int)��Length(T&amp;)���࣬����TΪ�����������͡�
/// </typeparam>
/// <typeparam name="DataTyInference">
/// ����Ԫ�������Ƶ�������Ҫ��һ����������T������ģ�壬����TΪ�����������ͣ�ģ���Ƶ�������������Ԫ�����͡�
/// </typeparam>
template<typename IterTy = DefaultVectorIter, template<typename> typename DataTyInference = iterator_data_t>
class VectorAlgorithm
{
public:

#define _StaIn static inline

	template<typename VecTy> using _DataOf = DataTyInference<VecTy>;
	using _Rel = GeometryRelation;

#define Operator(v1, v2, opt) VecTy res; ForEach([](auto& r, auto& a, auto & b) { r = a opt b; }, res, v1, v2); return res;

	/// <summary>
	/// �����͡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Add(VecTy v1, VecTy v2) { Operator(v1, v2, +); }
	/// <summary>
	/// �����
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Sub(VecTy v1, VecTy v2) { Operator(v1, v2, -); }
	/// <summary>
	/// ��������������������������ܳ˻���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Mul(VecTy v1, VecTy v2) { Operator(v1, v2, *); }
	/// <summary>
	/// �����̡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Div(VecTy v1, VecTy v2) { Operator(v1, v2, /); }
	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename VecTy> _StaIn _DataOf<VecTy> Dot(VecTy v1, VecTy v2)
	{
		_DataOf<VecTy> sum = 0;
		ForEach([&sum](auto& a, auto& b) { sum += a * b; }, v1, v2);
		return sum;
	}
	/// <summary>
	/// ����ģ������������
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά��ƽ���͵�����ƽ������</returns>
	template<typename VecTy> _StaIn auto Mod(VecTy v) { return sqrt(Dot(v, v)); }

	/// <summary>
	/// ������������ϵ���޻��������ߡ�
	/// ע��������������������ֱ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector1">����1��</param>
	/// <param name="vector2">����2��</param>
	/// <returns>���ι�ϵö�١�None��Perpendicular��Collinear��</returns>
	template<typename VecTy> _StaInCst _Rel Relation(VecTy vector1, VecTy vector2)
	{
		/*
			ʵ���߼���1���������Ϊ0ʱ��ֱ��2�������������ֵ������ģ�������н�����Ϊ��1��ʱ���ߡ�3������Ϊ�ޡ�
			ע��������2���ɿ���-ʩ�ߴĲ���ʽ֤�á�
		*/
		auto dot = Dot<VecTy>(vector1, vector2);
		if (Math::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (Math::Equal(Math::Abs(Math::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
	}

	/// <summary>
	/// ���������������ǹ�����������0��
	/// ע��������������������ֱ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector1">����1��</param>
	/// <param name="vector2">����2��</param>
	/// <returns>double�ͣ�������������k=v1 : v2���ǹ�����������0��</returns>
	template<typename VecTy> _StaIn double Proportion(VecTy vector1, VecTy vector2)
	{
		/*
			ʵ���߼���1���ǹ��߷���0��2������ʱ�������������ⷶ��֮�ȡ�
		*/
		if (!(Relation(vector1, vector2) & _Rel::Collinear)) return 0;
		return Norm(vector1, 1) / Norm(vector2, 1);
	}

	/// <summary>
	/// ��ȡ����������
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector">������</param>
	/// <param name="p">�������͡�1Ϊһ������2Ϊ��������0xffffffffffffffffui64���궨��UINT64_MAX��Ϊ�����������ΪP������</param>
	/// <returns>����������</returns>
	template<typename VecTy> _StaIn double Norm(VecTy vector, uint64_t p)
	{
		double result = 0;
		switch (p)
		{
		case 1:
			ForEach([&result](auto& a) { result += Math::Abs(a); }, vector);
			return result;
		case 2:
			ForEach([&result](auto& a) { result += Math::Pow2(a); }, vector);
			return sqrt(result);
		case UINT64_MAX:
			ForEach([&result](auto& a)
				{
					auto abs = Math::Abs(a);
					if (result < abs) result = abs;
				}, vector);
			return result;
		default:
			ForEach([&result, p](auto& a) { result += std::pow(a, p); }, vector);
			return pow(result, 1.0 / p);
		}
	}

	/// <summary>
	/// ͬʱ����n������ʵ��������n������Ԫ�ص�������������ѭ���������һ������ά����ͬ��
	/// ע������Ԫ��������iterator_data_t&lt;VecTy&gt;�Ƶ�ֵΪ׼������VecTy�������������͡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="vec">��һ��������</param>
	/// <param name="...args">n-1��������</param>
	template<typename VecTy, typename Func, typename... ArgsT>
	_StaIn constexpr void ForEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		size_t length = IterTy::Length(vec);
		for (int i = 0; i < length; i++)
			apply(IterTy::At(vec, i), IterTy::At(args, i)...);
	}

	/// <summary>
	/// ͬʱ����n������ʵ��������n������Ԫ�ص�������������ѭ����������Χ���С�
	/// ע������Ԫ��������iterator_data_t&lt;VecTy&gt;�Ƶ�ֵΪ׼������VecTy�������������͡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="begin">��ʼ������Ӧ��С���㡣</param>
	/// <param name="end">��ֹ����������������Ϊ���������������ȸ��ǡ�</param>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="vec">��һ��������</param>
	/// <param name="...args">n-1��������</param>
	template<typename VecTy, typename Func, typename... ArgsT>
	_StaIn constexpr void ForEachInRange(int begin, int end, Func apply, VecTy& vec, ArgsT&... args)
	{
		size_t length = IterTy::Length(vec);
		if (end < 0 || end > length) end = length;
		for (; begin < end; begin++)
			apply(IterTy::At(vec, begin), IterTy::At(args, begin)...);
	}

private:

};

/// <summary>
/// ���������ࡣ�ṩ���������㷨��
/// </summary>
typedef VectorAlgorithm<> VecAlgo;
