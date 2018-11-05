#ifndef USERNAMESCREENUTILS_H_INCLUDED
#define USERNAMESCREENUTILS_H_INCLUDED

#include <stdio.h>
#include "../Consts/Boolean.h"
#include "DrawUtils.h"

#define ASK_NAME_INIT_LINE 12
#define ASK_NAME_INIT_COLUMN 30
#define ASK_NAME_HEIGHT 5
#define ASK_NAME_LENGTH 60
#define ASK_NAME_BG_COLOR 15
#define ASK_NAME_BORDER_COLOR 4
#define ASK_NAME_LETTER_COLOR 0
#define NAME_MAX_LENGTH 45

void askUsername(char username[NAME_MAX_LENGTH]);
void drawUsernameScreen();

#endif // USERNAMESCREENUTILS_H_INCLUDED
