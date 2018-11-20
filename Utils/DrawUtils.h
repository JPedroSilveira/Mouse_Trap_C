#ifndef DRAWUTILS_H_INCLUDED
#define DRAWUTILS_H_INCLUDED

#define DEFAULT_TEXT_COLOR 15
#define DEFAULT_BG_COLOR 0

void drawMono(int lineInit, int colInit, int height, int length, int itemVector[height][length],
              char chvector[height][length], int itemColor, int letterColor, int bgColor, int hasBgCh, char bgCh,
              int hasSecondColor, char chSecondColor, int segundColor);

void drawMultiColor(int lineInit, int colInit, int height, int length, int itemVector[height][length], char chvector[height][length], int letterColor);

void drawGenericBackground(int height, int length, int startLine, int startColumn, int color, int borderColor);

#endif // DRAWUTILS_H_INCLUDED
