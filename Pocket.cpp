//
// Created by Max on 5/1/2019.
//

#include "Pocket.h"
#include <utility>
#include <string>
#include <cmath>
#include <iostream>
#include "Drawable.h"
#include "Color.h"

Pocket::Pocket() : Drawable() {

}
Pocket::Pocket(Color c, double radius, double x, double y, double z):Drawable(c, x, y, z){
    this->radius = radius;
}
void Pocket::draw(){
    double r = this->getRadius();
    double x = this->getX();
    double y = this->getY();
    double triangleAmount = this->getNumVertices();
    glColor3f(this->getColor().getR(), this->getColor().getG(), this->getColor().getB());
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; ++i) {
        glVertex2f(x + r * cos(i * 2 * 3.1415926 / triangleAmount), y + r * sin(i * 2 * 3.1415926 / triangleAmount));
    }
    glEnd();
}
void Pocket::setRadius(double radius){
    this->radius = radius;
}
double Pocket::getRadius(){
    return this->radius;
}
int Pocket::getNumVertices() {
    int numberOfSides = (int)(this->getRadius());
    int numberOfVertices = numberOfSides + 2;
    return numberOfVertices;
}
void Pocket::updateFrame(double) {
    return;
}
