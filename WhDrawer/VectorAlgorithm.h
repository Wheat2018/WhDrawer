#pragma once
#include "GeometryRelation.h"
#include "VectorNd.h"
#include "Math.h"


/// <summary>
/// VectorAlgorithm��Ĭ������Ԫ��ö�ٷ�����
/// </summary>
struct DefaultVectorIter
{
	template<typename Cont>
	static inline constexpr auto& At(Cont& container, int index) { return (iterator_data_t<Cont>&) * (container.begin() + index); }

	template<typename Cont>
	static inline constexpr size_t Length(Cont& container) { return container.end() - container.begin(); }
};

/// <summary>
/// ���������ࡣ�ṩ���������㷨��
/// <para>ע��ʹ���ྲ̬�㷨���ṩ����Ԫ��ö�ٷ���������Ԫ�������Ƶ��������������㷽��������ʵ����������֧��Ĭ�Ϲ��졣</para>
/// <para>����Ԫ��ö�ٷ�����Ҫ��һ��������̬����At(T&amp;, int)��Length(T&amp;)���࣬����TΪ�����������͡�</para>
/// <para>����Ԫ�������Ƶ�������Ҫ��һ����������T������ģ�壬����TΪ�����������ͣ�ģ���Ƶ�������������Ԫ�����͡�</para>
/// <para>�������㷽����Ҫ��һ��������̬����IsZero(T)���࣬�����������������Ƿ�Ϊ0�Ĳ���ֵ��</para>
/// </summary>
/// <typeparam name="IterTy">����Ԫ��ö�ٷ�����</typeparam>
/// <typeparam name="DataTyInference">����Ԫ�������Ƶ�������</typeparam>
/// <typeparam name="FloatZeroJudger">�������㷽����</typeparam>
template<
	typename IterTy = DefaultVectorIter, 
	template<typename> typename DataTyInference = iterator_data_t,
	typename FloatZeroJudger = DefaultFloatZeroJudger
>
class VectorAlgorithm
{
public:

#define _StaIn static inline
#define _StaInCst static inline constexpr

	template<typename VecTy> using _DataOf = DataTyInference<VecTy>;
	using _Itr = IterTy;
	using _Rel = GeometryRelation;
	using _Mth = typename _Math<FloatZeroJudger>;

#define Operator(v1, v2, opt) VecTy res; opt(res, v1, v2); return res;

	//Operator
	/// <summary>
	/// �����͡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Add(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Add); }
	/// <summary>
	/// �����
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Sub(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Sub); }
	/// <summary>
	/// ��������������������������ܳ˻���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Mul(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Mul); }
	/// <summary>
	/// �����̡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> _StaIn VecTy Div(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Div); }

	/// <summary>
	/// �����͡�
	/// </summary>
	/// <typeparam name="RV">��������������͡�</typeparam>
	/// <typeparam name="V1">����1�������͡�</typeparam>
	/// <typeparam name="V2">����2�������͡�</typeparam>
	/// <param name="r">���������</param>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��ӽ�����������á�</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Add(RV& r, const V1& v1, const V2& v2)
	{ 
		ForEach(_Add<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// �����
	/// </summary>
	/// <typeparam name="RV">��������������͡�</typeparam>
	/// <typeparam name="V1">����1�������͡�</typeparam>
	/// <typeparam name="V2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ���������������á�</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Sub(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Sub<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// ��������������������������ܳ˻���
	/// </summary>
	/// <typeparam name="RV">��������������͡�</typeparam>
	/// <typeparam name="V1">����1�������͡�</typeparam>
	/// <typeparam name="V2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ��˽�����������á�</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Mul(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Mul<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// �����̡�
	/// </summary>
	/// <typeparam name="RV">��������������͡�</typeparam>
	/// <typeparam name="V1">����1�������͡�</typeparam>
	/// <typeparam name="V2">����2�������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ���������������á�</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Div(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Div<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}


	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename LVT, typename RVT> _StaInCst auto Dot(const LVT& v1, const RVT& v2)
	{
		return SumEach(_mul<_DataOf<LVT>, _DataOf<RVT>>, v1, v2);
	}

	/// <summary>
	/// ������������ϵ���޻��������ߡ�
	/// ע��������������������ֱ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector1">����1��</param>
	/// <param name="vector2">����2��</param>
	/// <returns>���ι�ϵö�١�None��Perpendicular��Collinear��</returns>
	template<typename LVT, typename RVT> _StaInCst _Rel Relation(const LVT& vector1, const RVT& vector2)
	{
		/*
			ʵ���߼���1���������Ϊ0ʱ��ֱ��2�������������ֵ������ģ�������н�����Ϊ��1��ʱ���ߡ�3������Ϊ�ޡ�
			ע��������2���ɿ���-ʩ�ߴĲ���ʽ֤�á�
		*/
		auto dot = Dot(vector1, vector2);
		if (_Mth::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (_Mth::Equal(_Mth::Abs(_Mth::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

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
	template<typename LVT, typename RVT> _StaInCst double Proportion(const LVT& vector1, const RVT& vector2)
	{
		/*
			ʵ���߼���1���ǹ��߷���0��2������ʱ�������������ⷶ��֮�ȡ�
		*/
		if (!(Relation(vector1, vector2) & _Rel::Collinear)) return 0;
		return Norm(vector1, 1) / Norm(vector2, 1);
	}

	/// <summary>
	/// ��ȡ������������һ������ʹ�ó������ʽ��ֵ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector">������</param>
	/// <param name="p">�������͡�1Ϊһ������2Ϊ��������0xffffffffffffffffui64���궨��UINT64_MAX��Ϊ�����������ΪP������</param>
	/// <returns>����������</returns>
	template<typename VecTy> _StaInCst double Norm(const VecTy& vector, const int p)
	{
		double result = 0;
		switch (p)
		{
		case 1:
			return SumEach(Math::Abs<_DataOf<VecTy>>, vector);
		case 2:
			result = SumEach(Math::Pow2<_DataOf<VecTy>>, vector);
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
	_StaInCst void ForEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		auto length = _Itr::Length(vec);
		for (int i = 0; i < length; i++)
			apply(_Itr::At(vec, i), _Itr::At(args, i)...);
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
	_StaInCst void ForEachInRange(int begin, int end, Func apply, VecTy& vec, ArgsT&... args)
	{
		auto length = _Itr::Length(vec);
		if (end < 0 || end > length) end = length;
		for (; begin < end; begin++)
			apply(_Itr::At(vec, begin), _Itr::At(args, begin)...);
	}

	/// <summary>
	/// ͬʱ����n������ʵ��������n������Ԫ�ص��������������ۼӷ�������ֵ��ѭ���������һ������ά����ͬ��
	/// ע������Ԫ��������iterator_data_t&lt;VecTy&gt;�Ƶ�ֵΪ׼������VecTy�������������͡�����ֵ������������������ֵ������ͬ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <typeparam name="Func">Ӧ�÷������͡�</typeparam>
	/// <typeparam name="...ArgsT">���Ͱ���</typeparam>
	/// <param name="apply">Ӧ�÷�����</param>
	/// <param name="vec">��һ��������</param>
	/// <param name="...args">n-1��������</param>
	template<typename VecTy, typename Func, typename... ArgsT>
	_StaInCst auto SumEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		decltype(apply(_Itr::At(vec, 0), _Itr::At(args, 0)...)) sum = 0;
		auto length = _Itr::Length(vec);
		for (int i = 0; i < length; i++)
			sum += apply(_Itr::At(vec, i), _Itr::At(args, i)...);
		return sum;
	}

	/// <summary>
	/// ͬʱ����n������ʵ��������n������Ԫ�ص��������������ۼӷ�������ֵ��ѭ����������Χ���С�
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
	_StaInCst auto SumEachInRange(int begin, int end, Func apply, VecTy& vec, ArgsT&... args)
	{
		decltype(apply(_Itr::At(vec, begin), _Itr::At(args, begin)...)) sum = 0;
		auto length = _Itr::Length(vec);
		if (end < 0 || end > length) end = length;
		for (; begin < end; begin++)
			sum += apply(_Itr::At(vec, begin), _Itr::At(args, begin)...);
		return sum;
	}

private:

	template<typename LT, typename RT> _StaInCst auto _mul(const LT& a, const RT& b) { return a * b; }

	template<typename T1, typename T2, typename T3> _StaInCst void _Add(T1& r, const T2& a, const T3& b) { r = a + b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Sub(T1& r, const T2& a, const T3& b) { r = a - b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Mul(T1& r, const T2& a, const T3& b) { r = a * b; }
	template<typename T1, typename T2, typename T3> _StaInCst void _Div(T1& r, const T2& a, const T3& b) { r = a / b; }

};

/// <summary>
/// ���������ࡣ�ṩ���������㷨��
/// </summary>
typedef VectorAlgorithm<> VecAlgo;
