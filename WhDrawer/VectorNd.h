#pragma once
#include <iostream>

/// <summary>
/// Nά������
/// </summary>
/// <typeparam name="Ty">�����������͡�</typeparam>
template<typename Ty, size_t dim>
struct VectorNd
{
	/// <summary>
	/// ����ά�ȡ�
	/// </summary>
	static const size_t size = dim;

	/// <summary>
	/// ����Ԫ�ء�
	/// </summary>
	Ty elem[dim];

	Ty& operator[](int idx) { return elem[dim]; }

	auto begin() { return std::cbegin(elem); }
	auto end() { return std::cend(elem); }

};

