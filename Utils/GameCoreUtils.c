#include "GameCoreUtils.h"

void startGameCore(GAMEDATA *data){
    int userInput;

    clock_t start_mouse_move, elapsedTime;

    start_mouse_move = clock();

    //Desenha mapa inicial
    drawMap(data, data->mouse.faceDirection);

    do{
        //Limpa espaço de digitação do usuário na tela
        cleanScreen();

        //Caso o jogo deve esperar por uma tecla do usuário para começar
        if(data->waitForUserInput){
            userInput = waitForUserInput();
            data->waitForUserInput = 0;
         } else { //Se não, tenta detectar tecla e continua execução
            userInput = tryCaptureUserInput();
        }

        //Toma uma decisão conforme tecla pressionada
        takeDecision(data, userInput);

        if(data->mouse.isDog){
            //Calcula o tempo que se passou desde que o rato virou cachorro
            elapsedTime = ((end - data->mouse.start_time_dog) / (CLOCKS_PER_SEC / 1000));
            //Caso tenha passado do limite máximo ou seja igual a ele desativa o modo cachorro
            if(elapsedTime >= LIMIT_TIME_OF_DOG){
                data->mouse.isDog = FALSE;
                data->mouse.start_time_dog = FALSE;
                drawMouse(data->mouse.line, data->mouse.column, data->mouse.faceDirection, data->mouse.isDog);
            }
        }

        //Calcula o tempo passado desde o último deslocamento do rato
        elapsedTime = ((clock() - start_mouse_move) / (CLOCKS_PER_SEC / 1000));

        //Caso tenha passado do tempo limite de movimentação desloca o rato novamente
        if(elapsedTime > TIME_TO_MOVE_MOUSE){
            moveMouse(data);
            moveCat(data);
            start_mouse_move = clock();
        }

        //Verifica se deve atualizar o nível ou verificar se algum gato se chocou com o rato
        if(data->updateLevel){
            updateLevel(data);
        } else {
            verifyClash(data);
        }
    }while(!data->exitGame);
}

//Atualiza para um novo nível
void updateLevel(GAMEDATA* data){
    data->level++;

    freeOldData(data); //Validar função

    //Exibe mensagem avisando o usuário
    drawUpLevelMessage();

    Sleep(TIME_TO_SLEEP_WHEN_UPDATE_LEVEL);

    //Configura os dados do jogo
    startGameData(data, data->level, data->score, data->mouse.nlifes, FALSE);

    //Desenha nova tela
    drawSideColumns();

    drawGameInfo(*data);

    drawMap(data, data->mouse.faceDirection);
}

void freeOldData(GAMEDATA* data){
    CAT* cat = data->cat;
    CAT* nextCat = NULL;

    while(cat->exists){
        nextCat = cat->nextCat;
        free(&(cat));
        cat = nextCat;
    }

    DOOR* door = data->door;
    DOOR* nextDoor = NULL;

    while(cat->exists){
        nextDoor = door->nextDoor;
        free(&(door));
        door = nextDoor;
    }
}

//Verifica se algum gato se chocou contra o rato e toma decisão conforme estado do rato (normal ou cachorro)
void verifyClash(GAMEDATA *data){
    CAT* cat = data->cat;

    //Mantém o looping para cada gato existente
    while(cat->exists){
        if(cat->column == data->mouse.column && cat->line == data->mouse.line){
            //Caso o rato esteja no modo cachorro e o gato não esteja imortal
            if(data->mouse.isDog && !cat->immortal){
                drawItemByCh(cat->overlaid, cat->line, cat->column, FALSE, FALSE, FALSE, FALSE);
                data->gameMap[cat->line][cat->column] = cat->overlaid;
                data->gameMap[cat->initialLine][cat->initialColumn] = catCh;
                cat->line = cat->initialLine;
                cat->column = cat->initialColumn;
                cat->faceDirection = 0;
                cat->immortal = TRUE;
                cat->start_immortal_time = clock();
                data->score += SCORE_FOR_CAT;
                textcolor(SCORE_TEXT_COLOR_ON_UPDATE);
                updateScoreOnScreen(*data);
            } else if(!data->mouse.isDog) { // Caso o rato não esteja no modo cachorro, independente do estado do gato
                //Toma decisão conforme vidas restantes do rato
                if(data->mouse.nlifes > 1){
                    data->mouse.nlifes--;
                    updateLifesInfoOnScreen(*data);
                    drawDeathMessage();
                    Sleep(TIME_TO_SLEEP_AFTER_DEATH);
                    restartWithNewLife(data);
                } else {
                    data->mouse.nlifes--;
                    data->gameOver = TRUE;
                    updateLifesInfoOnScreen(*data);
                    drawDeathMessage();
                    Sleep(TIME_TO_SLEEP_AFTER_DEATH);
                    drawGameOverMessage(data);
                }
            } else if(data->mouse.isDog && cat->immortal){ //Caso o rato esteja no modo cachorro e o gato esteja imortal
                data->mouse.overlaid = catCh;
            }
        }
        cat = cat->nextCat;
    }
}

//Reinicia jogo com a próxima vida reposicionando os elementos móveis (rato e gato)
void restartWithNewLife(GAMEDATA* data){
    data->waitForUserInput = TRUE;
    data->mouse.column = data->mouse.initialColumn;
    data->mouse.line = data->mouse.initialLine;
    data->mouse.direction = 0;
    data->mouse.faceDirection = 0;
    data->gameMap[data->mouse.column][data->mouse.column] = mouseCh;

    CAT* cat = data->cat;
    while(cat->exists){
        drawItemByCh(cat->overlaid, cat->line, cat->column, FALSE, FALSE, FALSE, FALSE);
        data->gameMap[cat->line][cat->column] = cat->overlaid;
        data->gameMap[cat->initialLine][cat->initialColumn] = catCh;
        cat->column = cat->initialColumn;
        cat->line = cat->initialLine;
        cat->faceDirection = 0;
        cat = cat->nextCat;
    }

    drawMap(data, data->mouse.faceDirection);
}

//Move o cursor para o topo e limpa o espaço com a cor da borda do HEADER
void cleanScreen(){
    gotoxy(1,1);
    textbackground(HEADER_BG_BORDER_COLOR);
    textcolor(HEADER_BG_BORDER_COLOR);
    putchar(' ');
}

//Define os valores iniciais para um determinado nível do jogo,
//recebe a pontuação, o nível, o número de vidas e o nome do usuário para iniciar um novo nível.
//Conforme parâmetro askName a função pode solicitar o nome para o usuário.
void startGameData(GAMEDATA *data, int level, int score, int nlifes, int askName){
    if(askName){
        askUsername(data->username);
    }

    data->nfood = 0;
    data->updateLevel = FALSE;
    data->waitForUserInput = TRUE;
    data->paused = FALSE;
    data->level = level;
    data->gameOver = FALSE;
    data->menuOpened = FALSE;
    data->exitGame = FALSE;
    data->score = score;
    data->ncats = 0;
    data->doorsOpen = FALSE;
    data->mouse.nlifes = nlifes;
    data->mouse.direction = 0;
    data->mouse.isDog = FALSE;
    data->mouse.start_time_dog = 0;
    data->mouse.overlaid = ' ';
    data->door = malloc(sizeof(struct Door));
    data->door->exists = FALSE;
    data->cat = malloc(sizeof(struct Cat));
    data->cat->exists = FALSE;
    //Lê mapa do arquivo de texto
    readMap(MAP_LINES, MAP_COLUMNS, data);
}

//Toma uma decisão no jogo conforme tecla passada por parâmetro
void takeDecision(GAMEDATA *data, int userInput){
    switch(userInput){
        case DIRECTIONAL_KEYS:
            takeDecisionDirectionalKeys(data);
            break;
        case D_CHAR_CODE:
        case d_CHAR_CODE:
            data->mouse.direction = MOUSE_RIGHT_DIRECTION_CODE;
            break;
        case A_CHAR_CODE:
        case a_CHAR_CODE:
            data->mouse.direction = MOUSE_LEFT_DIRECTION_CODE;
            break;
        case W_CHAR_CODE:
        case w_CHAR_CODE:
            data->mouse.direction = MOUSE_UP_DIRECTION_CODE;
            break;
        case S_CHAR_CODE:
        case s_CHAR_CODE:
            data->mouse.direction = MOUSE_DOWN_DIRECTION_CODE;
            break;
        case B_CHAR_CODE:
        case b_CHAR_CODE:
            moveDoors(data);
            break;
        case P_CHAR_CODE:
        case p_CHAR_CODE:
            data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            data->waitForUserInput = 1;
            //Pausa o jogo e aguarda por entrada do usuário para continuar
            pauseGame(data);
            textcolor(DEFAULT_TEXT_COLOR);
            //Atualiza informação do estado do jogo em tela
            updateExecutionState(*data);
            //Atualiza desenho do mapa para remover mensagem de pausa
            drawMap(data, data->mouse.faceDirection);
            break;
        case M_CHAR_CODE:
        case m_CHAR_CODE:
        case TAB_CODE:
            data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            data->waitForUserInput = TRUE;
            //Abre o menu e aguarda por entrada do usuário
            openMenu(data);
            textcolor(DEFAULT_TEXT_COLOR);
            //Atualiza informação do estado do jogo em tela
            updateExecutionState(*data);
            //Atualiza desenho do mapa para remover mensagem de pausa
            drawMap(data, data->mouse.faceDirection);
            break;
    }
}

//Detecta uma tecla direcional pressionada e toma uma decisão de movimento
//Deve ser utilizada após a leitura do primeiro valor da tecla direcional
void takeDecisionDirectionalKeys(GAMEDATA *data){
    //Lê valor de tecla já pressionada
    int userInput = getche();
    switch(userInput){
        case DIRECTIONAL_RIGHT:
            data->mouse.direction = MOUSE_RIGHT_DIRECTION_CODE;
            break;
        case DIRECTIONAL_LEFT:
            data->mouse.direction = MOUSE_LEFT_DIRECTION_CODE;
            break;
        case DIRECTIONAL_UP:
            data->mouse.direction = MOUSE_UP_DIRECTION_CODE;
            break;
        case DIRECTIONAL_DOWN:
            data->mouse.direction = MOUSE_DOWN_DIRECTION_CODE;
            break;
    }
}

//Desenha uma mensagem informando ao usuário que o gato pegou o rato
void drawDeathMessage(){
    drawDeathMessageBG();
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(50, 16, "-> O gato te pegou! <-");

    drawCat(4, 6, TRUE, FALSE);
    drawCat(4, 21, FALSE, FALSE);
}

//Desenha o Background da mensagem de morte
void drawDeathMessageBG()
{
    drawGenericBackground(6, 46, 13, 37, 0, 14);
}

//Desenha uma mensagem informando ao usuário que passou de nível
void drawUpLevelMessage(){
    drawUpLevelBG();
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(50, 16, "-> Próximo level! <-");

    drawCat(4, 6, TRUE, FALSE);
    drawCat(4, 21, FALSE, FALSE);
}

//Desenha o Background da mensagem de novo nível
void drawUpLevelBG(){
    drawGenericBackground(6, 46, 13, 37, 0, 14);
}

//Desenha uma mensagem de fim de jogo
void drawGameOverMessage(GAMEDATA* data){
    int exit = FALSE, answer = 0;

    drawGameOverBG();
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(52, 16, "-> Game Over! <-");

    //Desenha imagens do gato nos lados da mensagem
    drawCat(4, 6, TRUE, FALSE);
    drawCat(4, 21, FALSE, FALSE);
    Sleep(GAME_OVER_WAIT_TIME);

    gotoxy(49,16);
    printf("Deseja reiniciar? (S/N)");

    textbackground(HEADER_BG_BORDER_COLOR);
    textcolor(HEADER_BG_BORDER_COLOR);

    //Mantém o looping até o usuário passar uma resposta válida
    do{
        gotoxy(1,1);
        answer = getche();

        //Reinicia o jogo
        if(answer == S_CHAR_CODE || answer == s_CHAR_CODE){
            freeOldData(data); //Validar função

            startGameData(data, INIT_LEVEL, 0, INIT_LIFE_AMOUNT, FALSE);

            drawSideColumns();

            drawGameInfo(*data);

            drawMap(data, data->mouse.faceDirection);

            exit = TRUE;
        } else if(answer == N_CHAR_CODE || answer == n_CHAR_CODE) {
            data->exitGame = TRUE;
            exit = TRUE;
        }
    }while(!exit);
}

//Desenha o background da mensagem de fim de jogo
void drawGameOverBG(){
    drawGenericBackground(6, 46, 13, 37, 0, 14);
}


