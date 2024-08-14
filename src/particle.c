#include <stdlib.h>
#include <time.h>
#include "particle.h"
#include <stdio.h>

float random_float(float min, float max){
  return min + (rand() / (float)RAND_MAX) * (max-min);
}

void init_particle(Particle *p, float x, float y, float Vx, float Vy, float min_rad, float max_rad, float min_mass, float max_mass){
  p->x = x;
  p->y = y;
  p->Vx = Vx;
  p->Vy = Vy;
  p->Ax = 0;
  p->Ay = 0;
  p->radius = random_float(min_rad, max_rad);
  p->mass = random_float(min_mass, max_mass);
}

void update_particle(Particle *p, float dt){
  //printf("before velocity update: x: %f y: %f\n", p->x, p->y);
  p->Vx += p->Ax * dt;
  p->Vy += p->Ay * dt;
  //printf("after velocity update: x: %f, y: %f\n", p->x, p->y);
  
  p->x += p->Vx * dt;
  p->y += p->Vy * dt;

  //printf("after position update: x: %f, y: %f\n", p->x, p->y);
}
