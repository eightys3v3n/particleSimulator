#ifndef SIMULATION_
#define SIMULATION_

#include <thread>
#include <vector>
#include <cmath>
#include <chrono>
#include "particle.hpp"
#include "structures.hpp"

extern std::map< std::string, Particle > particles;
extern bool interpreting;
extern bool pause;
extern long double universe_time;

void simulateParticle( std::string id )
{
	if ( ! particles[id].frozen )
	{
		setNetMovement( id );
		predictPosition( id );

		if ( checkPosition( id ) )
			markDeleted( id );
	}
}

void calculate()
{
	if (!interpreting && !pause)
	{
		for ( auto& id : particles)
			id.second.current = id.second.future;

		for ( auto& id : particles)
			simulateParticle( id.first );

		for ( auto& id : particles)
			id.second.current = id.second.future;

		deleteParticles(); // delete the marked particles

		universe_time++;
	}
}

#endif // SIMULATION_
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
