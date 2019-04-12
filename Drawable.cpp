//
// Created by Alex on 3/27/2019.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Drawable.h"

Drawable::Drawable(Color c, double x, double y, double z) {
	setColor(c);
	setX(x);
	setY(y);
	setZ(z);
	timeLastIncrX = 0;
	timeLastIncrY = 0;
}

Drawable::Drawable(double x, double y, double z) {
	Color c = {};
	Drawable(c, x, y, z);
}

Drawable::Drawable(Color c) {
	Drawable(c, 0, 0, 0);
}

Drawable::Drawable() {
	Color c = {};
	Drawable(c, 0, 0, 0);
}

double Drawable::getTimeSinceLastIncrX() const {
	return timeLastIncrX;
}

void Drawable::setTimeSinceLastIncrX(double timeSinceLastIncrX) {
	Drawable::timeLastIncrX = timeSinceLastIncrX;
}

double Drawable::getTimeSinceLastIncrY() const {
	return timeLastIncrY;
}

void Drawable::setTimeSinceLastIncrY(double timeSinceLastIncrY) {
	Drawable::timeLastIncrY = timeSinceLastIncrY;
}

void Drawable::draw() {
	glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
	glEnableClientState( GL_COLOR_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, getVerticesArray()); // point to the vertices to be used
	glColorPointer(3, GL_FLOAT, 0, getColorArray());
	glDrawArrays( GL_TRIANGLE_FAN, 0, getNumVertices()); // draw the vertixes
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex array attribute
}

GLfloat *Drawable::getColorArray() {
	int numberOfVertices = getNumVertices();
	auto * color = new GLfloat[numberOfVertices*3];

	for ( int i = 0; i < numberOfVertices; i++ ) {
		color[i*3] = Drawable::color.getR();
		color[i*3+1] = Drawable::color.getG();
		color[i*3+2] = Drawable::color.getB();
	}
	return color;
}
