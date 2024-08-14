#ifndef COLLISION_H
#define COLLISION_H 
#include "particle.h"

int check_collision(Particle *p1, Particle *p2);

void resolve_collision(Particle *p1, Particle *p2);

#endif
