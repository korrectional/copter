#include "shell.h"

static bool initShell(){ // aka welcome the user
    pushstr("Copter loaded");
    initKeyboard();
    pushstr("Keyboard initialized");

    pushstri("Timestamp: %i", SYSLOW_TIMESTAMP());
    pushstri("Timestamp: %i", SYSLOW_TIMESTAMP());
    pushstri("Pitch: %i", framebuffer->pitch);
    pushstri("Width: %i", framebuffer->width);
    pushstri("Height: %i", framebuffer->height);

    return 1;
}

bool pSHELL(){
    // setup all the stuff that pSHELL uses
    if(!initShell()){
        pushstr("Shell setup failed, panicking and dying");
        SYSLOW_HLT();
    }

    char oldKey = ' ';
    char inputBuffer[256];
    size_t x_offset = 0;
    while(1){
        char currentKey = keyIn();
        if(currentKey != oldKey && currentKey != 0){
            //new key, now act accordingly
            if(currentKey == ENTER){
                deput_y_offset+=10;
                x_offset=0;
                if(cmpStr(inputBuffer, "load tetris")){
                    SYSRUN_RUN(pTETRIS);
                }


                clearStr(inputBuffer, 256);
            }
            else{
                putchar(currentKey, DEPUT_STANDART_X_COORD + x_offset * (DEPUT_STANDART_X_SIZE*4), DEPUT_STANDART_Y_COORD + deput_y_offset, DEPUT_STANDART_X_SIZE, DEPUT_STANDART_Y_SIZE);
                inputBuffer[x_offset] = currentKey;
                ++x_offset;
            }
        }
        
        oldKey = currentKey;

    }

    //pushstr("Tetris loading");
    //SYSLOW_DELAY(DISPLAY_DELAY); // this is a deliberate pause to allow the presentees to visualize the terminal
    //pushstr("...");
    //SYSLOW_DELAY(DISPLAY_DELAY); // this one is too, deliberate...
    //SYSRUN_RUN(pTETRIS);

    pushstr("Copter hanging");
    
    return 1;
}