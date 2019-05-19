#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
#include <lib/common/shader.hpp>

#include "Ball.h"
#include "Wall.h"
#include "Drawables.h"
#include "Collidables.h"
#include "Pocket.h"
#include "ShootAI.h"

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
            176, 48, 96

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

	//Adding pockets
	double pocketHeight = radius*2.25/1.5;  //In modern pool tables pockets are 1.75-2.25 x larger than the diameter of the balls
	Color pocketColor;
	pocketColor.setColor(40, 45, 45);
	Pocket * topRight = new Pocket(pocketColor, pocketHeight, 0, windowWidth-pocketHeight*1.9, windowHeight-pocketHeight*1.9, 0);
	Pocket * middleTop = new Pocket(pocketColor, pocketHeight, 4, (windowWidth-pocketHeight*1.9)/2+pocketHeight, (windowHeight-pocketHeight*1.9)*(10/10), 0);
	Pocket * topLeft = new Pocket(pocketColor, pocketHeight, 1, 0+pocketHeight*1.9, windowHeight-pocketHeight*1.9, 0);
	Pocket * bottomLeft = new Pocket(pocketColor, pocketHeight, 2, 0+pocketHeight*1.9, 0+pocketHeight*2, 0);
	Pocket * middleBottom = new Pocket(pocketColor, pocketHeight, 5, (windowWidth-pocketHeight*1.9)/2+pocketHeight, (0+pocketHeight*1.9)*(10/10), 0);
	Pocket * bottomRight = new Pocket(pocketColor, pocketHeight, 3, windowWidth-pocketHeight*1.9, 0+pocketHeight*1.9, 0);
	drawables->add(topRight);
	drawables->add(middleTop);
	drawables->add(topLeft);
	drawables->add(bottomLeft);
	drawables->add(middleBottom);
	drawables->add(bottomRight);
	collidables->add(topRight);
	collidables->add(middleTop);
	collidables->add(topLeft);
	collidables->add(bottomLeft);
	collidables->add(middleBottom);
	collidables->add(bottomRight);

	Color sunColor;
	srand((unsigned)time(0));
	srand(std::rand());
	sunColor.setColor(1, 1, 1);
	Ball* whiteBall = new Ball(sunColor, windowWidth / 4, windowHeight / 2, 0, radius, 0, windowWidth, windowHeight);
	whiteBall->setMass(1000);
	drawables->add(whiteBall);
	collidables->add(whiteBall);

	int index = 0;
	bool stripes = true;
	/*Ball* s2 = new Ball(sunColor, windowWidth*1/4-50, windowHeight/2+50, 0, radius);
	s2->setMass(1000);
	s2->setVelocity(0, 0);
	//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
	Color newColor(static_cast<GLfloat>(rgbs[index] / 255.0), static_cast<GLfloat>(rgbs[index + 1] / 255.0),
	               static_cast<GLfloat>(rgbs[index + 2] / 255.0));
	index+=3;
	s2->setColor(newColor);
	s2->setStriped(stripes);
	drawables->add(s2);
	collidables->add(s2);

	Ball* s3 = new Ball(sunColor, windowWidth*1/4-80, windowHeight/2+150, 0, radius);
	s3->setMass(1000);
	s3->setVelocity(0, 0);
	//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
	Color newerColor(static_cast<GLfloat>(rgbs[index] / 255.0), static_cast<GLfloat>(rgbs[index + 1] / 255.0),
	               static_cast<GLfloat>(rgbs[index + 2] / 255.0));
	index+=3;
	s3->setColor(newerColor);
	s3->setStriped(stripes);
	drawables->add(s3);
	collidables->add(s3);*/
	int number = 1;
	for(int i = 0; i<5; ++i) {
		for(int j = 0; j<=i; ++j) {
			Ball* s2 = new Ball(sunColor, windowWidth*3/4 +horizontalSpacing*i, windowHeight / 2-(vertSpacing*j-vertSpacing/2*i), 0, radius, number, windowWidth, windowHeight);
			s2->setMass(1000);
			s2->setVelocity(0, 0);
			//Color newColor((double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0, (double)(std::rand()%255)/255.0);
            Color newColor(static_cast<GLfloat>(rgbs[index] / 255.0), static_cast<GLfloat>(rgbs[index + 1] / 255.0),
                           static_cast<GLfloat>(rgbs[index + 2] / 255.0));
			if(number==8){
                Color newColor(static_cast<GLfloat>(0), static_cast<GLfloat>(0),
                               static_cast<GLfloat>(0));
			}

			index+=3;

			if(index >= 24) {index = 0; stripes = false;}
			s2->setColor(newColor);
			//s2->setStriped(j%2);
			s2->setStriped(stripes);
			drawables->add(s2);
			collidables->add(s2);
			number++;
		}
	}

	collidables->setFriction(0.75);

	/*std::pair<double, double> v = ShootAI::shootWhiteBall(whiteBall, s3, topLeft->getX(), topLeft->getY());
	if(!ShootAI::predictCollide(whiteBall, s2, v.first, v.second, s3->getX())) {
		whiteBall->setVelocity(v.first/10, v.second/10);
	} else {
		std::cerr << "ERROR!" << std::endl;
		whiteBall->setVelocity(v.first, v.second);
	}*/


	// Loop until the user closes the window
	double setTime = glfwGetTime();
	while( /*glfwGetTime() - setTime < 10 && */glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glClear( GL_COLOR_BUFFER_BIT );

		collidables->updateAll(drawables);
		drawables->drawAll();

		// Swap front and back buffers
		glfwSwapBuffers( window );

		// Poll for and process events
		glfwPollEvents( );

		if(collidables->checkNotMoving(1)) {
			collidables->shootAI();
		}
		//wait(0.1);
	}
	glfwTerminate();
	free(collidables);
	free(drawables);

	return 0;
}