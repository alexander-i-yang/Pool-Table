//
// Created by Samuel on 5/17/2019.
//

#ifndef POOL_TABLE_POINT_H
#define POOL_TABLE_POINT_H


class Point {
public:
	double x, y;
	double radius;
	int tag;
	Point() = default;
	Point(double, double, int);
	Point(double, double, double, int);
	double distance(Point*);
	bool operator == (Point*);
	bool operator < (Point*);
	bool operator > (Point*);
};

struct HorizontalCompare {
	bool operator () (const Point* l, const Point* r) {
		if (l->x == r->x) {
			return l->y < r->y;
		}
		else {
			return l->x < r->x;
		}
	}
};

#endif //POOL_TABLE_POINT_H
