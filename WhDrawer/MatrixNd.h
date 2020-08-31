#pragma once
#include <iostream>

/// <summary>
/// N�׾���
/// </summary>
/// <typeparam name="Ty">�����������͡�</typeparam>
template<typename Ty, size_t rows, size_t cols>
struct MatrixNd
{
	typedef Ty(*_ArrPnt)[cols];
	//using _ArrPnt = Ty(*)[cols];

	/// <summary>
	/// ����������
	/// </summary>
	static const size_t rows = rows;
	/// <summary>
	/// ����������
	/// </summary>
	static const size_t cols = cols;
	/// <summary>
	/// ���󳤶ȡ�
	/// </summary>
	static const size_t length = rows * cols;

	/// <summary>
	/// ����Ԫ�ء�
	/// </summary>
	Ty elem[length];

	constexpr inline Ty* operator[](int idx) { return elem + idx * cols; }
	constexpr inline const Ty* operator[](int idx)const { return elem + idx * cols; }

	constexpr inline auto begin()const { return std::cbegin(elem); }
	constexpr inline auto end()const { return std::cend(elem); }

};
