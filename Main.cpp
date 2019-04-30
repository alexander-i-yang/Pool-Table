#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
#include <lib/common/shader.hpp>

#include "Ball.h"
//#include "Wall.h"
#include "Drawables.h"
#include "Collidables.h"

#include <iostream>
#include <vector>

#define PI 3.1415926538979323846

int main()
{
	GLFWwindow *window;

	// Initialize the library
	if ( !glfwInit( ) )
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	/*int windowWidth = mode->width;
	int windowHeight = mode->height;
	window = glfwCreateWindow(windowWidth, windowHeight, "The game", glfwGetPrimaryMonitor(), NULL);*/

	int windowWidth = 1024;
	int windowHeight = 768;
	window = glfwCreateWindow(windowWidth, windowHeight, "The Game", NULL, NULL);

	if ( !window )
	{
		glfwTerminate( );
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent( window );

	glViewport( 0.0f, 0.0f, windowWidth, windowHeight ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho( 0, windowWidth, 0, windowHeight, 0, 1 ); // essentially set coordinate system
	glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity( ); // same as above comment

	Drawables* drawables = new Drawables();
	Collidables* collidables = new Collidables();
	Color sunColor;
	srand((unsigned)time(0));
	srand(std::rand());
	//sunColor.setColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
	sunColor.setColor(0.8, 0.8, 0.8);
	Ball* s1 = new Ball(sunColor, windowWidth / 4, windowHeight / 2, 0, 15);
	s1->setVelocity(900, -10);
	s1->setMass(3000);
	drawables->add(s1);
	collidables->add(s1);

	int vertSpacing = 35;
	int horizontalSpacing = 27;
	for(int i = 0; i<4; ++i) {
		for(int j = 0; j<=i; ++j) {
			Ball* s2 = new Ball(sunColor, windowWidth * 3 / 4+horizontalSpacing*i, windowHeight / 2-(vertSpacing*j-vertSpacing/2*i), 0, 15);
			s2->setMass(1000);
			s2->setVelocity(0, 0);
			//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
			Color newColor(0, 0.8, 0.8);
			s2->setColor(newColor);
			drawables->add(s2);
			collidables->add(s2);
		}
	}


	/*for(int i = 0; i<10; ++i) {
		Wall* w = new Wall(0, windowWidth - 50, 80 * i, sunColor, 50, 50);
		w->setVelocity(-0.01*i, 0);
		drawables.add(w);
		Ball* sun = new Ball(0, 80*i, 0, 20, sunColor);
		sun->setVelocity(0.01*i, pow(-0.8, i));
		drawables.add(sun);
	}*/

	// Loop until the user closes the window
	double setTime = glfwGetTime();
	while( glfwGetTime() - setTime < 100 && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear( GL_COLOR_BUFFER_BIT );

		drawables->drawAll();
		collidables->updateAll();

		// Swap front and back buffers
		glfwSwapBuffers( window );

		// Poll for and process events
		glfwPollEvents( );
		//wait(0.1);
	}
	glfwTerminate();
	free(collidables);
	free(drawables);

	return 0;
}
