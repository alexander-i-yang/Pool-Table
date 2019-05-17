//
// Created by Alex on 3/27/2019.
//

#include "Color.h"

Color::Color(GLfloat rFloat, GLfloat gFloat, GLfloat bFloat) {
    setColor(rFloat, gFloat, bFloat);
}

void Color::setColor(GLfloat rFloat, GLfloat gFloat, GLfloat bFloat) {
    if(rFloat > 1 || gFloat > 1 || bFloat > 1) {
        rFloat /= 255;
        gFloat /= 255;
        bFloat /= 255;
    }
    r = rFloat;
    g = gFloat;
    b = bFloat;
}

GLfloat Color::getR() {return r;}
GLfloat Color::getG() {return g;}
GLfloat Color::getB() {return b;}

GLint Color::getIntR() {return static_cast<GLint>(r)*255;}
GLint Color::getIntG() {return static_cast<GLint>(g)*255;}
GLint Color::getIntB() {return static_cast<GLint>(b)*255;}
