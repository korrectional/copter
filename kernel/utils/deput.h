#pragma once
#include "../devices/gl.h"
#include "../devices/font8x8.h"
#include "sysstr.h"

#define WHITE 0xffffff
#define BLACK 0x000000
#define DEPUT_STANDART_X_COORD 10
#define DEPUT_STANDART_Y_COORD 10
#define DEPUT_STANDART_X_SIZE 2
#define DEPUT_STANDART_Y_SIZE 2

extern uint16_t deput_y_offset;

void putchar(char chr, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy);

void putstr(const char* str, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy);
void pushstr(const char* str);

void putstri(const char* str, uint32_t num, uint16_t x, uint16_t y, uint16_t sx, uint16_t sy);
void pushstri(const char* str, uint32_t num);