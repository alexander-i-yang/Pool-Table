//
// Created by samue on 2/27/2019.
//

#include <iostream>
#include <cmath>
#include "Wall.h"
#include "Color.h"

Wall::Wall() : Collidable() {
	width = 0;
	height = 0;
}

Wall::Wall(int z, int x, int y, Color c) : Wall(z, x, y, c, 0, 0) {}

Wall::Wall(int z, int x, int y, Color c, int width, int height) : Collidable(c, x, y, z) {
	this->width = width;
	this->height = height;
}

GLfloat *Wall::getVerticesArray() {
	int numberOfVertices = getNumVertices();
	GLfloat* vertices = new GLfloat[numberOfVertices*3];

	for ( int i = 0; i < numberOfVertices; i++ ) {
		float a = i%3==0?0:width;
		float b = (i-1>0?height:0);
		vertices[i * 3] = static_cast<GLfloat>(Drawable::x + a);
		vertices[( i * 3 ) + 1] = static_cast<GLfloat>(Drawable::y + b);
		vertices[( i * 3 ) + 2] = static_cast<GLfloat>(Drawable::z);
	}
	return vertices;
}

int Wall::getNumVertices() {
	return 4;
}

double Wall::getCenterX() {
	return Drawable::x+width/2.0;
}

double Wall::getCenterY() {
	return Drawable::y+height/2.0;
}
