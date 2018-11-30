#ifndef PENDULUM_H_INCLUDED
#define PENDULUM_H_INCLUDED

#include <cmath>
#include "simpleMath.h"
#include "glm.h"

#define GRAVITY 9.82

// Timestep for Euler
static float timeStep = 0.1f;
// Dampening value
static float dampen = 1.0f;
static bool play = false;

class pendulum
{
private:
	// Angle variables
	float angle;
	float aVel;

	// Mass, height and length of rope
	float ropeLength;
	float radius;
	float mass;

	// Affects movement
	float airDrag;
	float height;

	Vec3 pos;

	float index;

	float posX;
	float posY;

public:
	pendulum();
	pendulum(float x, float y, float z, int number, float nangle);

	float getX() { return pos.x; };
	float getAngle() { return angle; };
	float getRadius() { return radius; };
	float getAVel() { return aVel; };
	float getDampen() { return dampen; };

	void calculatePosition();
	void draw();
	int calDir();
	void setAngle(float nangle);
	void setAVel(float nVel);
	void setPlay(bool p);
	void drawStand();
	void drawColumn();
};

#endif // PENDULUM_H_INCLUDED

