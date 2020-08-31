#pragma once
#include <iostream>

/// <summary>
/// N维向量。
/// </summary>
/// <typeparam name="Ty">向量数据类型。</typeparam>
template<typename Ty, size_t dim>
struct VectorNd
{
	/// <summary>
	/// 向量维度。
	/// </summary>
	static const size_t size = dim;

	/// <summary>
	/// 向量元素。
	/// </summary>
	Ty elem[dim];

	constexpr inline Ty& operator[](int idx) { return elem[idx]; }
	constexpr inline const Ty& operator[](int idx)const { return elem[idx]; }

	constexpr inline auto begin()const { return std::cbegin(elem); }
	constexpr inline auto end()const { return std::cend(elem); }

};

