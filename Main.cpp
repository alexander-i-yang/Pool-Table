#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <lib/common/shader.hpp>

#include "Ball.h"
#include "Wall.h"
#include "Drawables.h"
#include "Collidables.h"

#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>

#define FULLSCREEN true

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        void *data = glfwGetWindowUserPointer(window);
        Ball *w = static_cast<Ball *>(data);
        if (!(w->getYVelocity() > 0.1 || w->getXVelocity() > 0.1)) {
            if (w->getTurnStatus()) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                xpos = xpos * 2;
                ypos = (mode->height - ypos) * 2;
                w->setVelocity(-(xpos - w->getX()) * 4, -(ypos - w->getY()) * 4);
                w->setShotStatus(false);
//                if (w->getOption() == 1) {
//                    int n = write(w->getFd(),"YOUR TURN",9);
//                    if (n < 0) error("ERROR writing to socket");
//                } else if (w->getOption() == 2) {
//                    int n = write(w->getFd(),"YOUR TURN",9);
//                    if (n < 0) error("ERROR writing to socket");
//                }
            } else {

            }
        }
    }
}

int main()
{
    std::cout << "Select an option" << std::endl;
    std::cout << "1. Host" << std::endl;
    std::cout << "2. Join" << std::endl;

    int option;
    std::cin >> option;
    //Yashs-MacBook-Pro.local

    //Server Variables
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    //Client Variables
    int CLIENTsockfd, CLIENTportno, CLIENTn;
    struct sockaddr_in CLIENTserv_addr;
    struct hostent *server;
    char CLIENTbuffer[256];

    if (option == 1) {
        //GET INPUT
        std::cout << "Specify a port number." << std::endl;
        int serverPortNumber;
        std::cin >> serverPortNumber;

        std::cout << "Created game at port " << serverPortNumber << std::endl;

        //SETUP ACTUAL SERVER
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = serverPortNumber;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0)
            error("ERROR on binding");
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,
                           (struct sockaddr *) &cli_addr,
                           &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
    } else if (option == 2) {
        //GET INPUT
        std::cout << "Port number to join." << std::endl;
        int clientPortNumber;
        std::cin >> clientPortNumber;

        std::cout << "Hostname to join." << std::endl;
        char clientHostname[30];
        std::cin >> clientHostname;

        std::cout << "Joining " << clientHostname << " at port " << clientPortNumber << std::endl;

        //SETUP ACTUAL CLIENT
        CLIENTportno = clientPortNumber;
        server = gethostbyname(clientHostname);
        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &CLIENTserv_addr, sizeof(CLIENTserv_addr));
        CLIENTserv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr,
              (char *) &CLIENTserv_addr.sin_addr.s_addr,
              server->h_length);
        CLIENTserv_addr.sin_port = htons(CLIENTportno);

        CLIENTsockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (CLIENTsockfd < 0)
            error("ERROR opening socket");
        if (connect(CLIENTsockfd, (struct sockaddr *) &CLIENTserv_addr, sizeof(CLIENTserv_addr)) < 0)
            error("ERROR connecting");
    }

    GLFWwindow *window;
    // Initialize the library
    if ( !glfwInit( ) ){
        std::cout << "Init failed" << std::endl;
        return -1;
    }
    int windowWidth = 1024;
    int windowHeight = 768;
    if(!FULLSCREEN) {
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
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glClearColor(9.0/255, 96.0/255, 89.0/255, 1);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
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
    double pocketHeight = radius*1.75;  //In modern pool tables pockets are 1.75-2.25 x larger than the diameter of the balls
    Color pocketColor;
    pocketColor.setColor(0, 0, 0);
    Pocket * topRight = new Pocket(pocketColor, pocketHeight, windowWidth-pocketHeight*1.9, windowHeight-pocketHeight*1.9, 0);
    Pocket * middleTop = new Pocket(pocketColor, pocketHeight, (windowWidth-pocketHeight*1.9)/2, windowHeight-pocketHeight*1.9, 0);
    Pocket * topLeft = new Pocket(pocketColor, pocketHeight, 0+pocketHeight*1.9, windowHeight-pocketHeight*1.9, 0);
    Pocket * bottomLeft = new Pocket(pocketColor, pocketHeight, 0+pocketHeight*1.9, 0+pocketHeight*1.9, 0);
    Pocket * middleBottom = new Pocket(pocketColor, pocketHeight, (windowWidth-pocketHeight*1.9)/2, 0+pocketHeight*1.9, 0);
    Pocket * bottomRight = new Pocket(pocketColor, pocketHeight, windowWidth-pocketHeight*1.9, 0+pocketHeight*1.9, 0);
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
    Ball* s1 = new Ball(sunColor, windowWidth / 4, windowHeight / 2, 0, radius);
    s1->setMass(1000);
    drawables->add(s1);
    collidables->add(s1);

    if (option == 1) {
        s1->setFd(newsockfd);
        s1->setShotStatus(true);
    } else if (option == 2) {
        s1->setFd(CLIENTsockfd);
        s1->setShotStatus(false);
    }

    bool myTurn;
    if (option == 1) {
        myTurn = true;
    } else {
        myTurn = false;
    }
    s1->setTurnStatus(myTurn);
    s1->setOption(option);

    glfwSetWindowUserPointer(window, s1);

    Ball* balls[16];

    int index = 0;
    int counter = 0;
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
            balls[counter] = s2;
            counter++;
        }
    }

    //add cue ball
    balls[15] = s1;

    collidables->setFriction(0.998);

    bool slowed = false;

    // Loop until the user closes the window
    double setTime = glfwGetTime();
    while( /*glfwGetTime() - setTime < 10 && */glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glClear( GL_COLOR_BUFFER_BIT );

        //server read
        if (option == 1) {
            double recievedCoords[32];
            int ballIncrementer = 0;

            int count;
            ioctl(newsockfd, FIONREAD, &count);

            if (count != 0) {
                n = read(newsockfd, &recievedCoords, sizeof(recievedCoords));
                s1->setTurnStatus(true);
                s1->setShotStatus(true);
                if (n < 0) error("ERROR reading from socket");
                for (int i = 0; i < 32; i+=2) {
                    balls[ballIncrementer]->setX(recievedCoords[i]);
                    balls[ballIncrementer]->setY(recievedCoords[i+1]);
                    ballIncrementer++;
                }
            }
        } else if (option == 2) {
            double recievedCoords[32];
            int ballIncrementer = 0;

            int count;
            ioctl(CLIENTsockfd, FIONREAD, &count);

            if (count != 0) {
                n = read(CLIENTsockfd, &recievedCoords, sizeof(recievedCoords));
                s1->setTurnStatus(true);
                s1->setShotStatus(true);
                if (n < 0) error("ERROR reading from socket");
                for (int i = 0; i < 32; i+=2) {
                    balls[ballIncrementer]->setX(recievedCoords[i]);
                    balls[ballIncrementer]->setY(recievedCoords[i+1]);
                    ballIncrementer++;
                }
            }
        }

        double xpos, ypos;
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwGetCursorPos( window, &xpos, &ypos );
        xpos = xpos * 2;
        ypos = (mode->height-ypos)*2;

        if (!(abs(s1->getYVelocity()) > 0.1 || abs(s1->getXVelocity()) > 0.1)) {
            if (!s1->getShotStatus() && s1->getTurnStatus()) {

                double coords[32];
                int incrementer = 0;
                for (int i = 0; i < 16; i++) {
                    coords[incrementer] = balls[i]->getX();
                    coords[incrementer+1] = balls[i]->getY();
                    incrementer += 2;
                }


                if (s1->getOption() == 1) {
                    int n = write(s1->getFd(), coords, sizeof(coords));
                    if (n < 0) error("ERROR writing to socket");
                    s1->setTurnStatus(false);
                } else if (s1->getOption() == 2) {
                    int n = write(s1->getFd(), coords, sizeof(coords));
                    if (n < 0) error("ERROR writing to socket");
                    s1->setTurnStatus(false);
                }
            }

            if (s1->getTurnStatus()) {
                GLfloat lineVertices[] =
                        {
                                static_cast<GLfloat>(xpos), static_cast<GLfloat>(ypos), 0,
                                static_cast<GLfloat>(s1->getX()), static_cast<GLfloat>(s1->getY()), 0
                        };

                glEnable( GL_LINE_SMOOTH );
                glEnable( GL_LINE_STIPPLE );
                glPushAttrib( GL_LINE_BIT );
                glLineWidth( 10 );
                glLineStipple( 1, 0x00FF );
                glEnableClientState( GL_VERTEX_ARRAY );
                glVertexPointer( 3, GL_FLOAT, 0, lineVertices );
                glDrawArrays( GL_LINES, 0, 2 );
                glDisableClientState( GL_VERTEX_ARRAY );
                glPopAttrib( );
                glDisable( GL_LINE_STIPPLE );
                glDisable( GL_LINE_SMOOTH );
            }
        }

        collidables->updateAll(drawables);
        drawables->drawAll();

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
