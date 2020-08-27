#pragma once

typedef unsigned char GeoRelType;
/// <summary>
/// 几何关系枚举。One-Hot编码，多种关系可能叠加，不应用switch判断值，应用或运算符判断是否存在该种关系。
/// </summary>
enum class GeometryRelation : GeoRelType
{
	/// <summary>
	/// 无。
	/// <para>点与点、点与线、点与面、向量与向量。</para>
	/// </summary>
	None = 0x01,

	/// <summary>
	/// 重合。
	/// <para>点与点、线与线、面与面。</para>
	/// </summary>
	Coincident = 0x02,

	/// <summary>
	/// 包含。
	/// <para>点与线、线与面。</para>
	/// </summary>
	Contained = 0x04,

	/// <summary>
	/// 相交。
	/// <para>线与线、线与面、面与面。</para>
	/// </summary>
	Intersectant = 0x08,

	/// <summary>
	/// 平行。
	/// <para>线与线、线与面、面与面。</para>
	/// </summary>
	Paralled = 0x10,

	/// <summary>
	/// 垂直。
	/// <para>线与线、线与面、面与面、向量与向量（正交）。</para>
	/// </summary>
	Perpendicular = 0x20,

	/// <summary>
	/// 异面。
	/// <para>三维线与三维线。</para>
	/// </summary>
	DifferentPlane = 0x40,

	/// <summary>
	/// 共线。
	/// <para>向量与向量。</para>
	/// </summary>
	Collinear = 0x80,
};

inline constexpr GeoRelType operator&(GeometryRelation r1, GeometryRelation r2) { return (GeoRelType)r1 & (GeoRelType)r2; }

inline constexpr GeometryRelation operator|(GeometryRelation r1, GeometryRelation r2) { return GeometryRelation((GeoRelType)r1 | (GeoRelType)r2); }
