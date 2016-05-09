#ifndef PARTICLE_
#define PARTICLE_

#include <string>
#include <vector>
#include "structures.hpp"

bool checkParticle( std::string id );
void setNetMovement( std::string id );
void predictPosition( std::string id );
bool checkPosition( std::string id );
void resetParticle( std::string id );
void reflect( std::string id );
std::string newParticle();
std::string newParticle(int x, int y);
void holdParticle( std::string id );
void releaseParticle( std::string id );
void markDeleted( std::string id );
void deleteParticles();
void growParticle( std::string id );
void shrinkParticle( std::string id );
void resize(unsigned int newParticleCount);
void scaleSpace(double relativeScale);
std::string generateID();
std::string generateNewID();

#endif // PARTICLE_
/*written by Terrence Plunkett - contact at eightys3v3n@gmail.com - all rights reserved*/
