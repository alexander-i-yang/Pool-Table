//
// Created by Samuel on 5/17/2019.
//

#include "Point.h"
#include <cmath>

Point::Point(double x, double y, int tag) {
	this->x = x;
	this->y = y;
	this->tag = tag;
}

Point::Point(double x, double y, double r, int tag) : Point(x, y, tag) {
	this->radius = r;
}

double Point::distance(Point* other) {
	return sqrt(pow(this->x - other->x, 2) + pow(this->y - other->y, 2));
}
bool Point::operator == (Point* other) {
	return this->x == other->x && this->y == other->y;
}
bool Point::operator < (Point* other) {
	if (this->y == other->y) {
		return this->x < other->x;
	}
	else {
		return this->y < other->y;
	}
}
bool Point::operator > (Point* other) {
	if (this->y == other->y) {
		return this->x > other->x;
	}
	else {
		return this->y > other->y;
	}
}