#include "collider.h"

// Check if two pendulum touch eachother
void collider(vector<pendulum>& base) {
	float touchRadius = 2 * base[0].getRadius();

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
	float Omega1 = p1.getO();
	float Omega2 = p2.getO();

	// Force at same direction = nothing
	if (p1.getTheta() == p2.getTheta() && p1.getO() == p2.getO() && p1.calDir() == p2.calDir()){
		return;
	}

	else{
		if (p1.calDir() != 0 && p2.calDir() != 0){
			// Change their omega as they hit eachother
			float tempOmega1 = Omega1 * ((p1.calDir() * p1.calDir() != p2.calDir()) + (1 * p1.calDir() == p2.calDir()));
			float tempOmega2 = Omega2 * ((p2.calDir() * p1.calDir() != p2.calDir()) + (1 * p1.calDir() == p2.calDir()));

			// Move them apart
			p1.setTheta(p1.getTheta() + (p2.getTheta() - p1.getTheta()));

			// Material here
			p1.setO(tempOmega2);
			p2.setO(tempOmega1);
		}

		// if p1 is stationary
		else if (p1.calDir() == 0){
			// Move them apart
			p1.setTheta(p1.getTheta() + (p2.getTheta() - p1.getTheta()));

			// Material here
			p1.setO(Omega2);
			p2.setO(Omega1);
		}

		// if p2 is stationary
		else if (p2.calDir() == 0){
			// Move them apart
			p2.setTheta(p2.getTheta() + (p1.getTheta() - p2.getTheta()));

			// Material here
			p1.setO(Omega2);
			p2.setO(Omega1);
		}
	}
}