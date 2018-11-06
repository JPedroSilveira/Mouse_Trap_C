#include "UsernameScreenUtils.h"

void askUsername(char username[NAME_MAX_LENGTH]){
    drawUsernameScreen();

    textbackground(ASK_NAME_BG_COLOR);
    textcolor(ASK_NAME_LETTER_COLOR);
    cputsxy(ASK_NAME_INIT_COLUMN + 2, ASK_NAME_INIT_LINE + 1, "Digite seu nome de usuario: ");

    gotoxy(ASK_NAME_INIT_COLUMN + 4, ASK_NAME_INIT_LINE + 2);

    gets(username);
}

void drawUsernameScreen(){
    int itemVector[ASK_NAME_HEIGHT][ASK_NAME_LENGTH];
    char chVector[ASK_NAME_HEIGHT][ASK_NAME_LENGTH];

    for (int x = 0; x < ASK_NAME_HEIGHT; x++){
        for (int y = 0; y < ASK_NAME_LENGTH; y++){
            if (x == 0 || y == 0 || x == ASK_NAME_HEIGHT - 1 || y == ASK_NAME_LENGTH - 1){
                itemVector[x][y] = ASK_NAME_BORDER_COLOR;
            } else{
                itemVector[x][y] = ASK_NAME_BG_COLOR;
            }
            chVector[x][y] = ' ';
        }
    }

    drawMultiColor(ASK_NAME_INIT_LINE, ASK_NAME_INIT_COLUMN, ASK_NAME_HEIGHT, ASK_NAME_LENGTH, itemVector, chVector, ASK_NAME_LETTER_COLOR);
}
