//
// Created by samue on 2/27/2019.
//
//
#include <iostream>
#include <cmath>
#include "Wall.h"
#include "Color.h"
#include "Wall.h"

Wall::Wall() : Drawable() {
	width = 0;
	height = 0;
}

Wall::Wall(int z, int x, int y, Color c) : Wall(z, x, y, c, 0, 0) {}

Wall::Wall(int z, int x, int y, Color c, int width, int height) : Drawable(c, x, y, z) {
	this->width = width;
	this->height = height;
}

int Wall::getNumVertices() {
	return 4;
}

void Wall::draw() {
	double x = this->getX();
	double y = this->getY();
	double w = this->getWidth();
	double h = this->getHeight();
	double triangleAmount = this->getNumVertices();
	glColor3f(this->getColor().getR(), this->getColor().getG(), this->getColor().getB());
	glBegin(GL_POLYGON);
	glVertex2f(x,y);
	glVertex2f(x+w,y);
	glVertex2f(x+w,y+h);
	glVertex2f(x,y+h);
	glEnd();
}

int Wall::getWidth() const {
	return width;
}

void Wall::setWidth(int width) {
	Wall::width = width;
}

int Wall::getHeight() const {
	return height;
}

void Wall::setHeight(int height) {
	Wall::height = height;
}

void Wall::updateFrame() {

}
