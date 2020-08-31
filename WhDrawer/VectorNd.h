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

	constexpr inline Ty& operator[](int idx) { return elem[idx]; }
	constexpr inline const Ty& operator[](int idx)const { return elem[idx]; }

	constexpr inline auto begin()const { return std::cbegin(elem); }
	constexpr inline auto end()const { return std::cend(elem); }

};

