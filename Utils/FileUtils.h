#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../Consts/MapCharacters.h"
#include "../Consts/Boolean.h"
#include "../Structs/GameData.h"

#define MAX_PATH_LENGTH 260

void getDirectoryName(char directory[MAX_PATH_LENGTH], int level);
void readMap(int ln, int col, GAMEDATA *data);
int saveGame(GAMEDATA data);
int loadGame(GAMEDATA* data);
void createSaveGameDirectoryIFDoesntExists(char directory[MAX_PATH_LENGTH]);
int createSaveGameFile(GAMEDATA data, char directory[MAX_PATH_LENGTH]);

#endif // FILEUTILS_H_INCLUDED
