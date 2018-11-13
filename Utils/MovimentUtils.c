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

//Executa o movimento dos gatos conforme as distancias mapeadas na propriedade mapDistances do GAMEDATA
void moveCat(GAMEDATA* data){
    CAT* cat = data->cat;

    while(cat != NULL){
        if(!cat->immortal){
            int distanceRight, distanceLeft, distanceUp, distanceDown, bestDistanceRL,
            bestDistanceUD, selectedDistanceRL, selectedDistanceUD, selectedDistance;

            POSITION newPosition;

            char temp;

            distanceRight = data->mapDistances[cat->position.line][cat->position.column + 1];
            distanceLeft = data->mapDistances[cat->position.line][cat->position.column - 1];
            distanceUp = data->mapDistances[cat->position.line - 1][cat->position.column];
            distanceDown = data->mapDistances[cat->position.line + 1][cat->position.column];

            if(data->mouse.isDog){
                bestDistanceRL = getLongerDistance(distanceRight, distanceLeft, &selectedDistanceRL);
                bestDistanceUD = getLongerDistance(distanceUp, distanceDown, &selectedDistanceUD);
                getLongerDistance(bestDistanceRL, bestDistanceUD, &selectedDistance);
            } else{
                bestDistanceRL = getShorterDistance(distanceRight, distanceLeft, &selectedDistanceRL);
                bestDistanceUD = getShorterDistance(distanceUp, distanceDown, &selectedDistanceUD);
                getShorterDistance(bestDistanceRL, bestDistanceUD, &selectedDistance);
            }

            if(selectedDistance == 1){ //Distancia menor entre Direita e Esquerda
                newPosition.line = cat->position.line;
                if(selectedDistanceRL == 1){ //Distancia menor direita
                    newPosition.column = cat->position.column + 1;
                    cat->faceDirection = 1;
                } else if(selectedDistanceRL == 2){ //Distancia menor esquerda
                    newPosition.column = cat->position.column - 1;
                    cat->faceDirection = 0;
                }
            } else if (selectedDistance == 2){ //Distancia menor entre Cima e Baixo
                newPosition.column = cat->position.column;
                if(selectedDistanceUD == 1){ //Distancia menor Cima
                    newPosition.line = cat->position.line - 1;
                } else if(selectedDistanceUD == 2){ //Distancia menor Baixo
                    newPosition.line = cat->position.line + 1;
                }
            }

            if(selectedDistance == 1 || selectedDistance == 2){
                temp = data->gameMap[newPosition.line][newPosition.column];

                data->gameMap[newPosition.line][newPosition.column] = catCh;
                data->gameMap[cat->position.line][cat->position.column] = cat->overlaid;

                if (temp != mouseCh){
                    drawCat(newPosition.line, newPosition.column, cat->faceDirection, cat->immortal);
                }

                drawItemByCh(cat->overlaid, cat->position.line, cat->position.column, 0, 0, 0, 0);

                cat->position.line = newPosition.line;
                cat->position.column = newPosition.column;
                if(temp != mouseCh && temp != catCh){
                    cat->overlaid = temp;
                } else{
                    cat->overlaid = ' ';
                }
            }
        } else{
            //Calcula o tempo passado desde o inicio da imortalidade do gato
            clock_t elapsedTime = ((clock() - cat->start_immortal_time) / (CLOCKS_PER_SEC / 1000));

            if(elapsedTime > CAT_IMMORTAL_TIME){
                cat->immortal = FALSE;
            }
        }

        cat = cat->nextCat;
    }
}

//Calcula o menor valor entre 2 inteiros, considerando negativos como nulos.
//Caso os numeros sejam iguais retorna d1
//O ponteiro selected retorna 1 caso d1 seja menor, 2 caso d2 seja menor e
//0 caso ambos sejam negativos;
int getShorterDistance(int d1, int d2, int* selected){
    int shorterDistance;
    if(d1 >= 0 && d2 >= 0){
        if(d1 <= d2){
            shorterDistance = d1;
            *selected = 1;
        } else {
            shorterDistance = d2;
            *selected = 2;
        }
    } else if(d1 >= 0){
        shorterDistance = d1;
        *selected = 1;
    } else if(d2 >= 0){
        shorterDistance = d2;
        *selected = 2;
    } else{
        shorterDistance = -1;
        *selected = 0;
    }

    return shorterDistance;
}

//Calcula o maior valor entre 2 inteiros, considerando negativos como nulos.
//Caso os numeros sejam iguais retorna d1
//O ponteiro selected retorna 1 caso d1 seja maior, 2 caso d2 seja maior e
//0 caso ambos sejam negativos;
int getLongerDistance(int d1, int d2, int* selected){
    int longerDistance;
    if(d1 >= 0 && d2 >= 0){
        if(d1 >= d2){
            longerDistance = d1;
            *selected = 1;
        } else {
            longerDistance = d2;
            *selected = 2;
        }
    } else if(d1 >= 0){
        longerDistance = d1;
        *selected = 1;
    } else if(d2 >= 0){
        longerDistance = d2;
        *selected = 2;
    } else{
        longerDistance = -1;
        *selected = 0;
    }

    return longerDistance;
}

//Realiza o movimento do rato conforme a sua direcao atual
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

//Verifica se eh possivel atravessar um item do mapa
int isCrossing(char item){
    for (int x = 0; x < AMOUNT_OF_NOT_PASSABLE_ITENS; x++){
        if (nCrossingItens[x] == item){
            return 0;
        }
    }
    return 1;
}

//Decide a direcao da face do rato
void decideMouseDirection(GAMEDATA* data){
    if (isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column + 1]) && !isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column - 1])){
        data->mouse.faceDirection = 1;
    } else if(isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column - 1]) && !isCrossing(data->gameMap[data->mouse.position.line][data->mouse.position.column + 1])){
        data->mouse.faceDirection = 0;
    }
}

//Muda a posicao do rato
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
        updateFoodInfoOnScreen(*data);
    } else if(temp == boneCh){
        data->mouse.isDog = 1;
        data->mouse.start_time_dog = clock();
    } else{ //Devolve o Score e a contagem de queijos para a cor padrão
        textcolor(DEFAULT_TEXT_COLOR);
        updateScoreOnScreen(*data);
        updateFoodInfoOnScreen(*data);
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
