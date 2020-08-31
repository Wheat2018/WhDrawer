#pragma once
#include "IBaseDrawable.h"
#include "IBrush1D.h"
#include "IBrush2D.h"
#include "Point.h"

/// <summary>
/// �ṩ������ͼ��������״��ͼ֧�֡�
/// </summary>
struct IShapeDrawable : public IBaseDrawable
{
	//Methods
	/// <summary>
	/// ��ȡ������ͼ������
	/// </summary>
	/// <returns>ָ�������ͼʵ����ָ�롣</returns>
	virtual IBaseDrawable* BaseDrawable() = 0;

	/// <summary>
	/// ����Ĭ����ɫ����ʹ�û�ˢ�ӿڵĺ����У�����nullptr�Ľӿ�ʵ��������Ĭ����ɫ��ɫ���ơ�
	/// </summary>
	/// <param name="color">Ĭ����ɫ��</param>
	virtual void SetDefaultColor(Color color) = 0;

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="p1">��ʼ�㡣</param>
	/// <param name="p2">��ֹ�㡣</param>
	/// <param name="brush">���������ʽ��</param>
	virtual void DrawLine(Point p1, Point p2, IBrush1D * brush) = 0;

	/// <summary>
	/// ���Ʒ��͹����Ρ�
	/// </summary>
	/// <param name="ps">��ն��㼯��˳ʱ����β�����Ķ������顣</param>
	/// <param name="ps_num">����������ն��㼯���鳤�ȣ�����ƥ��������Խ����ʡ�</param>
	/// <param name="brush">���������ʽ��</param>
	virtual void DrawPolygon(const Point ps[], int ps_num, IBrush1D * brush) = 0;

	/// <summary>
	/// ���������͹����Ρ�
	/// </summary>
	/// <param name="ps">��ն��㼯��˳ʱ����β�����Ķ������顣</param>
	/// <param name="ps_num">����������ն��㼯���鳤�ȣ�����ƥ��������Խ����ʡ�</param>
	/// <param name="brush">��״�������ʽ��</param>
	virtual void FillPolygon(const Point ps[], int ps_num, IBrush2D * brush) = 0;

};