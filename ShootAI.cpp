//
// Created by Alex on 5/7/2019.
//

#include "ShootAI.h"
#include "Ball.h"
#include <utility>
#include <iostream>
#include <cmath>

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