//
// Created by Samuel on 4/27/2019.
//

#include "Collidables.h"
#include "Drawables.h"
#include "ShootAI.h"
#include "Set.h"
#include <cmath>
#include <algorithm>
#include <climits>

#define INF INT_MAX

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
//		std::pair<int, int> closestPoints = closestPair();
//		std::cout << closestPoints.first << " " << closestPoints.second << std::endl;
		i->updateFrame(friction);
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

std::pair<int, int> Collidables::closestPair() {
	std::pair<int, int> ret;
	double minDist = INF;
	std::vector<Point*>* balls = new std::vector<Point*>;
	Set<Point>* s = new Set<Point>;
	for (int i = 0; i < objects.size(); ++i) {
		Point* p = new Point(objects[i]->getX(), objects[i]->getY(), objects[i]->getNumber());
		balls->push_back(p);
	}
	std::sort(balls->begin(), balls->end(), HorizontalCompare());
//	for (Point i : *balls) {
//		std::cout << i.x << " " << i.y << " " << i.tag << '\n';
//	}
	int leftMost = 0;
	for (int ii = 0; ii < balls->size(); ++ii) {
		Point* i = balls->at(ii);
		while (i->x - balls->at((unsigned)leftMost)->x >= minDist) {
			s->remove(balls->at((unsigned)leftMost));
			++leftMost;
		}
		Point* head = new Point(i->x, i->y + minDist, -1);
		Point* tail = new Point(i->x, i->y - minDist, -1);
		auto subSet = s->subset(s->root, *tail, *head);
		for (int jj = 0; jj < subSet->size(); ++jj) {
			Point* j = subSet->at(jj);
			double distance = i->distance(*j);
			if (distance < minDist) {
				minDist = distance;
				ret.first = i->tag;
				ret.second = j->tag;
			}
		}
//		for (Point j : s->subset(s->root, *tail, *head)) {
////            std::cout << j.tag << std::endl;
////			std::cout << "(" << j.x << ", " << j.y << ", " << j.tag << ") ";
//			double distance = i->distance(j);
//			if (distance < minDist) {
//				minDist = distance;
//				ret.first = i->tag;
//				ret.second = j.tag;
//			}
//		}
		free(head);
		free(tail);
		free(i);
//		std::cout << '\n';
		s->insert(i);
	}
	free(balls);
	free(s);
//	std::cout << "(" << ret.first << ", " << ret.second << ")" << std::endl;
	return ret;
}

void Collidables::setFriction(double friction) {
	Collidables::friction = friction;
}

bool Collidables::checkNotMoving(double threshold) {
	for (auto i : objects) {
		double vx = fabs(i->getXVelocity());
		double vy = fabs(i->getYVelocity());
		if(sqrt(vx * vx + vy * vy) > threshold) return false;
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

void Collidables::shootAI() {
	if(objects.size() > 1) {
		Ball *whiteBall = objects.at(0);
		for (auto b : objects) {
            std::pair<double, double> v = ShootAI::shootWhiteBall(whiteBall, b, pockets.at(0)->getX(), pockets.at(0)->getY());
            for (auto extra : objects) {
                if(extra->getNumber() != (b)->getNumber() && ShootAI::predictCollide(whiteBall, extra, v.first, v.second, (b)->getX())) {
                    continue;
                }
                whiteBall->setVelocity(v.first, v.second);
                break;
            }
		}
//		for(auto b = objects.begin()+1; b!=objects.end(); ++b) {
//			std::pair<double, double> v = ShootAI::shootWhiteBall(whiteBall, *b, pockets.at(0)->getX(), pockets.at(0)->getY());
//			bool theOne = true;
//			for(Ball* extra: objects) {
//				if(extra->getNumber() != (*b)->getNumber() && ShootAI::predictCollide(whiteBall, extra, v.first, v.second, (*b)->getX())) {
//					theOne = false;
//					break;
//				}
//			}
//			if(theOne) {
//				whiteBall->setVelocity(v.first, v.second);
//				break;
//			}
//		}
	}
}
