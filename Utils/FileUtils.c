#include "FileUtils.h"

//Lê o mapa apartir de um arquivo de texto e salva na estrutura GAMEDATA passada
//Os parâmetros ln e col representam o tamanho do vetor
void readMap(int ln, int col, GAMEDATA* data){
    int i, j;
    char line[col], directory[MAX_PATH_LENGTH];

    FILE* file;

    //Pega o diretório do arquivo baseado no nível
    getLevelDirectoryName(directory, data->level);

    //Lê o arquivo
    if ((file = fopen(directory, "r")) != NULL){

        for (i = 0; i < ln; i++){
            //Pega a linha atual do for
            fgets(line, col + 2, file);

            //Para cada coluna lê o caracter correspondente
            for (j = 0; j < col; j++){
                data->gameMap[i][j] = line[j];

                //Caso o caracter seja um rato inicializa ele com a posição inicial
                //na estrutura do jogo
                if (line[j] == mouseCh){
                    data->mouse.position.column = j;
                    data->mouse.initialPosition.column = j;
                    data->mouse.position.line = i;
                    data->mouse.initialPosition.line = i;
                } else if(line[j] == doorCh){
                    //Caso seja uma porta adiciona ela na lista e salva suas informações iniciais
                    DOOR* newDoor = malloc(sizeof(DOOR));

                    DOOR* door = data->door;

                    newDoor->position.column = j;
                    newDoor->position.line = i;
                    newDoor->opened = FALSE;
                    newDoor->overlaid = ' ';
                    newDoor->nextDoor = door;

                    data->door = newDoor;
                    data->ndoors++;
                } else if(line[j] == catCh){
                    //Caso o caracter represente um gato, adiciona ele na lista
                    //e inicializa com os valores iniciais
                    CAT* newCat = malloc(sizeof(CAT));

                    CAT* cat = data->cat;

                    newCat->immortal = FALSE;
                    newCat->position.column = j;
                    newCat->initialPosition.column = j;
                    newCat->position.line = i;
                    newCat->initialPosition.line = i;
                    newCat->faceDirection = FALSE;
                    newCat->overlaid = ' ';
                    newCat->nextCat = cat;

                    data->cat = newCat;
                    data->ncats++;
                } else if(line[j] == foodCh){
                    data->nfood++;
                }
            }
        }
    } else{
        data->win = TRUE;
    }
    //Fecha o arquivo
    fclose(file);
}

//Salva um estado de jogo
int saveGame(GAMEDATA data){
    int _return = 0;

    char directory[MAX_PATH_LENGTH];

    createSaveGameDirectoryIFDoesntExists(directory);

    _return = createSaveGameFile(data, directory);

    return _return;
}

//Carrega um jogo salvo
int loadGame(GAMEDATA* data){
    startLoadGameMenu(data);
    return 0;
}

//Cria o arquivo com o estado do jogo salvo
int createSaveGameFile(GAMEDATA data, char directory[MAX_PATH_LENGTH]){
    time_t rawtime;
    struct tm* timeinfo;
    int _return = 1;
    FILE* file;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    snprintf(directory,
             MAX_PATH_LENGTH,
             "%s\\%s_%d_%d_%d_%d_%d_%d%s",
             directory,
             "saved",
             timeinfo->tm_mday,
             timeinfo->tm_mon,
             timeinfo->tm_year,
             timeinfo->tm_hour,
             timeinfo->tm_min,
             timeinfo->tm_sec,
             ".bin");

    if((file = fopen(directory, "wb")) == NULL){
        _return = 0;
    } else if (fwrite(&data, sizeof(GAMEDATA), 1, file) != 1){
        _return = 0;
    } else{
        int x;

        CAT* cat = data.cat;
        for (x = 0; x < data.ncats; x++){
            fwrite(cat, sizeof(CAT), 1, file);
            cat = cat->nextCat;
        }

        DOOR* door = data.door;
        for (x = 0; x < data.ndoors; x++){
            fwrite(door, sizeof(DOOR), 1, file);
            door = door->nextDoor;
        }
    }
    fclose(file);
    return _return;
}

//Exibe um menu com os jogos salvos
int loadSavedGameFile(GAMEDATA* data, char fileName[MAX_FILE_NAME]){
    int _return = FALSE, x = 0;
    char directory[MAX_PATH_LENGTH];

    getSaveGamesDirectoryName(directory);

    snprintf(directory, MAX_PATH_LENGTH, "%s%s%s", directory, fileName, ".bin");

    FILE* file;

    if ((file = fopen(directory, "rb")) != NULL){
        //Desaloca memória guardada para antigos ponteiros de gatos e portas
        freeOldData(data);

        //Posiciona ponteiro no inicio do arquivo
        rewind(file);

        if(fread(data, sizeof(GAMEDATA), 1, file) == 1){
            _return = TRUE;
            data->waitForUserInput = TRUE;
            data->cat = malloc(sizeof(CAT));
            data->door = malloc(sizeof(DOOR));

            CAT* cat = data->cat;

            for(x = 0; x < data->ncats; x++){
                if(x >= 1){
                    cat->nextCat = malloc(sizeof(CAT));
                    cat = cat->nextCat;
                }

                if(fread(cat, sizeof(CAT), 1, file) != 1){
                    _return = FALSE;
                }
            }

            cat->nextCat = NULL;

            DOOR* door = data->door;

            for(x = 0; x < data->ndoors; x++){
                if(x >= 1){
                    door->nextDoor = malloc(sizeof(DOOR));
                    door = door->nextDoor;
                }

                if(fread(door, sizeof(DOOR), 1, file) != 1){
                    _return = FALSE;
                }
            }

            door->nextDoor = NULL;
        }
    }

    return _return;
}

//Criar o diretório de jogos salvos se não existir
void createSaveGameDirectoryIFDoesntExists(char directory[MAX_PATH_LENGTH]){
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s\\%s", directory, "SavedGames");

    mkdir(directory);
}

//Preenche o vetor com o nome dos arquivos de jogos salvos e retorna o número de arquivos encontrados
int getSavedGamesList(char directoryNames[MAX_FILES][MAX_FILE_NAME]){
    int filesLimit = 1, i = 0, countFiles = 0, trashCount = 0;
    char directory[MAX_PATH_LENGTH];

    getSaveGamesDirectoryName(directory);

    DIR *dir = NULL;
    struct dirent *drnt = NULL;
    dir = opendir(directory);

    if (dir){
        while ((drnt = readdir(dir)) && filesLimit){
            if (trashCount < 2){ //Pula os diretórios "." e ".."
                trashCount++;
            } else {
                //Copia o nome do arquivo para o vetor directoryNames
                strcpy(directoryNames[i], drnt->d_name);
                //Remove a extensão ".bin" dos nomes
                directoryNames[i][(strlen(directoryNames[i])-4)] = '\0';
                i++;

                //Verifica se o limite de arquivos carregados foi atingido e para a execução
                if (i == MAX_FILES){
                    filesLimit = 0;
                }
            }
        }
        countFiles = i;
        closedir(dir);
    }

    return countFiles;
}

//Retorna o diretório do arquivo do nível passado por parâmetro
void getLevelDirectoryName(char directory[MAX_PATH_LENGTH], int level){
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s%s%d%s", directory, "\\Levels\\nivel", level, ".txt");
}

//Retorna o diretório do arquivo do jogos salvos passado por parâmetro
void getSaveGamesDirectoryName(char directory[MAX_PATH_LENGTH]){
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s%s", directory, "\\SavedGames\\");
}

//Exibe as informações do menu de carregar jogo
//Retorno:
// 0 - Não foi possível carregar o jogo
// 1 - Jogo carregador
// 2 - Operação abortada pelo usuário
int startLoadGameMenu(GAMEDATA* data){
    char directoryNames[MAX_FILES][MAX_FILE_NAME];
    int userAnswer, fileSelected = 0, filesCount = 0, page = 1, selectedItem, lastPage = 1, _return = 0;

    filesCount = getSavedGamesList(directoryNames);

    lastPage = ceil((float)filesCount / LOAD_GAME_MENU_PAGE_LENGTH);

    textcolor(LOAD_GAME_MENU_TEXT_COLOR);
    textbackground(LOAD_GAME_MENU_BG_COLOR);

    drawFilesList(directoryNames, filesCount, page, lastPage);

    do{
        userAnswer = getch();

        switch(userAnswer){
            case DIRECTIONAL_KEYS:
                userAnswer = getch();
                switch(userAnswer){
                    case DIRECTIONAL_RIGHT:
                        if(page + 1 <= lastPage){
                            page++;
                            drawFilesList(directoryNames, filesCount, page, lastPage);
                        }
                        break;
                    case DIRECTIONAL_LEFT:
                        if(page - 1 >= 1){
                            page--;
                            drawFilesList(directoryNames, filesCount, page, lastPage);
                        }
                        break;
                }
                break;
            case M_CHAR_CODE:
            case m_CHAR_CODE:
                _return = 2;
                fileSelected = 1;
                break;
            default:
                selectedItem = filesCount - ((page - 1) * LOAD_GAME_MENU_PAGE_LENGTH) - userAnswer + 49;

                if(userAnswer - 49 < LOAD_GAME_MENU_PAGE_LENGTH && selectedItem > 0){
                    _return = loadSavedGameFile(data, directoryNames[selectedItem - 1]);
                    fileSelected = 1;
                }
                break;
        }
    }while(!fileSelected);
}

void drawFilesList(char directoryNames[MAX_FILES][MAX_FILE_NAME], int filesCount, int page, int lastPage){
    int count = 1, lastFile, firstFile, x = LOAD_GAME_MENU_INIT_COLUMN + 10, y = LOAD_GAME_MENU_INIT_LINE + 3;

    drawLoadGameMenuBG();

    cputsxy(x, y, "Digite o número da opção:");
    y += 1;
    x += 3;
    cputsxy(x, y, "(Tecle M para sair)");
    y += 3;
    x -= 5;

    //Pega o último indice do array que deve aparecer na página
    lastFile = filesCount - (page * LOAD_GAME_MENU_PAGE_LENGTH);

    //Pega o primeiro indice do array que deve aparecer na página
    firstFile = filesCount - ((page - 1) * LOAD_GAME_MENU_PAGE_LENGTH);

    //Caso o último indíce seja menor que ZERO (Última página com menos de LOAD_GAME_MENU_PAGE_LENGTH elementos, seta como ZERO
    if(lastFile < 0){
        lastFile = 0;
    }

    //Enquando o arquivo atual (firstFile) for maior que o último arquivo a ser exibido na página
    while(firstFile > lastFile){
        //Exibe o nome do arquivo e sua posição
        gotoxy(x, y);
        printf("[%d]: %s", count, directoryNames[firstFile - 1]);
        //Acrescenta valor ao Y para a distância do próximo elemento
        y += 2;
        //Acrescenta 1 ao contador que exibe o ID dos arquivos
        count++;
        //Decrescenta 1 para exibir o próximo arquivo
        firstFile--;
    }

    y += 1;
    x += 6;
    gotoxy(x, y);
    cputsxy(x, y, "Página ");
    printf("[%d] de [%d]", page, lastPage);

    y += 1;
    x -= 7;
    cputsxy(x, y, "Setas direcionáis mudam a página");
}

//Desenha o painel de fundo do menu de carregar jogo
void drawLoadGameMenuBG(){
    drawGenericBackground(LOAD_GAME_MENU_HEIGHT, LOAD_GAME_MENU_LENGTH, LOAD_GAME_MENU_INIT_LINE,
                            LOAD_GAME_MENU_INIT_COLUMN, LOAD_GAME_MENU_BG_COLOR, LOAD_GAME_MENU_BORDER_COLOR);
}
