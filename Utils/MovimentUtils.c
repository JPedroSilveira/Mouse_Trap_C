#include "MovimentUtils.h"

//Executa o movimento das portas, abrindo ou fechando
void moveDoors(GAMEDATA* data){
    DOOR* door = data->door;
    int newLine, newColumn;

    while (door != NULL){
        if (data->doorsOpened == door->opened){
            if (door->opened){
                newLine = door->position.line - DOOR_D_DISPL;
                newColumn = door->position.column - DOOR_R_DISPL;
            } else{
                newLine = door->position.line + DOOR_D_DISPL;
                newColumn = door->position.column + DOOR_R_DISPL;
            }
            char oldDoorPositionItem = data->gameMap[door->position.line][door->position.column];
            char newDoorPositionItem = data->gameMap[newLine][newColumn];

            if (newDoorPositionItem != mouseCh && newDoorPositionItem != catCh){
                drawDoor(newLine, newColumn);
                drawItemByCh(door->overlaid, door->position.line, door->position.column, 0, 0, 0, 0);
                data->gameMap[door->position.line][door->position.column] = door->overlaid;
                data->gameMap[newLine][newColumn] = oldDoorPositionItem;
                door->opened = !door->opened;
                door->overlaid = newDoorPositionItem;
                door->position.line = newLine;
                door->position.column = newColumn;
            }
        }

        door = door->nextDoor;
    }

    data->doorsOpened = !data->doorsOpened;
    mapDistances(data);
}

void moveCat(GAMEDATA* data){

}

int generateRandomDirection(){
    return rand() % (MOUSE_MAX_DIRECTION_NUMBER + 1 - MOUSE_MIN_DIRECTION_NUMBER) + MOUSE_MIN_DIRECTION_NUMBER;
}

void moveMouse(GAMEDATA* data){
    switch (data->mouse.direction){
        case MOUSE_RIGHT_DIRECTION_CODE:
            if (isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column + 1])){
                changeMousePosition(0, 1, 1, data);
            } else{
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_LEFT_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column - 1])){
                changeMousePosition(0, -1, 0, data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_UP_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.position.line - 1][data->mouse.position.column])){
                changeMousePosition(-1, 0, 0, data);
                decideMouseDirection(data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_DOWN_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.position.line + 1][data->mouse.position.column])){
                changeMousePosition(1, 0, 0, data);
                decideMouseDirection(data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        default:
            textcolor(DEFAULT_TEXT_COLOR);
            updateScoreOnScreen(*data);
            break;
    }
}

int isCrossing(char item){
    for (int x = 0; x < AMOUNT_OF_NOT_PASSABLE_ITENS; x++){
        if (nCrossingItens[x] == item){
            return 0;
        }
    }
    return 1;
}

void decideMouseDirection(GAMEDATA* data){
    if (isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column + 1]) && !isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column - 1])){
        data->mouse.faceDirection = 1;
    } else if(isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column - 1]) && !isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column + 1])){
        data->mouse.faceDirection = 0;
    }
}

void changeMousePosition(int lineIncrease, int columnIncrease, int faceDirection, GAMEDATA* data){
    int newLine = data->mouse.position.line + lineIncrease;
    int newColumn = data->mouse.position.column + columnIncrease;

    char temp = data->gameMap[newLine][newColumn];

    if (temp == foodCh){
        data->score += SCORE_FOR_FOOD;
        data->nfood--;
        if(data->nfood <= 0){
            data->updateLevel = TRUE;
        }
        textcolor(SCORE_TEXT_COLOR_ON_UPDATE);
        updateScoreOnScreen(*data);
    } else if(temp == boneCh){
        data->mouse.isDog = 1;
        data->mouse.start_time_dog = clock();
    } else{ //Devolve o Score para a cor padrão
        textcolor(DEFAULT_TEXT_COLOR);
        updateScoreOnScreen(*data);
    }

    data->gameMap[newLine][newColumn] = mouseCh;
    data->gameMap[data->mouse.position.line][data->mouse.position.column] = data->mouse.overlaid;

    if (temp != catCh || data->mouse.isDog){
        drawMouse(newLine, newColumn, faceDirection, data->mouse.isDog);
    }

    if (data->mouse.overlaid == catCh){
        CAT cat = getCatByPosition(*data, data->mouse.position.line, data->mouse.position.column);
        drawItemByCh(data->mouse.overlaid, data->mouse.position.line, data->mouse.position.column, cat.faceDirection, 0, 0, cat.immortal);
    } else{
        drawEmpty(data->mouse.position.line, data->mouse.position.column);
    }

    data->mouse.position.line = newLine;
    data->mouse.position.column = newColumn;
    data->mouse.faceDirection = faceDirection;
    data->mouse.overlaid = ' ';
}
