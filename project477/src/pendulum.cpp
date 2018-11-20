#include "pendulum.h"


// Default constructor
pendulum::pendulum()
{
	play = false;

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
	play = false;

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
	glTranslatef(prevPos.x, prevPos.y, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
	glutSolidSphere(radius, 30.0f, 30.0f);

	glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.9f, 0.9f, 0.8f);
	glutSolidCone(0.05f, ropeLength, 15.0f, 15.0f);


	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.9f, 0.9f, 0.8f);
	glutSolidCone(0.05f, ropeLength, 15.0f, 15.0f);

	glPopMatrix();
}


void pendulum::setPlay(bool p)
{
	play = p;
}