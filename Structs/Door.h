#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Position.h"

typedef struct Door
{
   int opened;
   POSITION position;
   char overlaid;
   struct Door* nextDoor;
}DOOR;

#endif // DOOR_H_INCLUDED
