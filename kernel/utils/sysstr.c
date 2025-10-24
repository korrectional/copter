#include "sysstr.h"


uint32_t strlen(const char* str){
    uint32_t length = 0;
    while(str[length] != 0){
        ++length;
    }
    return length;
}

void clearStr(char* str, uint32_t len){
    for(size_t i = 0; i < len; ++i){
        str[i] = 0;
    }
}

bool cmpStr(char* str0, char* str1){ // true if equal
    for(size_t i = 0; i < 256; ++i){
        if(str0[i] != str1[i]){
            return false;
        }
        if(str0[i] == 0){
            break;
        }
    }
    return true;
}