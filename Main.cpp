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

	double friction = 0.1;

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

	int radius = windowHeight/40;
	std::cout << radius << std::endl;
	int vertSpacing = static_cast<int>(60.0 / 27.0 * radius);
	int horizontalSpacing = static_cast<int>(55.0 / 27.0 * radius);

	Drawables* drawables = new Drawables();
	Collidables* collidables = new Collidables();
	Color sunColor;
	srand((unsigned)time(0));
	srand(std::rand());
	//sunColor.setColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
	sunColor.setColor(0.8, 0.8, 0.8);
	Ball* s1 = new Ball(sunColor, windowWidth / 4, windowHeight / 2, 0, radius);
	s1->setVelocity(900, -10);
	s1->setMass(3000);
	drawables->add(s1);
	collidables->add(s1);

	for(int i = 0; i<4; ++i) {
		for(int j = 0; j<=i; ++j) {
			Ball* s2 = new Ball(sunColor, windowWidth * 3 / 4+horizontalSpacing*i, windowHeight / 2-(vertSpacing*j-vertSpacing/2*i), 0, radius);
			s2->setMass(1000);
			s2->setVelocity(0, 0);
			//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
			Color newColor(0, 0.8, 0.8);
			s2->setColor(newColor);
			drawables->add(s2);
			collidables->add(s2);
		}
	}

	Wall* right = new Wall(0, windowWidth-20, 0, sunColor, 20, windowHeight);
	Wall* left = new Wall(0, 0, 0, sunColor, 20, windowHeight);
	Wall* top = new Wall(0, 20, 0, sunColor, windowWidth-40, 20);
	Wall* bottom = new Wall(0, 20, windowHeight-20, sunColor, windowWidth-40, 20);
	drawables->add(right);
	collidables->add(right);
	drawables->add(left);
	collidables->add(left);
	drawables->add(top);
	collidables->add(top);
	drawables->add(bottom);
	collidables->add(bottom);

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
		//wait(0.1);
	}
	glfwTerminate();
	free(collidables);
	free(drawables);

	return 0;
}
