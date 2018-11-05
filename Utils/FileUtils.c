#include "FileUtils.h"

//Lê o mapa apartir de um arquivo de texto e salva na estrutura GAMEDATA passada
//Os parâmetros ln e col representam o tamanho do vetor
void readMap(int ln, int col, GAMEDATA *data){
    int i, j;
    char line[col], directory[MAX_PATH_LENGTH];

    FILE *file;

    getDirectoryName(directory, data->level);

    if ((file = fopen(directory, "r")) != NULL)
    {
        for (i = 0; i < ln; i++)
        {
            fgets(line, col + 2, file);
            for (j = 0; j < col; j++)
            {
                data->gameMap[i][j] = line[j];
                if(line[j] == mouseCh){
                    data->mouse.column = j;
                    data->mouse.initialColumn = j;
                    data->mouse.line = i;
                    data->mouse.initialLine = i;
                } else if(line[j] == doorCh){
                    DOOR *door = data->door;

                    while(door->exists){
                        door = door->nextDoor;
                    }

                    door->column = j;
                    door->line = i;
                    door->exists = TRUE;
                    door->opened = FALSE;
                    door->overlaid = ' ';
                    door->nextDoor = malloc(sizeof(struct Door));
                    door->nextDoor->exists = FALSE;
                } else if(line[j] == catCh){
                    CAT *cat = data->cat;

                    while(cat->exists){
                        cat = cat->nextCat;
                    }

                    cat->immortal = FALSE;
                    cat->column = j;
                    cat->initialColumn = j;
                    cat->line = i;
                    cat->initialLine = i;
                    cat->exists = TRUE;
                    cat->faceDirection = FALSE;
                    cat->overlaid = ' ';
                    cat->nextCat = malloc(sizeof(struct Cat));
                    cat->nextCat->exists = FALSE;
                    data->ncats++;
                } else if(line[j] == foodCh){
                    data->nfood++;
                }
            }
        }
    }
    fclose(file);
}

void getDirectoryName(char directory[MAX_PATH_LENGTH], int level)
{
    getcwd(directory, MAX_PATH_LENGTH);

    snprintf(directory, MAX_PATH_LENGTH, "%s%s%d%s", directory, "\\Levels\\nivel", level, ".txt");
}
