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

	Ty& operator[](int idx) { return elem[dim]; }

	auto begin() { return std::cbegin(elem); }
	auto end() { return std::cend(elem); }

};

