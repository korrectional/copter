#include "tetris.h"
//#include "../utils/deput.h"

static bool tetrisGrid[20][10]; // y, x
static uint32_t currentBlock[8 /*4*2: y0,x0,y1,x1,... */];
static uint32_t intent[4]; // {w, a, s, d} store current key press intents 
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

        currentBlock[0] = 0; //  [0][2]
        currentBlock[1] = 5; //  [4][6]
        currentBlock[2] = 0; //
        currentBlock[3] = 6; //  [1][3]
        currentBlock[4] = 1; //  [5][7]
        currentBlock[5] = 5;
        currentBlock[6] = 1;
        currentBlock[7] = 6;
        break;

    case 1:
        // S tetromino (zigzag):
        //   [ ][ ]
        // [ ][ ]
        // placed so top-left is (0,4) and bottom-right is (1,6)
        tetrisGrid[0][5] = 1;
        tetrisGrid[0][6] = 1;
        tetrisGrid[1][4] = 1;
        tetrisGrid[1][5] = 1;

        currentBlock[0] = 0; currentBlock[1] = 5;
        currentBlock[2] = 0; currentBlock[3] = 6;
        currentBlock[4] = 1; currentBlock[5] = 4;
        currentBlock[6] = 1; currentBlock[7] = 5;
        break;

    case 2:
        // Z tetromino (mirror zigzag):
        // [ ][ ]
        //   [ ][ ]
        // placed so top-left is (0,4) and bottom-right is (1,6)
        tetrisGrid[0][4] = 1;
        tetrisGrid[0][5] = 1;
        tetrisGrid[1][5] = 1;
        tetrisGrid[1][6] = 1;

        currentBlock[0] = 0; currentBlock[1] = 4;
        currentBlock[2] = 0; currentBlock[3] = 5;
        currentBlock[4] = 1; currentBlock[5] = 5;
        currentBlock[6] = 1; currentBlock[7] = 6;
        break;

    case 3:
        // I tetromino (vertical 4-block bar):
        // [ ]
        // [ ]
        // [ ]
        // [ ]
        // placed so top-left is (0,5) and bottom-right is (3,5)
        tetrisGrid[0][5] = 1;
        tetrisGrid[1][5] = 1;
        tetrisGrid[2][5] = 1;
        tetrisGrid[3][5] = 1;

        currentBlock[0] = 0; currentBlock[1] = 5;
        currentBlock[2] = 1; currentBlock[3] = 5;
        currentBlock[4] = 2; currentBlock[5] = 5;
        currentBlock[6] = 3; currentBlock[7] = 5;
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

        lGL_dputarea(BLACK, (x0*30)+256, (y0*30)+100, 30, 30);
        lGL_dputarea(BLUE, (x0*30)+261, (y0*30)+105, 20, 20);
    }
    if(tetrisGrid[y0][x0] == 0){
        lGL_dputarea(LIGHT_GRAY, (x0*30)+256, (y0*30)+100, 30, 30);
        
        lGL_dputarea(BLACK, (x1*30)+256, (y1*30)+100, 30, 30);
        lGL_dputarea(BLUE, (x1*30)+261, (y1*30)+105, 20, 20);

    }
}

static bool checkBottom(uint32_t x, uint32_t y){ // check if under this block is occupied (false==empty)
    if(y >= 19) return true; // treat bottom edge as occupied so pieces stop
    return tetrisGrid[y+1][x];
}

static bool checkBlock(uint32_t x, uint32_t y){ // check if block is occupied
    return tetrisGrid[y][x];
}

static int turn(){
    // move blocks down; iterate from bottom-most block to top to avoid overwriting
    for(int b = 3; b >= 0; --b){
        int idx = b*2; // index into currentBlock: y then x
        uint32_t y = currentBlock[idx];
        uint32_t x = currentBlock[idx+1];

        // ensure within grid and there is a block and space below
        if(y < 19 && tetrisGrid[y][x] && !tetrisGrid[y+1][x]){
            swap(y, x, y+1, x);
            currentBlock[idx] = y + 1;
            //currentBlock[idx+1] = x + intent[3] - intent[1];
        }
        else{
            spawnBlock(SYSLOW_TIMESTAMP()%4);
            if(y<=5) return 1;
            break;
        }
    }
    return 0;
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
pTETRIS_start:
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

    // print frame
    lGL_dputarea(BLACK, 256-30, 100-30, 360, 660);

    // print grid
    spawnBlock(0);
    printGrid();
    while(1){
        uint32_t timestamp = SYSLOW_TIMESTAMP();
        
        currentKey = keyIn(); // get current key
        intent[0] = 0; // erase key intent
        intent[1] = 0;
        intent[2] = 0;
        intent[3] = 0;
        bool collision;
        switch (currentKey)
        {
        case 'w':
            intent[0] = 1;
            break;
        case 'a':
            intent[1] = 1;

            if(currentBlock[1]==0) break;
            collision = false;
            for(int b = 1; b <= 7; b+=2){
                if(tetrisGrid[currentBlock[b-1]][currentBlock[b]-1] == 1){
                    // we check if block to the right is 1 and if that isnt
                    if(b >= 3 && currentBlock[b-1] == currentBlock[b-3] && currentBlock[b]-1 == currentBlock[b-2]) continue;
                    collision = true;
                    break;
                }
            }
            if(collision) break;

            for(int b = 0; b <= 6; b+=2){
                uint32_t y = currentBlock[b];
                uint32_t x = currentBlock[b+1];
                swap(y, x, y, x-1);
                currentBlock[b+1] -= 1;
            }

            break;
        case 's':
            intent[2] = 1;

            
            break;
        case 'd':

            intent[3] = 1;

            if(currentBlock[7]>=9) break;
            bool collision = false;
            for(int b = 1; b <= 7; b+=2){
                if(tetrisGrid[currentBlock[b-1]][currentBlock[b]+1] == 1){
                    // we check if block to the right is 1 and if that isnt
                    if(b <= 5 && currentBlock[b-1] == currentBlock[b+1] && currentBlock[b]+1 == currentBlock[b+2]) continue;
                    collision = true;
                    break;
                }
            }
            if(collision) break;

            for(int b = 6; b >= 0; b-=2){
                uint32_t y = currentBlock[b];
                uint32_t x = currentBlock[b+1];
                swap(y, x, y, x+1);
                currentBlock[b+1] += 1;
            }

            break;
        }


        if(turn()) goto pTETRIS_start;// calculate "physics"
        //deput_y_offset-=10; 
        //printGrid(); // render everything
        
        // keep a stable 1s frame (1_000_000_000 ns) without unsigned underflow
        {
            uint32_t elapsed = SYSLOW_TIMESTAMP() - timestamp;
            const uint32_t frame_ns = 1000000000u;
            if (elapsed < frame_ns) {
                SYSLOW_DELAY(frame_ns - elapsed);
            }
            // otherwise we're behind; skip delay to catch up
        }
    }



    //pushstr("Should have placed tetrominos...");
    SYSLOW_HLT();

}

