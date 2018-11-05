#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <time.h>

#define MOUSE_STOP_DIRECTION_CODE 0
#define MOUSE_RIGHT_DIRECTION_CODE 1
#define MOUSE_LEFT_DIRECTION_CODE 2
#define MOUSE_UP_DIRECTION_CODE 3
#define MOUSE_DOWN_DIRECTION_CODE 4

typedef struct Mouse
{
    int faceDirection, line, column, nlifes, direction, initialColumn, initialLine, isDog;
    clock_t start_time_dog;
    char overlaid;
}MOUSE;


#endif // MOUSE_H_INCLUDED
