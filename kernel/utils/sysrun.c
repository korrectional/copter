#include "sysrun.h"

bool SYSRUN_RUN(bool (*program)(void)){
    return program();
}