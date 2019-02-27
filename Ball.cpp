//
// Created by samue on 2/27/2019.
//

#include <utility>
#include <string>
#include <cmath>

Ball::Ball() : Collidable() {

}

Ball::Ball(int x, int y) : Collidable(x, y) {

}

std::string getString() {
    return this->tag;
}

std::pair<int, int> getVelocity() {
    return velocity;
}

int getSpeed() {
    return sqrt(pow(this->getVelocity().first, 2) + pow(this->getVelocity().second, 2));
}

#include "Ball.h"
