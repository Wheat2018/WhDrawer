#pragma once
#include <initializer_list>
#include "GeometryRelation.h"
#include "VectorNd.h"
#include "Math.h"


/// <summary>
/// VecAlgorithm的默认向量元素枚举方法。
/// </summary>
struct DefaultVectorIter
{
	template<typename Cont>
	static inline auto& At(Cont& container, int index) { return (iterator_data_t<Cont>&) * (std::begin(container) + index); }

	template<typename Cont>
	static inline size_t Length(Cont& container) { return container.end() - container.begin(); }
};

/// <summary>
/// 向量算术类。提供各类向量算法。
/// 注：使用类静态算法需为VecAlgorithm提供向量元素枚举方法，并且实际向量类需支持默认构造。
/// </summary>
/// <typeparam name="IterTy">
/// 向量元素枚举方法。要求一个包含静态方法At(T&amp;, int)和Length(T&amp;)的类，其中T为向量容器类型。
/// </typeparam>
template<typename IterTy = DefaultVectorIter>
class VectorAlgorithm
{
public:
	template<typename VecTy> using _DataOf = iterator_data_t<VecTy>;
	using _Rel = GeometryRelation;

#define Operator(v1, v2, opt) VecTy res; ForEach(opt<iterator_data_t<VecTy>>, res, v1, v2); return res;

	/// <summary>
	/// 向量和。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相加生成的新向量。</returns>
	template<typename VecTy> static inline VecTy Add(VecTy v1, VecTy v2) { Operator(v1, v2, _add); }
	/// <summary>
	/// 向量差。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相减生成的新向量。</returns>
	template<typename VecTy> static inline VecTy Sub(VecTy v1, VecTy v2) { Operator(v1, v2, _sub); }
	/// <summary>
	/// 向量基本积。（哈达玛积、智能乘积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相乘生成的新向量。</returns>
	template<typename VecTy> static inline VecTy Mul(VecTy v1, VecTy v2) { Operator(v1, v2, _mul); }
	/// <summary>
	/// 向量商。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相除生成的新向量。</returns>
	template<typename VecTy> static inline VecTy Div(VecTy v1, VecTy v2) { Operator(v1, v2, _div); }
	/// <summary>
	/// 向量点积。（内积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度乘积的和。</returns>
	template<typename VecTy> static inline _DataOf<VecTy> Dot(VecTy v1, VecTy v2)
	{
		_DataOf<VecTy> sum = 0;
		ForEach([&sum](auto& a, auto& b) { sum += a * b; }, v1, v2);
		return sum;
	}
	/// <summary>
	/// 向量模。（二范数）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度平方和的算术平方根。</returns>
	template<typename VecTy> static inline auto Mod(VecTy v) { return sqrt(Dot(v, v)); }

	/// <summary>
	/// 向量与向量关系：无或正交或共线。
	/// 注：零向量与任意向量垂直。
	/// </summary>
	/// <typeparam name="VecTy">向量数据类型。</typeparam>
	/// <param name="vector1">向量1。</param>
	/// <param name="vector2">向量2。</param>
	/// <returns>几何关系枚举。None或Perpendicular或Collinear。</returns>
	template<typename VecTy>
	static _Rel Relation(VecTy vector1, VecTy vector2)
	{
		/*
			实现逻辑：1、向量点积为0时垂直。2、向量点积绝对值等于其模积（即夹角余弦为±1）时共线。3、其余为无。
			注：上述点2可由柯西-施瓦茨不等式证得。
		*/
		_DataOf<VecTy> a;
		auto dot = Dot<VecTy>(vector1, vector2);
		if (Math::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (Math::Equal(Math::Abs(Math::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
	}

	/// <summary>
	/// 同时遍历n个向量实例，并用n个向量元素调用所给方法。循环次数与第一个向量维度相同。
	/// 注：向量元素类型以iterator_data_t&lt;VecTy&gt;推导值为准，其中VecTy是向量容器类型。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="apply">应用方法。</param>
	/// <param name="vec">第一个向量。</param>
	/// <param name="...args">n-1个向量。</param>
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
