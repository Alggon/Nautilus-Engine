#pragma once

struct Vec2 
{
	float x = 0, y = 0;

	Vec2() = default;
	Vec2(double X, double Y) : x(X), y(Y) {}
};