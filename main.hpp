#ifndef MAIN_
#define MAIN_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "structures.hpp"

sf::RenderWindow window;
sf::Text simulationTime;
sf::Font font;
sf::IntRect selection;
sf::RectangleShape selectionBox;
sf::Color backgroundColour = sf::Color::Black;
sf::Color particleColour = sf::Color::White;

bool quit = false;
bool pause = false;
bool selecting = false;
bool holdingParticle = false;
bool followMode = false;
bool variableParticleRadius = false;
bool previousParticleState = false;
bool dynamicScale = true;
bool interpreting = false;
int framerate = 31;
int actualFramerate = 0;
int time_multiplier = 1;
int universeWidth = 800;
int universeHeight = 500;
int idLength = 5; // this may have to be increased to accomidate more particles
long globalRadius = 3;
long long globalMass = 100000;
long double actualSpeed = 0;
long double velocity_cap = 7;
long double universe_time = 0;
long double spaceScale = 1;
long long particleCount = 1;
std::string commandBuffer = "";
std::string fontPath = "resources/font.ttf";
std::string heldParticle = "";
std::map< std::string, Particle > particles;

#endif // MAIN_
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
