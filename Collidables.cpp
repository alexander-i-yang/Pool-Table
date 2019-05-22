//
// Created by Samuel on 4/27/2019.
//

#include "Collidables.h"
#include "Drawables.h"
#include "ShootAI.h"
#include "Ball.h"
#include <ctime>
#include <cmath>
#include <algorithm>


Collidables::Collidables() {
	objects = {};
	walls = {};
	friction = 1;
	hasCollided = false;
}

Collidables::~Collidables() {
	objects.clear();
	walls.clear();
	delete this;
}

void Collidables::add(Ball *ball) {
	this->objects.push_back(ball);
	if(ball->isStriped()&&ball->getNumber()!=0){
		stripes++;
	}
	else if(!(ball->isStriped())&&ball->getNumber()!=0){
		solids++;
	}
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
int Collidables::numOfStripes(){
	int stripeCount = 0;
	for(auto i : objects){
		if(i->isStriped()&&i->getNumber()!=0)
			stripeCount++;
	}
	return stripeCount;
}
int Collidables::numOfSolids(){
	int solidCount = 0;
	for(auto i : objects){
		if(!(i->isStriped())&&i->getNumber()!=0)
			solidCount++;
	}
	return solidCount;
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
int Collidables::updateAll(Drawables * drawables) {
	int returnVal = 0;
	for (auto i : objects) {
		for (auto j : objects) {
			if (i != j && i->checkCollide(j)) {
				std::pair<double, double> newVelocity = i->getNewVelocity(j);
				i->setVelocity(newVelocity.first, newVelocity.second);
			}
		}
		i->updateFrame(friction);
		double xv = i->getXVelocity();
		double yv = i->getYVelocity();
//		i->setVelocity((xv)*friction, (yv)*friction);
		for(auto j : pockets){
			if(collision(i, j)){
				if (i->isStriped()) {
					if (returnVal == 0) returnVal = 1;
					else if (returnVal == -1) returnVal = -1;
					else returnVal = 3;
					this->stripes--;
				} else {
					if (returnVal == 0) returnVal = 2;
					else if (returnVal == -1) returnVal = -1;
					else returnVal = 3;
					this->solids--;
					hasCollided = true;
				}
				if(i->getNumber()==0){
					i->setPos(i->getWindowWidth()/2, i->getWindowHeight()/2);
					i->setVelocity(0, 0);
					returnVal = -1;
					//this->solids++;
					std::cout<<"white ball fell in hole!"<<'\n';
				}
				else if(i->getNumber()==8){
					objects.clear();
					std::cout<<"8 Ball!"<<'\n';
				}
				else{
					objects.erase(std::remove(objects.begin(), objects.end(), i), objects.end());
					drawables->objects.erase(std::remove(drawables->objects.begin(), drawables->objects.end(), i), drawables->objects.end());
					std::cout << i->getNumber() << " fell in " << j->getNumber() << '\n';
//                    objects.erase(std::remove(objects.begin(), objects.end(), i), objects.end());
//                    drawables->objects.erase(std::remove(drawables->objects.begin(), drawables->objects.end(), i), drawables->objects.end());
				}

			}
		}
		for (auto j : walls) {
			collision(i, j);
		}
	}
	return returnVal;
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

void Collidables::shootAI() {
//	if(objects.size() > 1) {
//		Ball *whiteBall = objects.at(0);
//		for(auto b = objects.begin()+1; b!=objects.end(); ++b) {
//			std::pair<double, double> v = ShootAI::shootWhiteBall(whiteBall, *b, pockets.at(0)->getX(), pockets.at(0)->getY());
//			bool theOne = true;
//			for(Ball* extra: objects) {
//				if(extra != *b && ShootAI::predictCollide(whiteBall, extra, v.first, v.second, (*b)->getX())) {
//					theOne = false;
//					break;
//				}
//			}
//			if(theOne) {
//				whiteBall->setVelocity(v.first, v.second);
//				break;
//			}
//		}
//	}
	if(objects.size() > 1) {
		std::cout << "{";
		for (auto i : objects) {
			std::cout << i->getNumber() << ", ";
		}
		std::cout << "}\n";
		Ball *whiteBall = objects.at(0);
//		ShootAI::minimax(whiteBall, &objects, &walls[0], &pockets[0], true, 0, friction);
		for (int i = 0; i < objects.size(); ++i) {
			auto b = objects.at(i);
			if (b->getNumber() == whiteBall->getNumber()) continue;
			for (int j = 0; j < pockets.size(); ++j) {
				auto p = pockets.at(j);
				auto v = ShootAI::computePath(whiteBall, b, p);
				auto o = &objects;
				if (ShootAI::validPath(v, whiteBall, b, p, o)) {
					std::cout << "Target: " << (b)->getNumber() << " -> " << p->getNumber() << '\n';
					whiteBall->setVelocity(v.first.first*1500, v.first.second*1500);
					return;
				}
			}
		}

		/*
		for(auto b = objects.begin()+1; b!=objects.end(); ++b) {
			auto v = ShootAI::computePath(whiteBall, *b, pockets.at(0));
			auto o = &objects;
			if (ShootAI::validPath(v, whiteBall, *b, pockets.at(0), o)) {
				std::cout << "Target: " << (*b)->getNumber() << '\n';
				whiteBall->setVelocity(v.first.first*3000, v.first.second*3000);
				return;
			}
//			whiteBall->setVelocity(v.first.first*3000, v.first.second*3000);
		}
		*/

		whiteBall->setVelocity(1000*sqrt(3), 1000);
		std::cout << "Target: none" << std::endl;
	}
}

void Collidables::shootAI(int ballType) {
	// 1 will be for solids, -1 will be for stripes, 0 will be for nothing
	if (objects.empty()) return;
	auto balls = &objects;
	auto whiteBall = objects.at(0);
	std::pair<double, double> bestPath;
	std::pair<int, int> targets;
	int best = INT_MIN;
	bool sinkflag = false;
	bool hitEight = true;
	for (int i = 0; i < balls->size(); ++i) {
		Ball* b = balls->at(i);
		if (b->getNumber() == whiteBall->getNumber() || b->getNumber() == 8) continue;
		if (ballType == -1) {
			if (b->isStriped()) continue;
		}
		else if (ballType == 1) {
			if (!b->isStriped()) continue;
		}
		hitEight = false;
		for (int j = 0; j < 4; ++j) {
			Pocket* p = pockets[j];
			auto path = ShootAI::computePath(whiteBall, b, p);
			if (!ShootAI::validPath(path, whiteBall, b, p, balls)) continue;
			for (int power = 1500; power <= 2500; power += 250) {
				// add a check to see if the power is actually strong enough to hit the ball in the pocket
				auto newPaths = ShootAI::collisionVelocity(whiteBall, b, power, friction, path);
				auto finalPos = ShootAI::predictFinalLocation(std::make_pair(b->getX(), b->getY()), std::make_pair(newPaths.second.first * power, newPaths.second.second * power), friction);
				if (ShootAI::distance(finalPos.first, finalPos.second, b->getX(), b->getY()) < ShootAI::distance(b->getX(), b->getY(), p->getX(), p->getY())) {
					continue;
				}

				auto hitPos = std::make_pair(b->getX()-path.second.first*2*b->getRadius(), b->getY()-path.second.second*b->getRadius()*2);
				auto newPos = ShootAI::predictFinalLocation(hitPos, newPaths.first, friction);

				double rightWall = walls[0]->getX();
				double leftWall = walls[1]->getX() + walls[1]->getWidth();
				double topWall = walls[2]->getY();
				double bottomWall = walls[3]->getY() + walls[3]->getHeight();
				while (newPos.first > rightWall || newPos.first < leftWall) {
					if (newPos.first > rightWall)
						newPos.first -= 2*(newPos.first - rightWall);
					else if (newPos.first < leftWall)
						newPos.first += 2*(leftWall - newPos.first);
//					std::cout << "X: " << newPos.first << '\n';
				}
				while (newPos.second > topWall || newPos.second < bottomWall) {
					if (newPos.second > topWall)
						newPos.second -= 2*(newPos.second - topWall);
					else if (newPos.second < bottomWall)
						newPos.second += 2*(bottomWall - newPos.second);
//					std::cout << "Y: " << newPos.second << '\n';
				}

				auto oldPos = std::make_pair(whiteBall->getX(), whiteBall->getY());
				whiteBall->setPos(newPos.first, newPos.second);
				balls->erase(std::find(balls->begin(), balls->end(), b));
				int newBest = std::max(best, ShootAI::minimax(whiteBall, balls, &walls[0], &pockets[0], true, ballType, 1, friction));
				if (newBest > best) {
					best = newBest;
					bestPath = path.first;
					bestPath.first *= power;
					bestPath.second *= power;
					targets = std::make_pair(b->getNumber(), p->getNumber());
				}
				balls->push_back(b);
				whiteBall->setPos(oldPos.first, oldPos.second);
				sinkflag = true;
			}
		}
	}
	if (hitEight) {
		Ball* b;
		for (int i = 0; i < balls->size(); ++i) {
			if (balls->at(i)->getNumber() == 8) {
				b = balls->at(i);
			}
		}
		for (int j = 0; j < 4; ++j) {
			Pocket* p = pockets[j];
			auto path = ShootAI::computePath(whiteBall, b, p);
			if (!ShootAI::validPath(path, whiteBall, b, p, balls)) continue;
			balls->erase(std::find(balls->begin(), balls->end(), b));
			int newBest = ShootAI::evaluateTable(balls, true);
			balls->push_back(b);
			if (newBest > best) {
				best = newBest;
				bestPath = path.first;
				bestPath.first *= 2000;
				bestPath.second *= 2000;
				targets = std::make_pair(8, p->getNumber());
			}
		}
	}
	else if (!sinkflag) {
		// change implementation
		// right now it does not hit the cue ball if it can't find a move
		int newBest = ShootAI::minimax(whiteBall, balls, &walls[0], &pockets[0], false, ballType, 1, friction);
		if (newBest > best) {
			best = newBest;
			bestPath = std::make_pair(2200, 200);
			targets = std::make_pair(-1, -1);
		}
	}
	whiteBall->setVelocity(bestPath.first, bestPath.second);
//	std::cout << bestPath.first << " " << bestPath.second << '\n';
	std::cout << targets.first << " -> " << targets.second << '\n';
}
