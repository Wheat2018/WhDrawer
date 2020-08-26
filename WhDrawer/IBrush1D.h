#pragma once
#include "Color.h"

/// <summary>
/// ����һά��ˢ��ָ����������䷽ʽ��
/// </summary>
struct IBrush1D
{
	//Properties
	/// <summary>
	/// ��ȡ������ȡ�
	/// </summary>
	/// <returns>�޷������ͣ���ʾ������ȡ�</returns>
	virtual const size_t LineWidth()const = 0;

	//Methods
	/// <summary>
	/// <para>����ɫ������</para>
	/// <para>˵�����ú���ָ���˱��ʵ����ɫ�����ʵ㼴��ǰ���������������Ҫ���Ƶĵ㡣ʵ�ָýӿڷ����ɹ�ע��������ʣ�Ҳ�ɹ�ע����������</para>
	/// </summary>
	/// <param name="rate">��������ʣ���Χ��[0, 1]�ĸ�������</param>
	/// <returns></returns>
	virtual Color PixelIteration(float rate) = 0;
};