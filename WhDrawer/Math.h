#pragma once
#include <iostream>
#include <cmath>

/// <summary>
/// 提供各类数学算法。
/// </summary>
class Math
{
public:
	/// <summary>
	/// 浮点等价判断允许最大误差，当两个浮点数差值小于该值，认为其相等，默认为1e-6。
	/// </summary>
	static float eps;

	//Utility Constexpr
	/// <summary>
	/// 判断两个数是否相等。浮点与非浮点判断方法有异。
	/// </summary>
	/// <param name="num1">浮点。</param>
	/// <param name="num2">浮点。</param>
	/// <returns></returns>
	template<typename T1, typename T2> static constexpr bool Equal(const T1& num1, const T2& num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// 判断某数是否为0。
	/// </summary>
	/// <typeparam name="T">数字数据类型。</typeparam>
	/// <param name="num">数字。</param>
	/// <returns></returns>
	template<typename T> static constexpr bool IsZero(const T& num) { return num == T(0); }
	template<> static constexpr bool IsZero(const float& num) { return Abs(num) < eps; }
	template<> static constexpr bool IsZero(const double& num) { return Abs(num) < eps; }

	/// <summary>
	/// 取平方。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>平方。</returns>
	template<typename T> static constexpr T Pow2(const T& x) { return x * x; }

	/// <summary>
	/// 取绝对值。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>绝对值。</returns>
	template<typename T> static constexpr T Abs(const T& x) { return x >= 0 ? x : -x; }

	/// <summary>
	/// 取最大值。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr auto& Max(T1& num1, T2& num2, ArgsT&... args) 
	{ return Max(Max(num1, num2), args...); }
	template<typename T1, typename T2> static constexpr auto& Max(T1& num1, T2& num2) { return num1 >= num2 ? num1 : num2; }

	/// <summary>
	/// 取最小值。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr auto& Min(T1& num1, T2& num2, ArgsT&... args)
	{
		return Min(Min(num1, num2), args...);
	}
	template<typename T1, typename T2> static constexpr auto& Min(T1& num1, T2& num2) { return num1 <= num2 ? num1 : num2; }

	/// <summary>
	/// 取最大值索引。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr int ArgMax(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMax(left, right, num1, num2, args...);
		return left;
	}
	
	/// <summary>
	/// 取最小值索引。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr int ArgMin(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMin(left, right, num1, num2, args...);
		return left;
	}

	/// <summary>
	/// 取参数列表(num1, num2, num3...)中指定索引的引用。索引值越界或不合法，都返回索引为0的引用。该函数需在O2优化下以达到最佳性能。
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr auto& At(int index, T1& num1, T2& num2, ArgsT&... args)
	{
		int now = 0;
		return _At(now, index, num1, num2, args...);
	}

private:
	template<typename T1, typename T2> 
	static constexpr auto& _ArgMax(int& left, int& right, const T1& num1, const T2& num2)
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
	static constexpr auto& _ArgMax(int& left, int& right, const T1& num1, const T2& num2, const ArgsT&... args)
	{
		return _ArgMax(left, right, _ArgMax(left, right, num1, num2), args...);
	}
	template<typename T1, typename T2>
	static constexpr auto& _ArgMin(int& left, int& right, const T1& num1, const T2& num2)
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
	static constexpr auto& _ArgMin(int& left, int& right, const T1& num1, const T2& num2, const ArgsT&... args)
	{
		return _ArgMin(left, right, _ArgMin(left, right, num1, num2), args...);
	}
	template<typename T1, typename T2>
	static constexpr auto& _At(int& now, int target, T1& num1, T2& num2)
	{
		return ++now == target ? num2 : num1;
	}
	template<typename T1, typename T2, typename... ArgsT>
	static constexpr auto& _At(int& now, int target, T1& num1, T2& num2, ArgsT&... args)
	{
		return _At(now, target, _At(now, target, num1, num2), args...);
	}

};

template<typename T> struct promotion { using Type = float; };
template<> struct promotion<float> { using Type = float; };
template<> struct promotion<double> { using Type = double; };
template<typename T1, typename T2> struct upper { using Type = decltype(T1(0) + T2(0)); };
template <typename Cont>
struct iterator_data
{
	using ConstPointerType = decltype(Cont().begin());
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
