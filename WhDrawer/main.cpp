#include <iostream>
#include <vector>
#include "Geometry.h"
#include "Debug.h"
#include "VectorAlgorithm.h"
#include "MatrixAlgorithm.h"
#include "EasyXGraphics.h"
#include "Graphics.h"
#include "GradientBrush2D.h"
#include <MyTimer.h>
using namespace std;


int main(int argc, void* argv[])
{
	//int a[3] = { 1,2,3 };
	//auto x = Math::SumWith(begin(a), end(a), [](auto& x) {return x; });
	//cout << x;
	MyTimer timer;
	timer.Start();
	EasyXGraphics easy(500, 1000);
	easy.Create(1);
	Graphics graphic(&easy);
	graphic.SetDefaultColor(Color(ColorEnum::RED));
	int d = 0;
	while(true)
	{
		easy.BatchBegin();
		d = (d + 1) % 50;
		Point ps[] = { {50+d,20}, {10+d,400}, {500+d,350}, { 750+d, 10} };
		Color cs[] = { Color(ColorEnum::BLUE),Color(ColorEnum::RED),Color(ColorEnum::GREEN), Color(ColorEnum::CYAN) };
		GradientBrush2D brush(ps, cs, 4);
		graphic.Clean(Color(ColorEnum::DARKGRAY));
		graphic.FillPolygon(ps, 4, &brush);
		easy.BatchFinished();
		timer.DoInFPS(2, [&](float call_times) {
			cout << "\rFPS:" << timer.GetFPS() << "\t" << timer.GetTime() / 1000.0 << "s             ";
			});
		timer.MarkFPS();
	}
	system("pause");
}