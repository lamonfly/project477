#include "pendulum.h"


// Default constructor
pendulum::pendulum()
{
	initTheta = theta = -90.0; //Angle
	omega = 0; //Angular Velocity

	velocity = 0;
	pos.x = pos.y = pos.z = 0;
	prevPos.x = 0; prevPos.y = 0; prevPos.z = 0;

	ropeLength = 5;
	radius = 0.4f;
	mass = 10.0;

	// 0.47 sphere drag
	// 0.0011839 density of air at 25C

	airDrag = (0.47 / (2 * mass))*0.0011839*M_PI*(radius*radius)*ropeLength;

	initHeight = ropeLength * (1 - cos(theta * M_PI / 180));
	height = 0;

	index = 0;

}

// Constructor
pendulum::pendulum(float x, float y, float z, int number, float angle)
{
	initTheta = theta = angle; //Angle
	omega = 0; //Angular Velocity

	velocity = 0;
	pos.x = x; 
	pos.y = y; 
	pos.z = z;
	prevPos.x = x; 
	prevPos.y = y; 
	prevPos.z = z;

	ropeLength = 5;
	radius = 0.4f;
	mass = 10.0;

	// 0.47 sphere drag
	// 0.0011839 density of air at 25C

	airDrag = (0.47 / (2 * mass))*0.0011839*M_PI*(radius*radius)*ropeLength;



	initHeight = ropeLength * (1 - cos(theta * M_PI / 180));
	height = 0;

	//number of ball behing drawn
	index = number;
}

// Euler to Calculate next frame
void pendulum::calculatePosition()
{

	prevPos.x = pos.x;
	prevPos.y = pos.y;

	// omega and theta
	if (play)
	{
		// For a small theta it is approximated with theta
		if (theta < 0.05 && theta > -0.05)
			omega -= timeStep * (((GRAVITY / ropeLength)*theta) + airDrag * omega*abs(omega));

		else
			omega -= timeStep * ((GRAVITY / ropeLength)*sin(theta * M_PI / 180) + airDrag * omega*abs(omega));

		theta += timeStep * omega;
	}

	// height
	height = ropeLength * (1 - cos(theta * M_PI / 180));

	// velocity
	velocity = sqrt(2 * GRAVITY*(initHeight - height));


	// Update new values
	pos.y = -ropeLength * cos(theta * M_PI/180);
	pos.x = (ropeLength*sin(theta * M_PI / 180) + (2 * radius*index));
}

// Draw each sphere and rope new positions
void pendulum::draw()
{
	calculatePosition();

	glPushMatrix();
	// Add texture or color here

	//Draw sphere
	glTranslatef(prevPos.x, prevPos.y, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
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
	if (omega < -0.3){
		return -1;
	}
	// From Right
	else if (omega > 0.3){
		return 1;
	}
	// No move
	else{
		return 0;
	}
}

void pendulum::setTheta(float newTheta) {
	theta = newTheta;
}

void pendulum::setO(float newO) {
	omega = newO;
}

void pendulum::setPlay(bool p)
{
	play = p;
}