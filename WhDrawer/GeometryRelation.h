#pragma once

typedef unsigned char GeoRelType;
/// <summary>
/// ���ι�ϵö�١�One-Hot���룬���ֹ�ϵ���ܵ��ӣ���Ӧ��switch�ж�ֵ��Ӧ�û�������ж��Ƿ���ڸ��ֹ�ϵ��
/// </summary>
enum class GeometryRelation : GeoRelType
{
	/// <summary>
	/// �ޡ�
	/// <para>����㡢�����ߡ������桢������������</para>
	/// </summary>
	None = 0x01,

	/// <summary>
	/// �غϡ�
	/// <para>����㡢�����ߡ������档</para>
	/// </summary>
	Coincident = 0x02,

	/// <summary>
	/// ������
	/// <para>�����ߡ������档</para>
	/// </summary>
	Contained = 0x04,

	/// <summary>
	/// �ཻ��
	/// <para>�����ߡ������桢�����档</para>
	/// </summary>
	Intersectant = 0x08,

	/// <summary>
	/// ƽ�С�
	/// <para>�����ߡ������桢�����档</para>
	/// </summary>
	Paralled = 0x10,

	/// <summary>
	/// ��ֱ��
	/// <para>�����ߡ������桢�����桢��������������������</para>
	/// </summary>
	Perpendicular = 0x20,

	/// <summary>
	/// ���档
	/// <para>��ά������ά�ߡ�</para>
	/// </summary>
	DifferentPlane = 0x40,

	/// <summary>
	/// ���ߡ�
	/// <para>������������</para>
	/// </summary>
	Collinear = 0x80,
};

inline constexpr GeoRelType operator&(GeometryRelation r1, GeometryRelation r2) { return (GeoRelType)r1 & (GeoRelType)r2; }

inline constexpr GeometryRelation operator|(GeometryRelation r1, GeometryRelation r2) { return GeometryRelation((GeoRelType)r1 | (GeoRelType)r2); }
