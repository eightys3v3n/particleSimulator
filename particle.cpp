#include <iostream>
#include <vector>
#include <cmath>
#include "structures.hpp"
#include "math.hpp"
#include "calculate.hpp"
#include "particle.hpp"

extern int universeWidth;
extern int universeHeight;
extern int idLength;
extern double currentStep;
extern long globalRadius;
extern long long globalMass;
extern long double velocity_cap;
extern unsigned long long particleCount;
extern std::map< std::string, Particle > particles;

bool checkParticle( std::string id )
{
	bool status = false;

	if ( std::isnan( particles[id].mass ) )
	{
		std::cout << "particle's mass is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].shape.getRadius() ) )
	{
		std::cout << "particle's radius is nan" << std::endl;
		status = true;
	}

	else if ( std::isnan( particles[id].current.velocity ) )
	{
		std::cout << "particle's current velocity is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.acceleration ) )
	{
		std::cout << "particle's current acceleration is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.force ) )
	{
		std::cout << "particle's current force is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.position.x ) )
	{
		std::cout << "particle's current x position is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.position.y ) )
	{
		std::cout << "particle's current y position is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.direction.x ) )
	{
		std::cout << "particle's current x direction is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.direction.y ) )
	{
		std::cout << "particle's current y direction is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].current.direction.angle ) )
	{
		std::cout << "particle's current angle is nan" << std::endl;
		status = true;
	}


	else if ( std::isnan( particles[id].future.velocity ) )
	{
		std::cout << "particle's future velocity is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.acceleration ) )
	{
		std::cout << "particle's future acceleration is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.force ) )
	{
		std::cout << "particle's future force is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.position.x ) )
	{
		std::cout << "particle's future x position is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.position.y ) )
	{
		std::cout << "particle's future y position is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.direction.x ) )
	{
		std::cout << "particle's future x direction is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.direction.y ) )
	{
		std::cout << "particle's future y direction is nan" << std::endl;
		status = true;
	}
	else if ( std::isnan( particles[id].future.direction.angle ) )
	{
		std::cout << "particle's future angle is nan" << std::endl;
		status = true;
	}

	return status;
}

void setNetMovement( std::string id )
{
  long double net_x_vel;
  long double net_y_vel;
  long double net_x_acc;
  long double net_y_acc;

  net_x_acc = particles[id].current.acceleration * cos( radian( particles[id].current.direction.angle ) );
  net_y_acc = particles[id].current.acceleration * sin( radian( particles[id].current.direction.angle ) );

  net_x_vel = particles[id].current.velocity * cos( radian( particles[id].current.direction.angle ) );
  net_y_vel = particles[id].current.velocity * sin( radian( particles[id].current.direction.angle ) );

	for ( auto& idA : particles)
  {
    if ( idA.first != id )
    {
  		Displacement displacement;
  		long double velocity;
  		long double force;
		  long double acceleration;

      displacement = calc_displacement(particles[ idA.first ], particles[id]);
      force = calc_force(particles[id], particles[ idA.first ], displacement);
      acceleration = calc_acceleration(particles[ idA.first ], force);
      velocity = calc_velocity(acceleration);

      net_x_acc += acceleration * cos( radian( displacement.direction.angle ) );
      net_y_acc += acceleration * cos( radian( displacement.direction.angle ) );

      net_x_vel += velocity * cos( radian( displacement.direction.angle ) );
      net_y_vel += velocity * sin( radian( displacement.direction.angle ) );
    }
  }

  particles[ id ].future.acceleration = sqrt( net_x_acc * net_x_acc + net_y_acc * net_y_acc );
  particles[ id ].future.velocity = sqrt ( net_x_vel * net_x_vel + net_y_vel * net_y_vel );
  particles[ id ].future.direction.x = net_x_vel;
  particles[ id ].future.direction.y = net_y_vel;
  particles[ id ].future.direction.angle = stdAngle(net_x_vel, net_y_vel);

	//checkParticle( id );

	if (particles[ id ].future.velocity > velocity_cap)
		particles[ id ].future.velocity = velocity_cap;
}

void predictPosition( std::string id ) // predicts where the particle will move to using the pre-calculated values
{
	particles[id].future.position.x = particles[id].current.position.x + particles[id].future.velocity * cos( radian( particles[id].future.direction.angle ) );
	particles[id].future.position.y = particles[id].current.position.y + particles[id].future.velocity * sin( radian( particles[id].future.direction.angle ) );
}

bool checkPosition( std::string id )
{
  if (particles[id].future.position.x < particles[id].shape.getRadius() * 2)
		return true;
  else if (particles[id].future.position.x > universeWidth + particles[id].shape.getRadius())
		return true;
  else if (particles[id].future.position.y < particles[id].shape.getRadius() * 2)
		return true;
  else if (particles[id].future.position.y > universeHeight + particles[id].shape.getRadius() )
		return true;

// using the '.intercects' causes the particles to jump around the screen randomly
/*	for (unsigned int p = 0; p < particleCount; p++)
	{
		if ( particles[index].shape.getGlobalBounds().intersects( particles[p].shape.getGlobalBounds() ) )
		{
			particles[index].shape.setFillColor(sf::Color::Red);
			particles[p].shape.setFillColor(sf::Color::Red);
			cout << "Collision" << endl;
			return true;
		}
	}*/

  return false;
}

void resetParticle( std::string id )
{
	particles[id].mass = globalMass;
	particles[id].current.position.x = rand() % universeWidth + 1;
	particles[id].current.position.y = rand() % universeHeight + 1;
	particles[id].current.velocity = (rand() % 100 + 1) / 1000;
	particles[id].current.direction.x = rand() % -100;
	particles[id].current.direction.y = rand() % -100;
	particles[id].current.direction.angle = stdAngle(particles[id].current.direction.x, particles[id].current.direction.y);

	particles[id].shape.setFillColor(sf::Color::White);
	particles[id].shape.setRadius( globalRadius);
	particles[id].shape.setPosition(sf::Vector2f(0, 0));
	particles[id].shape.setOrigin( sf::Vector2f( particles[id].shape.getRadius(), particles[id].shape.getRadius() ) );
	particles[id].shape.setPosition( sf::Vector2f( particles[id].current.position.x, particles[id].current.position.y ) );

	particles[id].future = particles[id].current;
}

void reflect( std::string id )
{
  if ( particles[id].future.position.x < particles[id].shape.getRadius() || particles[id].future.position.x > universeWidth - particles[id].shape.getRadius() )
	{
		particles[id].future.position = particles[id].current.position;
    particles[id].future.direction.x *= -1;
		particles[id].future.direction.angle = stdAngle( particles[id].future.direction.x, particles[id].future.direction.y );
	}
  else if ( particles[id].future.position.y < particles[id].shape.getRadius() || particles[id].future.position.y > universeHeight - particles[id].shape.getRadius() )
	{
		particles[id].future.position = particles[id].current.position;
    particles[id].future.direction.y *= -1;
		particles[id].future.direction.angle = stdAngle( particles[id].future.direction.x, particles[id].future.direction.y );
	}

  particles[id].current.direction.angle = stdAngle(particles[id].current.direction.x, particles[id].current.direction.y);
}

std::string newParticle()
{
	return newParticle( rand() % universeWidth + 1, rand() % universeHeight + 1 );
}

std::string newParticle( int x, int y )
{
	std::string id = "";

	id = generateID();

	resetParticle( id );

	particles[id].current.position.x = x;
	particles[id].current.position.y = y;
	particles[id].future = particles[id].current;
	particles[id].shape.setPosition(sf::Vector2f(particles[id].current.position.x, particles[id].current.position.y));

	return id;
}

void holdParticle( std::string id )
{
	particles[id].frozen = true;
	particles[id].held = true;
}

void releaseParticle( std::string id )
{
	particles[id].frozen = false;
	particles[id].held = false;
}

void markDeleted( std::string id )
{
	particles[id].remove = true;
}

void deleteParticles()
{
  bool aagain = true;

  while ( aagain )
	{
    aagain = false;

    for (auto& id : particles )
  	{
  		if ( id.second.remove )
      {
  			particles.erase( id.first );
        aagain = true;
        break;
      }
  	}
  }
}

void resize(unsigned int newParticleCount)
{
	std::string id = "";

  while ( particles.size() < newParticleCount)
  {
    id = newParticle();
  	resetParticle( id );
  }
}

void scaleSpace(double relativeScale)
{
	for (auto& id : particles)
	{
		particles[id.first].future = particles[id.first].current;

		particles[id.first].future.position.x -= universeWidth / 2;
		particles[id.first].future.position.y *= relativeScale;
		particles[id.first].future.position.x += universeWidth / 2;

		particles[id.first].future.position.y -= universeHeight / 2;
		particles[id.first].future.position.y *= relativeScale;
		particles[id.first].future.position.y += universeHeight / 2;
	}
}

std::string generateID()
{
  std::string newID = "";
  bool duplicate = false;

  while ( duplicate || newID == "" )
  {
    newID = generateNewID();

    for ( auto& id : particles )
      if ( id.first == newID )
        duplicate = true;
  }

  return newID;
}

std::string generateNewID()
{
  static const char lookup[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string newID = "";

  for ( int i = 0; i < idLength; i++ )
    newID += lookup[ rand() % ( sizeof(lookup) - 1 ) ];

  return newID;
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
