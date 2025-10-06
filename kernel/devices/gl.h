#pragma once
#include <limine.h>

extern struct limine_framebuffer *framebuffer;

void putpixel(int color, int x, int y);
void putarea(int color, int x, int y, int sx, int sy);