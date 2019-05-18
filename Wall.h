//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_WALL_H
#define POOL_TABLE_WALL_H

#include "Color.h"
#include "Drawable.h"

class Wall : public Drawable {
private:
	int width;
	int height;
public:
	int getWidth() const;

	void setWidth(int width);

	int getHeight() const;

	void setHeight(int height);

	Wall();
	Wall(int z, int x, int y, Color c);
	Wall(int z, int x, int y, Color c, int width, int height);

	int getNumVertices() override;
	void draw() override;

	void updateFrame(double friction) override;
};


#endif //POOL_TABLE_WALL_H
