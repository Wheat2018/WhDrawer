#pragma once
#include <iostream>
#include <cmath>

/// <summary>
/// �ṩ������ѧ�㷨��
/// </summary>
class Math
{
public:
	/// <summary>
	/// ����ȼ��ж������������������������ֵС�ڸ�ֵ����Ϊ����ȣ�Ĭ��Ϊ1e-6��
	/// </summary>
	static float eps;

	//Utility Constexpr
	/// <summary>
	/// �ж��������Ƿ���ȡ�������Ǹ����жϷ������졣
	/// </summary>
	/// <param name="num1">���㡣</param>
	/// <param name="num2">���㡣</param>
	/// <returns></returns>
	template<typename T1, typename T2>
	static constexpr bool Equal(T1 num1, T2 num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// �ж�ĳ���Ƿ�Ϊ0��
	/// </summary>
	/// <typeparam name="T">�����������͡�</typeparam>
	/// <param name="num">���֡�</param>
	/// <returns></returns>
	template<typename T>
	static constexpr bool IsZero(T num) { return num == T(0); }

	/// <summary>
	/// �ж�ĳ���Ƿ�Ϊ0���������ػ����ء�
	/// </summary>
	/// <param name="num">���֡�</param>
	/// <returns></returns>
	template<>
	static constexpr bool IsZero(float num) { return Abs(num) < eps; }

	/// <summary>
	/// �ж�ĳ���Ƿ�Ϊ0���������ػ����ء�
	/// </summary>
	/// <param name="num">���֡�</param>
	/// <returns></returns>
	template<>
	static constexpr bool IsZero(double num) { return Abs(num) < eps; }

	/// <summary>
	/// ȡƽ����
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>ƽ����</returns>
	template<typename T>
	static constexpr T Pow2(T x) { return x * x; }

	/// <summary>
	/// ȡ����ֵ��
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>����ֵ��</returns>
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
/// �������͡�������������Ϊ�Ǹ���ʱ������Ϊfloat��������ԭ���͡�
/// </summary>
/// <typeparam name="T">���������͡�</typeparam>
template<typename T> 
using promotion_t = typename promotion<T>::Type;

/// <summary>
/// ��ȡ�߼����͡��Ƚ��������ͣ�����ȡ���нϸ߼������͡�
/// </summary>
/// <typeparam name="T1">����1��</typeparam>
/// <typeparam name="T2">����2��</typeparam>
template<typename T1, typename T2> 
using upper_t = typename upper<T1, T2>::Type;

/// <summary>
/// ����������begin()�����������ͣ��Ƶ���������Ԫ���������͡���������֧��Ĭ�Ϲ��졣
/// </summary>
/// <typeparam name="Cont">�������͡�</typeparam>
template <typename Cont> 
using iterator_data_t = typename iterator_data<Cont>::Type;
