#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <time.h>
#include "Position.h"

//Defini��es de DIRECTION_CODE
#define MOUSE_STOP_DIRECTION_CODE 0
#define MOUSE_RIGHT_DIRECTION_CODE 1
#define MOUSE_LEFT_DIRECTION_CODE 2
#define MOUSE_UP_DIRECTION_CODE 3
#define MOUSE_DOWN_DIRECTION_CODE 4

//Representa o rato e suas informa��es no jogo
// - faceDirection: Representa a dire��o da "face" do rato, 1 para direta e 0 para esquerda
// - nlifes: Representa o n�mero de vidas restantes do rato
// - direction: Representa a dire��o para a qual o rato est� andando. Respeita as defini��es de "DIRECTION_CODE"
// - isDog: Representa se o rato est� no estado de cachorro(1) ou n�o(0)
// - position: Representa a posi��o atual do rato no mapa
// - initialPosition: Representa a posi��o inicial do rato no jogo
// - start_time_dog: Representa o hor�rio no qual o rato virou cachorro
// - overlaid: Representa o elemento do jogo sobreposta pelo rato
typedef struct Mouse{
    int faceDirection, nlifes, direction, isDog;
    POSITION position, initialPosition;
    clock_t start_time_dog;
    char overlaid;
}MOUSE;


#endif // MOUSE_H_INCLUDED
