#pragma once
#include "IBaseDrawable.h"
#include "IBatchMarker.h"
#include <windows.h>
/// <summary>
/// ʹ��EasyXͼ�ο�ʵ�ֵĻ�����ͼ�ӿڼ�������ͼ��ǽӿڡ�
/// </summary>
class EasyXGraphics : public IBaseDrawable, public IBatchMarker
{
public:
	/// <summary>
	/// ָ�����ڴ�С������EasyX��ͼ��
	/// </summary>
	/// <param name="rows">����������</param>
	/// <param name="cols">����������</param>
	/// <returns></returns>
	EasyXGraphics(size_t rows, size_t cols);

	/// <summary>
	/// ����Windows���ڡ�EasyX��ֻ��Ϊ���̴���һ�����ڡ�
	/// </summary>
	/// <param name="flag">�Ƿ�������̨��0Ϊ��������1Ϊ������</param>
	void Create(int flag = 0);

	/// <summary>
	/// �رջ�ͼ���ڡ�
	/// </summary>
	void Close();

	// ͨ�� IBaseDrawable �̳�

	virtual const size_t Rows() override;
	virtual const size_t Cols() override;
	virtual void DrawPixel(int x, int y, Color color) override;
	virtual Color GetPixel(int x, int y) override;
	virtual void Clean(Color color = Color()) override;

	// ͨ�� IBatchMarker �̳�

	virtual void BatchBegin() override;
	virtual void BatchFinished() override;


private:
	size_t rows, cols;
	DWORD* pMem;
	RECT screen;
};

