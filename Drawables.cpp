//
// Created by Alex on 3/27/2019.
//

#include "Drawables.h"

Drawables::Drawables() {
	objects = {};
}

Drawables::~Drawables() {
	this->clear();
}

void Drawables::clear() {
	for(auto i: objects) {
		objects.pop_back();
	}
}

Drawable* Drawables::get(int i) {
	return objects.at(i);
}

void Drawables::drawAll() {
	for(auto i: objects) {
		i->draw();
	}
}

void Drawables::add(Drawable * add) {
	objects.push_back(add);
}
