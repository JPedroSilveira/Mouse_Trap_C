#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <time.h>
#include "Position.h"

//Definições de DIRECTION_CODE
#define MOUSE_STOP_DIRECTION_CODE 0
#define MOUSE_RIGHT_DIRECTION_CODE 1
#define MOUSE_LEFT_DIRECTION_CODE 2
#define MOUSE_UP_DIRECTION_CODE 3
#define MOUSE_DOWN_DIRECTION_CODE 4

//Representa o rato e suas informações no jogo
// - faceDirection: Representa a direção da "face" do rato, 1 para direta e 0 para esquerda
// - nlifes: Representa o número de vidas restantes do rato
// - direction: Representa a direção para a qual o rato está andando. Respeita as definições de "DIRECTION_CODE"
// - isDog: Representa se o rato está no estado de cachorro(1) ou não(0)
// - position: Representa a posição atual do rato no mapa
// - initialPosition: Representa a posição inicial do rato no jogo
// - start_time_dog: Representa o horário no qual o rato virou cachorro
// - overlaid: Representa o elemento do jogo sobreposta pelo rato
typedef struct Mouse{
    int faceDirection, nlifes, direction, isDog;
    POSITION position, initialPosition;
    clock_t start_time_dog;
    char overlaid;
}MOUSE;


#endif // MOUSE_H_INCLUDED
