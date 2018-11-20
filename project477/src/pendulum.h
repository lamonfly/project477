#ifndef PENDULUM_H_INCLUDED
#define PENDULUM_H_INCLUDED

#include <cmath>
#include "simpleMath.h"
#include "glm.h"

#define GRAVITY 9.82

// Timestep for Euler
static const float timeStep = 0.1f;

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

	bool play;

	Vec3 pos;
	Vec3 prevPos;

	float index;

public:
	pendulum();

	pendulum(float x, float y, float z, int number, float angle);

	void calculatePosition();
	void draw();

	Vec3 getPos() const { return pos; };
	float getX() const { return pos.x; };
	float getTheta() const { return theta; };
	float getRadius() const { return radius; };
	float getOmega() const { return omega; };

	void setPlay(bool p);
};

#endif // PENDULUM_H_INCLUDED

