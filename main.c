#include <windows.h>

#include "Structs/GameData.h"
#include "Utils/HeaderUtils.h"
#include "Utils/MapUtils.h"
#include "Utils/GameCoreUtils.h"
#include "Utils/ColumnUtils.h"

int hideCursor();

int main(){

    //Configura a semente para geração de valores aleatórios
    srand(time(NULL));

    //Configura posição e tamanho do terminal
    HWND wh = GetConsoleWindow();
    MoveWindow(wh, 600, 350, 994, 520, TRUE);

    //"Esconde" o cursor
    hideCursor();

    GAMEDATA data;

    //Desenha o cabeçalho
    drawHeader();

    //Inicializa as informações de estado do jogo
    startGameData(&data, INIT_LEVEL, 0, INIT_LIFE_AMOUNT, TRUE);

    //Desenha as colunas laterais e suas bordas
    drawSideColumns();

    //Desenha as informações básicas do jogo nas colunas laterais
    drawGameInfo(data);

    //Desenha tela solicitando o nome do usuário
    drawUserName(data);

    //Inicializa o jogo
    startGameCore(&data);

    return 0;
}

//Esconde o cursor do teclado
int hideCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(consoleHandle, &info);
}
