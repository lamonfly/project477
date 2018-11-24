#include "pendulum.h"


// Default constructor
pendulum::pendulum()
{
	angle = -90.0;
	aVel = 0; //Angular Velocity

	pos.x = pos.y = pos.z = 0;

	ropeLength = 5;
	radius = 0.4f;
	mass = 10.0;

	// 0.47 sphere drag
	// 0.0011839 density of air at 25C
	airDrag = (0.47 / (2 * mass))*0.0011839*M_PI*(radius*radius)*ropeLength;
	height = 0;

	index = 0;
}

// Constructor
pendulum::pendulum(float x, float y, float z, int number, float nAngle)
{
	angle = nAngle; //Angle
	aVel = 0; //Angular Velocity

	pos.x = x; 
	pos.y = y; 
	pos.z = z;

	ropeLength = 5;
	radius = 0.4f;
	mass = 10.0;

	// 0.47 sphere drag
	// 0.0011839 density of air at 25C
	airDrag = (0.47 / (2 * mass))*0.0011839*M_PI*(radius*radius)*ropeLength;
	height = 0;

	//number of ball behing drawn
	index = number;
}

// Euler integration to Calculate next frame
void pendulum::calculatePosition()
{
	// set new angular velocity and angle if pendulum is playing
	if (play){
		// For a small angle it is approximated with angle
		if (angle < 0.05 && angle > -0.05)
			aVel -= timeStep * (GRAVITY*angle + airDrag * aVel*abs(aVel));

		else
			aVel -= timeStep * (GRAVITY*sin(angle * M_PI / 180) + airDrag * aVel*abs(aVel));

		angle += timeStep * aVel;
	}

	// height
	height = ropeLength * (1 - cos(angle * M_PI / 180));

	// Update new values
	pos.y = -ropeLength * cos(angle * M_PI/180);
	pos.x = (ropeLength*sin(angle * M_PI / 180) + (2 * radius*index));
}

// Draw each sphere and rope new positions
void pendulum::draw()
{
	calculatePosition();

	glPushMatrix();
	// Add texture or color here

	//Draw sphere
	glTranslatef(pos.x, pos.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glutSolidSphere(radius, 30.0f, 30.0f);

	//Draw rope
	glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.025f, 0.025f, ropeLength, 15.0f, 15.0f);


	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 0.025f, 0.025f, ropeLength, 15.0f, 15.0f);

	glPopMatrix();
}

int pendulum::calDir()
{
	// From left
	if (aVel < -0.3){
		return -1;
	}
	// From Right
	else if (aVel > 0.3){
		return 1;
	}
	// No move
	else{
		return 0;
	}
}

void pendulum::setAngle(float nAngle) {
	angle = nAngle;
}

void pendulum::setAVel(float nVel) {
	aVel = nVel;
}

void pendulum::setPlay(bool p){
	play = p;
}