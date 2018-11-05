#include "ColumnUtils.h"

void drawGameInfo(GAMEDATA data){
    updateExecutionState(data);

    updateScoreOnScreen(data);

    updateLevelOnScreen(data);

    drawMouse(5, -12, TRUE, FALSE);

    updateLifesInfoOnScreen(data);

    drawCat(7, -12, TRUE, FALSE);

    updateCatsInfoOnScreen(data);

    cputsxy(7, 27, "[M] = Acessar o menu");

    cputsxy(89, 9, "Tenha cuidado, fuja dos gatos!");

    cputsxy(95, 15, "[P] Pausa o jogo.");
}

void drawUserName(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);

    gotoxy(33, 29);
    printf("%c%53c", '>','<');
    gotoxy(35, 29);
    printf("Jogador: %s", data.username);
}

void updateScoreOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(8, 12);
    printf("Pontuacao: %d", data.score);
}

void updateLevelOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(8, 14);
    printf("Nivel: %d", data.level);
}

void updateLifesInfoOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(12, 18);
    printf("x %d", data.mouse.nlifes);
}

void updateCatsInfoOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(12, 22);
    printf("x %d", data.ncats);
}

void updateExecutionState(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    if(data.paused){
        cputsxy(12, 9, "[Pausado]");
    } else {
        cputsxy(12, 9, "[Rodando]");
    }
}

void drawSideColumns(){
    drawRightSide();
    drawLeftSide();
    drawLineBetweenSides();
}

void drawLineBetweenSides(){
    int itemVector[1][LAST_COLUMN];
    char chVector[1][LAST_COLUMN];

    for (int y = 0; y < LAST_COLUMN; y++)
    {
        itemVector[0][y] = BORDER_COLOR;
        chVector[0][y] = ' ';
    }

    drawMultiColor(LAST_LINE, 1, 1, LAST_COLUMN, itemVector, chVector, 0);
}

void drawLeftSide(){
    int length = LEFT_SIDE_LAST_COLUMN - LEFT_SIDE_INIT_COLUMN;
    drawSide(length, LEFT_SIDE_INIT_COLUMN);
}

void drawRightSide(){
    int length = RIGHT_SIDE_LAST_COLUMN - RIGHT_SIDE_INIT_COLUMN;
    drawSide(length, RIGHT_SIDE_INIT_COLUMN);
}

void drawSide(int length, int initColumn){
    int itemVector[COLUMN_HEIGHT][length];
    char chVector[COLUMN_HEIGHT][length];

    for (int x = 0; x < COLUMN_HEIGHT; x++)
    {
        for (int y = 0; y < length; y++)
        {
            if (y == 0 || y == length - 1 || x == COLUMN_HEIGHT - 1)
            {
                itemVector[x][y] = BORDER_COLOR;
            }
            else
            {
                itemVector[x][y] = BG_COLOR;
            }
            chVector[x][y] = ' ';
        }
    }

    drawMultiColor(SIDE_INIT_LINE, initColumn, COLUMN_HEIGHT, length, itemVector, chVector, 0);
}
