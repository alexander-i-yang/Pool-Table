//
// Created by samue on 2/27/2019.
//

#ifndef POOL_TABLE_COLLIDABLE_H
#define POOL_TABLE_COLLIDABLE_H

#include <utility>
#include "Drawable.h"

class Collidable : public Drawable {
public:
	Collidable();

	explicit Collidable(const std::pair<int, int> &velocity);
	explicit Collidable(double vAngle);
	Collidable(double vAngle, double mass, const std::pair<int, int> &velocity);
	Collidable(Color c, double x, double y, double z);

	std::pair<double, double> getVelocity() const;
	double getVAngle() const;
	double getMass() const;
	double getXVelocity();
	double getYVelocity();

	void setVelocity(const std::pair<double, double> &velocity);
	void setVelocity(double, double);
	void setVAngle(double vAngle);
	void setMass(double mass);
	double getSpeed();

	void updateAngle();

	virtual void updateFrame();
	std::pair<double, double> getVelocityCollision(Drawable *) override;
	void getNewAngle(Collidable);
protected:
	std::pair<double, double> velocity;
	double vAngle{};
	double mass{};
};


#endif //POOL_TABLE_COLLIDABLE_H
