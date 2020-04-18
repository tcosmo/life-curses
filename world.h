#ifndef DEF_WORLD_H
#define DEF_WORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

struct World {
    int** cells;
    int height;
    int width;
};

typedef struct World World;


World new_world(int height, int width); 
void free_world(World w);

void print_world(World w, int screen_h, int screen_w);

void randomize_world(World w);
void update_world(World w);


#endif
