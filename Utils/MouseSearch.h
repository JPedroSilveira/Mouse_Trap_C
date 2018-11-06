#ifndef MOUSESEARCH_H_INCLUDED
#define MOUSESEARCH_H_INCLUDED

#include "../Consts/MapDimensions.h"
#include "../Structs/GameData.h""

void mapDistances(GAMEDATA* data);
void recursiveSearch(GAMEDATA* data, int distance, int line, int column, int comeFrom);
int newDistanceIsLower(GAMEDATA data, int line, int column, int distance);

#endif // MOUSESEARCH_H_INCLUDED
