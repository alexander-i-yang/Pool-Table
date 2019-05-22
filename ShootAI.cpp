//
// Created by Alex on 5/7/2019.
//

#include "ShootAI.h"
#include "Ball.h"
#include <utility>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include "math.h"

#define PI 3.14159265358979
#define ADJUST_FRICTION 0.002

std::pair<double,double> ShootAI::shootWhiteBall(Ball *whiteBall, Ball* shoot, double targetX, double targetY) {
	double a = whiteBall->getX();
	double b = whiteBall->getY();
	double c = shoot->getX();
	double d = shoot->getY();
	double r = whiteBall->getRadius();
	double th = atanf((targetY-d)/(targetX-c));
	if(targetY-d < 0) th-=3.14159265;
	double xf = -2*r*cosf(th)+c;
	double yf = -2*r*sinf(th)+d;
	double tho = atanf((yf-b)/(xf-a));
	if(yf-b < 0) tho -= 3.14159265;
	double xv = xf-a;
	double yv = yf-b;
	double targetDistance = sqrt((c-targetX)*(c-targetX)+(d-targetY)*(d-targetY));
	double ballDistance = sqrt((a-c)*(a-c)+(b-d)*(b-d));
	double xvf = log(targetDistance+ballDistance)*xv;
	double yvf = log(targetDistance+ballDistance)*yv;
	std::pair<double, double> ret = {xvf, yvf};
	return ret;
}

bool ShootAI::predictCollide(Ball* whiteBall, Ball* other, double xv, double yv, double stopX) {
	double a = whiteBall->getX();
	double b = whiteBall->getY();
	double c = other->getX();
	double d = other->getY();
	double r = whiteBall->getRadius();
	double yb = yv/xv*(c-a)+b-2*r;
	double yc = yv/xv*(c-a)+b+2*r;
	std::cout << "(" << a << ", " << b << ")" << std::endl;
	std::cout << "(" << c << ", " << d << ")" << std::endl;
	std::cout << "Radius: " << r << std::endl;
	std::cout << "<" << xv << ", " << yv << ">" << std::endl;
	std::cout << "Yb: " << yb << " Yc: " << yc << std::endl;
	std::cout << "stopx: " << stopX << std::endl;
	if((xv < 0 && a>c && c>stopX) || (xv > 0 && a<c && c<stopX)) {
		if(yb < d && d < yc) {
			return true;
		}
	}
	return false;
}

int ShootAI::minimax(Ball *whiteBall, std::vector<Ball *> *balls, Wall **walls, Pocket **pockets, bool isMaximizer, int ballType, int depth, double friction) {
	// maximizer will go for solids
	int score = evaluateTable(balls, isMaximizer);
	if (score >= 8 || score <= -8) return score;
	if (depth >= 4) return score;
//	if (isMaximizer) {
	int best = isMaximizer ? INT_MIN : INT_MAX;
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
			auto path = computePath(whiteBall, b, p);
			if (!validPath(path, whiteBall, b, p, balls)) continue;
			for (int power = 1000; power <= 2000; power += 500) {
				// add a check to see if the power is actually strong enough to hit the ball in the pocket
				auto newPaths = ShootAI::collisionVelocity(whiteBall, b, power, friction, path);
				auto finalPos = ShootAI::predictFinalLocation(std::make_pair(b->getX(), b->getY()), std::make_pair(newPaths.second.first * power, newPaths.second.second * power), friction);
				if (ShootAI::distance(finalPos.first, finalPos.second, b->getX(), b->getY()) < ShootAI::distance(b->getX(), b->getY(), p->getX(), p->getY())) {
					continue;
				}

				auto hitPos = std::make_pair(b->getX()-path.second.first*2*b->getRadius(), b->getY()-path.second.second*b->getRadius()*2);
				auto newPos = ShootAI::predictFinalLocation(hitPos, newPaths.first, friction);

				/*
				// x adjustments
				while (newPos.first >= walls[0]->getX() || newPos.first <= walls[1]->getX()) {
					if (newPos.first >= walls[0]->getX()) {
						newPos.first -= 2*(newPos.first - walls[0]->getX());
					}
					else if (newPos.first <= walls[1]->getX()) {
						newPos.first += 2*(walls[1]->getX() - newPos.first);
					}
				}
				// y adjustments
				while (newPos.second >= walls[2]->getY() || newPos.second <= walls[3]->getY()) {
					if (newPos.second >= walls[2]->getY()) {
						newPos.second -= 2*(newPos.second - walls[2]->getY());
					}
					else if (newPos.first <= walls[3]->getY()) {
						newPos.second += 2*(walls[3]->getY() - newPos.second);
					}
				}
				 */

				auto oldPos = std::make_pair(whiteBall->getX(), whiteBall->getY());
				whiteBall->setPos(newPos.first, newPos.second);
				balls->erase(std::find(balls->begin(), balls->end(), b));
				best = isMaximizer ? std::max(best, minimax(whiteBall, balls, walls, pockets, isMaximizer, ballType, depth + 1, friction)) :
						             std::min(best, minimax(whiteBall, balls, walls, pockets, isMaximizer, ballType, depth + 1, friction));
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
			auto path = computePath(whiteBall, b, p);
			if (!validPath(path, whiteBall, b, p, balls)) continue;
			balls->erase(std::find(balls->begin(), balls->end(), b));
			auto ret = evaluateTable(balls, isMaximizer);
			balls->push_back(b);
			return ret;
		}
	}
	else if (!sinkflag) {
		// change implementation
		// right now it does not hit the cue ball if it can't find a move
		best = isMaximizer ? std::max(best, minimax(whiteBall, balls, walls, pockets, !isMaximizer, ballType, depth + 1, friction)) :
				             std::min(best, minimax(whiteBall, balls, walls, pockets, !isMaximizer, ballType, depth + 1, friction));
	}
	return best;
//	}
}

std::pair<double, double> ShootAI::predictFinalLocation(std::pair<double, double> r, std::pair<double, double> v, double friction){
	double x = r.first;
	double y = r.second;
	double xVelocity = v.first;
	double yVelocity = v.second;

	double angle = atan2(yVelocity, xVelocity);
//	if (xVelocity < 0){
//		angle += 3.141592;
//	}                                                       // GETTING ANGLE FROM 0 to 2pi
	double frictionX = friction * cos(angle);
	double frictionY = friction * sin(angle);              // GETS X AND Y COMPONENTS OF FRICTION

	double dx = frictionX == 0 ? 0 : pow(xVelocity, 2)/(2 * frictionX) * ADJUST_FRICTION;
	double dy = frictionY == 0 ? 0 : pow(yVelocity, 2)/(2 * frictionY) * ADJUST_FRICTION;

	std::pair<double, double> endLoc = {x + dx, y + dy};
	return endLoc;
}

bool ShootAI::ccw(double ax, double ay, double bx, double by, double cx, double cy) {
	double dx1 = bx - ax;
	double dy1 = by - ay;
	double dx2 = cx - ax;
	double dy2 = cy - ay;
	if (dx1*dy2 >= dy1*dx2) return true;
	return false;
}

double ShootAI::distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}



int ShootAI::evaluateTable(std::vector<Ball *> *balls, bool isMaximizer) {
	int numStriped = 0, numSolid = 0;
	bool eightExists = true;
	for (int i = 0; i < balls->size(); ++i) {
		Ball* b = balls->at(i);
		if (b->getNumber() >= 1 || b->getNumber() <= 7) ++numSolid;
		else if (b->getNumber() >= 9 || b->getNumber() <=15) ++numStriped;
		else if (b->getNumber() == 8) eightExists = false;
	}
	if (!eightExists) {
		if (numSolid == 0) return 8;
		else if (numStriped == 0) return -8;
		else if (isMaximizer) return -8;
		else if (!isMaximizer) return 8;
	}
	else {
		return numSolid - numStriped;
	}
	return 0;
}

std::pair<std::pair<double, double>, std::pair<double, double> > ShootAI::computePath(Ball *whiteBall, Ball *targetBall, Pocket *targetPocket) {
	double tx, ty;
	if (targetPocket->getNumber() <= 3) {
		tx = targetPocket->getX() + targetPocket->getRadius()*sqrt(2)/2*(-pow(targetPocket->getNumber()-1.5, 2)+1.25);
		ty = targetPocket->getY() + targetPocket->getRadius()*sqrt(2)/2*((int)((targetPocket->getNumber()-1.5)*2)/2);
	}
	else if (targetPocket->getNumber() >= 4) {
		tx = targetPocket->getX();
		ty = targetPocket->getY()+targetPocket->getRadius()*(targetPocket->getNumber()-4.5)*2;
	}
//	tx = targetPocket->getX();
//	ty = targetPocket->getY();
	double dx2 = tx - targetBall->getX();
	double dy2 = ty - targetBall->getY();
	double d2Length = sqrt(dx2 * dx2 + dy2 * dy2);
	dx2 /= d2Length;
	dy2 /= d2Length;

	double tbx = targetBall->getX()-2*dx2*targetBall->getRadius();
	double tby = targetBall->getY()-2*dy2*targetBall->getRadius();
	double dx1 = tbx - whiteBall->getX();
	double dy1 = tby - whiteBall->getY();
	double d1Length = sqrt(dx1 * dx1 + dy1 * dy1);
	dx1 /= d1Length;
	dy1 /= d1Length;

	return std::make_pair(std::make_pair(dx1, dy1), std::make_pair(dx2, dy2));
}

bool ShootAI::validPath(std::pair<std::pair<double, double>, std::pair<double, double> > path, Ball *whiteBall, Ball *targetBall, Pocket *targetPocket, std::vector<Ball *> *balls) {
	// checks for valid angle
	double x1, y1, x2, y2;
	x1 = targetBall->getX() - targetBall->getRadius() * path.second.first;
	y1 = targetBall->getY() - targetBall->getRadius() * path.second.second;
	x2 = x1 + targetBall->getRadius()*path.second.second;
	y2 = y1 - targetBall->getRadius()*path.second.first;
	if (ccw(x1, y1, x2, y2, whiteBall->getX(), whiteBall->getY()))
		return false;
	// checks if there are any balls on the path
	return ShootAI::validFirstLeg(path, whiteBall, targetBall, balls) && ShootAI::validSecondLeg(path, targetBall, targetPocket, balls);
//	return true;
}

bool ShootAI::validFirstLeg(std::pair<std::pair<double, double>, std::pair<double, double> > path, Ball* whiteBall, Ball* targetBall, std::vector<Ball *> *balls) {
	double dx = path.first.first;
	double dy = path.first.second;
	double nx1 = whiteBall->getX() - dy*(whiteBall->getRadius());
	double ny1 = whiteBall->getY() + dx*(whiteBall->getRadius());
	double newCenterX = targetBall->getX() - 2*path.second.first*targetBall->getRadius();
	double newCenterY = targetBall->getY() - 2*path.second.second*targetBall->getRadius();
	double nx2 = newCenterX - dy*(targetBall->getRadius());
	double ny2 = newCenterY + dx*(targetBall->getRadius());
	for (int i = 0; i < balls->size(); ++i) {
		Ball* other = balls->at(i);
		if (other->getNumber() == whiteBall->getNumber() || other->getNumber() == targetBall->getNumber()) {
			continue;
		}
		if (distance(newCenterX, newCenterY, other->getX(), other->getY()) < whiteBall->getRadius() + other->getRadius()) {
			return false;
		}
		double distance = fabs(dy/dx*other->getX() - other->getY() + (whiteBall->getY()-whiteBall->getX()*dy/dx)) / sqrt((dy*dy)/(dx*dx)+1);
		if (distance <= 2*whiteBall->getRadius()) {
			if (!ccw(whiteBall->getX(), whiteBall->getY(), nx1, ny1, other->getX(), other->getY())) {
				if (ccw(newCenterX, newCenterY, nx2, ny2, other->getX(), other->getY())) {
					return false;
				}
			}
		}
	}
	return true;
}

bool ShootAI::validSecondLeg(std::pair<std::pair<double, double>, std::pair<double, double> > path, Ball *targetBall, Pocket *targetPocket, std::vector<Ball *> *balls) {
	for (int i = 0; i < balls->size(); ++i) {
		Ball* other = balls->at(i);
		if (other->getNumber() == targetBall->getNumber()) {
			continue;
		}
		double dx = path.second.first;
		double dy = path.second.second;
		double distance = fabs(dy/dx*other->getX() - other->getY() + (targetBall->getY()-targetBall->getX()*dy/dx)) / sqrt((dy*dy)/(dx*dx)+1);
		if (distance <= 2*targetBall->getRadius()) {
			double nx1 = targetBall->getX() - dy*(targetBall->getRadius());
			double ny1 = targetBall->getY() + dx*(targetBall->getRadius());
			double nx2 = targetPocket->getX() - dy*(targetBall->getRadius());
			double ny2 = targetPocket->getY() + dx*(targetBall->getRadius());
			if (!ccw(targetBall->getX(), targetBall->getY(), nx1, ny1, other->getX(), other->getY())) {
				if (ccw(targetPocket->getX(), targetPocket->getY(), nx2, ny2, other->getX(), other->getY())) {
					return false;
				}
			}
		}
	}
	return true;
}

std::pair<std::pair<double, double>, std::pair<double, double> > ShootAI::collisionVelocity(Ball *whiteBall, Ball *targetBall, double vi, double friction, std::pair<std::pair<double, double>, std::pair<double, double> > path) {
	double pathx1 = path.first.first;
	double pathy1 = path.first.second;
	double pathx2 = path.second.first;
	double pathy2 = path.second.second;
	double x2 = targetBall->getX() - 2*targetBall->getRadius()*pathx2;
	double y2 = targetBall->getY() - 2*targetBall->getRadius()*pathy2;
	double d = ShootAI::distance(whiteBall->getX(), whiteBall->getY(), x2, y2);
	double theta1 = atan2(pathy1, pathx1) + path.first.first < 0 ? PI : 0;
//	double vfx = sqrt(fabs(vi*vi - 2*d*friction)) * cos(theta1);
//	double vfy = sqrt(fabs(vi*vi - 2*d*friction)) * sin(theta1);
	double vf = sqrt(fabs(vi*vi - 2*d*friction*ADJUST_FRICTION));
	double theta = PI - acos((pathx1*pathx2+pathy1*pathy2)/(sqrt(pow(pathx1, 2)+pow(pathy1, 2))*sqrt(pow(pathx2, 2)+pow(pathy2, 2))));
	std::pair<double, double> newWhite = std::make_pair(pathx1*sin(theta)*vf, pathy1*sin(theta)*vf);
	std::pair<double, double> newTarget = std::make_pair(pathx2*cos(theta)*vf, pathy2*cos(theta)*vf);
	return std::make_pair(newWhite, newTarget);
}

