//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_COLLIDABLE_H
#define POOL_TABLE_COLLIDABLE_H


class Collidable {
private:
    int x, y;
public:
    Collidable();
    Collidable(int x, int y);
    int getX();
    int getY();
};


#endif //POOL_TABLE_COLLIDABLE_H
