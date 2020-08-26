#include "EasyXGraphics.h"
#include <easyx.h>


EasyXGraphics::EasyXGraphics(size_t rows, size_t cols) : rows(rows), cols(cols) { ; }

void EasyXGraphics::Create(int flag) 
{
	initgraph(rows, cols, flag);
}

void EasyXGraphics::Close() {
	closegraph();
}

const size_t EasyXGraphics::Rows() { return rows; }

const size_t EasyXGraphics::Cols() { return cols; }

void EasyXGraphics::DrawPixel(int x, int y, Color color)
{
	putpixel(x, y, color.ToBGRA());
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
