#pragma once
#include <iostream>

/// <summary>
/// N阶矩阵。
/// </summary>
/// <typeparam name="Ty">矩阵数据类型。</typeparam>
template<typename Ty, size_t rows, size_t cols>
struct MatrixNd
{
	typedef Ty(*_ArrPnt)[cols];
	//using _ArrPnt = Ty(*)[cols];

	/// <summary>
	/// 矩阵行数。
	/// </summary>
	static const size_t rows = rows;
	/// <summary>
	/// 矩阵行数。
	/// </summary>
	static const size_t cols = cols;
	/// <summary>
	/// 矩阵长度。
	/// </summary>
	static const size_t length = rows * cols;

	/// <summary>
	/// 矩阵元素。
	/// </summary>
	Ty elem[length];

	constexpr inline Ty* operator[](int idx) { return elem + idx * cols; }
	constexpr inline const Ty* operator[](int idx)const { return elem + idx * cols; }

	constexpr inline auto begin()const { return std::cbegin(elem); }
	constexpr inline auto end()const { return std::cend(elem); }

};
