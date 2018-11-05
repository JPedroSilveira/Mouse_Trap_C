#ifndef GAMECOREUTILS_H_INCLUDED
#define GAMECOREUTILS_H_INCLUDED

#define TIME_TO_MOVE_MOUSE 100
#define LIMIT_TIME_OF_DOG 5000
#define TIME_TO_SLEEP_AFTER_DEATH 1000
#define SCORE_FOR_CAT 50
#define IMMORTAL_TIME_CAT 3000
#define TIME_TO_SLEEP_WHEN_UPDATE_LEVEL 1500
#define GAME_OVER_WAIT_TIME 2000

#include <time.h>
#include "../Consts/GameStartData.h"
#include "../Consts/InputCharactersCode.h"
#include "../Consts/Boolean.h"
#include "FileUtils.h"
#include "UsernameScreenUtils.h"
#include "PauseUtils.h"
#include "MovimentUtils.h"
#include "ColumnUtils.h"
#include "MapUtils.h"

void startGameCore(GAMEDATA *data);
void updateLevel(GAMEDATA* data);
void freeOldData(GAMEDATA* data);
void verifyClash(GAMEDATA *data);
void restartWithNewLife(GAMEDATA* data);
void cleanScreen();
void startGameData(GAMEDATA *data, int level, int score, int nlifes, int askName);
void takeDecision(GAMEDATA *data, int userInput);
void takeDecisionDirectionalKeys(GAMEDATA *data);
void drawDeathMessage();
void drawDeathMessageBG();
void drawUpLevelMessage();
void drawUpLevelBG();
void drawGameOverMessage(GAMEDATA* data);
void drawGameOverBG();

#endif // GAMECOREUTILS_H_INCLUDED
