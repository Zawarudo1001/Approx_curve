#pragma once
#include "2dTypes.h"

float length(Vec2D const& v) { return sqrt(v.x * v.x + v.y * v.y); }
float dot(Vec2D const& a, Vec2D const& b) { return a.x * b.x + a.y * b.y; }
Vec2D norm(Vec2D &v) { return v / length(v); }
float length(Point2d const& p1, Point2d const& p2) { return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); }


Vec3D FindCenRad(Point2d &a, Point2d &b, Point2d &c) {
	float A = b.x - a.x;
	float B = b.y - a.y;
	float C = c.x - a.x;
	float D = c.y - a.y;
	float E = A * (a.x + b.x) + B * (a.y + b.y);
	float F = C * (a.x + c.x) + D * (a.y + c.y);
	float G = 2 * (A * (c.y - b.y) - B * (c.x - b.x));
	// ���� G = 0, ��� ������, ��� ����� ������ ����� ����� �������� ���������� ������.
	if (G == 0) return -1;

	float Cx = (D * E - B * F) / G;
	float Cy = (A * F - C * E) / G;
	float R = sqrt(powf(a.x - Cx, 2) + powf(a.y - Cy, 2));
	return Vec3D{ Cx, Cy, R };
}


Vec2D FindNorm(Point2d &A, Point2d &B, Point2d &C) {
	Vec2D AB = Vec2D{ A, B };
	AB = norm(AB);

	Vec2D AC = Vec2D{ A, C };
	float t = dot(AB, AC);			//�������� ����� ��������

	float x = A.x + AB.x * t;
	float y = A.y + AB.y * t;
	Vec2D n = Vec2D{ C.x - x, C.y - y };		//�������� ����� �������� �� �������, ������ ������� ������ ������� � ���� � ����������� ���
	return norm(n);
}


Vec2D NormCircle(Point2d P, Circle circ) {
	//������������, ��� ���� ����� �� ����������. � ����� ������ ������ ������� ����� ����� ���������������� ������� ����� ������� � ������ �� ���.
	Vec2D n = Vec2D{ P.x - circ.c.x, P.y - circ.c.y };
	return norm(n);
	//���������� ������ ������� � �����
}
