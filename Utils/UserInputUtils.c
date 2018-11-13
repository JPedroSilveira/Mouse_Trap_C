#include "UserInputUtils.h"

//Tenta capturar uma tecla pressionada pelo usuário, retorna ZERO caso nenhuma tecla tenha sido pressionada
int tryCaptureUserInput(){
    if (kbhit()){
        return getche();
    } else{
        return 0;
    }
}
