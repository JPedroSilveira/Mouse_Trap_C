#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

typedef struct Door
{
   int opened, line, column, exists;
   char overlaid;
   struct Door *nextDoor;
}DOOR;

#endif // DOOR_H_INCLUDED
