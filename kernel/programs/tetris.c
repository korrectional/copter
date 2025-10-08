#include "tetris.h"
//#include "../utils/deput.h"
#define DISPLAY_DELAY 10000//10000//1000000000
#define DISPLAY_DELAY_VISUAL 0

bool tetrisGrid[20][10]; // y, x
uint32_t currentBlock[8 /*4*2: y0,x0,y1,x1,... */];
volatile char currentKey = 0;

// ###### TETRIS FUNCTIONS
static void spawnBlock(uint32_t type){
    switch (type)
    {
    case 0:
        tetrisGrid[0][5] = 1;
        tetrisGrid[0][6] = 1; //  [][]
        tetrisGrid[1][5] = 1; //  [][]
        tetrisGrid[1][6] = 1;

        currentBlock[0] = 0; //
        currentBlock[1] = 5; //
        currentBlock[2] = 0; //
        currentBlock[3] = 6; 
        currentBlock[4] = 1;
        currentBlock[5] = 5;
        currentBlock[6] = 1;
        currentBlock[7] = 6;
        break;
    
    default:
        break;
    }
}

static void swap(uint32_t y0, uint32_t x0, uint32_t y1, uint32_t x1){
    // y/x are unsigned; no negative check
    bool buffer = tetrisGrid[y0][x0]; 
    tetrisGrid[y0][x0] = tetrisGrid[y1][x1];
    tetrisGrid[y1][x1] = buffer;
    if(buffer == 0){
        lGL_dputarea(LIGHT_GRAY, (x1*30)+256, (y1*30)+100, 30, 30);
    }
    if(tetrisGrid[y0][x0] == 0){
        lGL_dputarea(LIGHT_GRAY, (x0*30)+256, (y0*30)+100, 30, 30);
    }
}

static bool checkBottom(uint32_t x, uint32_t y){ // check if under this block is occupied (false==empty)
    if(y >= 19) return true; // treat bottom edge as occupied so pieces stop
    return tetrisGrid[y+1][x];
}

static bool checkBlock(uint32_t x, uint32_t y){ // check if block is occupied
    return tetrisGrid[y][x];
}

static void turn(){
    // move blocks down; iterate from bottom-most block to top to avoid overwriting
    for(int b = 3; b >= 0; --b){
        int idx = b*2; // index into currentBlock: y then x
        uint32_t y = currentBlock[idx];
        uint32_t x = currentBlock[idx+1];
        // ensure within grid and there is a block and space below
        if(y < 19 && tetrisGrid[y][x] && !tetrisGrid[y+1][x]){
            swap(y, x, y+1, x);
            currentBlock[idx] = y + 1;
        }
        else{
            spawnBlock(0);
        }
    }
}

static void printGrid(){
    for(int y = 0; y < 20; ++y){
        for(int x = 0; x < 10; ++x){
            if(tetrisGrid[y][x] == 1){
                lGL_dputarea(BLACK, (x*30)+256, (y*30)+100, 30, 30);
                lGL_dputarea(BLUE, (x*30)+261, (y*30)+105, 20, 20);
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
    spawnBlock(0);
    printGrid();
    while(1){
        uint32_t timestamp = SYSLOW_TIMESTAMP();
        turn();
        pushstr("TURN");
        //lGL_dclearscreen(LIGHT_GRAY);
        deput_y_offset-=10;
        pushstr("TURN");
        printGrid();
        
        currentKey = keyIn();
        switch (currentKey)
        {
        case 'w':
            
            break;
        case 'a':
            
            break;
        case 's':
            
            break;
        case 'd':
            
            break;
        }
        
        SYSLOW_DELAY(1000000000 - (timestamp - SYSLOW_TIMESTAMP()));
    }



    //pushstr("Should have placed tetrominos...");
    SYSLOW_HLT();

}

