#include "gl.h"

struct limine_framebuffer *framebuffer;
uint32_t lGL_framebuffer[WIDTH*HEIGHT];

void lGL_dputpixel(int color, int x, int y){
    volatile uint32_t *fb_ptr = framebuffer->address;

    fb_ptr[x + y * framebuffer->pitch / 4] = color;
}

void lGL_dputarea(int color, int x, int y, int sx, int sy){ // paint block in one color
    volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < sx; ++i){
        for(int j = 0; j < sy; ++j){
            //if(x+i>WIDTH || y+j>HEIGHT) continue;
            fb_ptr[(x+i) + (y+j)*framebuffer->pitch / 4] = color; // paint XY + offset
        }
    }
}

void lGL_dclearscreen(int color){
    volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < framebuffer->width; ++i){
        for(int j = 0; j < framebuffer->height; ++j){
            fb_ptr[i+j*framebuffer->width] = color;
        }
    }
}




// onto lGL_framebuffer  PLEASE DONT USE

void lGL_putpixel(int color, int x, int y){
    //volatile uint32_t *fb_ptr = framebuffer->address;

    lGL_framebuffer[x + y * framebuffer->pitch / 4] = color;
}

void lGL_putarea(int color, int x, int y, int sx, int sy){ // paint block in one color
    //volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < sx; ++i){
        for(int j = 0; j < sy; ++j){
            lGL_framebuffer[(x+i) + (y+j)*framebuffer->pitch / 4] = color; // paint XY + offset
        }
    }
}

void lGL_clearscreen(int color){
    //volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < framebuffer->width; ++i){
        for(int j = 0; j < framebuffer->height; ++j){
            lGL_framebuffer[i+j*framebuffer->width] = color;
        }
    }
}

void lGL_writeFramebuffer(){
    volatile uint32_t *fb_ptr = framebuffer->address;

    for(int i = 0; i < framebuffer->width; ++i){
        for(int j = 0; j < framebuffer->height; ++j){
            fb_ptr[i+j*framebuffer->width] = lGL_framebuffer[i+j*framebuffer->width];
        }
    }
}
