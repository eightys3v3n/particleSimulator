#include <iostream>
#include <stdlib.h>
#include <map>
#include <SFML/Graphics.hpp>
#include "parse.hpp"
#include "particle.hpp"

extern sf::RenderWindow window;

extern bool pause, quit, dynamicScale;
extern int framerate;
extern long globalRadius;
extern long long globalMass;
extern long long particleCount;
extern std::map< std::string, Particle > particles;

extern std::map< std::string, Particle > particles;

void interpret(std::string buffer)
{
	FindResult result;

	std::cout << "interpreting '" << buffer << "'" << std::endl;

	if ( buffer.length() > 9 && buffer.substr( 0, 9 ) == "framerate" && isNumber( buffer[9] ) )
	{
		framerate = stoi( buffer.substr( 9 ) );
		window.setFramerateLimit(framerate);
		std::cout << "framerate: " << framerate << std::endl;
	}

	else if ( buffer.length() > 12 && buffer.substr( 0, 12 ) == "globalRadius" && isNumber( buffer[12] ) )
	{
		globalRadius = stol( buffer.substr( 12 ) );
		std::cout << "globalRadius: " << globalRadius << std::endl;

		for ( auto& id : particles )
			id.second.shape.setRadius(globalRadius);
	}

	else if ( buffer.length() > 5 && buffer.substr( 0, 5 ) == "scale" && isNumber( buffer[5] ) )
	{
		scaleSpace( stod( buffer.substr( 5 ) ) );
		std::cout << "scale: " << stod( buffer.substr( 5 ) ) << std::endl;
	}

	else if ( buffer.length() > 10 && buffer.substr( 0, 10 ) == "globalMass" && isNumber( buffer[10] ) )
	{
		globalMass = stoll( buffer.substr( 10 ) );
		std::cout << "globalMass: " << globalMass << std::endl;

		for ( auto& id : particles)
			id.second.mass = globalMass;
	}

	else if ( buffer == "particles" )
	{
		std::cout << "particles: " << particles.size() << std::endl;
	}

	else if ( buffer.length() > 9 && buffer.substr( 0, 9 ) == "particles" && isNumber( buffer[9] ) )
	{
		resize( stoi( buffer.substr( 9 ) ) );
		std::cout << "particles: " << stoi( buffer.substr( 9 ) ) << std::endl;
	}

	else if( buffer == "randomize_masses"  || buffer == "randomizeMass" || buffer == "randomizeMasses" )
	{
		std::cout << "randomizing masses" << std::endl;

		for ( auto& id : particles )
			id.second.mass = rand() % 100000000000 + 1;
	}

	else if ( buffer == "quit" || buffer == "close" || buffer == "exit" )
	{
		quit = true;
		window.close();
	}

	if ( buffer == "pause" )
	{
		if ( ! pause )
		{
			std::cout << "pause" << std::endl;
			pause = true;
		}
		else
			std::cout << "already paused" << std::endl;
	}

	if ( buffer == "resume" )
	{
		if ( pause )
		{
			std::cout << "resume" << std::endl;
			pause = false;
		}
		else
			std::cout << "not paused" << std::endl;
	}

//TODO this needs to be adapted to use ids instead of index numbers - also use FindResult instead of Result
/*	if ( buffer.length() > 8 && buffer.substr( 0, 8 ) == "particle" )
	{
		std::string id = "";
		std::string secondaryBuffer = "";
		parse::Result = parse::find( ".", buffer.substr( 8 ) );

		if ( result.position != -1 )

		secondaryBuffer = buffer.substr( 8, result.position );

		id = secondaryBuffer;
		buffer = buffer.substr( result.position + 1 );
		secondaryBuffer = "";

		if ( buffer == "" )
		{
			std::cout << "particle[" << id << "]" << std::endl;
			std::cout << " mass: " << particles[id].mass << std::endl;
			std::cout << " radius: " << particles[id].shape.getRadius() << std::endl;
			std::cout << " current position: (" << particles[id].current.position.x << ", " << particles[id].current.position.y << ")" << std::endl;
			std::cout << " current velocity: " << particles[id].current.velocity << std::endl;
			std::cout << " current acceleration: " << particles[id].current.acceleration << std::endl;
			std::cout << " future  position: (" << particles[id].future.position.x << ", " << particles[id].future.position.y << ")" << std::endl;
			std::cout << " future  velocity: " << particles[id].future.velocity << std::endl;
			std::cout << " future  acceleration: " << particles[id].future.acceleration << std::endl;

			if ( particles[id].frozen )
				std::cout << " frozen" << std::endl;
			if ( particles[id].remove )
				std::cout << " remove" << std::endl;
			if ( particles[id].held )
				std::cout << " held" << std::endl;
		}

		else if ( buffer == "mass" )
			std::cout << "particle [" << id << "].mass: " << particles[id].mass << std::endl;

		else if ( buffer == "radius" )
			std::cout << "particle [" << id << "].radius: " << particles[id].shape.getRadius() << std::endl;
		else if ( buffer == "velocity" || buffer == "vel" )
			std::cout << "particle [" << id << "].velocity: " << particles[id].current.velocity <<
			 	" -> " << particles[id].future.velocity << std::endl;
		else if ( buffer == "acceleration" || buffer == "accel" )
			std::cout << "particle [" << id << "].acceleration: " << particles[id].current.acceleration <<
				" -> " << particles[id].future.acceleration << std::endl;
		else if ( buffer == "position" || buffer == "pos" )
			std::cout << "particle [" << id << "].position: (" << particles[id].current.position.x << ", " << particles[id].current.position.y <<
				") -> (" << particles[id].future.position.x << ", " << particles[id].future.position.y << ")" << std::endl;
		else if ( buffer == "reset" )
		{
			std::cout << "reset particle[" << id << "]" << std::endl;
			resetParticle( particles[id] );
		}

		if ( ( result = find( buffer, "mass*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 4; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].mass = stoll( secondaryBuffer );
			std::cout << "particle[" << id << "].mass: " << particles[id].mass << std::endl;

			buffer = buffer.substr( result.position + 4 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}

		if ( ( result = find( buffer, "radius*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 6; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].shape.setRadius( stod( secondaryBuffer ) );
			std::cout << "particle[" << id << "].radius: " << particles[id].shape.getRadius() << std::endl;

			buffer = buffer.substr( result.position + 6 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}

		if ( ( result = find( buffer, "currentVelocity*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 15; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) || buffer[c] == '.' )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].current.velocity = stold( secondaryBuffer );
			std::cout << "particle[" << id << "].current.velocity: " << particles[id].current.velocity << std::endl;

			buffer = buffer.substr( result.position + 15 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}

		if ( ( result = find( buffer, "futureVelocity*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 14; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) || buffer[c] == '.' )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].future.velocity = stold( secondaryBuffer );
			std::cout << "particle[" << id << "].future.velocity: " << particles[id].future.velocity << std::endl;

			buffer = buffer.substr( result.position + 14 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}

		if ( ( result = find( buffer, "currentAcceleration*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 19; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) || buffer[c] == '.' )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].current.acceleration = stold( secondaryBuffer );
			std::cout << "particle[" << id << "].current.acceleration: " << particles[id].current.acceleration << std::endl;

			buffer = buffer.substr( result.position + 19 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}

		if ( ( result = find( buffer, "futureAcceleration*" ) ).position != -1 )
		{
			for (unsigned int c = result.position + 18; c < buffer.length(); c++)
			{
				if ( isNumber( buffer[c] ) || buffer[c] == '.' )
					secondaryBuffer += buffer[c];
				else
					break;
			}

			particles[id].future.acceleration = stold( secondaryBuffer );
			std::cout << "particle[" << id << "].future.acceleration: " << particles[id].future.acceleration << std::endl;

			buffer = buffer.substr( result.position + 18 + secondaryBuffer.length() );
			secondaryBuffer = "";
		}
	}*/
}

void interpretArgs(std::string buffer)
{
	FindResult result;

	do
	{
		result = find( buffer, " " );

		if ( result.position == -1 )
		{
			interpret( buffer );
			buffer = "";
		}
		else
		{
			interpret( buffer.substr(0, result.position) );
			buffer = buffer.substr( result.position + 1 );
		}
	}
	while ( result.position != -1 && buffer != "" );
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
