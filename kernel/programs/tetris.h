#pragma once
#include <stdbool.h>
#include "../utils/deput.h"
#include "../utils/syslow.h"
#include "../utils/sysio.h"
#include "../devices/gl.h"
#include "../devices/keyboard.h"

// Why a delay? This was initially built for a club project, and I wanted to make it evident that this was not just tetris,
// but an OS with tetris on top. If tetris just spawned after I launched the VM subcounciously it would look like any other
// game
#define DISPLAY_DELAY 1//10000//1000000000 
#define DISPLAY_DELAY_VISUAL 1


extern volatile char currentKey;

bool pTETRIS();