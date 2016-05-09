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

  // this is for troubleshooting the negative gravity.
  particles.clear();
  Particle particleOne, particleTwo;
  particleOne.mass = 100000000;
  particleTwo.mass = 100000000;
  particleOne.current.position.x = 370;
  particleOne.current.position.y = 250;
  particleTwo.current.position.x = 430;
  particleTwo.current.position.y = 250;
  particleOne.current.velocity = 0;
  particleOne.current.acceleration = 0;
  particleOne.current.direction.x = 0;
  particleOne.current.direction.y = 0;
  particleOne.current.direction.angle = 0;
  particleTwo.current.velocity = 0;
  particleTwo.current.acceleration = 0;
  particleTwo.current.direction.x = 0;
  particleTwo.current.direction.y = 0;
  particleTwo.current.direction.angle = 0;
  particleOne.future = particleOne.current;
  particleTwo.future = particleTwo.current;
  particles["one"] = particleOne;
  particles["two"] = particleTwo;
  // end of troubleshooting code

  while (!quit && window.isOpen())
  {
		if (!interpreting && !pause)
			calculate();

    // this is for troubleshooting the negative gravity.
    cout << "particle[one] { force=" << particles["one"].current.force << " & " <<  particles["one"].current.force << " }" << endl;
    cout << "particle[two] { force=" << particles["two"].current.force << " & " <<  particles["two"].current.force << " }" << endl;
    // end of troubleshooting code

    // calculate the actualFramerate
		draw();
		input();
	}

  return false;
}
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
