#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int random(int max){
    return rand() % max;
}

#endif