//
// Created by Samuel on 4/27/2019.
//

#include "Collidables.h"

Collidables::Collidables() {
	objects = {};
}

Collidables::~Collidables() {
	objects.clear();
	delete this;
}

void Collidables::add(Ball *ball) {
	this->objects.push_back(ball);
}

void Collidables::clear() {
	this->objects.clear();
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
	}
}