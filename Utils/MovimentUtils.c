#include "MovimentUtils.h"

void moveDoors(GAMEDATA *data){
    DOOR *door = data->door;
    int newLine, newColumn;

    while(door->exists){
        if(data->doorsOpen == door->opened){
            if(door->opened){
                newLine = door->line - DOOR_D_DISPL;
                newColumn = door->column - DOOR_R_DISPL;
            } else {
                newLine = door->line + DOOR_D_DISPL;
                newColumn = door->column + DOOR_R_DISPL;
            }
            char oldDoorPositionItem = data->gameMap[door->line][door->column];
            char newDoorPositionItem = data->gameMap[newLine][newColumn];

            if(newDoorPositionItem != mouseCh && newDoorPositionItem != catCh){
                drawDoor(newLine, newColumn);
                drawItemByCh(door->overlaid, door->line, door->column, 0, 0, 0, 0);
                data->gameMap[door->line][door->column] = door->overlaid;
                data->gameMap[newLine][newColumn] = oldDoorPositionItem;
                door->opened = !door->opened;
                door->overlaid = newDoorPositionItem;
                door->line = newLine;
                door->column = newColumn;
            }
        }

        door = door->nextDoor;
    }

    data->doorsOpen = !data->doorsOpen;
}

void moveCat(GAMEDATA *data){

}

void moveMouse(GAMEDATA *data){
    switch(data->mouse.direction){
        case MOUSE_RIGHT_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.line][data->mouse.column + 1])){
                changeMousePosition(0, 1, 1, data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_LEFT_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.line][data->mouse.column - 1])){
                changeMousePosition(0, -1, 0, data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_UP_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.line - 1][data->mouse.column])){
                changeMousePosition(-1, 0, 0, data);
                decideMouseDirection(data);
            } else {
                data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            }
            break;
        case MOUSE_DOWN_DIRECTION_CODE:
            if(isCrossing(data->gameMap[data->mouse.line + 1][data->mouse.column])){
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
    for(int x = 0; x < AMOUNT_OF_NOT_PASSABLE_ITENS; x++){
        if(nCrossingItens[x] == item){
            return 0;
        }
    }
    return 1;
}

void decideMouseDirection(GAMEDATA *data){
    if(isCrossing(data->gameMap[data->mouse.line][data->mouse.column + 1]) && !isCrossing(data->gameMap[data->mouse.line][data->mouse.column - 1])){
        data->mouse.faceDirection = 1;
    } else if (isCrossing(data->gameMap[data->mouse.line][data->mouse.column - 1]) && !isCrossing(data->gameMap[data->mouse.line][data->mouse.column + 1])){
        data->mouse.faceDirection = 0;
    }
}

void changeMousePosition(int lineIncrease, int columnIncrease, int faceDirection, GAMEDATA *data){
    int newLine = data->mouse.line + lineIncrease;
    int newColumn = data->mouse.column + columnIncrease;

    char temp = data->gameMap[newLine][newColumn];

    if(temp == foodCh){
        data->score += SCORE_FOR_FOOD;
        data->nfood--;
        if(data->nfood <= 0){
            data->updateLevel = TRUE;
        }
        textcolor(SCORE_TEXT_COLOR_ON_UPDATE);
        updateScoreOnScreen(*data);
    }else if(temp == boneCh){
        data->mouse.isDog = 1;
        data->mouse.start_time_dog = clock();
    }else{ //Devolve o Score para a cor padrão
        textcolor(DEFAULT_TEXT_COLOR);
        updateScoreOnScreen(*data);
    }

    data->gameMap[newLine][newColumn] = mouseCh;
    data->gameMap[data->mouse.line][data->mouse.column] = data->mouse.overlaid;

    if(temp != catCh || data->mouse.isDog){
        drawMouse(newLine, newColumn, faceDirection, data->mouse.isDog);
    }

    if(data->mouse.overlaid == catCh){
        CAT cat = getCatByPosition(*data, data->mouse.line, data->mouse.column);
        drawItemByCh(data->mouse.overlaid, data->mouse.line, data->mouse.column, cat.faceDirection, 0, 0, cat.immortal);
    } else {
        drawEmpty(data->mouse.line, data->mouse.column);
    }

    data->mouse.line = newLine;
    data->mouse.column = newColumn;
    data->mouse.faceDirection = faceDirection;
    data->mouse.overlaid = ' ';
}
