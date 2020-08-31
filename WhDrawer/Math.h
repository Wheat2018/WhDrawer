#pragma once
#include <iostream>
#include <cmath>

template<typename T> struct promotion { using Type = float; };
template<> struct promotion<float> { using Type = float; };
template<> struct promotion<double> { using Type = double; };
template<typename T1, typename T2> struct upper { using Type = decltype(T1(0) + T2(0)); };
template <typename Cont>
struct iterator_data
{
	template<typename _Cont>
	static constexpr auto Decl() {  _Cont* p; return Decl(*p); }
	template<typename _Cont>
	static constexpr auto Decl(_Cont cont) { return std::cbegin(cont); }
	template<typename _Tp>
	static constexpr auto Decl(_Tp* tp) { return *tp; }

	using ConstPointerType = decltype(Decl<Cont>());
	using ConstType = std::remove_pointer_t<ConstPointerType>;
	using Type = std::remove_const_t< ConstType>;
};

//Type inference
/// <summary>
/// 提升类型。当待提升类型为非浮点时，提升为float，否则保留原类型。
/// </summary>
/// <typeparam name="T">待提升类型。</typeparam>
template<typename T>
using promotion_t = typename promotion<T>::Type;

/// <summary>
/// 提取高级类型。比较两个类型，并提取其中较高级的类型。
/// </summary>
/// <typeparam name="T1">类型1。</typeparam>
/// <typeparam name="T2">类型2。</typeparam>
template<typename T1, typename T2>
using upper_t = typename upper<T1, T2>::Type;

/// <summary>
/// 根据容器的begin()函数返回类型，推导出容器的元素数据类型。容器必须支持默认构造。
/// </summary>
/// <typeparam name="Cont">容器类型。</typeparam>
template <typename Cont>
using iterator_data_t = typename iterator_data<Cont>::Type;


struct DefaultFloatZeroJudger;

/// <summary>
/// 提供各类数学算法。
/// <para>浮点判零方法：要求一个包含静态方法IsZero(T)的类，方法返回所给数字是否为0的布尔值。</para>
/// </summary>
/// <typeparam name="FloatZeroJudger">浮点判零方法。</typeparam>
template <typename FloatZeroJudger = DefaultFloatZeroJudger>
class _Math
{
public:
#define _StaInCst static inline constexpr
#define _StaIn static inline

	/// <summary>
	/// 取容器中最大值的引用。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <returns>对容器中最大值的引用</returns>
	template<typename Cont> _StaIn auto& MaxIn(Cont& container)
	{
		return MaxIn(std::begin(container), std::end(container));
	}
	template<typename Iter> _StaIn Iter& MaxIn(Iter begin, Iter end)
	{
		auto pMax = begin;
		auto pEnd = end;
		if (pMax != pEnd)
			for (auto iter = pMax + 1; iter != pEnd; iter++)
				if (*pMax < *iter) pMax = iter;
		return *pMax;
	}
	/// <summary>
	/// 取容器中最小值的引用。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <returns>对容器中最大值的引用</returns>
	template<typename Cont> _StaIn auto& MinIn(Cont& container)
	{
		return MinIn(std::begin(container), std::end(container));
	}
	template<typename Iter> _StaIn auto& MinIn(Iter begin, Iter end)
	{
		auto pMin = begin;
		auto pEnd = end;
		if (pMin != pEnd)
			for (auto iter = pMin + 1; iter != pEnd; iter++)
				if (*pMin > * iter) pMin = iter;
		return *pMin;
	}

	/// <summary>
	/// 容器元素值求和。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <returns>容器元素值求和值。</returns>
	template<typename Cont> _StaIn auto SumOf(const Cont& container)
	{
		return SumOf(std::begin(container), std::end(container));
	}
	template<typename Iter> _StaIn auto SumOf(const Iter& begin, const Iter& end)
	{
		std::remove_const_t<std::remove_reference_t<decltype(*begin)>> sum = 0;
		auto iter = begin;
		auto pEnd = end;
		for (; iter != pEnd; iter++) sum += *iter;
		return sum;
	}

	/// <summary>
	/// 对容器中元素应用处理方法，并取最大值引用。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <param name="func">处理方法：以容器数据类型（或引用）为入参、返回已重载小于号的类型数据的函数或Lambda表达式。</param>
	/// <returns>对容器中最大值的引用。</returns>
	template<typename Cont, typename Func> _StaIn auto& MaxWith(Cont& container, Func func)
	{
		return MaxWith(std::begin(container), std::end(container), func);
	}
	template<typename Iter, typename Func> _StaIn auto& MaxWith(Iter begin, Iter end, Func func)
	{
		auto pMax = begin;
		auto max = func(*pMax);
		auto pEnd = end;
		if (pMax != pEnd)
			for (auto iter = pMax + 1; iter != pEnd; iter++)
			{
				auto res = func(*iter);
				if (max < res)
				{
					pMax = iter;
					max = res;
				}
			}
		return *pMax;
	}

	/// <summary>
	/// 对容器中元素应用处理方法，并取最小值引用。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <param name="func">处理方法：以容器数据类型（或引用）为入参、返回已重载大于号的类型数据的函数或Lambda表达式。</param>
	/// <returns>对容器中最小值的引用。</returns>
	template<typename Cont, typename Func> _StaIn auto& MinWith(Cont& container, Func func)
	{
		return MinWith(std::begin(container), std::end(container), func);
	}
	template<typename Iter, typename Func> _StaIn auto& MinWith(Iter begin, Iter end, Func func)
	{
		auto pMin = begin;
		auto min = func(*pMin);
		auto pEnd = end;
		if (pMin != pEnd)
			for (auto iter = pMin + 1; iter != pEnd; iter++)
			{
				auto res = func(*iter);
				if (min > res)
				{
					pMin = iter;
					min = res;
				}
			}
		return *pMin;
	}

	/// <summary>
	/// 对容器中元素应用处理方法，并取返回值相加。
	/// </summary>
	/// <typeparam name="Cont">容器类型。</typeparam>
	/// <param name="container">容器。</param>
	/// <param name="func">处理方法：以容器数据类型（或引用）为入参、返回已重载加号的类型数据的函数或Lambda表达式。</param>
	/// <returns>处理方法返回值求和。</returns>
	template<typename Cont, typename Func> _StaIn auto SumWith(const Cont& container, Func func)
	{
		return SumWith(std::begin(container), std::end(container), func);
	}
	template<typename Iter, typename Func> _StaIn auto SumWith(Iter begin, Iter end, Func func)
	{
		std::remove_const_t<std::remove_reference_t<decltype(func(*begin))>> sum = 0;
		for (; begin != end; begin++) sum += func(*begin);
		return sum;
	}

	//Utility Constexpr
	/// <summary>
	/// 判断两个数是否相等。浮点与非浮点判断方法有异。
	/// </summary>
	/// <param name="num1">浮点。</param>
	/// <param name="num2">浮点。</param>
	/// <returns></returns>
	template<typename T1, typename T2> _StaInCst bool Equal(const T1& num1, const T2& num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// 判断若干个数是否相等。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst bool Equal(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		if (Equal(num1, num2))
			return Equal(num2, args...);
		return false;
	}

	/// <summary>
	/// 判断某数是否为0。
	/// </summary>
	/// <typeparam name="T">数字数据类型。</typeparam>
	/// <param name="num">数字。</param>
	/// <returns></returns>
	template<typename T> _StaInCst bool IsZero(const T& num) { return num == T(0); }
	template<> _StaInCst bool IsZero(const float& num) { return DefaultFloatZeroJudger::IsZero((const float&)num); }
	template<> _StaInCst bool IsZero(const double& num) { return DefaultFloatZeroJudger::IsZero((const double&)num); }

	/// <summary>
	/// 取平方。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>平方。</returns>
	template<typename T> _StaInCst T Pow2(const T& x) { return x * x; }

	/// <summary>
	/// 取绝对值。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>绝对值。</returns>
	template<typename T> _StaInCst T Abs(const T& x) { return x >= 0 ? x : -x; }

	/// <summary>
	/// 取最大值。该函数需在O2优化下以达到最佳性能。入参含临时变量时，函数可能返回临时变量引用，谨慎使用。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto&& Max(T1&& num1, T2&& num2, ArgsT&&... args)
	{ return Max(Max(num1, num2), args...); }
	template<typename T1, typename T2> _StaInCst auto&& Max(T1&& num1, T2&& num2) { return num1 >= num2 ? num1 : num2; }

	/// <summary>
	/// 取最小值。该函数需在O2优化下以达到最佳性能。入参含临时变量时，函数可能返回临时变量引用，谨慎使用。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto&& Min(T1&& num1, T2&& num2, ArgsT&&... args)
	{
		return Min(Min(num1, num2), args...);
	}
	template<typename T1, typename T2> _StaInCst auto&& Min(T1&& num1, T2&& num2) { return num1 <= num2 ? num1 : num2; }

	/// <summary>
	/// 取最大值索引。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst int ArgMax(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMax(left, right, num1, num2, args...);
		return left;
	}
	
	/// <summary>
	/// 取最小值索引。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst int ArgMin(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMin(left, right, num1, num2, args...);
		return left;
	}

	/// <summary>
	/// 取参数列表(num1, num2, num3...)中指定索引的引用。索引值越界或不合法，都返回索引为0的引用。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto& At(int index, T1& num1, T2& num2, ArgsT&... args)
	{
		int now = 0;
		return _At(now, index, num1, num2, args...);
	}

	/// <summary>
	/// 获取类型的无穷值。
	/// </summary>
	/// <typeparam name="T">类型。</typeparam>
	/// <returns>无符号整型全位为1，有符号整型除符号位外为1，浮点类型为其溢出值。</returns>
	template<typename T> _StaInCst T Infinity()
	{
		return std::is_signed_v<T> ? ((T(0) - 1) ^ ((T)1 << (sizeof(T) * 8 - 1))) : (T(0) - 1);
	}
	template<> _StaInCst float Infinity() { return 1e+300 * 1e+300; }
	template<> _StaInCst double Infinity() { return 1e+300 * 1e+300; }


private:
	template<typename T1, typename T2> 
	_StaInCst auto& _ArgMax(int& left, int& right, const T1& num1, const T2& num2)
	{
		++right;
		if (num1 < num2)
		{
			left = right;
			return num2;
		}
		return num1;
	}
	template<typename T1, typename T2, typename... ArgsT> 
	_StaInCst auto& _ArgMax(int& left, int& right, const T1& num1, const T2& num2, const ArgsT&... args)
	{
		return _ArgMax(left, right, _ArgMax(left, right, num1, num2), args...);
	}
	template<typename T1, typename T2>
	_StaInCst auto& _ArgMin(int& left, int& right, const T1& num1, const T2& num2)
	{
		++right;
		if (num1 > num2)
		{
			left = right;
			return num2;
		}
		return num1;
	}
	template<typename T1, typename T2, typename... ArgsT>
	_StaInCst auto& _ArgMin(int& left, int& right, const T1& num1, const T2& num2, const ArgsT&... args)
	{
		return _ArgMin(left, right, _ArgMin(left, right, num1, num2), args...);
	}
	template<typename T1, typename T2>
	_StaInCst auto& _At(int& now, int target, T1& num1, T2& num2)
	{
		return ++now == target ? num2 : num1;
	}
	template<typename T1, typename T2, typename... ArgsT>
	_StaInCst auto& _At(int& now, int target, T1& num1, T2& num2, ArgsT&... args)
	{
		return _At(now, target, _At(now, target, num1, num2), args...);
	}

};

/// <summary>
/// 提供各类数学算法。
/// </summary>
typedef _Math<> Math;

struct DefaultFloatZeroJudger
{
	/// <summary>
	/// 浮点等价判断允许最大误差，当两个浮点数差值小于该值，认为其相等，默认为1e-6。
	/// </summary>
	static constexpr float eps = 1e-6f;
	template<typename T> static constexpr bool IsZero(const T& x) { return Math::Abs(x) < eps; }
};

