#include "MenuUtils.h"

void openMenu(GAMEDATA *data){
    data->menuOpened = TRUE;
    data->paused = TRUE;
    updateExecutionState(*data);
    drawMenu();
    executeMenuChoice(data);
    data->menuOpened = FALSE;
}

void executeMenuChoice(GAMEDATA *data){
    clock_t start_time_dog = clock() - data->mouse.start_time_dog;
    int optSelected;
    int userCommand;

    do{
        optSelected = TRUE;
        userCommand = tryCaptureUserInput();

        switch(userCommand){
            case TAB_CODE:
            case M_CHAR_CODE:
            case m_CHAR_CODE:
                data->paused = FALSE;
                data->mouse.start_time_dog = clock() - start_time_dog;
                break;
            case N_CHAR_CODE:
            case n_CHAR_CODE:
                data->paused = FALSE;
                break;
            case C_CHAR_CODE:
            case c_CHAR_CODE:
                data->paused = FALSE;
                break;
            case Q_CHAR_CODE: //Q
            case q_CHAR_CODE:
                data->exitGame = TRUE;
                break;
            case S_CHAR_CODE:
            case s_CHAR_CODE:
                data->paused = FALSE;
                break;
            default:
                optSelected = FALSE;
        }
    }while(!optSelected);
}

void drawMenu()
{
    drawMenuBG();
    drawMenuText();
}

void drawMenuText()
{
    int x = MENU_INIT_COLUMN + 20;
    int y = MENU_INIT_LINE + 3;
    textcolor(MENU_TEXT_COLOR);
    textbackground(MENU_BG_COLOR);
    cputsxy(x, y, "[Menu]");
    y += 4;
    x -= 6;
    textcolor(MENU_TEXT_COLOR);
    cputsxy(x, y, "[M] Voltar ao jogo");
    y += 2;
    cputsxy(x, y, "[C] Carregar jogo");
    y += 2;
    cputsxy(x, y, "[N] Novo jogo");
    y += 2;
    cputsxy(x, y, "[S] Salvar jogo");
    y += 2;
    cputsxy(x, y, "[Q] Sair do jogo");
    drawMouse(2, 6, TRUE, FALSE);
    drawMouse(4, 6, TRUE, FALSE);
    drawMouse(6, 6, TRUE, FALSE);
    drawMouse(8, 6, TRUE, FALSE);
    drawCat(2, 20, FALSE, FALSE);
    drawCat(4, 20, FALSE, FALSE);
    drawCat(6, 20, FALSE, FALSE);
    drawCat(8, 20, FALSE, FALSE);
}

void drawMenuBG()
{
    drawGenericBackground(MENU_HEIGHT, MENU_LENGTH, MENU_INIT_LINE, MENU_INIT_COLUMN, MENU_BG_COLOR, MENU_BORDER_COLOR);
}
