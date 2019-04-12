//
// Created by Alex on 3/27/2019.
//

#ifndef POOL_TABLE_DRAWABLES_H
#define POOL_TABLE_DRAWABLES_H

#include <vector>

#include "Drawable.h"

class Drawables {
private:
	std::vector<Drawable*> objects;
public:
	Drawables();
	~Drawables();
	void drawAll();
	void updateAll();
	void add(Drawable*);
	void clear();
	Drawable* get(int i);
};


#endif //POOL_TABLE_DRAWABLES_H
