//
// Created by Max on 5/1/2019.
//

#ifndef POOL_TABLE_POCKET_H
#define POOL_TABLE_POCKET_H
#include <utility>
#include <string>

#include "Drawable.h"

class Pocket: public Drawable {
protected:
    double radius;
public:
    Pocket();
    Pocket(Color c, double radius, double x, double y, double z);
    void setRadius(double radius);
    double getRadius();
    void draw() override;
    int getNumVertices() override;
    void updateFrame(double friction) override;
};


#endif //POOL_TABLE_POCKET_H