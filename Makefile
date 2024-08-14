CC = gcc
CFLAGS = -Wall -Iinclude $(shell sdl2-config --cflags)
LDFLAGS = -L/usr/lib -lSDL2 -lm
SRC = src/main.c src/particle.c src/collision.c
OBJ = $(SRC:.c=.o)
EXEC = particle_sim

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
