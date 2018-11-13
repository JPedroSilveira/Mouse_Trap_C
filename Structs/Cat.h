#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED

#include "Position.h"

//Estrutura para representar as informa��es do GATO no jogo
// - faceDirection: Representa a dire��o da "face" do gato, 1 para direta e 0 para esquerda
// - immortal: Representa se o gato est� em um estado de imortalidade
// - position: Representa a posi��o atual do gato
// - initialPosition: Representa a posi��o inicial do gato no jogo
// - overlaid: Representa um elemento sobreposto pelo gato
// - start_immortal_time: Representa o hor�rio em que o gato iniciou seu estado de imortalidade
// - nextCat: Ponteiro para o pr�ximo gato da lista
typedef struct Cat
{
    int faceDirection, immortal;
    POSITION position, initialPosition;
    char overlaid;
    clock_t start_immortal_time;
    struct Cat* nextCat;
}CAT;

#endif // CAT_H_INCLUDED
