#include "tetris.h"
#include "../devices/gl.h"
//#include "../utils/deput.h"
#define DISPLAY_DELAY 10000//1000000000
#define DISPLAY_DELAY_VISUAL 0

bool tetrisGrid[20][10]; // y, x


// ###### TETRIS FUNCTIONS
static void spawnBlock(uint32_t type, uint32_t x, uint32_t y){
    switch (type)
    {
    case 0:
        tetrisGrid[y][x] = 1;
        break;
    
    default:
        break;
    }
}

static void swap(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){
    if(y1<0||y2<0){
        return 0;
    }
    bool buffer = tetrisGrid[y1][x1]; 
    tetrisGrid[y1][x1] = tetrisGrid[y2][x2];
    tetrisGrid[y2][x2] = buffer;
}

static void checkBottom(uint32_t x, uint32_t y){ // check if under this block is empty
    return tetrisGrid[y+1][x];
}

static bool checkBlock(uint32_t x, uint32_t y){ // check if block is empty
    return tetrisGrid[y][x];
}

static void turn(){
    for(int y = 18; y >= 0; --y){ // we dont go down to block 19th (bottom)
        for(int x = 10; x >= 0; --x){
            if(tetrisGrid[y][x] == 1){// && tetrisGrid[y+1][x] == 0){
                swap(x, y, x, y+1);
                //pushstr("SWAP OCURRED");
            }
        }    
    }
}

static void printGrid(){
    for(int y = 0; y < 20; ++y){
        for(int x = 0; x < 10; ++x){
            if(tetrisGrid[y][x] == 1){
                lGL_dputarea(BLACK, (x*30)+100, (y*30)+100, 30, 30);
                lGL_dputarea(BLUE, (x*30)+105, (y*30)+105, 20, 20);
            }
        }
    }
}
// ###### TETRIS FUNCTIONS




bool pTETRIS(){
    pushstr("TETROMINO PROGRAM HAS INITIALIZED");
    if(DISPLAY_DELAY_VISUAL){
        pushstr("TETROMINO PROGRAM HAS INITIALIZED");
        SYSLOW_DELAY(DISPLAY_DELAY);
        lGL_dclearscreen(NAVY);
        SYSLOW_DELAY(DISPLAY_DELAY);
        lGL_dclearscreen(YELLOW);
        SYSLOW_DELAY(DISPLAY_DELAY);
        lGL_dclearscreen(BLACK);
        SYSLOW_DELAY(DISPLAY_DELAY);
        
        pushstr("Tetromino Entertainment Software Corporation");
        SYSLOW_DELAY(DISPLAY_DELAY);
        pushstr("1992 C Copyright");
        SYSLOW_DELAY(DISPLAY_DELAY);
        pushstr("Presented to you by David...");
        SYSLOW_DELAY(DISPLAY_DELAY*20);
        pushstr(" ");
        pushstr(" ");
        pushstr("...   ...  yeaa I made an OS");
        SYSLOW_DELAY(DISPLAY_DELAY);
        int turn = 0, xLOGO = 300, yLOGO = 200;
        while(yLOGO<700){
            lGL_dputarea(BLUE, xLOGO, yLOGO, 50, 50);
            ++yLOGO;
            xLOGO+=(++turn)/20;
            SYSLOW_DELAY(10000000);
        }
    }
    SYSLOW_DELAY(DISPLAY_DELAY);
    pushstr("Setting up game...");
    SYSLOW_DELAY(DISPLAY_DELAY);
    lGL_dclearscreen(LIGHT_GRAY);
    putstr("TETROMINO!", 50, 20, 2, 2);
    
    for(int y = 0; y < 20; ++y){
        for(int x = 0; x < 10; ++x){
            tetrisGrid[y][x] = 0;
        }    
    }
    tetrisGrid[0][0] = 1;
    tetrisGrid[1][1] = 1;
    tetrisGrid[18][8] = 1;
    tetrisGrid[19][9] = 1;

    // print grid
    printGrid();

    while(1){
        SYSLOW_DELAY(1000000000);
        turn();
        pushstr("TURN");
        lGL_dclearscreen(LIGHT_GRAY);
        //SYSLOW_DELAY(1000000000);
        printGrid();

    }



    //pushstr("Should have placed tetrominos...");
    SYSLOW_HLT();

}

