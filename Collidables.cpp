//
// Created by Samuel on 4/27/2019.
//

#include "Collidables.h"
#include <cmath>

Collidables::Collidables() {
	objects = {};
	walls = {};
	friction = 1;
}

Collidables::~Collidables() {
	objects.clear();
	walls.clear();
	delete this;
}

void Collidables::add(Ball *ball) {
	this->objects.push_back(ball);
}

void Collidables::add(Wall *wall) {
	this->walls.push_back(wall);
}

void Collidables::clear() {
	this->objects.clear();
	this->walls.clear();
}

void collision(Ball* b, Wall* w) {
	double cx = b->getX();
	double cy = b->getY();
	double rx = w->getX();
	double ry = w->getY();
	double rw = w->getWidth();
	double rh = w->getHeight();
	double testX = cx;
	double testY = cy;

	// which edge is closest?
	if (cx < rx)         testX = rx;      // test left edge
	else if (cx > rx+rw) testX = rx+rw;   // right edge
	if (cy < ry)         testY = ry;      // top edge
	else if (cy > ry+rh) testY = ry+rh;   // bottom edge

	// get distance from closest edges
	float distX = cx-testX;
	float distY = cy-testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= b->getRadius()) {
		if(cx-b->getRadius() > rx && cx+b->getRadius() < rx+rw) {
			b->flipYV();
			if(testY == ry) b->setY(b->getY()+(distance-b->getRadius()));
			else b->setY(b->getY()-(distance-b->getRadius()));
		}
		else {
			b->flipXV();
			if(testX == rx) b->setX(b->getX()+(distance-b->getRadius()));
			else b->setX(b->getX()-(distance-b->getRadius()));
		}
	}
	//return false;
}

void Collidables::updateAll() {
	for (auto i : objects) {
		for (auto j : objects) {
			if (i != j && i->checkCollide(j)) {
				std::pair<double, double> newVelocity = i->getNewVelocity(j);
				i->setVelocity(newVelocity.first, newVelocity.second);
			}
		}
		i->updateFrame();
		double xv = i->getXVelocity();
		double yv = i->getYVelocity();
		double th = 0;
		if (xv == 0) th = 3.14159265389/2;
		else th = atanf(yv/xv);
		if(xv < 0) th += 3.14159265389;

		double newX, newY;
		if (xv == 0) newX = 0;
		else {
			double amount = friction * cos(th);
			if (amount < 0) amount *= -1;

			if (xv > 0) newX = xv - amount;
			else newX = xv + amount;
			if (newX * xv < 0) newX = 0;
		}

		if (yv == 0) newY = 0;
		else {
			double amount = friction * sin(th);
			if (amount < 0) amount *= -1;

			if (yv > 0) newY = yv - amount;
			else newY = yv + amount;
			if (newY * yv < 0) newY = 0;
		}

		i->setVelocity(newX, newY);
		for (auto j : walls) {
			collision(i, j);
		}
	}
}

void Collidables::setFriction(double friction) {
	Collidables::friction = friction;
}

bool Collidables::checkNotMoving(double threshold) {
	for (auto i : objects) {
		double vx = fabs(i->getXVelocity());
		double vy = fabs(i->getYVelocity());
		if(vx > threshold || vy>threshold) return false;
	}
	return true;
}

void Collidables::stopAll() {
	for (auto i : objects) {
		i->setVelocity(0, 0);
	}
}

void Collidables::slowAll() {
	friction = friction*friction;
}