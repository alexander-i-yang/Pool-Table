//
// Created by Alex on 3/27/2019.
//

#ifndef POOL_TABLE_DRAWABLE_H
#define POOL_TABLE_DRAWABLE_H

#include <iostream>
#include "Color.h"

class Drawable {
protected:
	Color color;
	double x, y, z;
	double timeLastIncrX;
	double timeLastIncrY;
public:
	double getTimeSinceLastIncrX() const;
	void setTimeSinceLastIncrX(double timeSinceLastIncrX);
	double getTimeSinceLastIncrY() const;
	void setTimeSinceLastIncrY(double timeSinceLastIncrY);

	Drawable();
	Drawable(Color c);
	Drawable(double  x, double y, double z);
	Drawable(Color c, double x, double y, double z);

	double getX() {return x;}
	double getY() {return y;}
	double getZ() {return z;}
	Color getColor() {return color;}

	void setX(double x) {Drawable::x = x;}
	void setY(double y) {Drawable::y = y;}
	void setZ(double z) {Drawable::z = z;}
	void setColor(Color c) {color = c;}

	void incrX(double incr) {x+=incr;}
	void incrY(double incr) {y+=incr;}

	virtual double getCenterX() {return x;}
	virtual double getCenterY() {return y;}

	virtual bool checkCollide(Drawable*) {return NULL;}

	virtual std::pair<double, double> getVelocityCollision(Drawable *) {std::cout << "Returning bad" << std::endl;}

	virtual void draw();
	virtual GLfloat* getVerticesArray() {return nullptr;}
	virtual int getNumVertices() {return 0;}
	GLfloat* getColorArray();
	virtual void updateFrame() {}
};

#endif //POOL_TABLE_DRAWABLE_H
