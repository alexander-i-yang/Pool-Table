#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <common/shader.hpp>

#include <iostream>

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides );
void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint r, GLint g, GLint b);

void drawRectangle( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
void drawRectangle( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLint r, GLint g, GLint b);

int main( void )
{
	GLFWwindow *window;

	// Initialize the library
	if ( !glfwInit( ) )
	{
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int windowWidth = mode->width;
	int windowHeight = mode->height;
	window = glfwCreateWindow(windowWidth, windowHeight, "The game", glfwGetPrimaryMonitor(), NULL);

	/*int windowWidth = 1024;
	int windowHeight = 768;
	window = glfwCreateWindow(windowWidth, windowHeight, "The Game", NULL, NULL);*/

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

	// Loop until the user closes the window
	double i = 0;
	double startTime = glfwGetTime();

	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ) {
		glClear( GL_COLOR_BUFFER_BIT );


		// render OpenGL here
		drawCircle( windowWidth/2, windowHeight/2, 0, 50, 40, 63, 0, 181);
		drawRectangle(static_cast<GLfloat>(10 * i - 0.5 * 0.05 * i * i), 20, 0, 50, 50);

		drawRectangle( static_cast<GLfloat>(windowWidth / 2-25 + 75 * sin(i / 50)),
		               static_cast<GLfloat>(windowHeight / 2-25 + 75 * cos(i / 50)), 0, 50, 50, 0, 150, 150);
		drawCircle( static_cast<GLfloat>(windowWidth / 2-25 + 150 * sin(i / 30+20)),
		            static_cast<GLfloat>(windowHeight / 2-25 + 150 * cos(i / 30+20)), 0, 30, 30, 255, 255, 0);
		drawCircle( static_cast<GLfloat>(windowWidth / 2-25 + 300 * sin(i / 40-10)),
		            static_cast<GLfloat>(windowHeight / 2-25 + 300 * cos(i / 40-10)), 0, 50, 40, 0, 0, 50);
		drawCircle( static_cast<GLfloat>(windowWidth / 2-25 + 225 * sin(i / 80-5)),
		            static_cast<GLfloat>(windowHeight / 2-25 + 225 * cos(i / 80-5)), 0, 10, 10, 255, 0, 255);
		drawCircle( static_cast<GLfloat>(windowWidth / 2-25 + 225 * sin(i / 80-5)),
		            static_cast<GLfloat>(windowHeight / 2-25 + 225 * cos(i / 80-5)), 0, 10, 10, 180, 0, 255);
		drawCircle( static_cast<GLfloat>(windowWidth / 2-25 + 500 * cos(i / 60-5)*cos(2.5)-400*sin(i / 60-5)*sin(2.5)),
		            static_cast<GLfloat>(windowHeight / 2-25 + 500 * cos(i / 60-5)*sin(2.5)+400*sin(i / 60-5)*cos(2.5)), 0, 10, 10, 255, 0, 180);

		// Swap front and back buffers
		glfwSwapBuffers( window );

		// Poll for and process events
		glfwPollEvents( );

		double curTime = glfwGetTime();

		// Compute time difference between current and last frame
		int deltaTime = static_cast<int>((curTime-startTime) * 1000)%10;
		if(deltaTime == 0) i+= 1;
	}

	glfwTerminate( );

	return 0;
}

void drawRectangle( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height) {
	drawRectangle(x, y, z, width, height, 255, 255, 255);
}

void drawRectangle( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLint r, GLint g, GLint b) {
	int numberOfVertices = 4;
	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	for ( int i = 0; i < numberOfVertices; i++ )
	{
		float a = i%3==0?0:width;
		float b = (i-1>0?height:0);
		circleVerticesX[i] = x + a;
		circleVerticesY[i] = y + b;
		circleVerticesZ[i] = z;
	}

	GLfloat vertices[numberOfVertices*3];
	GLfloat color[numberOfVertices*3];

	for ( int i = 0; i < numberOfVertices; i++ )
	{
		vertices[i * 3] = circleVerticesX[i];
		vertices[( i * 3 ) + 1] = circleVerticesY[i];
		vertices[( i * 3 ) + 2] = circleVerticesZ[i];
		color[i*3] = r;
		color[i*3+1] = g;
		color[i*3+2] = b;
	}

	glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
	glEnableClientState( GL_COLOR_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, vertices); // point to the vertices to be used
	glColorPointer( 3, GL_INT, 0, color);
	glDrawArrays( GL_QUADS, 0, numberOfVertices); // draw the vertixes
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex array attribute
}

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides ) {
	drawCircle(x, y, z, radius, numberOfSides, 255, 255, 255);
}

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint r, GLint g, GLint b)
{
	int numberOfVertices = numberOfSides + 2;

	GLfloat twicePi = 2.0f * M_PI;

	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for ( int i = 1; i < numberOfVertices; i++ )
	{
		circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
		circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
		circleVerticesZ[i] = z;
	}

	GLfloat allCircleVertices[( numberOfVertices ) * 3];
	GLfloat color[numberOfVertices*3];

	for ( int i = 0; i < numberOfVertices; i++ )
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
		allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
		color[i*3] = r;
		color[i*3+1] = g;
		color[i*3+2] = b;
	}

	glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
	glEnableClientState( GL_COLOR_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices); // point to the vertices to be used
	glColorPointer( 3, GL_INT, 0, color);
	glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices); // draw the vertixes
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex array attribute
}