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
	template<typename T1, typename T2> static constexpr bool Equal(const T1& num1, const T2& num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// �ж�ĳ���Ƿ�Ϊ0��
	/// </summary>
	/// <typeparam name="T">�����������͡�</typeparam>
	/// <param name="num">���֡�</param>
	/// <returns></returns>
	template<typename T> static constexpr bool IsZero(const T& num) { return num == T(0); }
	template<> static constexpr bool IsZero(const float& num) { return Abs(num) < eps; }
	template<> static constexpr bool IsZero(const double& num) { return Abs(num) < eps; }

	/// <summary>
	/// ȡƽ����
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>ƽ����</returns>
	template<typename T> static constexpr T Pow2(const T& x) { return x * x; }

	/// <summary>
	/// ȡ����ֵ��
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>����ֵ��</returns>
	template<typename T> static constexpr T Abs(const T& x) { return x >= 0 ? x : -x; }

	/// <summary>
	/// ȡ���ֵ���ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr auto& Max(T1& num1, T2& num2, ArgsT&... args) 
	{ return Max(Max(num1, num2), args...); }
	template<typename T1, typename T2> static constexpr auto& Max(T1& num1, T2& num2) { return num1 >= num2 ? num1 : num2; }

	/// <summary>
	/// ȡ��Сֵ���ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr auto& Min(T1& num1, T2& num2, ArgsT&... args)
	{
		return Min(Min(num1, num2), args...);
	}
	template<typename T1, typename T2> static constexpr auto& Min(T1& num1, T2& num2) { return num1 <= num2 ? num1 : num2; }

	/// <summary>
	/// ȡ���ֵ�������ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr int ArgMax(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMax(left, right, num1, num2, args...);
		return left;
	}
	
	/// <summary>
	/// ȡ��Сֵ�������ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> static constexpr int ArgMin(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMin(left, right, num1, num2, args...);
		return left;
	}

	/// <summary>
	/// ȡ�����б�(num1, num2, num3...)��ָ�����������á�����ֵԽ��򲻺Ϸ�������������Ϊ0�����á��ú�������O2�Ż����Դﵽ������ܡ�
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
