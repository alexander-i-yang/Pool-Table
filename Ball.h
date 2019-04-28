//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_BALL_H
#define POOL_TABLE_BALL_H

#include <utility>
#include <string>

#include "Drawable.h"

class Ball : public Drawable {

private:
	double referenceTime;

protected:
    double radius;
    std::pair<double, double> velocity;
    double theta;
    double mass;

public:
    Ball();
    Ball(Color c, double x, double y, double z, double radius);
    Ball(Color c, double x, double y, double z, double radius, std::pair<double, double> velocity, double theta, double mass);

    double getTime();
	double getRadius();
	double getTheta();
	double getMass();
	double getXVelocity();
	double getYVelocity();
	double getSpeed();

	void setTime(double time);
	void setRadius(double radius);
	void setTheta(double theta);
	void setMass(double mass);
	void setVelocity(double vx, double vy);
	void updateAngle();

	/* for drawing */
	int getNumSides();
	void draw() override;
	double *getVerticesArray() override;
	int getNumVertices() override;
	void updateFrame() override; /* this is how the ball will 'move' */
	double* getColorArray() override;

	/* for mechanics */
	double friction(); /* returns the frictional force */
	bool checkCollide(Ball* other); /* consider moving this function to Collidables */
	std::pair<double, double> getNewVelocity(Ball* other);
	double getNewAngle(Ball* other);

	/* utility */
	double perpendicularDistance(Ball* other); /* consider creating a utility class */
};


#endif //POOL_TABLE_BALL_H
