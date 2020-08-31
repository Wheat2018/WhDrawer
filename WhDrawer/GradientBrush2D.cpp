#include "GradientBrush2D.h"
#include "Math.h"

GradientBrush2D::GradientBrush2D(Point* ps, Color* cs, int ps_num) :
	ps(std::vector<PointF>(ps_num)),
	cs(std::vector<Color>(ps_num)),
	d(std::vector<float>(ps_num)),
	psNum(ps_num)
{
	int minX = Math::MinWith(ps, ps + ps_num, [](auto& p) { return p.x; }).x;
	int maxX = Math::MaxWith(ps, ps + ps_num, [](auto& p) { return p.x; }).x;
	int minY = Math::MinWith(ps, ps + ps_num, [](auto& p) { return p.y; }).y;
	int maxY = Math::MaxWith(ps, ps + ps_num, [](auto& p) { return p.y; }).y;
	int dx = maxX - minX, dy = maxY - minY;

	for (int i = 0; i < ps_num; i++)
	{
		this->ps[i] = PointF{ float(ps[i].x - minX) / dx, float(ps[i].y - minY) / dy };
		this->cs[i] = cs[i];
	}
}

Color GradientBrush2D::PixelIteration(float rate_x, float rate_y)
{
	float sum = 0;
	for (int i = 0; i < psNum; i++)
	{
		float dis = Math::Pow2(rate_x - ps[i].x) + Math::Pow2(rate_y - ps[i].y);
		if (dis == 0) return cs[i];
		sum += d[i] = 1 / dis;
	}

	float r = 0, g = 0, b = 0, a = 0;
	for (int i = 0; i < psNum; i++)
	{
		float rate = d[i] / sum;
		Color& color = cs[i];
		r += color.R() * rate;
		g += color.G() * rate;
		b += color.B() * rate;
		a += color.A() * rate;
	}

	return Color(r, g, b, a);
}
