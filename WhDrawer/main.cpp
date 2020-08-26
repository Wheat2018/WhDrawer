#include <iostream>
#include <vector>
#include "Geometry.hpp"
#include "Debug.h"
#include "VectorAlgorithm.h"
using namespace std;

int main(int argc, void* argv[])
{

	Plane3D<int> e1 = { 1,2,3,4 };
	Plane e2 = { 2,4,6,0 };

	auto v3 =  Geometry::Relation(e1, e2);
	cout << v3;
}