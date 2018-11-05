#ifndef MAPUTILS_H_INCLUDED
#define MAPUTILS_H_INCLUDED

#include <stdio.h>

#include "../Consts/Boolean.h"
#include "../Consts/MapDimensions.h"
#include "../Consts/MapTimers.h"
#include "../Consts/MapColors.h"
#include "../Consts/MapCharacters.h"

#include "../Structs/GameData.h"

#include "DrawUtils.h"
#include "ColumnUtils.h"
#include "MenuUtils.h"
#include "HeaderUtils.h"

#define NUM_CATS 4

void drawWall(int line, int col);
void drawMouse(int line, int col, int toRight, int isDog);
void drawFood(int line, int col);
void drawBone(int line, int col);
void drawCat(int line, int col, int toRight, int isImmortal);
void drawDoor(int line, int col);
void drawMapItem(int lineInit, int colInit, int colorvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH], char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH], int background, int color);
void drawMap(GAMEDATA *data, int mouseToRight);
CAT getCatByPosition(GAMEDATA data, int line, int column);
void drawItemByCh(char ch, int line, int column, int catToRight, int mouseToRight, int mouseIsDog, int catIsImmortal);
void printMap(char map[MAP_LINES][MAP_COLUMNS]);
void drawEmptyMap();

#endif // MAPUTILS_H_INCLUDED
