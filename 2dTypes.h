#pragma once
#include <math.h>


struct Point2d {
	float x, y;
	Point2d(float value) : x(value), y(value) {}
	Point2d(float _x, float _y) : x(_x), y(_y) {}
};

struct Vec2D{
	float x, y;

	Vec2D(float value) : x(value), y(value) {}
	Vec2D(float _x, float _y) : x(_x), y(_y) {}
	Vec2D(Point2d s, Point2d e) : x(e.x - s.x), y(e.y - s.y) {}

	Vec2D operator+(Vec2D const& other) { return Vec2D(x + other.x, y + other.y); }
	Vec2D operator-(Vec2D const& other) { return Vec2D(x - other.x, y - other.y); }
	Vec2D operator*(Vec2D const& other) { return Vec2D(x * other.x, y * other.y); }
	Vec2D operator/(Vec2D const& other) { return Vec2D(x / other.x, y / other.y); }
};

struct Vec3D {
	float x, y, w;
	Vec3D(float _x, float _y, float _w) : x(_x), y(_y), w(_w) {}
	Vec3D(float value) : x(value), y(value), w(value) {}
};

struct Circle {
	Point2d c;
	float r;
	Circle(Point2d _c, float _r) : c(_c), r(_r) {}
};

