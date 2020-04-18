#include "world.h"
#include "routines.h"

World new_world(int height, int width) {
    
    World w;
    w.height = height;
    w.width = width;

    w.cells = (int**) calloc(w.height,sizeof(int*));
    
    for(int y = 0 ; y < w.height ; y += 1) {
        w.cells[y] = (int*) calloc(w.width,sizeof(int));    
    }

    return w;
}

void free_world(World w) {
    
    for(int y = 0 ; y < w.height ; y += 1) {
        free(w.cells[y]);
    }

    free(w.cells);
}

char cell_to_char(int cell) {
    return cell ? '#' : ' ';
}

void print_world(World w, int screen_h, int screen_w) {
    
    int d_y = (screen_h - w.height) / 2;
    int d_x = (screen_w - w.width) / 2;

    for(int y = 0 ; y < w.height ; y += 1) 
        for(int x = 0 ; x < w.width ; x += 1) 
            mvprintw(y+d_y, x+d_x, "%c", cell_to_char(w.cells[y][x]));
    
    return;
}

void randomize_world(World w) {
    
    for(int y = 0 ; y < w.height ; y += 1)
        for(int x = 0 ; x < w.width ; x += 1) 
           w.cells[y][x] = randint(0,1); 

    return;
}


int get_nb_alive_neighbors(World w, int y, int x) {
    /* On Torus */
    
    int directions[8][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}, 
                            {1,1}, {-1,-1}, {1,-1}, {-1,1}};

    int result = 0;
    for(int i_dir = 0 ; i_dir < 8 ; i_dir += 1) {
       
        int d_y = directions[i_dir][0], d_x = directions[i_dir][1]; 
        int new_y = (w.height + y + d_y)%(w.height), new_x = (w.width + x + d_x)%(w.width);

        result += w.cells[new_y][new_x];
    }

    return result;
}

void update_world(World w) {

    int new_cells[w.height][w.width];

    for(int y = 0 ; y < w.height ; y += 1) {
        for(int x = 0 ; x < w.width ; x += 1) {
            
            int cell = w.cells[y][x];
            int nb_alive_neighbors = get_nb_alive_neighbors(w,y,x);            
            new_cells[y][x] = !cell ? nb_alive_neighbors == 3 : ( nb_alive_neighbors == 2 || nb_alive_neighbors == 3 ); 
        }
    }

    for(int y = 0 ; y < w.height ; y += 1)
        for(int x = 0 ; x < w.width ; x += 1)
            w.cells[y][x] = new_cells[y][x];

    return;
}
