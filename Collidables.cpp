//
// Created by Samuel on 4/27/2019.
//

#include "Collidables.h"
#include "Drawables.h"
#include <cmath>
#include <algorithm>


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
void Collidables::add(Pocket *pocket){
	this->pockets.push_back(pocket);
}
void Collidables::clear() {
	this->objects.clear();
	this->walls.clear();
}
bool collision(Ball * b, Pocket * p){
	double ballX = b->getX();
	double ballY = b->getY();
	double pocketX = p->getX();
	double pocketY = p->getY();
	double pocketWidth = p->getRadius();
	double testX = pocketX;
	double testY = pocketY;

	float distX = ballX - testX;
	float distY = ballY - testY;
	float distance = sqrt((distX*distX)+(distY*distY));

	//collision!
	if(distance<=b->getRadius()*2){
		return true;
	}
	return false;
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
void Collidables::updateAll(Drawables * drawables) {
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
		i->setVelocity((xv)*friction, (yv)*friction);
		for(auto j : pockets){
			if(collision(i, j)){
				objects.erase(std::remove(objects.begin(), objects.end(), i), objects.end());
				drawables->objects.erase(std::remove(drawables->objects.begin(), drawables->objects.end(), i), drawables->objects.end());
			}
		}
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