#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED

#include "../Consts/MapDimensions.h"
#include "Mouse.h"
#include "Door.h"
#include "Cat.h"

#define NAME_MAX_LENGTH 45
#define DOOR_AMOUNT 7

//Representa as informa��es de estado do jogo
// - paused: Representa se o jogo est� pausado (1) ou n�o (0)
// - level: Representa o n�vel atual do jogo
// - gameOver: Representa se a partida foi finalizada (1) ou n�o (0)
// - menuOpened: Representa se o menu est� aberto (1) ou n�o (0)
// - exitGame: Representa se o jogo foi finalizado (1) ou n�o (0)
// - score: Representa a pontua��o atual do jogador
// - ncats: Representa o n�mero de gatos no mapa
// - ndoors: Representa o n�mero de portas no jogo
// - doorsOpened: Representa se as portas devem estar abertas(1) ou n�o(0)
// - waitForUserInput: Utilizada para aguardar por entrada do usu�rio antes de realizar uma a��o
// - nfood: Represeta o n�mero de comidas no jogo
// - updateLevel: Representa se o n�vel deve ser aumentado(1) ou n�o(0)
// - win: Representa se o jogador ganhou o jogo (ganhou todos os mapas)(1) ou n�o(0)
// - mapDistances: Representa um mapa com as dist�ncias das posi��es percorridas para o rato
// - gameMap: Representa o mapa do jogo
// - username: Representa o nome do usu�rio
// - door: Representa um ponteiro para a primeira porta da lista do jogo
// - cat: Representa um ponteiro para o primeiro gato da lista do jogo
// - mouse: Representa as informa��es do rato no jogo
typedef struct GameData{
   int paused, level,
        gameOver, menuOpened,
        exitGame, score, ncats, ndoors,
        doorsOpened, waitForUserInput,
        nfood, updateLevel, win,
        mapDistances[MAP_LINES][MAP_COLUMNS];
   char gameMap[MAP_LINES][MAP_COLUMNS], username[NAME_MAX_LENGTH];
   DOOR* door;
   CAT* cat;
   MOUSE mouse;
}GAMEDATA;

#endif // GAMEDATA_H_INCLUDED
