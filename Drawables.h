//
// Created by Alex on 3/27/2019.
//

#ifndef POOL_TABLE_DRAWABLES_H
#define POOL_TABLE_DRAWABLES_H

#include <vector>

#include "Drawable.h"

class Drawables {
public:
	std::vector<Drawable*> objects;
	Drawables();
	~Drawables();
	void drawAll();
	void add(Drawable*);
	void clear();
	Drawable* get(int i);
};


#endif //POOL_TABLE_DRAWABLES_H
