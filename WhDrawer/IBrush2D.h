#pragma once
#include "Color.h"

/// <summary>
/// �����ά��ˢ��ָ��ƽ�����䷽ʽ��
/// </summary>
struct IBrush2D
{
	/// <summary>
	/// <para>����ɫ������</para>
	/// <para>˵�����ú���ָ���˱��ʵ����ɫ�����ʵ㼴��ǰ���������������Ҫ���Ƶĵ㡣ʵ�ָýӿڷ����ɹ�ע��������ʣ�Ҳ�ɹ�ע����������</para>
	/// </summary>
	/// <param name="rate_x">ˮƽ���У���������ʣ���Χ��[0, 1]�ĸ�������</param>
	/// <param name="rate_y">��ֱ���У���������ʣ���Χ��[0, 1]�ĸ�������</param>
	/// <returns></returns>
	virtual Color PixelIteration(float rate_x, float rate_y) = 0;
};