#include "HeaderUtils.h"

const char chSecondColor = '?';

//Desenha o cabeçalho do jogo
void drawHeader(){
    drawGameNameBackground();
    drawGameName();
}

//Desenha o nome do jogo no cabeçalho
void drawGameName(){
    drawM(GAME_NAME_INIT_LINE, GAME_NAME_INIT_COLUMN);
    int column = GAME_NAME_INIT_COLUMN + LETTER_LENGTH + 1;
    drawO(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawU(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawS(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawE(GAME_NAME_INIT_LINE, column);
    column += (LETTER_LENGTH * 2 - 1);
    drawT(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawR(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawA(GAME_NAME_INIT_LINE, column);
    column += LETTER_LENGTH + 1;
    drawP(GAME_NAME_INIT_LINE, column);
}

//Desenha o background do Header
void drawGameNameBackground(){
    drawGenericBackground(HEADER_HEIGHT, HEADER_LENGTH, GAME_NAME_BG_INIT_LINE, GAME_NAME_BG_INIT_COLUMN, HEADER_BG_COLOR,  HEADER_BG_BORDER_COLOR);
}

//Desenha uma letra conforme vetor passadi utilizando algumas pré-definições como tamanho da letra e cores
void drawLetter(int lineInit, int colInit, int itemVector[LETTER_HEIGHT][LETTER_LENGTH], char chVector[LETTER_HEIGHT][LETTER_LENGTH], int itemColor){
    drawMono(lineInit, colInit, LETTER_HEIGHT, LETTER_LENGTH, itemVector, chVector,
             itemColor, HEADER_CH_COLOR, HEADER_BG_COLOR, FALSE, ' ', TRUE, chSecondColor,
             HEADER_BG_BORDER_COLOR);
}

//Monta vetores para desenha o M
void drawM(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 0, 1, 1},
                                                    {1, 0, 1, 0, 1},
                                                    {1, 0, 1, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', chSecondColor, chSecondColor, chSecondColor, ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o O
void drawO(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '}};

    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o U
void drawU(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o S
void drawS(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 0},
                                                    {1, 1, 1, 1, 1},
                                                    {0, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o E
void drawE(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 0},
                                                    {1, 1, 1, 0, 0},
                                                    {1, 0, 0, 0, 0},
                                                    {1, 1, 1, 1, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o T
void drawT(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {0, 0, 1, 0, 0},
                                                    {0, 0, 1, 0, 0},
                                                    {0, 0, 1, 0, 0},
                                                    {0, 0, 1, 0, 0}};

    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {chSecondColor, chSecondColor, ' ', chSecondColor, chSecondColor}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o R
void drawR(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1},
                                                    {1, 0, 0, 1, 0},
                                                    {1, 0, 0, 1, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', chSecondColor, chSecondColor, ' ', ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o A
void drawA(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 0, 0, 0, 1}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', chSecondColor, chSecondColor, chSecondColor, ' '}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}

//Monta vetores para desenha o P
void drawP(int line, int col){
    int itemVector[LETTER_HEIGHT][LETTER_LENGTH] = {{1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 1},
                                                    {1, 1, 1, 1, 1},
                                                    {1, 0, 0, 0, 0},
                                                    {1, 0, 0, 0, 0}};
    char chvector[LETTER_HEIGHT][LETTER_LENGTH] = {{' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', ' ', ' ', ' ', ' '},
                                                   {' ', chSecondColor, chSecondColor, chSecondColor, chSecondColor}};
    drawLetter(line, col, itemVector, chvector, LETTER_COLOR);
}
