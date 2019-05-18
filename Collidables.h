//
// Created by Samuel on 4/27/2019.
//

#ifndef POOL_TABLE_COLLIDABLES_H
#define POOL_TABLE_COLLIDABLES_H


#include <vector>
#include <cmath>
#include "Ball.h"
#include "Drawables.h"
#include "Wall.h"
#include "Pocket.h"

class Point {

public:
    double x;
	double y;
	int tag;
	Point() {
	    x = 0;
	    y = 0;
	    tag = -2;
	}
	Point(double x, double y, int tag) {
	    this->x = x;
	    this->y = y;
	    this->tag = tag;
	}
	double distance(Point other) {
	    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
	}
	bool operator == (Point other) {
	    return this->x == other.x && this->y == other.y;
	}
	bool operator < (Point other) {
	    if (this->y == other.y) {
	        return this->x < other.x;
	    }
	    else {
	        return this->y < other.y;
	    }
	}
	bool operator > (Point other) {
        if (this->y == other.y) {
            return this->x > other.x;
        }
        else {
            return this->y > other.y;
        }
	}

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

class Collidables {

private:
	std::vector<Ball*> objects;
	std::vector<Wall*> walls;
    std::vector<Pocket*> pockets;
    double friction;
public:
	void setFriction(double friction);
	Collidables();
	~Collidables();
	void add(Ball* ball);
	void add(Wall* wall);
    void add(Pocket * pocket);
    Ball* getBall(int index) {return objects.at(index);}
    void clear();
	bool checkNotMoving(double threshold);
	void stopAll();
	void slowAll();
	void shootAI();
    void updateAll(Drawables * drawables); // will this update the Ball in Drawables as well?
	                  // it should, but this will pose problems if it doesn't
	                  // lol nvm we good
	std::pair<int, int> closestPair();
};

#endif //POOL_TABLE_COLLIDABLES_H