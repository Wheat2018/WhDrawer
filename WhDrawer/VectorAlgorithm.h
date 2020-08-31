#pragma once
#include "GeometryRelation.h"
#include "VectorNd.h"
#include "Math.h"


/// <summary>
/// VectorAlgorithm的默认向量元素枚举方法。
/// </summary>
struct DefaultVectorIter
{
	template<typename Cont>
	static inline constexpr auto& At(Cont& container, int index) { return (iterator_data_t<Cont>&) * (container.begin() + index); }

	template<typename Cont>
	static inline constexpr size_t Length(Cont& container) { return container.end() - container.begin(); }
};

/// <summary>
/// 向量算术类。提供各类向量算法。
/// <para>注：使用类静态算法需提供向量元素枚举方法、向量元素类型推导方法及浮点判零方法，并且实际向量类需支持默认构造。</para>
/// <para>向量元素枚举方法：要求一个包含静态方法At(T&amp;, int)和Length(T&amp;)的类，其中T为向量容器类型。</para>
/// <para>向量元素类型推导方法：要求一个接受类型T的类型模板，其中T为向量容器类型，模板推导出向量容器的元素类型。</para>
/// <para>浮点判零方法：要求一个包含静态方法IsZero(T)的类，方法返回所给数字是否为0的布尔值。</para>
/// </summary>
/// <typeparam name="IterTy">向量元素枚举方法。</typeparam>
/// <typeparam name="DataTyInference">向量元素类型推导方法。</typeparam>
/// <typeparam name="FloatZeroJudger">浮点判零方法。</typeparam>
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
	/// 向量和。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相加生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Add(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Add); }
	/// <summary>
	/// 向量差。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相减生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Sub(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Sub); }
	/// <summary>
	/// 向量基本积。（哈达玛积、智能乘积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相乘生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Mul(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Mul); }
	/// <summary>
	/// 向量商。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相除生成的新向量。</returns>
	template<typename VecTy> _StaIn VecTy Div(const VecTy& v1, const VecTy& v2) { Operator(v1, v2, Div); }

	/// <summary>
	/// 向量和。
	/// </summary>
	/// <typeparam name="RV">结果向量容器类型。</typeparam>
	/// <typeparam name="V1">向量1容器类型。</typeparam>
	/// <typeparam name="V2">向量2容器类型。</typeparam>
	/// <param name="r">结果向量。</param>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相加结果向量的引用。</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Add(RV& r, const V1& v1, const V2& v2)
	{ 
		ForEach(_Add<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// 向量差。
	/// </summary>
	/// <typeparam name="RV">结果向量容器类型。</typeparam>
	/// <typeparam name="V1">向量1容器类型。</typeparam>
	/// <typeparam name="V2">向量2容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相减结果向量的引用。</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Sub(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Sub<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// 向量基本积。（哈达玛积、智能乘积）
	/// </summary>
	/// <typeparam name="RV">结果向量容器类型。</typeparam>
	/// <typeparam name="V1">向量1容器类型。</typeparam>
	/// <typeparam name="V2">向量2容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相乘结果向量的引用。</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Mul(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Mul<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}
	/// <summary>
	/// 向量商。
	/// </summary>
	/// <typeparam name="RV">结果向量容器类型。</typeparam>
	/// <typeparam name="V1">向量1容器类型。</typeparam>
	/// <typeparam name="V2">向量2容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>元素对应相除结果向量的引用。</returns>
	template<typename RV, typename V1, typename V2> _StaIn RV& Div(RV& r, const V1& v1, const V2& v2)
	{
		ForEach(_Div<_DataOf<RV>, _DataOf<V1>, _DataOf<V2>>, r, v1, v2);
		return r;
	}


	/// <summary>
	/// 向量点积。（内积）
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="v1">向量1。</param>
	/// <param name="v2">向量2。</param>
	/// <returns>两向量各维度乘积的和。</returns>
	template<typename LVT, typename RVT> _StaInCst auto Dot(const LVT& v1, const RVT& v2)
	{
		return SumEach(_mul<_DataOf<LVT>, _DataOf<RVT>>, v1, v2);
	}

	/// <summary>
	/// 向量与向量关系：无或正交或共线。
	/// 注：零向量与任意向量垂直。
	/// </summary>
	/// <typeparam name="VecTy">向量数据类型。</typeparam>
	/// <param name="vector1">向量1。</param>
	/// <param name="vector2">向量2。</param>
	/// <returns>几何关系枚举。None或Perpendicular或Collinear。</returns>
	template<typename LVT, typename RVT> _StaInCst _Rel Relation(const LVT& vector1, const RVT& vector2)
	{
		/*
			实现逻辑：1、向量点积为0时垂直。2、向量点积绝对值等于其模积（即夹角余弦为±1）时共线。3、其余为无。
			注：上述点2可由柯西-施瓦茨不等式证得。
		*/
		auto dot = Dot(vector1, vector2);
		if (_Mth::IsZero(dot)) return _Rel::Perpendicular;

		auto mod_product_squr = Dot(vector1, vector1) * Dot(vector2, vector2);
		if (_Mth::Equal(_Mth::Abs(_Mth::Pow2(dot)), mod_product_squr)) return _Rel::Collinear;

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
	template<typename LVT, typename RVT> _StaInCst double Proportion(const LVT& vector1, const RVT& vector2)
	{
		/*
			实现逻辑：1、非共线返回0，2、共线时比例等于其任意范数之比。
		*/
		if (!(Relation(vector1, vector2) & _Rel::Collinear)) return 0;
		return Norm(vector1, 1) / Norm(vector2, 1);
	}

	/// <summary>
	/// 获取向量范数。仅一范数可使用常量表达式求值。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <param name="vector">向量。</param>
	/// <param name="p">范数类型。1为一范数，2为二范数，0xffffffffffffffffui64（宏定义UINT64_MAX）为无穷范数，其余为P范数。</param>
	/// <returns>向量范数。</returns>
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
	_StaInCst void ForEach(Func apply, VecTy& vec, ArgsT&... args)
	{
		auto length = _Itr::Length(vec);
		for (int i = 0; i < length; i++)
			apply(_Itr::At(vec, i), _Itr::At(args, i)...);
	}

	/// <summary>
	/// 同时遍历n个向量实例，并用n个向量元素调用所给方法。循环以所给范围进行。
	/// 注：向量元素类型以iterator_data_t&lt;VecTy&gt;推导值为准，其中VecTy是向量容器类型。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="begin">起始索引，应不小于零。</param>
	/// <param name="end">终止索引，过长或设置为负数则以向量长度覆盖。</param>
	/// <param name="apply">应用方法。</param>
	/// <param name="vec">第一个向量。</param>
	/// <param name="...args">n-1个向量。</param>
	template<typename VecTy, typename Func, typename... ArgsT>
	_StaInCst void ForEachInRange(int begin, int end, Func apply, VecTy& vec, ArgsT&... args)
	{
		auto length = _Itr::Length(vec);
		if (end < 0 || end > length) end = length;
		for (; begin < end; begin++)
			apply(_Itr::At(vec, begin), _Itr::At(args, begin)...);
	}

	/// <summary>
	/// 同时遍历n个向量实例，并用n个向量元素调用所给方法，累加方法返回值。循环次数与第一个向量维度相同。
	/// 注：向量元素类型以iterator_data_t&lt;VecTy&gt;推导值为准，其中VecTy是向量容器类型。返回值类型与所给方法返回值类型相同。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="apply">应用方法。</param>
	/// <param name="vec">第一个向量。</param>
	/// <param name="...args">n-1个向量。</param>
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
	/// 同时遍历n个向量实例，并用n个向量元素调用所给方法，累加方法返回值。循环以所给范围进行。
	/// 注：向量元素类型以iterator_data_t&lt;VecTy&gt;推导值为准，其中VecTy是向量容器类型。
	/// </summary>
	/// <typeparam name="VecTy">向量容器类型。</typeparam>
	/// <typeparam name="Func">应用方法类型。</typeparam>
	/// <typeparam name="...ArgsT">类型包。</typeparam>
	/// <param name="begin">起始索引，应不小于零。</param>
	/// <param name="end">终止索引，过长或设置为负数则以向量长度覆盖。</param>
	/// <param name="apply">应用方法。</param>
	/// <param name="vec">第一个向量。</param>
	/// <param name="...args">n-1个向量。</param>
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
/// 向量算术类。提供各类向量算法。
/// </summary>
typedef VectorAlgorithm<> VecAlgo;
