//
// Created by Alex on 5/7/2019.
//

#include "ShootAI.h"
#include "Ball.h"
#include <utility>
#include <iostream>
#include <cmath>
#include <climits>

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

int ShootAI::minimax(Ball *whiteBall, std::vector<Ball *> *balls, Wall **walls, Pocket **pockets, bool isMaximizer, int depth) {
	// maximizer will go for solids
	int score = evaluateTable(balls, isMaximizer);
	if (score >= 8 || score <= -8) return score;
	if (isMaximizer) {
		int best = INT_MIN;
		for (int i = 0; i < balls->size(); ++i) {
			Ball* b = balls->at(i);
			if (b->getNumber() == whiteBall->getNumber()) continue;
			if (b->isStriped()) continue;
			for (int j = 0; j < balls->size(); ++j) {
				Pocket* p = pockets[j];
				auto path = computePath(whiteBall, b, p);
				if (!validPath(path, whiteBall, b, p, balls)) continue;
				for (int power = 2000; power <= 6000; power += 2000) {

				}
			}
		}
	}
	return 0;
}

double ShootAI::ccw(double ax, double ay, double bx, double by, double cx, double cy) {
	return (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
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
	x1 = targetBall->getX() - targetBall->getRadius()*path.second.first;
	y1 = targetBall->getY() - targetBall->getRadius()*path.second.second;
	x2 = x1 + targetBall->getRadius()*path.second.second;
	y2 = y1 - targetBall->getRadius()*path.second.first;
	if (ccw(x1, y1, x2, y2, whiteBall->getX(), whiteBall->getY())>=0)
		return false;
	// checks if there are any balls on the path
	return ShootAI::validFirstLeg(path.first, whiteBall, targetBall, balls) && ShootAI::validSecondLeg(path.second, targetBall, targetPocket, balls);
//	return true;
}

bool ShootAI::validFirstLeg(std::pair<double, double> path, Ball* whiteBall, Ball* targetBall, std::vector<Ball *> *balls) {
	for (int i = 0; i < balls->size(); ++i) {
		Ball* other = balls->at(i);
		if (other->getNumber() == whiteBall->getNumber() || other->getNumber() == targetBall->getNumber()) {
			continue;
		}
		double dx = path.first;
		double dy = path.second;
		double distance = (dy/dx*other->getX() - other->getY() + (whiteBall->getY()-whiteBall->getX()*dy/dx)) / sqrt((dy*dy)/(dx*dx)+1);
		if (distance <= 2*whiteBall->getRadius()) {
			double nx1 = -whiteBall->getY() - dy*(whiteBall->getRadius());
			double ny1 = whiteBall->getX() + dx*(whiteBall->getRadius());
			double nx2 = -targetBall->getRadius() - dy*(targetBall->getRadius());
			double ny2 = targetBall->getRadius() + dx*(targetBall->getRadius());
			if (ccw(whiteBall->getX(), whiteBall->getY(), nx1, ny1, other->getX(), other->getY())>=0) {
				if (ccw(targetBall->getX(), targetBall->getY(), nx2, ny2, other->getX(), other->getY())<=0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool ShootAI::validSecondLeg(std::pair<double, double> path, Ball *targetBall, Pocket *targetPocket, std::vector<Ball *> *balls) {
	for (int i = 0; i < balls->size(); ++i) {
		Ball* other = balls->at(i);
		if (other->getNumber() == targetBall->getNumber()) {
			continue;
		}
		double dx = path.first;
		double dy = path.second;
		double distance = (dy/dx*other->getX() - other->getY() + (targetBall->getY()-targetBall->getX()*dy/dx)) / sqrt((dy*dy)/(dx*dx)+1);
		if (distance <= 2*targetBall->getRadius()) {
			double nx1 = -targetBall->getY() - dy*(targetBall->getRadius());
			double ny1 = targetBall->getX() + dx*(targetBall->getRadius());
			double nx2 = -targetPocket->getX() - dy*(targetBall->getRadius());
			double ny2 = targetPocket->getY() + dx*(targetBall->getRadius());
			if (ccw(targetBall->getX(), targetBall->getY(), nx1, ny1, other->getX(), other->getY())>=0) {
				if (ccw(targetPocket->getX(), targetPocket->getY(), nx2, ny2, other->getX(), other->getY())<=0) {
					return false;
				}
			}
		}
	}
	return true;
}

