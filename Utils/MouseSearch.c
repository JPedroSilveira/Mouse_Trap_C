#include "MouseSearch.h"
//Calcula a distância de todos os pontos passíveis de acesso ao rato
void mapDistances(GAMEDATA* data){
    for(int y = 0; y < MAP_LINES; y++){
        for(int x = 0; x < MAP_COLUMNS; x++){
            data->mapDistances[y][x] = -1;
        }
    }

    //Salva a posição do rato como distância 0
    data->mapDistances[data->mouse.position.line][data->mouse.position.column] = 0;

    //Inicia a busca recursiva com a posição do rato
    recursiveSearch(data, 0, data->mouse.position.line, data->mouse.position.column, 0);
}

//Calcula recursivamente a distância de cada ponto
//comeFrom
//0 = Mouse
//1 = Right
//2 = Left
//3 = Up
//4 = Down
void recursiveSearch(GAMEDATA* data, int distance, int line, int column, int comeFrom){
    distance++;

    if (comeFrom != 1 && isCrossing(data->gameMap[line][column + 1]) && newDistanceIsLower(*data, line, column + 1, distance)){
        data->mapDistances[line][column + 1] = distance;
        recursiveSearch(data, distance, line, column + 1, 2);
    }


    if (comeFrom != 2 && isCrossing(data->gameMap[line][column - 1]) && newDistanceIsLower(*data, line, column - 1, distance)){
        data->mapDistances[line][column - 1] = distance;
        recursiveSearch(data, distance, line, column - 1, 1);
    }

    if (comeFrom != 3 && isCrossing(data->gameMap[line - 1][column]) && newDistanceIsLower(*data, line - 1, column, distance)){
        data->mapDistances[line - 1][column] = distance;
        recursiveSearch(data, distance, line - 1, column, 4);
    }

    if (comeFrom != 4 && isCrossing(data->gameMap[line + 1][column]) && newDistanceIsLower(*data, line + 1, column, distance)){
        data->mapDistances[line + 1][column] = distance;
        recursiveSearch(data, distance, line + 1, column, 3);
    }

}

//Retorna se a distância atual do vetor é menor que a nova
int newDistanceIsLower(GAMEDATA data, int line, int column, int distance){
    return data.mapDistances[line][column] == -1 || data.mapDistances[line][column]  > distance;
}
