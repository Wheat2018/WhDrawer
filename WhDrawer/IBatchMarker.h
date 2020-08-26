#pragma once

/// <summary>
/// �ṩ������ͼ��Ƿ�������ǻ�ͼ�����ж�ʱ���ڵĴ���������
/// <para>ע����������ͼ��ʼ��ˢ��֮����κλ�ͼ�����������������֣��Դ˽���ˢ�´�����������˸��</para>
/// </summary>
struct IBatchMarker
{
	/// <summary>
	/// ��ʼ�������ơ�
	/// </summary>
	virtual void BatchBegin() = 0;

	/// <summary>
	/// ����������ɡ�
	/// </summary>
	virtual void BatchFinished() = 0;
};