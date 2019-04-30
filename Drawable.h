//
// Created by Alex on 3/27/2019.
//

#ifndef POOL_TABLE_DRAWABLE_H
#define POOL_TABLE_DRAWABLE_H

#include <iostream>
#include "Color.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Drawable {

protected:
	Color color;
	double x, y, z;

public:
	Drawable();
	explicit Drawable(Color c);
	Drawable(double x, double y, double z);
	Drawable(Color c, double x, double y, double z);

	double getX() {return x;}
	double getY() {return y;}
	double getZ() {return z;}
	Color getColor() {return color;}

	void setX(double x) {Drawable::x = x;}
	void setY(double y) {Drawable::y = y;}
	void setZ(double z) {Drawable::z = z;}
	void setColor(Color c) {color = c;}

	virtual void draw() = 0;
	virtual int getNumVertices() = 0;
	virtual void updateFrame() = 0;
};

#endif //POOL_TABLE_DRAWABLE_H
