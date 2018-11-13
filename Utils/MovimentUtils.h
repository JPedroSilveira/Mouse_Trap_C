#ifndef MOVIMENTUTILS_H_INCLUDED
#define MOVIMENTUTILS_H_INCLUDED

#include <windows.h>
#include <time.h>
#include "../Consts/Boolean.h"
#include "../Consts/MapCharacters.h"
#include "../Consts/Boolean.h"
#include "../Structs/GameData.h"
#include "../Structs/Mouse.h"
#include "DrawUtils.h"
#include "MapUtils.h"

#define SCORE_FOR_FOOD 10

#define CAT_IMMORTAL_TIME 2000

#define DOOR_R_DISPL 1
#define DOOR_D_DISPL 1

#define SCORE_TEXT_COLOR_ON_UPDATE 4

#define MOVIMENT_DELAY 200

void moveMouse(GAMEDATA* data);
void moveDoors(GAMEDATA* data);
void decideMouseDirection(GAMEDATA *data);
int isCrossing(char item);
int isFood(char item);
void changeMousePosition(int lineIncrease, int columnIncrease, int mouseDirection, GAMEDATA *data);
void moveCat(GAMEDATA* data);
int getShorterDistance(int d1, int d2, int* selected);
int getLongerDistance(int d1, int d2, int* selected);

#endif // MOVIMENTUTILS_H_INCLUDED
