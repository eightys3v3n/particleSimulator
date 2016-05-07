#ifndef STRUCTURES_
#define STRUCTURES_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct Coord
{
	double x = 0;
  double y = 0;
};

struct Direction
{
  double x = 0;
  double y = 0;
  double angle = 0;
};

struct Displacement
{
  double distance = 0;
	Direction direction;
};

struct Velocity
{
  double speed = 0;
  Direction direction; // angle of rotation in standard position.
};

struct ParticleState
{
  ParticleState();

  Coord position;
  Direction direction;
  long double velocity = 0;
  long double acceleration = 0;
  long double force = 0;
};

struct Particle
{
	Particle();

	long long mass = 1;
  ParticleState current;
  ParticleState future;
  sf::CircleShape shape;

  // states
    bool frozen = false;
    bool remove = false;
    bool held = false;
};

#endif // STRUCTURES_
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
