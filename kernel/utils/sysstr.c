#include "sysstr.h"
#include <stddef.h>


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