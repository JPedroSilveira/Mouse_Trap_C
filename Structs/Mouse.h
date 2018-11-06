#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <time.h>
#include "Position.h"

#define MOUSE_MIN_DIRECTION_NUMBER 1
#define MOUSE_STOP_DIRECTION_CODE 0
#define MOUSE_RIGHT_DIRECTION_CODE 1
#define MOUSE_LEFT_DIRECTION_CODE 2
#define MOUSE_UP_DIRECTION_CODE 3
#define MOUSE_DOWN_DIRECTION_CODE 4
#define MOUSE_MAX_DIRECTION_NUMBER 4

typedef struct Mouse
{
    int faceDirection, nlifes, direction, isDog;
    POSITION position, initialPosition;
    clock_t start_time_dog;
    char overlaid;
}MOUSE;


#endif // MOUSE_H_INCLUDED
