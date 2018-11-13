#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Position.h"

//Representa a porta e suas informa��es dentro do jogo
// - opened: 1 para porta aberta(na posi��o inicial) e 2 para porta fechado
// - position: Representa a posi��o atual da porta
// - overlaid: Representa um elemento do jogo sobreposto pela porta
// - nextDoor: Ponteiro para a pr�xima porta da lista
typedef struct Door
{
   int opened;
   POSITION position;
   char overlaid;
   struct Door* nextDoor;
}DOOR;

#endif // DOOR_H_INCLUDED
