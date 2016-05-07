#ifndef INPUT_
#define INPUT_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "particle.hpp"
#include "interpreter.hpp"

extern bool selecting, interpreting, holdingParticle, previousParticleState;
extern sf::RenderWindow window;
extern std::map< std::string, Particle > particles;
extern sf::IntRect selection;
extern sf::RectangleShape selectionBox;
extern std::string commandBuffer;
extern long double spaceScale;
extern std::string heldParticle;

bool defaultCommands(sf::Event* event)
{
	if (event->type == sf::Event::Closed)
	{
		window.close();
		return true;
	}

	if (event->type == sf::Event::KeyPressed)
	{
		if ( event->text.unicode == 5 ) // f key, toggle particle frozen state
		{
			if ( holdingParticle )
			{
				previousParticleState = ! previousParticleState;

				return true;
			}
		}
		else if (event->text.unicode == 56) // subtract key, zoom out
		{
			if ( ! holdingParticle )
				scaleSpace( 1 - spaceScale );
			else
				particles[heldParticle].shape.setRadius( particles[heldParticle].shape.getRadius() - 1 );

			return true;
		}

		else if (event->text.unicode == 55) // equals key, zoom in
		{
			if ( ! holdingParticle )
				scaleSpace( 1 + spaceScale );
			else
				particles[heldParticle].shape.setRadius( particles[heldParticle].shape.getRadius() + 1 );

			return true;
		}

		// move screen
		else if (event->text.unicode == 71) // move screen west
		{
			for ( auto& id : particles )
				id.second.future.position.x += 10;

			return true;
		}

		else if (event->text.unicode == 72) // move screen east
		{
			for ( auto& id : particles )
				id.second.future.position.x -= 10;
			return true;
		}

		else if (event->text.unicode == 73) // move screen north
		{
			for ( auto& id : particles )
				id.second.future.position.y += 10;
			return true;
		}

		else if (event->text.unicode == 74) // move screen south
		{
			for ( auto& id : particles )
				id.second.future.position.y -= 10;
			return true;
		}
	}
	else if (event->type == sf::Event::MouseButtonPressed) // place new particle under mouse
	{
		if (event->mouseButton.button == sf::Mouse::Left)
		{

			for ( auto& id : particles )
			{
				if ( id.second.shape.getGlobalBounds().contains( sf::Vector2f( event->mouseButton.x, event->mouseButton.y ) ) )
				{
					heldParticle = id.first;
					previousParticleState = particles[heldParticle].frozen;
					holdParticle( heldParticle );
					holdingParticle = true;
					return true;
				}
			}

			heldParticle = newParticle(event->mouseButton.x, event->mouseButton.y);
			previousParticleState = false;
			holdParticle( heldParticle );
			holdingParticle = true;

			return true;
		}
		else if (event->mouseButton.button == sf::Mouse::Right)
		{
			selecting = true;
			selection = sf::IntRect(event->mouseButton.x, event->mouseButton.y, 0, 0);
			//std::cout << "started selecting at (" << event->mouseButton.x << ", " << event->mouseButton.y << ")" << std::endl;
			return true;
		}
	}
	else if (event->type == sf::Event::MouseButtonReleased )
	{
		if ( event->mouseButton.button == sf::Mouse::Left )
		{
			if ( holdingParticle )
			{
				releaseParticle( heldParticle );
				particles[heldParticle].frozen = previousParticleState;
				holdingParticle = false;
			}
		}
		else if ( event->mouseButton.button == sf::Mouse::Right ) // finished selecting particles to delete
		{
			selecting = false;
			selection = sf::IntRect(selection.left, selection.top, event->mouseButton.x - selection.left, event->mouseButton.y - selection.top);
			//std::cout << "stopped selecting at (" << event->mouseButton.x << ", " << event->mouseButton.y << ")" << std::endl;

			for ( auto& id : particles )
				if (selection.contains( id.second.current.position.x, id.second.current.position.y))
					markDeleted( id.first );

			return true;
		}
	}
	else if ( event->type == sf::Event::MouseMoved )
	{
		if ( selecting )
			selection = sf::IntRect(selection.left, selection.top, event->mouseMove.x - selection.left, event->mouseMove.y - selection.top);

		else if ( holdingParticle )
		{
			particles[heldParticle].current.position.x = event->mouseMove.x;
			particles[heldParticle].current.position.y = event->mouseMove.y;
			particles[heldParticle].future.position.x = event->mouseMove.x;
			particles[heldParticle].future.position.y = event->mouseMove.y;
		}
	}

	return false;
}

void simulationCommands(sf::Event* event)
{
	if (event->type == sf::Event::KeyPressed)
	{
		if (event->key.code == 36) // escape key, quit simulation
			window.close();

		else if (event->key.code == 52) // start command interpreter
			interpreting = true;

		else
			std::cout << "unknown input:" << event->key.code << std::endl;
	}
}

void interpreterCommands(sf::Event* event)
{
	if (event->type == sf::Event::KeyPressed)
	{
		if (event->key.code == 36) // escape key, stop interpreting
		{
			interpreting = false;
			commandBuffer = "";
		}
	}

	else if (event->type == sf::Event::TextEntered)
	{
		if (event->text.unicode == 13) // enter key completes command
		{
			interpreting = false;
			commandBuffer = commandBuffer.substr( 1 );
			interpretArgs(commandBuffer);
			commandBuffer = "";
		}

		else if (event->text.unicode == 8) // delete key
		{
			if (commandBuffer.length() > 0)
				commandBuffer = commandBuffer.substr(0, commandBuffer.length() - 1);
		}
		else
			commandBuffer += (char)event->text.unicode;
	}
}

void input()
{
  sf::Event event;

  while (window.pollEvent(event))
  {
		if (!defaultCommands(&event))
		{
			if (!interpreting)
				simulationCommands(&event);
			else
				interpreterCommands(&event);
		}
  }
}

#endif // INPUT_