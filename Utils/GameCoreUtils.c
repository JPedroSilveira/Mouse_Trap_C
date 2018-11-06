#include "GameCoreUtils.h"

void startGameCore(GAMEDATA* data){
    int userInput;

    clock_t start_mouse_move, elapsedTime;

    start_mouse_move = clock();

    //Desenha mapa inicial
    drawMap(data, data->mouse.faceDirection);

    //Mapeia as dist�ncias do rato
    mapDistances(&data);

    do{
        //Limpa espa�o de digita��o do usu�rio na tela
        cleanScreen();

        //Caso o jogo deve esperar por uma tecla do usu�rio para come�ar
        if(data->waitForUserInput){
            userInput = waitForUserInput();
            data->waitForUserInput = 0;
        } else{ //Se n�o, tenta detectar tecla e continua execu��o
            userInput = tryCaptureUserInput();
        }

        //Toma uma decis�o conforme tecla pressionada
        takeDecision(data, userInput);

        if (data->mouse.isDog){
            //Calcula o tempo que se passou desde que o rato virou cachorro
            elapsedTime = ((clock() - data->mouse.start_time_dog) / (CLOCKS_PER_SEC / 1000));
            //Caso tenha passado do limite m�ximo ou seja igual a ele desativa o modo cachorro
            if (elapsedTime >= LIMIT_TIME_OF_DOG){
                data->mouse.isDog = FALSE;
                data->mouse.start_time_dog = FALSE;
                drawMouse(data->mouse.position.line, data->mouse.position.column, data->mouse.faceDirection, data->mouse.isDog);
            }
        }

        //Calcula o tempo passado desde o �ltimo deslocamento do rato
        elapsedTime = ((clock() - start_mouse_move) / (CLOCKS_PER_SEC / 1000));

        //Caso tenha passado do tempo limite de movimenta��o desloca o rato novamente
        if (elapsedTime > TIME_TO_MOVE_MOUSE){
            moveMouse(data);
            moveCat(data);
            start_mouse_move = clock();
            //Mapeia as dist�ncias do rato
            mapDistances(&data);
        }

        //Verifica se deve atualizar o n�vel ou verificar se algum gato se chocou com o rato
        if (data->updateLevel){
            updateLevel(data);
        } else{
            verifyClash(data);
        }
    }while(!data->exitGame);
}

//Atualiza para um novo n�vel
void updateLevel(GAMEDATA* data){
    data->level++;

    freeOldData(data); //Validar fun��o

    //Exibe mensagem avisando o usu�rio
    drawUpLevelMessage();

    Sleep(TIME_TO_SLEEP_WHEN_UPDATE_LEVEL);

    //Configura os dados do jogo
    startGameData(data, data->level, data->score, data->mouse.nlifes, FALSE);

    //Desenha nova tela
    drawSideColumns();

    drawGameInfo(*data);

    drawMap(data, data->mouse.faceDirection);
}

//Desaloca a mem�rio reservada para a lista de gatos e portas
void freeOldData(GAMEDATA* data){
    CAT* cat = data->cat;
    CAT* nextCat = NULL;

    while (cat != NULL){
        nextCat = cat->nextCat;
        free(cat);
        cat = nextCat;
    }

    DOOR* door = data->door;
    DOOR* nextDoor = NULL;

    while (door != NULL){
        nextDoor = door->nextDoor;
        free(door);
        door = nextDoor;
    }
}

//Verifica se algum gato se chocou contra o rato e toma decis�o conforme estado do rato (normal ou cachorro)
void verifyClash(GAMEDATA* data){
    CAT* cat = data->cat;

    //Mant�m o looping para cada gato existente
    while (cat != NULL){
        if (cat->position.column == data->mouse.position.column && cat->position.line == data->mouse.position.line){
            //Caso o rato esteja no modo cachorro e o gato n�o esteja imortal
            if (data->mouse.isDog && !cat->immortal){
                drawItemByCh(cat->overlaid, cat->position.line, cat->position.column, FALSE, FALSE, FALSE, FALSE);
                data->gameMap[cat->position.line][cat->position.column] = cat->overlaid;
                data->gameMap[cat->initialPosition.line][cat->initialPosition.column] = catCh;
                cat->position.line = cat->initialPosition.line;
                cat->position.column = cat->initialPosition.column;
                cat->faceDirection = 0;
                cat->immortal = TRUE;
                cat->start_immortal_time = clock();
                data->score += SCORE_FOR_CAT;
                textcolor(SCORE_TEXT_COLOR_ON_UPDATE);
                updateScoreOnScreen(*data);
            } else if(!data->mouse.isDog){ // Caso o rato n�o esteja no modo cachorro, independente do estado do gato
                //Toma decis�o conforme vidas restantes do rato
                if(data->mouse.nlifes > 1){
                    data->mouse.nlifes--;
                    updateLifesInfoOnScreen(*data);
                    drawDeathMessage();
                    Sleep(TIME_TO_SLEEP_AFTER_DEATH);
                    restartWithNewLife(data);
                } else{
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

//Reinicia jogo com a pr�xima vida reposicionando os elementos m�veis (rato e gato)
void restartWithNewLife(GAMEDATA* data){
    data->waitForUserInput = TRUE;
    data->mouse.position.column = data->mouse.initialPosition.column;
    data->mouse.position.line = data->mouse.initialPosition.line;
    data->mouse.direction = 0;
    data->mouse.faceDirection = 0;
    data->gameMap[data->mouse.position.column][data->mouse.position.column] = mouseCh;

    CAT* cat = data->cat;
    while (cat != NULL){
        drawItemByCh(cat->overlaid, cat->position.line, cat->position.column, FALSE, FALSE, FALSE, FALSE);
        data->gameMap[cat->position.line][cat->position.column] = cat->overlaid;
        data->gameMap[cat->initialPosition.line][cat->initialPosition.column] = catCh;
        cat->position.column = cat->initialPosition.column;
        cat->position.line = cat->initialPosition.line;
        cat->faceDirection = 0;
        cat = cat->nextCat;
    }

    drawMap(data, data->mouse.faceDirection);
}

//Move o cursor para o topo e limpa o espa�o com a cor da borda do HEADER
void cleanScreen(){
    gotoxy(1,1);
    textbackground(HEADER_BG_BORDER_COLOR);
    textcolor(HEADER_BG_BORDER_COLOR);
    putchar(' ');
}

//Define os valores iniciais para um determinado n�vel do jogo,
//recebe a pontua��o, o n�vel, o n�mero de vidas e o nome do usu�rio para iniciar um novo n�vel.
//Conforme par�metro askName a fun��o pode solicitar o nome para o usu�rio.
void startGameData(GAMEDATA* data, int level, int score, int nlifes, int askName){
    if (askName){
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
    data->ndoors = 0;
    data->doorsOpened = FALSE;
    data->mouse.nlifes = nlifes;
    data->mouse.direction = 0;
    data->mouse.isDog = FALSE;
    data->mouse.start_time_dog = 0;
    data->mouse.overlaid = ' ';
    data->door = NULL;
    data->cat = NULL;
    //L� mapa do arquivo de texto
    readMap(MAP_LINES, MAP_COLUMNS, data);
}

//Toma uma decis�o no jogo conforme tecla passada por par�metro
void takeDecision(GAMEDATA* data, int userInput){
    switch (userInput){
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
            //Pausa o jogo e aguarda por entrada do usu�rio para continuar
            pauseGame(data);
            textcolor(DEFAULT_TEXT_COLOR);
            //Atualiza informa��o do estado do jogo em tela
            updateExecutionState(*data);
            //Atualiza desenho do mapa para remover mensagem de pausa
            drawMap(data, data->mouse.faceDirection);
            break;
        case M_CHAR_CODE:
        case m_CHAR_CODE:
        case TAB_CODE:
            data->mouse.direction = MOUSE_STOP_DIRECTION_CODE;
            data->waitForUserInput = TRUE;
            //Abre o menu e aguarda por entrada do usu�rio
            openMenu(data);
            textcolor(DEFAULT_TEXT_COLOR);
            //Atualiza informa��o do estado do jogo em tela
            updateExecutionState(*data);
            //Atualiza desenho do mapa para remover mensagem de pausa
            drawMap(data, data->mouse.faceDirection);
            break;
    }
}

//Detecta uma tecla direcional pressionada e toma uma decis�o de movimento
//Deve ser utilizada ap�s a leitura do primeiro valor da tecla direcional
void takeDecisionDirectionalKeys(GAMEDATA* data){
    //L� valor de tecla j� pressionada
    int userInput = getche();
    switch (userInput){
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

//Desenha uma mensagem informando ao usu�rio que o gato pegou o rato
void drawDeathMessage(){
    drawDeathMessageBG();
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(50, 16, "-> O gato te pegou! <-");

    drawCat(4, 6, TRUE, FALSE);
    drawCat(4, 21, FALSE, FALSE);
}

//Desenha o Background da mensagem de morte
void drawDeathMessageBG(){
    drawGenericBackground(6, 46, 13, 37, 0, 14);
}

//Desenha uma mensagem informando ao usu�rio que passou de n�vel
void drawUpLevelMessage(){
    drawUpLevelBG();
    textcolor(PAUSE_SCREEN_TEXT_COLOR);
    textbackground(PAUSE_SCREEN_BACKGROUND_COLOR);
    cputsxy(50, 16, "-> Pr�ximo level! <-");

    drawCat(4, 6, TRUE, FALSE);
    drawCat(4, 21, FALSE, FALSE);
}

//Desenha o Background da mensagem de novo n�vel
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

    //Mant�m o looping at� o usu�rio passar uma resposta v�lida
    do {
        gotoxy(1,1);
        answer = getche();

        //Reinicia o jogo
        if (answer == S_CHAR_CODE || answer == s_CHAR_CODE){
            freeOldData(data); //Validar fun��o

            startGameData(data, INIT_LEVEL, 0, INIT_LIFE_AMOUNT, FALSE);

            drawSideColumns();

            drawGameInfo(*data);

            drawMap(data, data->mouse.faceDirection);

            exit = TRUE;
        } else if(answer == N_CHAR_CODE || answer == n_CHAR_CODE){
            data->exitGame = TRUE;
            exit = TRUE;
        }
    }while(!exit);
}

//Desenha o background da mensagem de fim de jogo
void drawGameOverBG(){
    drawGenericBackground(6, 46, 13, 37, 0, 14);
}


