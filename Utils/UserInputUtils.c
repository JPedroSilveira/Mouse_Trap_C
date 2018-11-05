#include "UserInputUtils.h"

int tryCaptureUserInput(){
    if(kbhit()){
        return getche();
    } else {
        return 0;
    }
}

int waitForUserInput(){
    return getche();
}
