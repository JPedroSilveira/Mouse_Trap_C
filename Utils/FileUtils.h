#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#include "../Consts/MapCharacters.h"
#include "../Consts/Boolean.h"
#include "../Consts/InputCharactersCode.h"

#include "../Structs/GameData.h"

#define MAX_PATH_LENGTH 260
#define MAX_FILES 100
#define MAX_FILE_NAME 100

#define LOAD_GAME_MENU_HEIGHT 20
#define LOAD_GAME_MENU_LENGTH 46
#define LOAD_GAME_MENU_INIT_LINE 8
#define LOAD_GAME_MENU_INIT_COLUMN 37
#define LOAD_GAME_MENU_BG_COLOR 0
#define LOAD_GAME_MENU_BORDER_COLOR 14
#define LOAD_GAME_MENU_CH_COLOR 0
#define LOAD_GAME_MENU_TEXT_COLOR 15
#define LOAD_GAME_MENU_PAGE_LENGTH 5

int getSavedGamesList(char directoryNames[MAX_FILES][MAX_FILE_NAME]);
void getLevelDirectoryName(char directory[MAX_PATH_LENGTH], int level);
void getSaveGamesDirectoryName(char directory[MAX_PATH_LENGTH]);
void readMap(int ln, int col, GAMEDATA *data);
int saveGame(GAMEDATA data);
int loadGame(GAMEDATA* data);
void createSaveGameDirectoryIFDoesntExists(char directory[MAX_PATH_LENGTH]);
int createSaveGameFile(GAMEDATA data, char directory[MAX_PATH_LENGTH]);
int loadSavedGameFile(GAMEDATA* data, char fileName[MAX_FILE_NAME]);
void drawFilesList(char directoryNames[MAX_FILES][MAX_FILE_NAME], int filesCount, int page, int lastPage);
int startLoadGameMenu(GAMEDATA* data);

#endif // FILEUTILS_H_INCLUDED
