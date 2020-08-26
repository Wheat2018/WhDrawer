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
	template<typename T1, typename T2>
	static constexpr bool Equal(T1 num1, T2 num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// 判断某数是否为0。
	/// </summary>
	/// <typeparam name="T">数字数据类型。</typeparam>
	/// <param name="num">数字。</param>
	/// <returns></returns>
	template<typename T>
	static constexpr bool IsZero(T num) { return num == T(0); }

	/// <summary>
	/// 判断某数是否为0。浮点型特化重载。
	/// </summary>
	/// <param name="num">数字。</param>
	/// <returns></returns>
	template<>
	static constexpr bool IsZero(float num) { return Abs(num) < eps; }

	/// <summary>
	/// 判断某数是否为0。浮点型特化重载。
	/// </summary>
	/// <param name="num">数字。</param>
	/// <returns></returns>
	template<>
	static constexpr bool IsZero(double num) { return Abs(num) < eps; }

	/// <summary>
	/// 取平方。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>平方。</returns>
	template<typename T>
	static constexpr T Pow2(T x) { return x * x; }

	/// <summary>
	/// 取绝对值。
	/// </summary>
	/// <typeparam name="T">数据类型。</typeparam>
	/// <param name="x">数据。</param>
	/// <returns>绝对值。</returns>
	template<typename T>
	static constexpr T Abs(T x) { return x >= 0 ? x : -x; }

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
