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
	bool striped;
	int number;
	double windowWidth;
	double windowHeight;
public:
    Ball();
    Ball(Color c, double x, double y, double z, double radius, int number, double windowWidth, double windowHeight);
    Ball(Color c, double x, double y, double z, double radius, std::pair<double, double> velocity, double theta, double mass);

    double getTime();

	bool isStriped() const;

	void setStriped(bool striped);

	void setNumber(int n);
	int getNumber();

	void setWindowWidth(double width);
	double getWindowWidth();

	void setWindowHeight(double height);
	double getWindowHeight();

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
	void setXVelocity(double vx);
	void setYVelocity(double vy);
	void updateAngle();
	void setPos(double x, double y);
	void setColorRGB(double r, double g, double b);
	void flipXV() {velocity.first *= -1;}
	void flipYV() {velocity.second *= -1;}

	/* for drawing */
	int getNumSides();
	void draw() override;
	int getNumVertices() override;
	void updateFrame(double friction) override; /* this is how the ball will 'move' */

	/* for mechanics */
	double friction(); /* returns the frictional force */
	bool checkCollide(Ball* other); /* consider moving this function to Collidables */
	std::pair<double, double> getNewVelocity(Ball* other);
	double getNewAngle(Ball* other);

	/* utility */
	double perpendicularDistance(Ball* other); /* consider creating a utility class */
};


#endif //POOL_TABLE_BALL_H
