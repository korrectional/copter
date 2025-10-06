#include "syslow.h"

void SYSLOW_HLT(){
    for (;;) {
        asm ("hlt");
    }
    return;
}


uint32_t SYSLOW_TIMESTAMP(){
    uint32_t timestamp;
    asm volatile("rdtsc"
        : "=a"(timestamp)
        : 
        : "edx"
    );
    return timestamp;
}


void SYSLOW_DELAY(uint64_t delay){
    uint64_t currentTime = SYSLOW_TIMESTAMP(), now;
    do{
        now = SYSLOW_TIMESTAMP();
    }while((now-currentTime)<delay);
    return;
}
