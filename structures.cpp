#include <SFML/Graphics.hpp>
#include "structures.hpp"

extern sf::Color particleColour;
extern long long globalRadius;

ParticleState::ParticleState()
{
  direction.x = 0;
  direction.y = 0;
  direction.angle = 0;

  position.x = 0;
  position.y = 0;

  velocity = 0;
  acceleration = 0;
};

Particle::Particle()
{
	shape.setFillColor(particleColour);
	shape.setRadius(globalRadius);
}