//
// Created by Alex on 3/27/2019.
//

#include "Drawable.h"

Drawable::Drawable(Color c, double x, double y, double z) {
	this->setColor(c);
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

Drawable::Drawable() {
	Color c = {};
	this->setColor(c);
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Drawable::Drawable(Color c) {
	this->setColor(c);
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Drawable::Drawable(double x, double y, double z) {
	Color c = {};
	this->setColor(c);
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}