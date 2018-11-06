#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "Position.h"

typedef struct Cat
{
    int faceDirection, immortal;
    POSITION position, initialPosition;
    char overlaid;
    clock_t start_immortal_time;
    struct Cat* nextCat;
}CAT;

#endif // CAT_H_INCLUDED
