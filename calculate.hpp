#ifndef CALCULATE_
#define CALCULATE_

#include "structures.hpp"

Displacement calc_displacement(Particle &particleOne, Particle &particleTwo);
long double calc_force(Particle &particleOne, Particle &particleTwo, Displacement displacement);
long double calc_acceleration(Particle &particleOne, long double force);
long double calc_velocity(long double acceleration);

#endif // CALCULATE
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
