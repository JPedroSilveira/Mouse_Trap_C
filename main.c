#include "Structs/GameData.h"
#include "Utils/HeaderUtils.h"
#include "Utils/MapUtils.h"
#include "Utils/GameCoreUtils.h"
#include "Utils/ColumnUtils.h"

int hideCursor();

int main(){
    hideCursor();

    GAMEDATA data;

    drawHeader();

    startGameData(&data, INIT_LEVEL, 0, INIT_LIFE_AMOUNT, TRUE);

    drawSideColumns();

    drawGameInfo(data);

    drawUserName(data);

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
