#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED

#include "../Consts/MapDimensions.h"
#include "Mouse.h"
#include "Door.h"
#include "Cat.h"

#define NAME_MAX_LENGTH 45
#define DOOR_AMOUNT 7

typedef struct GameData
{
   int paused, level,
        gameOver, menuOpened,
        exitGame, score, ncats, ndoors,
        doorsOpened, waitForUserInput,
        nfood, updateLevel;
   char gameMap[MAP_LINES][MAP_COLUMNS], username[NAME_MAX_LENGTH];
   int mapDistances[MAP_LINES][MAP_COLUMNS];
   DOOR* door;
   CAT* cat;
   MOUSE mouse;
}GAMEDATA;

#endif // GAMEDATA_H_INCLUDED
