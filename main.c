#include "world.h"
#include "routines.h"

int main() {

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    World w = new_world(max_y/(1.5),max_x/(1.5));
    randomize_world(w);

    int min_delay = 3000;
    int delay = min_delay;
    int d_delay = 100000;

    nodelay(stdscr, TRUE);

    int is_paused = 0;

    while(1) {
        erase(); 
         
        print_world(w, max_y, max_x);
        
        if( !is_paused )
            update_world(w);

        refresh();
    
        int c = getch();

        /* Toggle pause */
        if( c == 'p' ) 
            is_paused = 1-is_paused;

        /* Restart from random */
        if( c == 'r' )
            randomize_world(w);
        
        /* Slower */
        if( c == 's') 
            delay += d_delay;

        /* Faster */
        if( c == 'f') 
            delay = max(min_delay, delay - d_delay);
        
        if( c == 'q' ) 
            break;

        usleep(delay);
    }

    free_world(w);
    endwin(); 
}
