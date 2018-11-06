#include "FileUtils.h"

//Lê o mapa apartir de um arquivo de texto e salva na estrutura GAMEDATA passada
//Os parâmetros ln e col representam o tamanho do vetor
void readMap(int ln, int col, GAMEDATA* data){
    int i, j;
    char line[col], directory[MAX_PATH_LENGTH];

    FILE* file;

    //Pega o diretório do arquivo baseado no nível
    getDirectoryName(directory, data->level);

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

//Cria o arquivo com o estado do jogo salvo
int createSaveGameFile(GAMEDATA data, char directory[MAX_PATH_LENGTH]){
    time_t rawtime;
    struct tm* timeinfo;
    int cursorPosition = 1, _return = 1;
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
    } else if (fwrite(&data, sizeof(GAMEDATA), cursorPosition, file) != 1){
        _return = 0;
    } else{
        int x;

        CAT* cat = data.cat;
        for (x = 0; x < data.ncats; x++){
            cursorPosition++;
            if (fwrite(cat, sizeof(CAT), cursorPosition, file) != 1) {
                _return = 0;
            }
            cat = cat->nextCat;
        }

        DOOR* door = data.door;
        for (x = 0; x < data.ndoors; x++){
            cursorPosition++;
            if (fwrite(door, sizeof(DOOR), cursorPosition, file) != 1){
                _return = 0;
            }
            door = door->nextDoor;
        }
    }
    fclose(file);
    return _return;
}

//Criar o diretório de jogos salvos se não existir
void createSaveGameDirectoryIFDoesntExists(char directory[MAX_PATH_LENGTH]){
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s\\%s", directory, "SavedGames");

    mkdir(directory);
}

int loadGame(GAMEDATA* data){

}

//Retorna o diretório do arquivo do nível passado por parâmetro
void getDirectoryName(char directory[MAX_PATH_LENGTH], int level)
{
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s%s%d%s", directory, "\\Levels\\nivel", level, ".txt");
}
