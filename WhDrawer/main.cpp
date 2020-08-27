#include <iostream>
#include <vector>
#include "Geometry.hpp"
#include "Debug.h"
#include "VectorAlgorithm.h"
using namespace std;

#define max(a,b) ((a) >= (b) ? (a) : (b))

int main(int argc, void* argv[])
{
	constexpr int a = 0, b = 1, c = 2, d = 6;
	constexpr auto x = Math::At(0, a, b, c, d);


	//constexpr int index = Math::ArgMax(1, 6, 2, 8, 5);
	//constexpr auto n = Math::Max(1, 6, 2, 8, 5);
	//cout << index;
	//int a, b, c, d, e;
	//cin >> a >> b >> c >> d >> e;
	//auto x = std::_Max_value(a, std::_Max_value(b, std::_Max_value(c, std::_Max_value(d,e))));
	//cout << x;
	//cin >> a >> b >> c >> d >> e;
	//x = Math::Max(a, b, c, d, e);
	//cout << x;
	//cin >> a >> b >> c >> d >> e;
	//x = max(a, max(b, max(c, max(d, e))));
	//cout << x;
	//Point3F p = { 0,0,0 };
	//Line3 line = { {1,1,1},{1,-1,0} };
	//auto v3 =  Geometry::Distance(p, line);
	//cout << v3;
}