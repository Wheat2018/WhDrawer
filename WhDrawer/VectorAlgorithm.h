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
/// ע��ʹ���ྲ̬�㷨��ΪVecAlgorithm�ṩ����Ԫ��ö�ٷ���������ʵ����������֧��Ĭ�Ϲ��졣
/// </summary>
/// <typeparam name="IterTy">
/// ����Ԫ��ö�ٷ�����Ҫ��һ��������̬����At(T&amp;, int)��Length(T&amp;)���࣬����TΪ�����������͡�
/// </typeparam>
template<typename IterTy = DefaultVectorIter>
class VectorAlgorithm
{
public:
	template<typename VecTy> using _DataOf = iterator_data_t<VecTy>;
	using _Rel = GeometryRelation;

#define Operator(v1, v2, opt) VecTy res; ForEach(opt<iterator_data_t<VecTy>>, res, v1, v2); return res;

	/// <summary>
	/// �����͡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> static inline VecTy Add(VecTy v1, VecTy v2) { Operator(v1, v2, _add); }
	/// <summary>
	/// �����
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> static inline VecTy Sub(VecTy v1, VecTy v2) { Operator(v1, v2, _sub); }
	/// <summary>
	/// ��������������������������ܳ˻���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> static inline VecTy Mul(VecTy v1, VecTy v2) { Operator(v1, v2, _mul); }
	/// <summary>
	/// �����̡�
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>Ԫ�ض�Ӧ������ɵ���������</returns>
	template<typename VecTy> static inline VecTy Div(VecTy v1, VecTy v2) { Operator(v1, v2, _div); }
	/// <summary>
	/// ������������ڻ���
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="v1">����1��</param>
	/// <param name="v2">����2��</param>
	/// <returns>��������ά�ȳ˻��ĺ͡�</returns>
	template<typename VecTy> static inline _DataOf<VecTy> Dot(VecTy v1, VecTy v2)
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
	template<typename VecTy> static inline auto Mod(VecTy v) { return sqrt(Dot(v, v)); }

	/// <summary>
	/// ������������ϵ���޻��������ߡ�
	/// ע��������������������ֱ��
	/// </summary>
	/// <typeparam name="VecTy">�����������͡�</typeparam>
	/// <param name="vector1">����1��</param>
	/// <param name="vector2">����2��</param>
	/// <returns>���ι�ϵö�١�None��Perpendicular��Collinear��</returns>
	template<typename VecTy>
	static _Rel Relation(VecTy vector1, VecTy vector2)
	{
		/*
			ʵ���߼���1���������Ϊ0ʱ��ֱ��2�������������ֵ������ģ�������н�����Ϊ��1��ʱ���ߡ�3������Ϊ�ޡ�
			ע��������2���ɿ���-ʩ�ߴĲ���ʽ֤�á�
		*/
		_DataOf<VecTy> a;
		auto dot = Dot<VecTy>(vector1, vector2);
		if (Math::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (Math::Equal(Math::Abs(Math::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
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
	static constexpr void ForEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		size_t length = IterTy::Length(vec);
		for (int i = 0; i < length; i++)
			apply(IterTy::At(vec, i), IterTy::At(args, i)...);
	}

private:
	template<typename T> static constexpr void _add(T& res, const T& a, const T& b) { res = a + b; }
	template<typename T> static constexpr void _sub(T& res, const T& a, const T& b) { res = a - b; }
	template<typename T> static constexpr void _mul(T& res, const T& a, const T& b) { res = a * b; }
	template<typename T> static constexpr void _div(T& res, const T& a, const T& b) { res = a / b; }

};

typedef VectorAlgorithm<> VecAlgo;
