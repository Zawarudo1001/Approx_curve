#include "2dTypes.h"
#include "2Doperations.h"
#include <iostream>
#include <vector>


#define FLT_EPSILON 1.19e-07 
#define MAX_FLT_VAL 3.402823466e+38

using namespace std;


//commit 1
Vec2D getGeneralNormVect(vector<Point2d> &pointData, vector<Vec2D> &normData) {
	Vec2D n = 0;
	Vec2D temp;
	int t = pointData.size();
	if (t > 0) {
		Point2d P_0 = pointData[0];
		Point2d P_N = pointData[--t];
		for (int i = 1; i < t; i++) {
			temp = FindNorm(P_0, P_N, pointData[i]);
			n = n + temp;
			normData.push_back(temp);
		}
		if ((length(n) - 0) < FLT_EPSILON) return 0;		//если усредненный вектор нормали в конечном итоге оказался близок к нулю, то центр окружности найти будет невозможно
		else return norm(n);
	}
	else return 0;
}


vector<Circle> CalcCentRad(Vec2D &n, vector<Point2d> &pointData, vector<Vec2D> &normData) {
	vector<Circle> res;
	int t = pointData.size();		// = normData.size();

	if (t > 0) {
		Point2d P_0 = pointData[0];
		Point2d P_N = pointData[--t];
		for (int i = 1; i < t; i++) {
			float m = dot(normData[i-1], n);		//для каждой точки мы ранее запомнили ее вектор нормали к прямой. Теперь отесечем "проблемные" точки скалярным произведением главной нормали и нормали из точки
			if (m > 0){
				Vec3D data = FindCenRad(P_0, pointData[i], P_N);
				if (data.w == -1) {
					continue;
				}
				Circle temp{ Point2d{data.x, data.y}, data.w };
				res.push_back(temp);		//вносим найденный радиус и координаты центра окружности
			}
			else {
				pointData.erase(pointData.begin() + i++);		//если точка оказалась неподходящей, уберем ее из рассмотрения
			}
		}
	}
	return res;		//в итоговом списке получим список центров окружностей и их радиусов, которые попадают под необходимые условия
}


Circle GetOptimalParameters(vector<Circle> &points, vector<Point2d> &pointData) {
	int s = points.size();
	int p = pointData.size();
	float temp = 0;
	float dist = MAX_FLT_VAL;
	int index;

	for (int i = 0; i < s; i++) {			//в этом цикле проходимся по всем найденным центрам окружностей
		temp = 0;
		for (int j = 0; j < p; j++) {			//в этом цикле проходимся по каждой точке на дуге
			temp += length(points[i].c, pointData[j]) - points[i].r;		//для каждой точки находим расстояние до окружности и суммируем отрицательные и положительные расстояния, получая среднее
		}
		temp = fabs(temp);
		if (temp < dist) {
			dist = temp;				//стремимся получить расстояние наиболее близкое к 0, находим минимальное расстояние
			index = i;
		}
	}
	return points[index];
}


int main() {

	vector<Point2d> pointData;		//в данном векторе храним информацию о точках кусочно заданной дуги. Начальный и конечный элемент - концевые, органичивающие точки дуги.
	vector<Vec2D> normData;		//в данный векткор будем заносить данные о номралях для конкретных точек для избавления от дублирования вычислений

	pointData.push_back({ 0.75, -1 });
	pointData.push_back({ 0.5, -0.2 });
	pointData.push_back({ 0.7,0.1 });
	pointData.push_back({ 0.5,0.3 });
	pointData.push_back({ 1.5,0 });
	pointData.push_back({ 1,1.4 });

	/*тут храним набор из точек, с которыми будет производиться работа
	будем считать, что первый и последний член списка является концевыми точками для дуги P0, Pn
	*/

	Vec2D n = getGeneralNormVect(pointData, normData);		//получили по точкам вектор нормали, который определяет изгиб дуги окружности
	vector<Circle> RadMap = CalcCentRad(n, pointData, normData);		//посчитали возможные центры окружностей и радиусы, отфильтровали

	Circle Ans = GetOptimalParameters(RadMap, pointData);

	cout << Ans.c.x << " " << Ans.c.y << " " << Ans.r << endl;	// итоговая дуга окружности по выбранным параметрам будет включать концевые точки и оптимальным образом объединит точки маршрута
	return 0;
}
