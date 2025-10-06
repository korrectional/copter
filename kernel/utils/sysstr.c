#include "sysstr.h"

uint32_t strlen(const char* str){
    uint32_t length = 0;
    while(str[length] != 0){
        ++length;
    }
    return length;
}
