#include "Graphics.h"
#include "Math.h"
#include "Debug.h"
#include <algorithm>
Graphics::Graphics(IBaseDrawable* p_base_graphic) 
{
	pBaseGraphic = dynamic_cast<IBaseDrawable*>(p_base_graphic);
	
	Debug::Assert(pBaseGraphic != nullptr, "Graphics(IBaseDrawable): 参数类型未实现IBaseDrawable!");
}

void Graphics::DrawLine(Point p1, Point p2, IBrush1D * brush)
{
	float delta_x, delta_y, delta_process, x, y, process;
	int dx, dy, steps;
	Color color = defaultColor;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	steps = Math::Max(Math::Abs(dx), Math::Abs(dy));
	
	delta_x = (float)dx / steps;
	delta_y = (float)dy / steps;
	delta_process = 1.0f / steps;
	x = p1.x;
	y = p1.y;
	if (brush) color = brush->PixelIteration(process = 0);
	DrawPixel(x, y, color);
	for (int k = 1; k <= steps; k++) {
		if (k == steps - 1)
		{
			char a = 1;
		}
		x += delta_x;
		y += delta_y;
		if (brush) color = brush->PixelIteration(process += delta_process);
		DrawPixel(x + 0.5f, y + 0.5f, color);
	}
}

void Graphics::DrawPolygon(const Point ps[], int ps_num, IBrush1D * brush)
{
	for (int i = 0; i < ps_num; i++)
	{
		DrawLine(ps[i], ps[(i + 1) % ps_num], brush);
	}
}

struct _VectorCanva : public IBaseDrawable
{
	int minY, maxY;
	int* left, * right;
	size_t rows, cols;

	_VectorCanva(int minY, int maxY, size_t rows, size_t cols): rows(rows), cols(cols)
	{
		this->minY = Math::Max(minY, 0);
		this->maxY = Math::Min(maxY, rows - 1);
		left = new int[maxY - minY + 1];
		right = new int[maxY - minY + 1];
		for (int i = 0; i <= maxY - minY; i++) left[i] = cols - 1, right[i] = 0;
	}

	~_VectorCanva() { delete[] left; delete[] right; }

	// 通过 IBaseDrawable 继承
	virtual const size_t Rows() override { return rows; }

	virtual const size_t Cols() override { return cols; }

	virtual void DrawPixel(int x, int y, Color color) override
	{
		y -= minY;
		if (y < 0 || y >= maxY - minY + 1) return;
		//Debug::Assert(y >= 0 && y < maxY - minY + 1, "_VectorCanva::DrawPixel: 出现了，越界怪！");

		if (x < 0) x = 0;
		if (x > cols - 1) x = cols - 1;
		if (x < left[y]) left[y] = x;
		if (x > right[y]) right[y] = x;
	}

	virtual Color GetPixel(int x, int y) override { return Color(); }


	virtual void Clean(Color color) override { ; }

};

void Graphics::FillPolygon(const Point ps[], int ps_num, IBrush2D * brush)
{
	int minX = Math::MinWith(ps, ps + ps_num, [](auto& p) { return p.x; }).x;
	int maxX = Math::MaxWith(ps, ps + ps_num, [](auto& p) { return p.x; }).x;
	int minY = Math::MinWith(ps, ps + ps_num, [](auto& p) { return p.y; }).y;
	int maxY = Math::MaxWith(ps, ps + ps_num, [](auto& p) { return p.y; }).y;

	_VectorCanva base(minY, maxY, Rows(), Cols());
	Graphics vec(&base);
	//将多边形边框绘制到容器中。
	vec.DrawPolygon(ps, ps_num, nullptr);

	Color color = defaultColor;
	for (int i = 0; i <= base.maxY - base.minY; i++)
	{
		int y = i + base.minY;
		for (int x = base.left[i]; x < base.right[i]; x++)
		{
			if (brush)
				color = brush->PixelIteration(float(x - minX) / (maxX - minX), float(y - minY) / (maxY - minY));
			DrawPixel(x, y, color);
		}
	}
}
