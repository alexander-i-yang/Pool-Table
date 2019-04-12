//
// Created by samue on 2/27/2019.
//

#include <utility>
#include <string>
#include <cmath>
#include <iostream>

#include "Ball.h"
#include "Collidable.h"
#include "Drawable.h"

Ball::Ball() : Collidable() {

}

Ball::Ball(int radius) : radius(radius) {}

Ball::Ball(GLint x, GLint y, GLint z, GLint radius, Color c) : Collidable(c, x, y, z) {
    this->radius = radius;
}

int Ball::getRadius() const {
    return radius;
}

void Ball::setRadius(int radius) {
    Ball::radius = radius;
}

GLfloat *Ball::getVerticesArray() {
    int numberOfVertices = this->getNumVertices();
    int numberOfSides = this->getNumSides();
    auto twicePi = static_cast<GLfloat>(2.0f * M_PI);

    auto * allCircleVertices = new GLfloat[( numberOfVertices ) * 3];

    allCircleVertices[0] = static_cast<GLfloat>(getX());
    allCircleVertices[1] = static_cast<GLfloat>(getY());
    allCircleVertices[2] = static_cast<GLfloat>(getZ());

    for ( int i = 1; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 3] = static_cast<GLfloat>(Drawable::x+(this->radius*cos(i*twicePi/numberOfSides)));
        allCircleVertices[( i * 3 ) + 1] = static_cast<GLfloat>(Drawable::y+(this->radius*sin(i*twicePi/numberOfSides)));
        allCircleVertices[( i * 3 ) + 2] = static_cast<GLfloat>(Drawable::z);
    }

    return allCircleVertices;
}

int Ball::getNumVertices() {
    int numberOfSides = radius*3;
    int numberOfVertices = numberOfSides + 2;
    return numberOfVertices;
}

int Ball::getNumSides() {
    return radius*3;
}

bool Ball::checkCollide(Drawable* c) {
    Ball* collidable = dynamic_cast<Ball*>(c);
    //std::cout << sqrt(pow(collidable->getCenterX()-getCenterX(), 2) + pow(collidable->getCenterY()-getCenterY(), 2)) << " " << collidable->radius + radius << std::endl;
    return sqrt(pow(collidable->getCenterX()-getCenterX(), 2) + pow(collidable->getCenterY()-getCenterY(), 2)) <= collidable->radius + radius;
}