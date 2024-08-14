#include <math.h>
#include "collision.h"
#include <stdlib.h>

int check_collision(Particle *p1, Particle *p2) {
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    float distance = sqrt(dx * dx + dy * dy);
    float combined_radius = p1->radius + p2->radius;

    return distance <= combined_radius;
}

// Function to resolve the collision between two particles
void resolve_collision(Particle *p1, Particle *p2) {
    // Calculate the difference vector
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    float distance = sqrt(dx * dx + dy * dy);
    
    if(distance == 0){
      distance = 1.0f;
      dx = 1.0f;
      dy = 0.0f;
    }
    
    // Normalize the difference vector
    float nx = dx / distance;
    float ny = dy / distance;

    // Calculate relative velocity
    float dvx = p1->Vx - p2->Vx;
    float dvy = p1->Vy - p2->Vy;
    float dot_product = (dvx * nx + dvy * ny);

    // Calculate impulse scalar
    float coefficient_of_restitution = 0.8f; // Elasticity coefficient
    float mass_sum = p1->mass + p2->mass;
    float impulse = (2 * dot_product) / mass_sum;

    // Update velocities based on impulse
    p1->Vx -= impulse * p2->mass * nx;
    p1->Vy -= impulse * p2->mass * ny;
    p2->Vx += impulse * p1->mass * nx;
    p2->Vy += impulse * p1->mass * ny;

    // Adjust positions to resolve overlap
    float overlap = (p1->radius + p2->radius - distance) / 2;
    p1->x += overlap * nx;
    p1->y += overlap * ny;
    p2->x -= overlap * nx;
    p2->y -= overlap * ny;
}
