#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "particle.hpp"

extern sf::RenderWindow window;
extern sf::Text simulationTime;
extern sf::IntRect selection;
extern sf::RectangleShape selectionBox;
extern sf::Color backgroundColour;

extern bool selecting;
extern bool variableParticleRadius;
extern int actualFramerate;
extern long double actualSpeed;
extern long double universe_time;
extern long long particleCount;
extern std::map< std::string, Particle > particles;

void drawParticles()
{
  for ( auto& id : particles )
  {
    id.second.shape.setPosition(sf::Vector2f(id.second.current.position.x, id.second.current.position.y));

		if (variableParticleRadius)
		{
			if (id.second.mass < 1000000)
				id.second.shape.setRadius(1);
			else if (id.second.mass < 100000000)
				id.second.shape.setRadius(3);
			else if (id.second.mass < 10000000000)
				id.second.shape.setRadius(6);
			else
				id.second.shape.setRadius(10);
		}

    if ( id.second.held )
      id.second.shape.setFillColor( sf::Color::Green );
    else if ( id.second.frozen )
      id.second.shape.setFillColor( sf::Color::Red );
    else
      id.second.shape.setFillColor( sf::Color::White );

    window.draw(id.second.shape);
  }
}

void drawInformation()
{
  simulationTime.setString( "time: " + std::to_string(universe_time) + " | fps: " + std::to_string(actualFramerate) + " | speed: " + std::to_string(actualSpeed) + "t/s");
  window.draw(simulationTime);
}

void drawSelectionBox()
{
  selectionBox.setPosition(sf::Vector2f(selection.left, selection.top));
  selectionBox.setSize( sf::Vector2f( selection.width, selection.height ));

  window.draw(selectionBox);
}

void draw()
{
  window.clear(backgroundColour);

	drawParticles();

	if (selecting) // draws the selection box
    drawSelectionBox();

	drawInformation();

  window.display();
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
