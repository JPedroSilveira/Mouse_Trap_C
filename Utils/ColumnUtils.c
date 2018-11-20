#include "ColumnUtils.h"

//Desenha as informa��es do estado do jogo (pontua��o, vidas, n�mero gatos, etc)
void drawGameInfo(GAMEDATA data){
    updateExecutionState(data);

    updateScoreOnScreen(data);

    updateLevelOnScreen(data);

    drawMouse(5, -12, TRUE, FALSE);

    updateLifesInfoOnScreen(data);

    drawCat(7, -12, TRUE, FALSE);

    updateCatsInfoOnScreen(data);

    updateFoodInfoOnScreen(data);

    cputsxy(7, 27, "[M] = Acessar o menu ");

    cputsxy(89, 9, "Tenha cuidado, fuja dos gatos!");

    cputsxy(89, 10, "Ou pegue os ossos e ataque!");

    cputsxy(89, 13, "Use as teclas direcionais,");

    cputsxy(89, 14, "ou A/W/S/D para movimento");

    cputsxy(89, 17, "Pegue todos os queijos e");

    cputsxy(89, 18, "avance de n�vel!");

    cputsxy(89, 21, "Tecle [B] para mover as portas");

    cputsxy(95, 26, "[P] Pausa o jogo.");
}

//Desenha o nome de usu�rio na tela
void drawUserName(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);

    gotoxy(33, 29);
    printf("%c%53c", '>','<');
    gotoxy(35, 29);
    printf("Jogador: %s", data.username);
}

//Atualiza a contagem de queijos restantes na tela
void updateFoodInfoOnScreen(GAMEDATA data){
    gotoxy(5, 25);
    printf("Queijos restantes: %d     ", data.nfood);
}

//Atualiza a pontua��o na tela
void updateScoreOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(8, 12);
    printf("Pontuacao: %d", data.score);
}

//Atualiza o n�vel do jogo na tela
void updateLevelOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(8, 14);
    printf("Nivel: %d", data.level);
}

//Atualiza o n�mero de vidas restantes na tela
void updateLifesInfoOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(12, 18);
    printf("x %d", data.mouse.nlifes);
}

//Atualiza o n�mero de gatos na tela
void updateCatsInfoOnScreen(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    gotoxy(12, 22);
    printf("x %d", data.ncats);
}

//Atualiza o estado do jogo na tela (pausado ou rodando)
void updateExecutionState(GAMEDATA data){
    textbackground(DEFAULT_BG_COLOR);
    if(data.paused){
        cputsxy(7, 9, "      [Pausado]     ");
    } else if(data.waitForUserInput){
        cputsxy(7, 9, "[Aguardando usu�rio]");
    } else{
        cputsxy(7, 9, "      [Rodando]     ");
    }
}

//Desenha as colunas laterais ao mapa na tela
void drawSideColumns(){
    drawRightSide();
    drawLeftSide();
    drawLineBetweenSides();
}

//Desenha uma barra inferior que liga as colunas direita e esquerda
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

//Desenha a coluna esquerda
void drawLeftSide(){
    int length = LEFT_SIDE_LAST_COLUMN - LEFT_SIDE_INIT_COLUMN;
    drawSide(length, LEFT_SIDE_INIT_COLUMN);
}

//Desenha a coluna direita
void drawRightSide(){
    int length = RIGHT_SIDE_LAST_COLUMN - RIGHT_SIDE_INIT_COLUMN;
    drawSide(length, RIGHT_SIDE_INIT_COLUMN);
}

//Desenha uma coluna baseado em um tamanho e em uma coluna inicial
void drawSide(int length, int initColumn){
    int itemVector[COLUMN_HEIGHT][length];
    char chVector[COLUMN_HEIGHT][length];

    for (int x = 0; x < COLUMN_HEIGHT; x++){
        for (int y = 0; y < length; y++){
            if (y == 0 || y == length - 1 || x == COLUMN_HEIGHT - 1){
                //Salva a cor da borda nas laterais do vetor
                itemVector[x][y] = BORDER_COLOR;
            } else{
                //Salva a cor de fundo nas outras partes do vetor
                itemVector[x][y] = BG_COLOR;
            }
            chVector[x][y] = ' ';
        }
    }

    //Desenha o vetor em tela
    drawMultiColor(SIDE_INIT_LINE, initColumn, COLUMN_HEIGHT, length, itemVector, chVector, 0);
}
