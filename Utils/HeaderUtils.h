#ifndef HEADERUTILS_H_INCLUDED
#define HEADERUTILS_H_INCLUDED

#include "../Consts/Boolean.h"
#include "DrawUtils.h"
#include "MapUtils.h"

#define GAME_NAME_BG_INIT_LINE 1
#define GAME_NAME_BG_INIT_COLUMN 1

#define GAME_NAME_INIT_LINE 2
#define GAME_NAME_INIT_COLUMN 32

#define HEADER_HEIGHT 6
#define HEADER_LENGTH 120

#define HEADER_BG_BORDER_COLOR 4
#define HEADER_BG_COLOR 1
#define HEADER_CH_COLOR 4

#define LETTER_LENGTH 5
#define LETTER_HEIGHT 5
#define LETTER_COLOR 14

void drawHeader();
void drawGameNameBackground();
void drawGameName();
void drawLetter(int lineInit, int colInit, int itemVector[LETTER_HEIGHT][LETTER_LENGTH], char chVector[LETTER_HEIGHT][LETTER_LENGTH], int itemColor);
void drawM(int line, int col);
void drawO(int line, int col);
void drawU(int line, int col);
void drawS(int line, int col);
void drawE(int line, int col);
void drawT(int line, int col);
void drawR(int line, int col);
void drawA(int line, int col);
void drawP(int line, int col);

#endif // HEADERUTILS_H_INCLUDED
