# Approx_curve
#### 2dTypes.h
В нем объявлены типы, которые используются в процессе работы. Определены такие типы, как двумерная точка, двумерный вектор, трехмерный вектор, окружность

#### 2Doperations.h
Содержит функции для работы с двумерными графическими объектами.
##### length(vec / point,point) - вычисление длины вектора или расстояние между 2 точками.
##### dot(vec, vec) - вычисление скалярного произведения векторов.
##### norm(vec) - нормализация вектора (приведение к единичному).

##### FindCentRad(point, point, point) - вычисление центра и радиуса окружности по 3 точкам. Возвращает 3-мерный вектор с параметрами. Если вычислить невозможно возвращает вектор (-1, -1, -1).
##### FindNorm(point, point, point) - вычисление вектора нормали по 2 концевым точкам и третьей точки, из которой будет опущен перпендикуляр и который совпадет с вектором нормали.
##### NormCircle(point, circle) - вычисление вектора нормали в точке, лежащей на окружности с заданными параметрами. 

Алгоритм вычисления оптимальныхх параметров сводится к следующему формальному описанию:
1. Строим отрезок между концевыми точками кусочной дуги и в каждой точке изгиба ищем вектор нормали(перпендикуляр) к отрезку.
2. Сумма единичных нормалей позволяет определить усредненную, которая будет определять выпуклость окружности
3. Имея потенциальные центры и радиусы окружностей, вычислим нормали в точках изгиба и посчитаем скалярное произведение с нормалью
4. Отберем только те точки, в которых скалярное произведение будет больше 0. Эти точки соответствуют изгибу в нужную сторону
5. Для каждого потенциального параметра посчитаем сумму расстояний от остальных точек до потенциальной окружности. Если точки лежат внутри - расстояние отрицательное. Иначе положительное или равно 0, если точка лежит на окружности. Для концевых точек считать не нужно, так как они лежат на каждой из окружностей.
6. Ищем такие параметры окружности, при которых расстояние до всех точек будет минимальным. Выбираем их в качестве опорных.
7. ВОзвращаем найденные параметры

