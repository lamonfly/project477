#ifndef PENDULUM_H_INCLUDED
#define PENDULUM_H_INCLUDED

#include <cmath>
#include "simpleMath.h"
#include "glm.h"

#define GRAVITY 9.82

// Timestep for Euler
static const float timeStep = 0.1f;
static bool play = false;

class pendulum
{
private:
	// Angle variables
	float initTheta;
	float theta;
	float velocity;
	float omega;

	// Mass, height and length of rope
	float mass;
	float initHeight;
	float height;
	float ropeLength;
	float airDrag;
	float radius;

	Vec3 pos;
	Vec3 prevPos;

	float index;

public:
	pendulum();
	pendulum(float x, float y, float z, int number, float angle);

	float getX() const { return pos.x; };
	float getTheta() const { return theta; };
	float getRadius() const { return radius; };
	float getO() const { return omega; };

	void calculatePosition();
	void draw();
	int calDir();
	void setTheta(float newTheta);
	void setO(float newO);
	void setPlay(bool p);
};

#endif // PENDULUM_H_INCLUDED

