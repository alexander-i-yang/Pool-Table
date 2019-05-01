#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
#include <lib/common/shader.hpp>

#include "Ball.h"
#include "Wall.h"
#include "Drawables.h"
#include "Collidables.h"

#include <iostream>
#include <vector>

#define FULLSCREEN true

int main()
{
	GLFWwindow *window;
	// Initialize the library
	if ( !glfwInit( ) ){
		std::cout << "Init failed" << std::endl;
		return -1;
	}
	int windowWidth = 1024;
	int windowHeight = 768;
	if(FULLSCREEN) {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		windowWidth = mode->width;
		windowHeight = mode->height;
		window = glfwCreateWindow(windowWidth, windowHeight, "The game", glfwGetPrimaryMonitor(), NULL);
	} else {
		window = glfwCreateWindow(windowWidth, windowHeight, "The Game", NULL, NULL);
	}
	if ( !window ) {
		glfwTerminate( );
		std::cout << "Window failed" << std::endl;
		return -1;
	}

	double rgbs[] = {
		242, 227, 60,
		73, 147, 244,
		237, 18, 58,
		139, 35, 224,
		242, 163, 16,
		27, 214, 34,
		0, 0, 0
	};

	// Make the window's context current
	glfwMakeContextCurrent( window );

	glClearColor(9.0/255, 96.0/255, 89.0/255, 1);

	glViewport( 0.0f, 0.0f, windowWidth, windowHeight ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho( 0, windowWidth, 0, windowHeight, 0, 1 ); // essentially set coordinate system
	glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity( ); // same as above comment

	int radius = windowHeight/40+1;
	int vertSpacing = static_cast<int>(60.0 / 27.0 * radius);
	int horizontalSpacing = static_cast<int>(55.0 / 27.0 * radius);

	Drawables* drawables = new Drawables();
	Collidables* collidables = new Collidables();
	Color sunColor;
	srand((unsigned)time(0));
	srand(std::rand());
	sunColor.setColor(1, 1, 1);
	Ball* s1 = new Ball(sunColor, windowWidth / 4, windowHeight / 2, 0, radius);
	s1->setVelocity(windowHeight*4, windowHeight/40);
	s1->setMass(1000);
	drawables->add(s1);
	collidables->add(s1);

	int index = 0;
	bool stripes = false;
	for(int i = 0; i<5; ++i) {
		for(int j = 0; j<=i; ++j) {
			Ball* s2 = new Ball(sunColor, windowWidth*3/4 +horizontalSpacing*i, windowHeight / 2-(vertSpacing*j-vertSpacing/2*i), 0, radius);
			s2->setMass(1000);
			s2->setVelocity(0, 0);
			//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
			Color newColor(static_cast<GLfloat>(rgbs[index] / 255.0), static_cast<GLfloat>(rgbs[index + 1] / 255.0),
			               static_cast<GLfloat>(rgbs[index + 2] / 255.0));
			index+=3;
			if(index >= 24) {index = 0; stripes = true;}
			s2->setColor(newColor);
			//s2->setStriped(j%2);
			s2->setStriped(stripes);
			drawables->add(s2);
			collidables->add(s2);
		}
	}

	Color wallColor;
	int wallThickness = windowWidth/1024.0*40.0;
	wallColor.setColor(150.0/255, 104.0/255, 31.0/255);
	Wall* right = new Wall(0, windowWidth-wallThickness, 0, wallColor, wallThickness, windowHeight);
	Wall* left = new Wall(0, 0, 0, wallColor, wallThickness, windowHeight);
	Wall* top = new Wall(0, wallThickness, 0, wallColor, windowWidth-wallThickness*2, wallThickness);
	Wall* bottom = new Wall(0, wallThickness, windowHeight-wallThickness, wallColor, windowWidth-wallThickness*2, wallThickness);
	drawables->add(right);
	collidables->add(right);
	drawables->add(left);
	collidables->add(left);
	drawables->add(top);
	collidables->add(top);
	drawables->add(bottom);
	collidables->add(bottom);

	collidables->setFriction(0.99925);


	bool slowed = false;
	// Loop until the user closes the window
	double setTime = glfwGetTime();
	while( /*glfwGetTime() - setTime < 10 && */glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear( GL_COLOR_BUFFER_BIT );

		drawables->drawAll();
		collidables->updateAll();

		// Swap front and back buffers
		glfwSwapBuffers( window );

		// Poll for and process events
		glfwPollEvents( );

		if(!slowed && collidables->checkNotMoving(30)) {
			collidables->slowAll();
			collidables->slowAll();
			collidables->slowAll();
			slowed = true;
		}
		//wait(0.1);
	}
	glfwTerminate();
	free(collidables);
	free(drawables);

	return 0;
}
