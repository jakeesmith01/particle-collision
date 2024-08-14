#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct{
  float x, y; //position 
  float Vx, Vy; //velocity 
  float Ax, Ay; //acceleration
  float radius; //radius of particle 
  float mass;   //mass of particle 
} Particle;

void init_particle(Particle *p, float x, float y, float Vx, float Vy, float min_rad, float max_rad, float min_mass, float max_mass);

void update_particle(Particle *p, float dt);

#endif
