//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_BALL_H
#define POOL_TABLE_BALL_H

#include <utility>
#include <string>

#include "Collidable.h"
#include "Drawable.h"

class Ball : public Collidable {
private:
    std::string tag = "BALL";
    int radius;
public:
    Ball();
    Ball(GLint x, GLint y, GLint z, GLint radius, Color c);
	Ball(int radius);

	std::string getTag() {return tag;}
	int getRadius() const;
	void setRadius(int radius);

	void setTag(std::string tag) {this->tag = tag;}

	bool checkCollide(Drawable* collidable) override;

	int getNumSides();
	GLfloat *getVerticesArray() override;
	int getNumVertices() override;
};


#endif //POOL_TABLE_BALL_H
