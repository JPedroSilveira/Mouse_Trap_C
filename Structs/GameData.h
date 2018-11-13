#ifndef GAMEDATA_H_INCLUDED
#define GAMEDATA_H_INCLUDED

#include "../Consts/MapDimensions.h"
#include "Mouse.h"
#include "Door.h"
#include "Cat.h"

#define NAME_MAX_LENGTH 45
#define DOOR_AMOUNT 7

//Representa as informações de estado do jogo
// - paused: Representa se o jogo está pausado (1) ou não (0)
// - level: Representa o nível atual do jogo
// - gameOver: Representa se a partida foi finalizada (1) ou não (0)
// - menuOpened: Representa se o menu está aberto (1) ou não (0)
// - exitGame: Representa se o jogo foi finalizado (1) ou não (0)
// - score: Representa a pontuação atual do jogador
// - ncats: Representa o número de gatos no mapa
// - ndoors: Representa o número de portas no jogo
// - doorsOpened: Representa se as portas devem estar abertas(1) ou não(0)
// - waitForUserInput: Utilizada para aguardar por entrada do usuário antes de realizar uma ação
// - nfood: Represeta o número de comidas no jogo
// - updateLevel: Representa se o nível deve ser aumentado(1) ou não(0)
// - win: Representa se o jogador ganhou o jogo (ganhou todos os mapas)(1) ou não(0)
// - mapDistances: Representa um mapa com as distâncias das posições percorridas para o rato
// - gameMap: Representa o mapa do jogo
// - username: Representa o nome do usuário
// - door: Representa um ponteiro para a primeira porta da lista do jogo
// - cat: Representa um ponteiro para o primeiro gato da lista do jogo
// - mouse: Representa as informações do rato no jogo
typedef struct GameData
{
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
