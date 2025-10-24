#pragma once
#include "../utils/sysio.h"
#define ESC         0x1B
#define SPACE       ' '
#define BACKSPACE   0x08
#define TAB         0x09
#define ENTER       0x1C
#define LSHIFT      0x2A
#define RSHIFT      0x36
#define LCTRL       0x1D

extern unsigned char symbolTable[256];

void initKeyboard();
char keyIn();