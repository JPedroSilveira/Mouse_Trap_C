#include "MapUtils.h"

//Desenha o vetor do mapa na tela
void drawMap(GAMEDATA* data, int mouseToRight){
    int catFaceDirection = 0, catIsImmortal = FALSE;

    for (int i = 0; i < MAP_LINES; i++){
        for (int j = 0; j < MAP_COLUMNS; j++){
            if(data->gameMap[i][j] == catCh){
                CAT cat = getCatByPosition(*data, i, j);
                catFaceDirection = cat.faceDirection;
                catIsImmortal = cat.immortal;
            }
            drawItemByCh(data->gameMap[i][j], i, j, catFaceDirection, mouseToRight, data->mouse.isDog, catIsImmortal);
        }
    }
}

//Retorna o gato que estiver em uma determinada localiza��o (linha x coluna)
CAT getCatByPosition(GAMEDATA data, int line, int column){
    CAT* cat = data.cat;

    while (cat != NULL){
        if (cat->position.line == line && cat->position.column == column){
            return *cat;
        }

        cat = cat->nextCat;
    }

    return *cat;
}

//Dsenha um item do mapa em tela pelo caracter passado (Ex.: G => Gato)
void drawItemByCh(char ch, int line, int column, int catToRight, int mouseToRight, int mouseIsDog, int catIsImmortal){
    switch (ch)
    {
        case ' ':
            drawEmpty(line, column);
            break;
        case 'M':
            drawMouse(line, column, mouseToRight, mouseIsDog);
            break;
        case 'T':
            drawDoor(line, column);
            break;
        case 'G':
            drawCat(line, column, catToRight, catIsImmortal);
            break;
        case 'O':
            drawBone(line, column);
            break;
        case 'X':
            drawWall(line, column);
            break;
        case 'Q':
            drawFood(line, column);
            break;
    }
}

//Converte uma localiza��o X do mapa vetor para uma localiza��o do mapa na tela
int convertXToDrawPosition(int x){
    return MAP_INIT_COLUMN + (x * MAP_ITEM_LENGTH);
}

//Converte uma localiza��o Y do mapa vetor para uma localiza��o do mapa na tela
int convertYToDrawPosition(int y){
    return MAP_INIT_LINE + (y * MAP_ITEM_LENGTH);
}

//Desenha uma parede em uma posi��o (linha x coluna)
void drawWall(int line, int col){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{1, 1}, {1, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{' ', ' '}, {' ', ' '}};
    drawMapItem(line, col, itemVector, chvector, WALL_COLOR, WALL_CH_COLOR);
}

//Desenha um rato em uma posi��o (linha x coluna)
void drawMouse(int line, int col, int toRight, int isDog){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{!toRight, toRight}, {1, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{'o', 'o'}, {'u', 'u'}};
    int chColor = MOUSE_CH_COLOR;
    int bgColor = MOUSE_COLOR;
    if (isDog){
        chColor = MOUSE_DOG_CH_COLOR;
        bgColor = MOUSE_DOG_COLOR;
    }
    drawMapItem(line, col, itemVector, chvector, bgColor, chColor);
}

//Desenha uma comida em uma posi��o (linha x coluna)
void drawFood(int line, int col){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{0, 0}, {0, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{' ', ' '}, {' ', 'o'}};
    drawMapItem(line, col, itemVector, chvector, FOOD_COLOR, FOOD_CH_COLOR);
}

//Desenha um osso em uma posi��o (linha x coluna)
void drawBone(int line, int col){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{0, 0}, {0, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{' ', ' '}, {'+', '+'}};
    drawMapItem(line, col, itemVector, chvector, BONE_COLOR, BONE_CH_COLOR);
}

//Desenha um gato em uma posi��o (linha x coluna)
void drawCat(int line, int col, int toRight, int isImmortal){
    int chColor = CAT_CH_COLOR;
    int color = CAT_COLOR;
    if(isImmortal){
        chColor = CAT_IMMORTAL_CH_COLOR;
        color = CAT_IMMORTAL_COLOR;
    }
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{!toRight, toRight}, {1, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{'>', '<'}, {'U', 'U'}};
    drawMapItem(line, col, itemVector, chvector, color, chColor);
}

//Desenha uma porta em uma posi��o (linha x coluna)
void drawDoor(int line, int col){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{1, 1}, {1, 1}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{'o', ' '}, {'=', '='}};
    drawMapItem(line, col, itemVector, chvector, DOOR_COLOR, DOOR_CH_COLOR);
}

//Desenha um espa�o vazio em uma posi��o (linha x coluna)
void drawEmpty(int line, int col){
    int itemVector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{0, 0}, {0, 0}};
    char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH] = {{' ', ' '}, {' ', ' '}};
    drawMapItem(line, col, itemVector, chvector, EMPTY_COLOR, EMPTY_CH_COLOR);
}

//Desenha um item do mapa com as configura��es padr�o de posi��o
void drawMapItem(int lineInit, int colInit, int colorvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH], char chvector[MAP_ITEM_HEIGHT][MAP_ITEM_LENGTH], int background, int color){
    drawMono(convertYToDrawPosition(lineInit), convertXToDrawPosition(colInit),
              MAP_ITEM_HEIGHT, MAP_ITEM_LENGTH, colorvector, chvector, background,
              color, DEFAULT_ITEM_BG_COLOR, FALSE, ' ', FALSE, ' ', 0);
}
