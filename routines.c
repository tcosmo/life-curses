#include "routines.h"

int max(int a, int b) {
    return (a >b) ? a : b;
}

int randint(int min, int max) {
    /* Max included */
    return rand()%(max-min+1) + min;
}
