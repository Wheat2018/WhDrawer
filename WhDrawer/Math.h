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


struct DefaultFloatZeroJudger;

/// <summary>
/// �ṩ������ѧ�㷨��
/// <para>�������㷽����Ҫ��һ��������̬����IsZero(T)���࣬�����������������Ƿ�Ϊ0�Ĳ���ֵ��</para>
/// </summary>
/// <typeparam name="FloatZeroJudger">�������㷽����</typeparam>
template <typename FloatZeroJudger = DefaultFloatZeroJudger>
class _Math
{
public:
#define _StaInCst static inline constexpr
#define _StaIn static inline

	/// <summary>
	/// ȡ���������ֵ�����á�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <returns>�����������ֵ������</returns>
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
	/// ȡ��������Сֵ�����á�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <returns>�����������ֵ������</returns>
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
	/// ����Ԫ��ֵ��͡�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <returns>����Ԫ��ֵ���ֵ��</returns>
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
	/// ��������Ԫ��Ӧ�ô���������ȡ���ֵ���á�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <param name="func">���������������������ͣ������ã�Ϊ��Ρ�����������С�ںŵ��������ݵĺ�����Lambda���ʽ��</param>
	/// <returns>�����������ֵ�����á�</returns>
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
	/// ��������Ԫ��Ӧ�ô���������ȡ��Сֵ���á�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <param name="func">���������������������ͣ������ã�Ϊ��Ρ����������ش��ںŵ��������ݵĺ�����Lambda���ʽ��</param>
	/// <returns>����������Сֵ�����á�</returns>
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
	/// ��������Ԫ��Ӧ�ô���������ȡ����ֵ��ӡ�
	/// </summary>
	/// <typeparam name="Cont">�������͡�</typeparam>
	/// <param name="container">������</param>
	/// <param name="func">���������������������ͣ������ã�Ϊ��Ρ����������ؼӺŵ��������ݵĺ�����Lambda���ʽ��</param>
	/// <returns>����������ֵ��͡�</returns>
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
	/// �ж��������Ƿ���ȡ�������Ǹ����жϷ������졣
	/// </summary>
	/// <param name="num1">���㡣</param>
	/// <param name="num2">���㡣</param>
	/// <returns></returns>
	template<typename T1, typename T2> _StaInCst bool Equal(const T1& num1, const T2& num2) { return IsZero(num1 - num2); }

	/// <summary>
	/// �ж����ɸ����Ƿ���ȡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst bool Equal(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		if (Equal(num1, num2))
			return Equal(num2, args...);
		return false;
	}

	/// <summary>
	/// �ж�ĳ���Ƿ�Ϊ0��
	/// </summary>
	/// <typeparam name="T">�����������͡�</typeparam>
	/// <param name="num">���֡�</param>
	/// <returns></returns>
	template<typename T> _StaInCst bool IsZero(const T& num) { return num == T(0); }
	template<> _StaInCst bool IsZero(const float& num) { return DefaultFloatZeroJudger::IsZero((const float&)num); }
	template<> _StaInCst bool IsZero(const double& num) { return DefaultFloatZeroJudger::IsZero((const double&)num); }

	/// <summary>
	/// ȡƽ����
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>ƽ����</returns>
	template<typename T> _StaInCst T Pow2(const T& x) { return x * x; }

	/// <summary>
	/// ȡ����ֵ��
	/// </summary>
	/// <typeparam name="T">�������͡�</typeparam>
	/// <param name="x">���ݡ�</param>
	/// <returns>����ֵ��</returns>
	template<typename T> _StaInCst T Abs(const T& x) { return x >= 0 ? x : -x; }

	/// <summary>
	/// ȡ���ֵ���ú�������O2�Ż����Դﵽ������ܡ���κ���ʱ����ʱ���������ܷ�����ʱ�������ã�����ʹ�á�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto&& Max(T1&& num1, T2&& num2, ArgsT&&... args)
	{ return Max(Max(num1, num2), args...); }
	template<typename T1, typename T2> _StaInCst auto&& Max(T1&& num1, T2&& num2) { return num1 >= num2 ? num1 : num2; }

	/// <summary>
	/// ȡ��Сֵ���ú�������O2�Ż����Դﵽ������ܡ���κ���ʱ����ʱ���������ܷ�����ʱ�������ã�����ʹ�á�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto&& Min(T1&& num1, T2&& num2, ArgsT&&... args)
	{
		return Min(Min(num1, num2), args...);
	}
	template<typename T1, typename T2> _StaInCst auto&& Min(T1&& num1, T2&& num2) { return num1 <= num2 ? num1 : num2; }

	/// <summary>
	/// ȡ���ֵ�������ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst int ArgMax(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMax(left, right, num1, num2, args...);
		return left;
	}
	
	/// <summary>
	/// ȡ��Сֵ�������ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst int ArgMin(const T1& num1, const T2& num2, const ArgsT&... args)
	{
		int left = 0, right = 0;
		_ArgMin(left, right, num1, num2, args...);
		return left;
	}

	/// <summary>
	/// ȡ�����б�(num1, num2, num3...)��ָ�����������á�����ֵԽ��򲻺Ϸ�������������Ϊ0�����á��ú�������O2�Ż����Դﵽ������ܡ�
	/// </summary>
	template<typename T1, typename T2, typename... ArgsT> _StaInCst auto& At(int index, T1& num1, T2& num2, ArgsT&... args)
	{
		int now = 0;
		return _At(now, index, num1, num2, args...);
	}

	/// <summary>
	/// ��ȡ���͵�����ֵ��
	/// </summary>
	/// <typeparam name="T">���͡�</typeparam>
	/// <returns>�޷�������ȫλΪ1���з������ͳ�����λ��Ϊ1����������Ϊ�����ֵ��</returns>
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
/// �ṩ������ѧ�㷨��
/// </summary>
typedef _Math<> Math;

struct DefaultFloatZeroJudger
{
	/// <summary>
	/// ����ȼ��ж������������������������ֵС�ڸ�ֵ����Ϊ����ȣ�Ĭ��Ϊ1e-6��
	/// </summary>
	static constexpr float eps = 1e-6f;
	template<typename T> static constexpr bool IsZero(const T& x) { return Math::Abs(x) < eps; }
};

