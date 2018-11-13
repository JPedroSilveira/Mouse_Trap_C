#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Position.h"

//Representa a porta e suas informações dentro do jogo
// - opened: 1 para porta aberta(na posição inicial) e 2 para porta fechado
// - position: Representa a posição atual da porta
// - overlaid: Representa um elemento do jogo sobreposto pela porta
// - nextDoor: Ponteiro para a próxima porta da lista
typedef struct Door
{
   int opened;
   POSITION position;
   char overlaid;
   struct Door* nextDoor;
}DOOR;

#endif // DOOR_H_INCLUDED
