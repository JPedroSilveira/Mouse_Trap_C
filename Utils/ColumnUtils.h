#ifndef COLUMNUTILS_H_INCLUDED
#define COLUMNUTILS_H_INCLUDED

#include <stdio.h>
#include <conio.h>

#include "../Structs/GameData.h"
#include "../Consts/Boolean.h"
#include "DrawUtils.h"
#include "MapUtils.h"

#define LEFT_SIDE_INIT_COLUMN 1
#define LEFT_SIDE_LAST_COLUMN 33
#define RIGHT_SIDE_INIT_COLUMN 87
#define RIGHT_SIDE_LAST_COLUMN 121

#define SIDE_INIT_LINE 7
#define COLUMN_HEIGHT 23

#define BORDER_COLOR 4
#define BG_COLOR 0

#define LAST_LINE 30
#define LAST_COLUMN 120

#define DEFAULT_BG_COLOR 0

void drawGameInfo(GAMEDATA data);
void updateScoreOnScreen(GAMEDATA data);
void updateExecutionState(GAMEDATA data);
void updateLevelOnScreen(GAMEDATA data);
void updateLifesInfoOnScreen(GAMEDATA data);
void updateCatsInfoOnScreen(GAMEDATA data);
void drawSideColumns();
void drawLineBetweenSides();
void drawLeftSide();
void drawRightSide();
void drawSide(int length, int initColumn);
void drawUserName(GAMEDATA data);

#endif // COLUMNUTILS_H_INCLUDED
