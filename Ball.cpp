//
// Created by samue on 2/27/2019.
//

#include <utility>
#include <string>
#include <cmath>
#include <iostream>
#include "Ball.h"
#include "Drawable.h"

void wait(double seconds) {
	double last = glfwGetTime();
	//std::cout << last << std::endl;
	while(last+seconds > glfwGetTime()) {
		//std::cout << glfwGetTime()<< std::endl;
	}
}

Ball::Ball() : Drawable() {
	this->referenceTime = glfwGetTime();
}

Ball::Ball(Color c, double x, double y, double z, double radius) : Drawable(c, x, y, z) {
	this->referenceTime = glfwGetTime();
	this->radius = radius;
}

Ball::Ball(Color c, double x, double y, double z, double radius, std::pair<double, double> velocity, double theta, double mass) : Drawable(c, x, y, z) {
	this->referenceTime = glfwGetTime();
	this->radius = radius;
	this->velocity = std::make_pair(velocity.first, velocity.second);
	this->theta = theta;
	this->mass = mass;
}

double Ball::getTime() {return this->referenceTime;}
double Ball::getRadius() {return this->radius;}
double Ball::getTheta() {return this->theta;}
double Ball::getMass() {return this->mass;}
double Ball::getXVelocity() {return this->velocity.first;}
double Ball::getYVelocity() {return this->velocity.second;}
double Ball::getSpeed() {return sqrt(pow(this->getXVelocity(), 2) + pow(this->getYVelocity(), 2));}

void Ball::setTime(double time) {this->referenceTime = time;}
void Ball::setRadius(double radius) {this->radius = radius;}
void Ball::setTheta(double theta) {this->theta = theta;}
void Ball::setMass(double mass) {this->mass = mass;}
void Ball::setVelocity(double vx, double vy) {this->velocity = std::make_pair(vx, vy);}
void Ball::updateAngle() {this->setTheta(atan2(this->getYVelocity(), this->getXVelocity()));}

int Ball::getNumSides() {
	return (int)this->getRadius() * 3;
}

/* needs implementation */
void Ball::draw() {
	double r = this->getRadius();
	double x = this->getX();
	double y = this->getY();
	double triangleAmount = this->getNumVertices();
	//glColorPointer(3, GL_FLOAT, 0, this->getColorArray());
	glColor3f(this->getColor().getR(), this->getColor().getG(), this->getColor().getB());
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= triangleAmount; ++i) {
		glVertex2f(x + r * cos(i * 2 * 3.1415926 / triangleAmount), y + r * sin(i * 2 * 3.1415926 / triangleAmount));
	}
	glEnd();

	if(striped) {
		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (int i = triangleAmount / 8; i <= triangleAmount * 5 / 8; ++i) {
			glVertex2f(x + r * cos(i * 2 * 3.1415926538979323846 / triangleAmount),
			           y + r * sin(i * 2 * 3.1415926538979323846 / triangleAmount));
		}
		glEnd();
	}
}

int Ball::getNumVertices() {
	int numberOfSides = (int)(this->getRadius());
	int numberOfVertices = numberOfSides + 2;
	return numberOfVertices;
}

void Ball::updateFrame(double friction = 0) {
	double xVelocity = this->getXVelocity();
	double yVelocity = this->getYVelocity();
	double timeElapsed = glfwGetTime() - this->getTime();
	this->setTime(glfwGetTime());
	Drawable::setX(this->getX() + timeElapsed * xVelocity);
	Drawable::setY(this->getY() + timeElapsed * yVelocity);
	double addX = 1-0.5*timeElapsed*friction*timeElapsed*mass;
	double addY = 1-0.5*timeElapsed*friction*timeElapsed*mass;
	setVelocity(xVelocity*addX, yVelocity*addY);
}

/* needs implementation */
double Ball::friction() {
	return 0;
}

void Ball::setColorRGB(double r, double g, double b) {
	this->getColor().setColor(r, g, b);
}

bool Ball::checkCollide(Ball *other) {
	/* calculate the distance between their centers
	 * if this value is greater than the sum of their radii then they do not collide
	 * otherwise they do
	 */
	double distBetween = this->perpendicularDistance(other);
	double radiiSum = this->getRadius() + other->getRadius();
	if(distBetween+1 < radiiSum) {
		//Shifts the balls over if they're on top of each other.
		//Assumes they both have the same radius.
		double a = this->getX();
		double b = this->getY();
		double c = other->getX();
		double d = other->getY();
		double t = atanf((b-d)/(a-c));
		if(a-c < 0) t += 3.14;
		double midX = (a+c)/2;
		double midY = (b+d)/2;
		double r = this->getRadius();
		double addX = r*cos(t);
		double addY = r*sin(t);
		std::cout << std::endl;
		if(sqrt((a-(midX-addX))*(a-(midX-addX))-(b-(midY-addY))*(b-(midY-addY))) < r-1) {
			this->setPos(midX-addX, midY-addY);
			other->setPos(midX+addX, midY+addY);
		} else {
			this->setPos(midX+addX, midY+addY);
			other->setPos(midX-addX, midY-addY);
		}
	}
	return distBetween <= radiiSum;
}

void Ball::setPos(double x, double y) {
	setX(x);
	setY(y);
}

/* clean up */
std::pair<double, double> Ball::getNewVelocity(Ball *other) {
	double m2 = other->getMass();

	if(m2 == 0 || this->mass == 0) {
		std::cout << "ERROR: Mass is 0" <<std::endl;
		return this->velocity;
	}
	double vf = velocity.first;
	double vs = velocity.second;
	double vof = other->velocity.first;
	double vos = other->velocity.second;
	std::pair<double, double> n = {other->getX()-Drawable::getX(), other->getY()-Drawable::getY()};
	std::pair<double, double> un = {n.first, n.second};
	double nNorm = sqrt(n.first*n.first+n.second*n.second);
	un.first /= nNorm;
	un.second /= nNorm;
	std::pair<double, double> ut = {-1*un.second, un.first};
	double v1n = un.first*vf + un.second*vs;
	double v2n = un.first*vof + un.second*vos;
	double v2t = ut.first*vof + ut.second*vos;
	double vPrime1n = (v1n*(this->mass-m2)+2*m2*v2n)/(this->mass+other->mass);
	double vPrime2n = (v2n*(other->mass-mass)+2*mass*v1n)/(mass+other->mass);
	double vPrime1t = ut.first*velocity.first + ut.second*velocity.second;
	this->setVelocity(vPrime1n*un.first+vPrime1t*ut.first, vPrime1n*un.second+vPrime1t*ut.second);
	std::pair<double, double> vPrime2nVector = {vPrime2n*un.first, vPrime2n*un.second};
	std::pair<double, double> vPrime2tVector = {v2t*ut.first, v2t*ut.second};
	other->setVelocity(vPrime2nVector.first+vPrime2tVector.first, vPrime2nVector.second+vPrime2tVector.second);
	return velocity;
}

/* needs implementation */
double Ball::getNewAngle(Ball* other) {
	return 0;
}

double Ball::perpendicularDistance(Ball *other) {
	double x1 = this->getX();
	double y1 = this->getY();
	double x2 = other->getX();
	double y2 = other->getY();
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool Ball::isStriped() const {
	return striped;
}

void Ball::setStriped(bool striped) {
	Ball::striped = striped;
}

void Ball::setXVelocity(double vx) {
	velocity.first = vx;
}

void Ball::setYVelocity(double vy) {
	velocity.second = vy;
}
