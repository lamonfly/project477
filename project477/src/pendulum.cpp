
#include <iostream>
#include "pendulum.h"

int highestAngle;
float highestSpeed = 20;
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
	if (play) {
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
	pos.y = -ropeLength * cos(angle * M_PI / 180);
	pos.x = (ropeLength*sin(angle * M_PI / 180) + (2 * radius*index));
}
void pendulum::setSelectedColor() {
	rcolor = 1;
	gcolor = 0;
	bcolor = 0;
}

void pendulum::setUnselectedColor() {
	rcolor = 0.5;
	gcolor = 0.5;
	bcolor = 0.5;
}
void pendulum::drawColumn() {
	//Start of the stand
	float posX = -1.2;

	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
	glTranslatef(posX, -0.1, 1.8);
	glutSolidSphere(radius, 30.0f, 30.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX, -0.25, -2.2);
	glutSolidSphere(radius, 30.0f, 30.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX, 0, 1.8);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 6, 15.0f, 15.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX, -0.15, -2.2);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 6, 15.0f, 15.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(posX, -6.3, -2.6);
	glRotatef(45, 0, 0, 1);
	gluCylinder(gluNewQuadric(), 0.7f, 0.7f, 5, 4, 4);
	glPopMatrix();

	//End of the stand
	posX = 1.2;

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -0.1, 1.8);
	glutSolidSphere(radius, 30.0f, 30.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -0.25, -2.2);
	glutSolidSphere(radius, 30.0f, 30.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), 0, 1.8);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 6, 15.0f, 15.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -0.15, -2.2);
	glRotatef(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 6, 15.0f, 15.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -6.3, -2.6);
	glRotatef(45, 0, 0, 1);
	gluCylinder(gluNewQuadric(), 0.7f, 0.7f, 5, 4, 4);
	glPopMatrix();


}
void pendulum::drawStand() {
	float posX = -1;
	//Draw Stands
	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -0.05, 1.80);
	glRotatef(90, 0, 1, 0);
	glColor3f(0.1, 0.1, 0.1);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 2, 10.0f, 10.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -0.2, -2.2);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.3f, 0.3f, 2, 10.0f, 10.0f);
	glPopMatrix();

	posX = -1.7;
	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -6.8, 2.4);
	glRectf(0, 0, 3.4, 1);
	glPopMatrix();

	posX = -1.7;
	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -6.8, -2.6);
	glRectf(0, 0, 3.4, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -5.8, -2.6);
	glRotatef(90, 1, 0, 0);
	glRectf(0, 0, 3.4, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(posX + (2 * radius*index), -6.8, -2.6);
	glRotatef(90, 1, 0, 0);
	glRectf(0, 0, 3.4, 5);
	glPopMatrix();

}
// Draw each sphere and rope new positions
void pendulum::draw()
{
	glPushMatrix();
	// Add texture or color here

	//Draw sphere
	glColor3f(rcolor, gcolor, bcolor);
	glTranslatef(pos.x, pos.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glutSolidSphere(radius, 30.0f, 30.0f);

	//Draw rope
	glColor3f(0.1, 0.1, 0.1);
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