#pragma once
#include "IBrush2D.h"
#include "Point.h"
#include <vector>
class GradientBrush2D : public IBrush2D
{
private:
	std::vector<PointF> ps;
	std::vector<Color> cs;
	std::vector<float> d;
	int psNum;

public:

	GradientBrush2D(Point* ps, Color* cs, int ps_num);

	// Í¨¹ý IBrush2D ¼Ì³Ð
	virtual Color PixelIteration(float rate_x, float rate_y) override;
};

