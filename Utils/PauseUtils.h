#ifndef PAUSEUTILS_H_INCLUDED
#define PAUSEUTILS_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "../Consts/Boolean.h"
#include "MapUtils.h"
#include "UserInputUtils.h"

#define PAUSE_SCREEN_HEIGHT 10
#define PAUSE_SCREEN_LENGTH 46
#define PAUSE_SCREEN_BACKGROUND_COLOR 0
#define PAUSE_SCREEN_INIT_LINE 8
#define PAUSE_SCREEN_INIT_COLUMN 37
#define PAUSE_SCREEN_CH_COLOR 0
#define PAUSE_SCREEN_BORDER_COLOR 14
#define PAUSE_SCREEN_TEXT_COLOR 15

void pauseGame(GAMEDATA *data);
void drawPauseScreen();
void drawPauseScreenBackground();
void drawPauseScreenText();

#endif // PAUSEUTILS_H_INCLUDED
