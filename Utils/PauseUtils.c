#include "PauseUtils.h"

void pauseGame(GAMEDATA* data){
    clock_t start_time_dog = clock() - data->mouse.start_time_dog;
    data->paused = TRUE;
    updateExecutionState(*data);
    drawPauseScreen();
    int _userCommand;
    int _continue = TRUE;
    do {
        _userCommand = tryCaptureUserInput();

        switch (_userCommand){
            case 80: //P
            case 112:
                data->paused = FALSE;
                data->mouse.start_time_dog = clock() - start_time_dog;
                _continue = FALSE;
                break;
            case 77: //M - Tab
            case 109:
            case 9:
                data->mouse.start_time_dog = clock() - start_time_dog;
                openMenu(data);
                _continue = FALSE;
                break;
        }
    }while(_continue);
}

void drawPauseScreen(){
    drawPauseScreenBackground();
    drawPauseScreenText();
}

void drawPauseScreenText(){
    int x = PAUSE_SCREEN_INIT_COLUMN + 17;
    int y = PAUSE_SCREEN_INIT_LINE + 3;
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(x, y, "-> PAUSADO <-");
    y += 4;
    x -= 9;
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    cputsxy(x, y, "Aperte [P] para voltar ao jogo.");

    drawMouse(2, 8, TRUE, FALSE);
    drawCat(2, 19, FALSE, FALSE);
}

void drawPauseScreenBackground(){
    drawGenericBackground(PAUSE_SCREEN_HEIGHT, PAUSE_SCREEN_LENGTH, PAUSE_SCREEN_INIT_LINE, PAUSE_SCREEN_INIT_COLUMN, PAUSE_SCREEN_BACKGROUND_COLOR, PAUSE_SCREEN_BORDER_COLOR);
}
