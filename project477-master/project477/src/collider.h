#pragma once
#include <vector>
#include <iostream>
#include "simpleMath.h"
#include "pendulum.h"

using namespace std;

//Collider functions

void collider(vector<pendulum>& base);
void collision(pendulum& p1, pendulum& p2);
