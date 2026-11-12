#pragma once

struct Vec2
{
	float x = 0, y = 0;

	Vec2() = default;
	Vec2(const double& v) : x(v), y(v) {};
	Vec2(const double& X, const double& Y) : x(X), y(Y) {};

	const float& Length() const { return std::sqrt(x * x + y * y); };
	const Vec2& Normalize() { return *this / Length(); };

	const Vec2& operator+(const Vec2& other) { return Vec2(x + other.x, y + other.y); }
	const Vec2& operator+=(const Vec2& other) { *this = *this + other; return *this; }
	const Vec2& operator-(const Vec2& other) { return Vec2(x - other.x, y - other.y); }
	const Vec2& operator-=(const Vec2& other) { *this = *this - other; return *this; }

	const Vec2& operator*(const double& v) { return Vec2(x * v, y * v); }
	const Vec2& operator*(const Vec2& other) { return Vec2(x * other.x, y * other.y); }
	const Vec2& operator*=(const double& v) { *this = *this * v; return *this; };
	const Vec2& operator*=(const Vec2& other) { *this = *this * other; return *this; };

	const Vec2& operator/(const double& v) { return Vec2(x / v, y / v); }
	const Vec2& operator/(const Vec2& other) { return Vec2(x / other.x, y / other.y); }
	const Vec2& operator/=(const double& v) { *this = *this / v; return *this; };
	const Vec2& operator/=(const Vec2& other) { *this = *this / other; return *this; };
};