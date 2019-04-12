//
// Created by samue on 2/27/2019.
//

#include "Collidable.h"
#include <cmath>
#include <ctime>
#include "Ball.h"

Collidable::Collidable() : Drawable() {
    std::pair<int, int> v;
    v.first = 0;
    v.second = 0;
    setVelocity(v);
    setVAngle(0);
    timeLastIncrX = glfwGetTime();
    setMass(0);
}

Collidable::Collidable(Color c, double x, double y, double z) : Drawable(c, x, y, z) {
	std::pair<int, int> v;
	v.first = 0;
	v.second = 0;
	setVelocity(v);
	setVAngle(0);
	timeLastIncrX = glfwGetTime();
	setMass(0);
}

Collidable::Collidable(const std::pair<int, int> &velocity) : Collidable() {
    setVelocity(velocity);
}

Collidable::Collidable(double vAngle) : Collidable() {
    setVAngle(vAngle);
}

Collidable::Collidable(double vAngle, double mass, const std::pair<int, int> &velocity) : Collidable() {
    setMass(mass);
    setVAngle(vAngle);
    setVelocity(velocity);
}

std::pair<double, double> Collidable::getVelocity() const {
    return velocity;
}

double Collidable::getVAngle() const {
    return vAngle;
}

double Collidable::getMass() const {
    return mass;
}

double Collidable::getSpeed() {
    return sqrt(pow(this->getVelocity().first, 2) + pow(this->getVelocity().second, 2));
}

double Collidable::getXVelocity() {return velocity.first;}
double Collidable::getYVelocity() {return velocity.second;}

void Collidable::setVelocity(const std::pair<double, double> &velocity) {
    Collidable::velocity = velocity;
    updateAngle();
}

void Collidable::setVAngle(double vAngle) {
    Collidable::vAngle = vAngle;
}

void Collidable::setMass(double mass) {
    Collidable::mass = mass;
}

void Collidable::setVelocity(double x, double y) {
    velocity.first = x;
    velocity.second = y;
    updateAngle();
    //std::cout << "Set: " << velocity.first << " " << velocity.second << std::endl;
}

void Collidable::updateAngle() {
    vAngle = sin(velocity.second/velocity.first);
}

void Collidable::updateFrame() {
    double xV = this->getXVelocity();
    double yV = this->getYVelocity();
	double difTime = glfwGetTime() - timeLastIncrX;
	timeLastIncrX = glfwGetTime();
	Drawable::incrX(xV*difTime);
	Drawable::incrY(yV*difTime);
}

std::pair<double, double> Collidable::getVelocityCollision(Drawable *o) {
    auto other = dynamic_cast<Collidable*>(o);
	if(other->mass == 0 || this->mass == 0) {
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
	double vPrime1n = (v1n*(this->mass-other->mass)+2*other->mass*v2n)/(this->mass+other->mass);
	double vPrime2n = (v2n*(other->mass-mass)+2*mass*v1n)/(mass+other->mass);
	double vPrime1t = ut.first*velocity.first + ut.second*velocity.second;
	this->setVelocity(vPrime1n*un.first+vPrime1t*ut.first, vPrime1n*un.second+vPrime1t*ut.second);
	std::pair<double, double> vPrime2nVector = {vPrime2n*un.first, vPrime2n*un.second};
	std::pair<double, double> vPrime2tVector = {v2t*ut.first, v2t*ut.second};
	other->setVelocity(vPrime2nVector.first+vPrime2tVector.first, vPrime2nVector.second+vPrime2tVector.second);
	return velocity;
}