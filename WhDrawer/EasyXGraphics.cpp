#include "EasyXGraphics.h"
#include <easyx.h>


EasyXGraphics::EasyXGraphics(size_t rows, size_t cols) : rows(rows), cols(cols) { ; }

void EasyXGraphics::Create(int flag) 
{
	initgraph(cols, rows, flag);
	pMem = GetImageBuffer();
	GetClipBox(GetImageHDC(), &screen);
}

void EasyXGraphics::Close() {
	closegraph();
}

const size_t EasyXGraphics::Rows() { return rows; }

const size_t EasyXGraphics::Cols() { return cols; }

void EasyXGraphics::DrawPixel(int x, int y, Color color)
{
	//putpixel(x, y, color.ToBGRA());
	pMem[(screen.top + y) * screen.right + screen.left + x] = color.ToRGBA();
}

Color EasyXGraphics::GetPixel(int x, int y)
{
	return Color().FromBGRA(getpixel(x,y));
}

void EasyXGraphics::BatchBegin()
{
	BeginBatchDraw();
}

void EasyXGraphics::BatchFinished()
{
	FlushBatchDraw();
	EndBatchDraw();
}

void EasyXGraphics::Clean(Color color)
{
	setbkcolor(color.ToBGRA());
	cleardevice();
}
