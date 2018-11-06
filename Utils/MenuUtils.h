#ifndef MENUUTILS_H_INCLUDED
#define MENUUTILS_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "../Consts/InputCharactersCode.h"
#include "../Consts/Boolean.h"
#include "../Structs/GameData.h"
#include "DrawUtils.h"
#include "UserInputUtils.h"
#include "MapUtils.h"

#define MENU_INIT_LINE 8
#define MENU_INIT_COLUMN 37
#define MENU_HEIGHT 20
#define MENU_LENGTH 46
#define MENU_BG_COLOR 0
#define MENU_CH_COLOR 0
#define MENU_BORDER_COLOR 14
#define MENU_TEXT_COLOR 15

void openMenu(GAMEDATA* data);
void executeMenuChoice(GAMEDATA *data);
void drawMenu();
void drawMenuBG();
void drawMenuText();
char waitForMenuOption();

#endif // MENUUTILS_H_INCLUDED
