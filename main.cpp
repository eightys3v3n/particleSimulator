#include <iostream>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "interpreter.hpp"
#include "input.hpp"
#include "graphics.hpp"
#include "structures.hpp"
#include "simulation.hpp"
#include "main.hpp"
using namespace std;
using namespace chrono;

// initialize variables
void initialize()
{
	srand(time(NULL));

	window.create(sf::VideoMode(universeWidth, universeHeight), "terrence & sean's particle simulator", sf::Style::Close);

	selectionBox.setFillColor(sf::Color::Transparent);
	selectionBox.setOutlineColor(sf::Color::Red);
	selectionBox.setOutlineThickness(1);
  font.loadFromFile(fontPath);
  simulationTime.setFont(font);

  simulationTime.setColor(sf::Color::White);
  simulationTime.setPosition(sf::Vector2f(0, window.getSize().y - 10));
  simulationTime.setCharacterSize(10);

  window.clear(sf::Color::Black);
  window.setFramerateLimit(framerate);
	window.display();
}

int main(int argc, char** argv)
{
	std::string argumentBuffer = "";

	if ( argc > 1 )
		for ( int a = 1; a < argc; a++ )
			argumentBuffer += string( argv[a] ) + " ";

  // read arguments and set variables accordingly
  interpretArgs(argumentBuffer);

  // initialize main variables
  initialize();

	while (!quit && window.isOpen())
	{
		if (!interpreting && !pause)
			calculate();

    // calculate the actualFramerate
		draw();
		input();
	}

  return false;
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
