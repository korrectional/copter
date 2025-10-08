#pragma once
#include <stdbool.h>
#include "../utils/deput.h"
#include "../utils/syslow.h"
#include "../utils/sysio.h"
#include "../devices/gl.h"
#include "../devices/keyboard.h"

extern volatile char currentKey;
extern uint32_t currentBlock[8 /*4*2: x0,y0,x1,y1*/];

bool pTETRIS();