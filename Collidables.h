//
// Created by Samuel on 4/27/2019.
//

#ifndef POOL_TABLE_COLLIDABLES_H
#define POOL_TABLE_COLLIDABLES_H


#include <vector>
#include "Ball.h"
#include "Drawables.h"
#include "Wall.h"
#include "Pocket.h"


class Collidables {

private:
	std::vector<Ball*> objects;
	std::vector<Wall*> walls;
	std::vector<Pocket*> pockets;
	double friction;
public:
	void setFriction(double friction);
	Collidables();
	~Collidables();
	void add(Ball* ball);
	void add(Wall* wall);
	void add(Pocket * pocket);
	void clear();
	bool checkNotMoving(double threshold);
	void stopAll();
	void slowAll();
	void updateAll(Drawables * drawables); // will this update the Ball in Drawables as well?
	// it should, but this will pose problems if it doesn't
	// lol nvm we good
};

#endif //POOL_TABLE_COLLIDABLES_H
