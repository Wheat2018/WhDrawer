#pragma once
#include "Color.h"

/// <summary>
/// �ṩ������ͼ֧�֡�
/// </summary>
struct IBaseDrawable
{
	//Properties
	/// <summary>
	/// ��ȡͼ��������
	/// </summary>
	/// <returns>�޷������ͣ���ʾͼ���������</returns>
	virtual const size_t Rows() = 0;

	/// <summary>
	/// ��ȡͼ��������
	/// </summary>
	/// <returns>�޷������ͣ���ʾͼ���������</returns>
	virtual const size_t Cols() = 0;

	//Methods
	/// <summary>
	/// ���Ƶ㡣
	/// </summary>
	/// <param name="x">�����꣨��������</param>
	/// <param name="y">�����꣨������</param>
	/// <param name="color">�����ɫ��</param>
	virtual void DrawPixel(int x, int y, Color color) = 0;

	/// <summary>
	/// ��ȡ����ɫ��
	/// </summary>
	/// <param name="x">�����꣨��������</param>
	/// <param name="y">�����꣨������</param>
	/// <returns>�����ɫ��</returns>
	virtual Color GetPixel(int x, int y) = 0;
};

