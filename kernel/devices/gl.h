#pragma once
#include <limine.h>

#define WHITE      0xffffff
#define BLACK      0x000000
#define RED        0xff0000
#define GREEN      0x00ff00
#define BLUE       0x0000ff
#define YELLOW     0xffff00
#define CYAN       0x00ffff
#define MAGENTA    0xff00ff
#define GRAY       0x808080
#define LIGHT_GRAY 0xc0c0c0
#define ORANGE     0xffa500
#define PURPLE     0x800080
#define BROWN      0x8b4513
#define PINK       0xff69b4
#define LIME       0x32cd32
#define NAVY       0x000080

extern struct limine_framebuffer *framebuffer;

void putpixel(int color, int x, int y);
void putarea(int color, int x, int y, int sx, int sy);
void clearscreen(int color);