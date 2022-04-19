#pragma once

#include <iostream>

using namespace std;

class Shape
{
	int height, width;
	int rectangle;
	float circle;
	float radius;

public:
	Shape(int _height, int _width, float _radius);

	~Shape();

	int GetRectangle();

	float GetCircle();
};
