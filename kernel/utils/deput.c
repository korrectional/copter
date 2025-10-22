#include "deput.h"
#include <stddef.h>

uint16_t deput_y_offset = 0;

void putchar(char chr, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy){
    for(size_t i = 0; i < 8; ++i){
        int buffer = 0b00000001;
        for(size_t j = 0; j < 8; ++j){
            if(((buffer << j) & font8x8[(int)chr][i])>0){
                lGL_dputarea(WHITE, (x+j)*sx, (y+i)*sy, sx, sy);
            }
        }
    }
}



void putstr(const char* str, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy){
    uint32_t length = strlen(str);
    for(size_t i = 0; i < length; ++i){
        if(str[i] == 0){
            break;
        }
        putchar(str[i], x+i*(sx*4), y, sx, sy);
    }
}

void pushstr(const char* str){
    putstr(str, DEPUT_STANDART_X_COORD, DEPUT_STANDART_Y_COORD + deput_y_offset, DEPUT_STANDART_X_SIZE, DEPUT_STANDART_Y_SIZE);
    deput_y_offset += 10;
}

// ## int input ##
void putstri(const char* str, uint32_t num, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy){
    uint32_t length = strlen(str);
    for(size_t i = 0; i < length; ++i){
        if(str[i]=='%' && str[i+1]=='i'){
            uint32_t buffer = num;
            size_t numlen;
            uint32_t stack[255];
            while(1){
                stack[numlen] = buffer%10;
                buffer /= 10;
                ++numlen;
                if(buffer<=0) break;
            }
            for(size_t j = numlen; j > 0; --j){
                putchar((char)(stack[j-1] + '0'), x+i*(sx*4), y, sx, sy);
                ++i;
            }
            i+=2;
        }
        else{
            putchar(str[i], x+i*(sx*4), y, sx, sy);
        }
    }
}

void pushstri(const char* str, uint32_t num){
    putstri(str, num, DEPUT_STANDART_X_COORD, DEPUT_STANDART_Y_COORD + deput_y_offset, DEPUT_STANDART_X_SIZE, DEPUT_STANDART_Y_SIZE);
    deput_y_offset += 10;
}