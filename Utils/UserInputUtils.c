#include "UserInputUtils.h"

//Tenta capturar uma tecla pressionada pelo usu�rio, retorna ZERO caso nenhuma tecla tenha sido pressionada
int tryCaptureUserInput(){
    if (kbhit()){
        return getche();
    } else{
        return 0;
    }
}
