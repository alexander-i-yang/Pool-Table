//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_BALL_H
#define POOL_TABLE_BALL_H

#include <utility>
#include <string>

class Ball : Collidable {
private:
    std::string tag = "BALL";
    std::pair<int, int> velocity;
public:
    Ball();
    Ball(int x, int y);
    std::string getTag();
    std::pair<int, int> getVelocity();
    int getSpeed();
};


#endif //POOL_TABLE_BALL_H
