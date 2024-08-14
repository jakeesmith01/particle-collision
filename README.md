# particle-collision
This is a simple application written in C, using SDL2. It will create a specified number of particles with collision. Collision occurs between the boundaries of the window (set as 800x600) and between different particles. 

SDL2 does not natively support drawing a circle, so instead I convert the circle to a triangle fan and draw it that way. 

Usage: To run the program, run the make file, and then start the application with ./particle_sim <number of particles>. There is no hardcoded limit of particles, however you have to have at least one. Should you input a ridiculously large number of particles it will either break or run extremely slow as SDL2 is not the most performant graphics library out there.
