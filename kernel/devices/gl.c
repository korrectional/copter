#include "gl.h"

struct limine_framebuffer *framebuffer;

void putpixel(int color, int x, int y){
    volatile uint32_t *fb_ptr = framebuffer->address;

    fb_ptr[x + y * framebuffer->pitch / 4] = color;
}

void putarea(int color, int x, int y, int sx, int sy){ // paint block in one color
    volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < sx; ++i){
        for(int j = 0; j < sy; ++j){
            fb_ptr[(x+i) + (y+j)*framebuffer->pitch / 4] = color; // paint XY + offset
        }
    }
}

void clearscreen(int color){
    volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < framebuffer->width; ++i){
        for(int j = 0; j < framebuffer->height; ++j){
            fb_ptr[i+j*framebuffer->width] = color;
        }
    }
}
