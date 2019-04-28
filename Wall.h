//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_WALL_H
#define POOL_TABLE_WALL_H

#include "Collidable.h"
#include "Color.h"

class Wall : public Collidable {
private:
	int width;
	int height;
public:
	Wall();
	Wall(int z, int x, int y, Color c);
	Wall(int z, int x, int y, Color c, int width, int height);

	GLfloat *getVerticesArray() override;
	int getNumVertices() override;

	double getCenterX() override;

	double getCenterY() override;
};


#endif //POOL_TABLE_WALL_H
