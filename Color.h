//
// Created by Alex on 3/27/2019.
//

#ifndef POOL_TABLE_COLOR_H
#define POOL_TABLE_COLOR_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Color {
private:
	GLfloat r;
	GLfloat g;
	GLfloat b;
public:
	Color() : r(0), g(0), b(0) {}
	Color(GLfloat, GLfloat, GLfloat);

	void setColor(GLfloat, GLfloat, GLfloat);
	GLfloat getR();
	GLfloat getG();
	GLfloat getB();

	GLint getIntR();
	GLint getIntG();
	GLint getIntB();
};


#endif //POOL_TABLE_COLOR_H
