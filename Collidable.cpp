//
// Created by samue on 2/27/2019.
//

Collidable::Collidable() {
    this->x = 0;
    this->y = 0;
}

Collidable::Collidable(int x, int y) {
    this->x = x;
    this->y = y;
}

int Collidable::getX() {
    return x;
}

int Collidable::getY() {
    return y;
}

#include "Collidable.h"
