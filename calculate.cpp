#include <cmath>
#include "structures.hpp"
#include "math.hpp"

extern long double universe_time;

Displacement calc_displacement(Particle &particleOne, Particle &particleTwo)
{
  Displacement displacement;
  displacement.distance = 0;
  displacement.direction.angle = 0;
  displacement.direction.x = 0;
  displacement.direction.y = 0;

  if (particleOne.current.position.x == 0 && particleOne.current.position.y == 0 && particleTwo.current.position.x == 0 && particleTwo.current.position.y == 0)
    return displacement;

  long double x = ( particleTwo.current.position.x - particleOne.current.position.x );
  long double y = ( particleTwo.current.position.y - particleOne.current.position.y );

  displacement.direction.x = x;
  displacement.direction.y = y;
  displacement.direction.angle = stdAngle(x, y);

  displacement.distance = sqrt( pow(y, 2) + pow(x, 2) );

  return displacement;
}

long double calc_force(Particle &particleOne, Particle &particleTwo, Displacement displacement)
{
  long double force;

	if (displacement.distance == 0)
		return 0;
	else
  	force = 0.00000000006673 * particleOne.mass * particleTwo.mass / pow(displacement.distance, 2);

  return force;
}

long double calc_acceleration(Particle &particleOne, long double force)
{
  long double acceleration;

  acceleration = force / particleOne.mass;

  return acceleration;
}

long double calc_velocity(long double acceleration)
{
  long double velocity;

  velocity = acceleration;

	return velocity;
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
