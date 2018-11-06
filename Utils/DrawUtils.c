#include "DrawUtils.h"

void drawMono(int lineInit, int colInit, int height, int length, int itemVector[height][length],
              char chvector[height][length], int itemColor, int letterColor, int bgColor, int hasBgCh, char bgCh,
              int hasSecondColor, char chSecondColor, int segundColor)
{
    /*CONFIGURA A COR DO TEXTO*/
    textcolor(letterColor);

    /*VAI PARA A POSIÇÃO INICIAL*/
    gotoxy(colInit, lineInit);

    /*MONTA O DESENHO EM CADA BLOCO CONFORME VETORES*/
    for (int x = 0; x < height; x++){
        for (int y = 0; y < length; y++){
            //Se for para desenhar nesta posição
            if (itemVector[x][y]){
                //Desenha o caracter
                textbackground(itemColor);
                putchar(chvector[x][y]);
            } else if (hasSecondColor && chvector[x][y] == chSecondColor){ //Caso tenha uma segunda cor beaseada em um caracter
                //Desenha essa cor em tela com fundo em branco
                textbackground(segundColor);
                putchar(' ');
            } else{
                //Desenha o fundo
                textbackground(bgColor);
                if (hasBgCh){
                    putchar(bgCh);
                } else{
                    putchar(chvector[x][y]);
                }
            }
        }
        gotoxy(colInit, lineInit + x + 1);
    }

    /*RETORNA A COR DE FUNDO PARA O PADR�O*/
    textbackground(DEFAULT_BG_COLOR);

    /*RETORNA A COR DE TEXTO PARA O PADR�O*/
    textcolor(DEFAULT_TEXT_COLOR);
}

//Desenha em tela beaseado em um vetor de cores e um de caracteres
void drawMultiColor(int lineInit, int colInit, int height, int length, int itemVector[height][length], char chvector[height][length], int letterColor){
    /*CONFIGURA A COR DO TEXTO*/
    textcolor(letterColor);

    /*VAI PARA A POSI��O INICIAL*/
    gotoxy(colInit, lineInit);

    /*MONTA O DESENHO EM CADA BLOCO CONFORME VETORES*/
    for (int x = 0; x < height; x++){
        for (int y = 0; y < length; y++){
            textbackground(itemVector[x][y]);
            putchar(chvector[x][y]);
        }
        gotoxy(colInit, lineInit + x + 1);
    }

    /*RETORNA A COR DE FUNDO PARA O PADR�O*/
    textbackground(DEFAULT_BG_COLOR);

    /*RETORNA A COR DE TEXTO PARA O PADR�O*/
    textcolor(DEFAULT_TEXT_COLOR);
}
