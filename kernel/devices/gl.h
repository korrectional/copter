#pragma once
#include <limine.h>

#define WIDTH 1024
#define HEIGHT 768

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
extern uint32_t lGL_framebuffer[WIDTH*HEIGHT];


// directly onto framebuffer
void lGL_dputpixel(int color, int x, int y);
void lGL_dputarea(int color, int x, int y, int sx, int sy);
void lGL_dclearscreen(int color);

// onto gl framebuffer PLEASE DONT USE
void lGL_putpixel(int color, int x, int y);
void lGL_putarea(int color, int x, int y, int sx, int sy);
void lGL_clearscreen(int color);
void lGL_writeFramebuffer();