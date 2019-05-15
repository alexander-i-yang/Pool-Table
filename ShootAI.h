//
// Created by Alex on 5/7/2019.
//

#ifndef POOL_TABLE_SHOOTAI_H
#define POOL_TABLE_SHOOTAI_H

#include "Ball.h"
#include <utility>

class ShootAI {
public:
	ShootAI() = default;
	static std::pair<double, double> shootWhiteBall(Ball* whiteBall, Ball* shoot, double targetX, double targetY);
	static bool predictCollide(Ball* whiteBall, Ball* other, double xv, double yv, double stopX);
};

#endif //POOL_TABLE_SHOOTAI_H
