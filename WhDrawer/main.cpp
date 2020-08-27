#include <iostream>
#include <vector>
#include "Geometry.hpp"
#include "Debug.h"
#include "VectorAlgorithm.h"
using namespace std;

int main(int argc, void* argv[])
{
	constexpr Plane left = { 1,1.1,0,0 };
	constexpr Plane right = { 1,1,0,1 };

	cout << Geometry::Relation(left, right);
}