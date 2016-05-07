#ifndef INPUT_
#define INPUT_

#include <SFML/System.hpp>

bool defaultCommands(sf::Event* event);
void simulationCommands(sf::Event* event);
void interpreterCommands(sf::Event* event);
void input();

#endif // INPUT_