#include "MenuUtils.h"

//Desenha o menu em tela e espera por uma entrada do usuário
void openMenu(GAMEDATA* data){
    //Configura o estado do jogo para Menu aberto
    data->menuOpened = TRUE;
    data->paused = TRUE;

    //Atualiza o estado do jogo em tela
    updateExecutionState(*data);

    //Desenha o Menu sobre a tela
    drawMenu();

    //Aguarda e executa a escolha do usuário
    executeMenuChoice(data);

    //Finaliza o menu
    data->menuOpened = FALSE;
}

//Mantem o menu aberto e aguarda uma entrada do usuário para executar a opção
void executeMenuChoice(GAMEDATA* data){
    clock_t start_time_dog = clock() - data->mouse.start_time_dog;
    int optSelected;
    int response;
    int userCommand;

    do {
        optSelected = TRUE;

        //Tenta capturar a entrada do usuario
        userCommand = tryCaptureUserInput();

        //Toma uma decisão conforme a tela pressionada
        switch (userCommand){
            case TAB_CODE:
            case M_CHAR_CODE:
            case m_CHAR_CODE:
            case V_CHAR_CODE:
            case v_CHAR_CODE:
                data->paused = FALSE;
                data->mouse.start_time_dog = clock() - start_time_dog;
                break;
            case N_CHAR_CODE:
            case n_CHAR_CODE:
                data->paused = FALSE;
                break;
            case C_CHAR_CODE:
            case c_CHAR_CODE:
                freeOldData(data);
                response = startLoadGameMenu(data);
                if(!response){
                    data->gameOver = TRUE;
                    data->exitGame = TRUE;
                }
                drawSideColumns();
                drawGameInfo(*data);
                drawMap(data, data->mouse.faceDirection);
                data->paused = FALSE;
                break;
            case Q_CHAR_CODE:
            case q_CHAR_CODE:
                data->exitGame = TRUE;
                break;
            case S_CHAR_CODE:
            case s_CHAR_CODE:
                saveGame(*data);
                data->paused = FALSE;
                break;
            default:
                //Caso não tenha sido pressionada nenhuma tecla válida continua o loop
                optSelected = FALSE;
        }
    }while(!optSelected);
}

//Desenha o menu na tela
void drawMenu(){
    drawMenuBG();
    drawMenuText();
}

//Desenha os textos do menu
void drawMenuText(){
    int x = MENU_INIT_COLUMN + 20;
    int y = MENU_INIT_LINE + 3;
    textcolor(MENU_TEXT_COLOR);
    textbackground(MENU_BG_COLOR);
    cputsxy(x, y, "[Menu]");
    y += 4;
    x -= 6;
    textcolor(MENU_TEXT_COLOR);
    cputsxy(x, y, "[V] Voltar ao jogo");
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

//Desenha o fundo do Menu
void drawMenuBG(){
    drawGenericBackground(MENU_HEIGHT, MENU_LENGTH, MENU_INIT_LINE, MENU_INIT_COLUMN, MENU_BG_COLOR, MENU_BORDER_COLOR);
}
