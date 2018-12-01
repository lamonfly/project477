#include "collider.h"

// Check if two pendulum touch eachother
void collider(vector<pendulum>& base) {
	float touchRadius = 2 * base[0].getRadius() + 0.01f;

	for (unsigned i = 0; i < base.size() - 1; i++) {
		// Send velocity to next sphere
		if (abs(base[i].getX() - base[i + 1].getX()) < touchRadius)
		{
			collision(base[i], base[i + 1]);
		}
	}
}

// React to two pendulum touching each other
void collision(pendulum& p1, pendulum& p2) {
	float Omega1 = p1.getAVel();
	float Omega2 = p2.getAVel();

	// nothing moving
	if (!p1.getPlay()) {
		if (abs(p1.getAngle()) > abs(p2.getAngle())) {
			p2.setAngle(p2.getAngle() + (p1.getAngle() - p2.getAngle()));
		}
		else {
			p1.setAngle(p1.getAngle() + (p2.getAngle() - p1.getAngle()));
		}
	}

	// p1 and p2 not stationary
	if (p1.calDir() != 0 && p2.calDir() != 0){
		// Change their omega as they hit eachother
		float tempOmega1 = Omega1 * ((p1.calDir() * p1.calDir() != p2.calDir()) + (1 * p1.calDir() == p2.calDir()));
		float tempOmega2 = Omega2 * ((p2.calDir() * p1.calDir() != p2.calDir()) + (1 * p1.calDir() == p2.calDir()));

		// Move them apart
		p1.setAngle(p1.getAngle() + (p2.getAngle() - p1.getAngle()));

		if (p1.calDir() != p2.calDir()) {
			// Material here
			p1.setAVel(tempOmega2 * p1.getDampen());
			p2.setAVel(tempOmega1 * p2.getDampen());
		}
	}

	// if p1 is stationary
	else if (p1.calDir() == 0){
		// Move them apart
		if (abs(p2.calDir())) {
			p2.setAngle(p2.getAngle() + (p1.getAngle() - p2.getAngle()));
		}
		else {
			p1.setAngle(p1.getAngle() + (p2.getAngle() - p1.getAngle()));
		}

		// Material here
		p1.setAVel(Omega2 * p1.getDampen());
		p2.setAVel(Omega1 * p2.getDampen());
	}

	// if p2 is stationary
	else if (p2.calDir() == 0){
		// Move them apart
		if (abs(p1.calDir())) {
			p1.setAngle(p1.getAngle() + (p2.getAngle() - p1.getAngle()));
		}
		else {
			p2.setAngle(p2.getAngle() + (p1.getAngle() - p2.getAngle()));
		}

		// Material here
		p1.setAVel(Omega2 * p1.getDampen());
		p2.setAVel(Omega1 * p2.getDampen());
	}
}