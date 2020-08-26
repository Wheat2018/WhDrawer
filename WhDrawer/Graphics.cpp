#include "Graphics.h"
#include "Graphics.h"
#include "Debug.h"
#include <algorithm>

Graphics::Graphics(IBaseDrawable* p_base_graphic) 
{
	pBaseGraphic = dynamic_cast<IBaseDrawable*>(p_base_graphic);
	
	Debug::Assert(pBaseGraphic != nullptr, "Graphics(IBaseDrawable): 参数类型未实现IBaseDrawable!");
}

void Graphics::Line(Point p1, Point p2, const IBrush1D& brush)
{
	//float delta_x, delta_y, x, y;
	//int dx, dy, steps;
	//dx = p1.x - p2.x;
	//dy = p1.y - p2.y;
	//steps = std::max(std::abs(dx), std::abs(dy));
	//
	//if (steps > 10000) steps = 10000;
	//delta_x = (float)dx / steps;
	//delta_y = (float)dy / steps;
	//x = xa;
	//y = ya;
	//Pixel(x, y, color);
	//for (int k = 1; k <= steps; k++) {
	//	x += delta_x;
	//	y += delta_y;
	//	Pixel(x, y, color);
	//}

}

void Graphics::Polygon(Point ps[], int ps_num, const IBrush1D& brush)
{
}

void Graphics::FillPolygon(Point ps[], int ps_num, const IBrush1D& brush)
{
}
