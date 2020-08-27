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
/// <para>注：使用类静态算法需为VecAlgorithm提供向量元素枚举方法及向量元素类型推导方法，并且实际向量类需支持默认构造。</para>
/// <para>向量元素枚举方法：要求一个包含静态方法At(T&amp;, int)和Length(T&amp;)的类，其中T为向量容器类型。</para>
/// <para>向量元素类型推导方法：要求一个接受类型T的类型模板，其中T为向量容器类型，模板推导出向量容器的元素类型。</para>
/// </summary>
/// <typeparam name="IterTy">
/// 向量元素枚举方法。要求一个包含静态方法At(T&amp;, int)和Length(T&amp;)的类，其中T为向量容器类型。
/// </typeparam>
/// <typeparam name="DataTyInference">
/// 向量元素类型推导方法。要求一个接受类型T的类型模板，其中T为向量容器类型，模板推导出向量容器的元素类型。
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
	/// 向量和。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相加生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Add(VecTy v1, VecTy v2) { Operator(v1, v2, +); }
	/// <summary>
	/// 向量差。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相减生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Sub(VecTy v1, VecTy v2) { Operator(v1, v2, -); }
	/// <summary>
	/// 向量基本积。（哈达玛积、智能乘积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相乘生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Mul(VecTy v1, VecTy v2) { Operator(v1, v2, *); }
	/// <summary>
	/// 向量商。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相除生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Div(VecTy v1, VecTy v2) { Operator(v1, v2, /); }
	/// <summary>
	/// 向量点积。（内积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度乘积的和。</returns>
	template<typename VecTy> _StaIn _DataOf<VecTy> Dot(VecTy v1, VecTy v2)
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
	template<typename VecTy> _StaIn auto Mod(VecTy v) { return sqrt(Dot(v, v)); }

	/// <summary>
	/// 向量与向量关系：无或正交或共线。
	/// 注：零向量与任意向量垂直。
	/// </summary>
	/// <typeparam name="VecTy">向量数据类型。</typeparam>
	/// <param name="vector1">向量1。</param>
	/// <param name="vector2">向量2。</param>
	/// <returns>几何关系枚举。None或Perpendicular或Collinear。</returns>
	template<typename VecTy> _StaInCst _Rel Relation(VecTy vector1, VecTy vector2)
	{
		/*
			实现逻辑：1、向量点积为0时垂直。2、向量点积绝对值等于其模积（即夹角余弦为±1）时共线。3、其余为无。
			注：上述点2可由柯西-施瓦茨不等式证得。
		*/
		auto dot = Dot<VecTy>(vector1, vector2);
		if (Math::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (Math::Equal(Math::Abs(Math::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

		return _Rel::None;
	}

	/// <summary>
	/// 共线向量比例，非共线向量返回0。
	/// 注：零向量与任意向量垂直。
	/// </summary>
	/// <typeparam name="VecTy">向量数据类型。</typeparam>
	/// <param name="vector1">向量1。</param>
	/// <param name="vector2">向量2。</param>
	/// <returns>double型，共线向量返回k=v1 : v2，非共线向量返回0。</returns>
	template<typename VecTy> _StaIn double Proportion(VecTy vector1, VecTy vector2)
	{
		/*
			实现逻辑：1、非共线返回0，2、共线时比例等于其任意范数之比。
		*/
		if (!(Relation(vector1, vector2) & _Rel::Collinear)) return 0;
		return Norm(vector1, 1) / Norm(vector2, 1);
	}

	/// <summary>
	/// 获取向量范数。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="vector">向量。</param>
	/// <param name="p">范数类型。1为一范数，2为二范数，0xffffffffffffffffui64（宏定义UINT64_MAX）为无穷范数，其余为P范数。</param>
	/// <returns>向量范数。</returns>
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
	_StaIn constexpr void ForEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		size_t length = IterTy::Length(vec);
		for (int i = 0; i < length; i++)
			apply(IterTy::At(vec, i), IterTy::At(args, i)...);
	}

	/// <summary>
	/// 同时遍历n个向量实例，并用n个向量元素调用所给方法。循环以所给范围进行。
	/// 注：向量元素类型以iterator_data_t&lt;VecTy&gt;推导值为准，其中VecTy是向量容器类型。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="begin">开始索引，应不小于零。</param>
	/// <param name="end">终止索引，过长或设置为负数则以向量长度覆盖。</param>
	/// <param name="apply">应用方法。</param>
	/// <param name="vec">第一个向量。</param>
	/// <param name="...args">n-1个向量。</param>
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
/// 向量算术类。提供各类向量算法。
/// </summary>
typedef VectorAlgorithm<> VecAlgo;
