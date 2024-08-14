#include <SDL2/SDL.h>
#include <stdio.h>
#include "particle.h"
#include "collision.h"
#include <math.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define PI 3.14159265358979323846
#define WINDOW_HEIGHT 600

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius){
  const int num_segments = 360;
  SDL_Point points[num_segments + 1];
  
  //printf("init x: %d, init y: %d, init rad: %d\n", x, y, radius);

  for(int i = 0; i < num_segments; i++){
    float angle = 2.0f * PI * i / num_segments;
    points[i].x = x + radius * cosf(angle);
    points[i].y = y + radius * sinf(angle);
  }

  points[num_segments] = points[0];

  SDL_RenderDrawLines(renderer, points, num_segments + 1);
}

int main(int argc, char *argv[]) {
  if(argc < 2){
    printf("Usage: %s <number of particles>\n", argv[0]);
    return 1;
  }

  int num_particles;

  if(atoi(argv[1]) < 1){
    printf("Must have at least one particle, using default value of 10");
    num_particles = 10;
  } else {
    num_particles = atoi(argv[1]);
  }



  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Particle Collision Sim",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WINDOW_WIDTH, WINDOW_HEIGHT,
                                     SDL_WINDOW_SHOWN);
  if (win == NULL){
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer == NULL){
    SDL_DestroyWindow(win);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  
  Particle particles[num_particles];

  for(int i = 0; i < num_particles; i++){
    init_particle(&particles[i], rand() % (WINDOW_WIDTH - 20) + 10, rand() % (WINDOW_HEIGHT - 20) + 10, 1.0f * (rand() % 5 + 1), 1.0f * (rand() % 5 + 1), 1.0f, 10.0f, 0.5f, 2.5f); // radius=range 1-10, mass=range 0.5-2.5
   printf("Particle %d - x: %f, y: %f, radius: %f, mass: %f\n", i, particles[i].x, particles[i].y, particles[i].radius, particles[i].mass);
  }

  int running = 1;
  SDL_Event event;
  while(running){
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = 0;
      }
    }

    for(int i = 0; i < num_particles; i++){
      printf("particle %d values before update -- x: %f, y: %f\n", i, particles[i].x, particles[i].y);
      update_particle(&particles[i], 0.1f);

      if(particles[i].x - particles[i].radius <= 0 || particles[i].x - particles[i].radius >= WINDOW_WIDTH){
        particles[i].Vx = -particles[i].Vx;
      }

      if(particles[i].y - particles[i].radius <= 0 || particles[i].y - particles[i].radius >= WINDOW_HEIGHT){
        particles[i].Vy = -particles[i].Vy;
      }
      
      printf("particle %d values after border collision detection -- x: %f, y: %f\n", i, particles[i].x, particles[i].y);
      for(int j = 0; j < num_particles; j++){
        if(check_collision(&particles[i], &particles[j])){
          resolve_collision(&particles[i], &particles[j]);
        }
      }

      printf("particle %d values after collision check/resolution -- x: %f, y: %f", i, particles[i].x, particles[i].y);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = 0; i < num_particles; i++){
      //printf("starting draw_circle for particle %d with values x: %f, y: %f\n", i, particles[i].x, particles[i].y);
      int floorx = round(particles[i].x);
      int floory = round(particles[i].y);
      int floorrad = round(particles[i].radius);
      //printf("values passed: %d, %d, %d\n", floorx, floory, floorrad);
      draw_circle(renderer, floorx, floory, floorrad);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
