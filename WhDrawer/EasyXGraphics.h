#pragma once
#include "IBaseDrawable.h"
#include "IBatchMarker.h"
#include <windows.h>
/// <summary>
/// 使用EasyX图形库实现的基本绘图接口及批量绘图标记接口。
/// </summary>
class EasyXGraphics : public IBaseDrawable, public IBatchMarker
{
public:
	/// <summary>
	/// 指定窗口大小，构造EasyX绘图。
	/// </summary>
	/// <param name="rows">窗口行数。</param>
	/// <param name="cols">窗口列数。</param>
	/// <returns></returns>
	EasyXGraphics(size_t rows, size_t cols);

	/// <summary>
	/// 创建Windows窗口。EasyX库只能为进程创建一个窗口。
	/// </summary>
	/// <param name="flag">是否保留控制台。0为不保留，1为保留。</param>
	void Create(int flag = 0);

	/// <summary>
	/// 关闭绘图窗口。
	/// </summary>
	void Close();

	// 通过 IBaseDrawable 继承

	virtual const size_t Rows() override;
	virtual const size_t Cols() override;
	virtual void DrawPixel(int x, int y, Color color) override;
	virtual Color GetPixel(int x, int y) override;
	virtual void Clean(Color color = Color()) override;

	// 通过 IBatchMarker 继承

	virtual void BatchBegin() override;
	virtual void BatchFinished() override;


private:
	size_t rows, cols;
	DWORD* pMem;
	RECT screen;
};

