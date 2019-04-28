//
// Created by Samuel on 4/27/2019.
//

#ifndef POOL_TABLE_COLLIDABLES_H
#define POOL_TABLE_COLLIDABLES_H

#include <vector>
#include "Ball.h"

class Collidables {

private:
	std::vector<Ball*> objects;

public:
	Collidables();
	~Collidables();
	void add(Ball* ball);
	void clear();
	void updateAll(); // will this update the Ball in Drawables as well?
	                  // it should, but this will pose problems if it doesn't
	                  // lol nvm we good
};


#endif //POOL_TABLE_COLLIDABLES_H
