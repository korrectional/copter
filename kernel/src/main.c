#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "../utils/sysmem.h"
#include "../utils/syslow.h"
#include "../utils/sysrun.h"
#include "../utils/deput.h"
#include "../devices/gl.h"
#include "../devices/keyboard.h"
#include "../programs/tetris.h"


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};
__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;
__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

/*
#define PRESENT 0x1
#define WRITE   0x2

// A page directory contains 1024 entries, each 4 bytes, total size = 4 KB
__attribute__((aligned(4096))) uint32_t page_directory[1024];

// A page table contains 1024 entries, each maps a 4 KB page
__attribute__((aligned(4096))) uint32_t first_page_table[1024];

void initPaging(){
    for(int i = 0; i < 1024; ++i) { // for each page table entry we set the base adress + flags
        first_page_table[i] = (i * 0x1000) | PRESENT | WRITE; // 0x1000 == 4KIB
    }

    //Point the first entry in the Page Directory to our Page Table
    page_directory[0] = ((uint32_t)first_page_table) | PRESENT | WRITE;
    for (int i = 1; i < 1024; i++) { // mark other directories as not present so they dont get marked
        page_directory[i] = 0;
    }

    // load table adress onto CR3 (table register)
    asm volatile(
        "movl %0, %%cr3"
        ::"r"(page_directory)
    );
    
    // enabling paging by modifying cr0:
    uint32_t cr0;
    asm volatile(
        "movl %%cr0, %0"
        :"=r"(cr0)
    );
    // set bit 31 (0x80000000) to enable paging
    cr0 |= 0x80000000;
    asm volatile(
        "movl %0, %%cr0"
        ::"r"(cr0)
    );


}
*/

void kmain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        SYSLOW_HLT();
    }
    if (framebuffer_request.response == NULL
        || framebuffer_request.response->framebuffer_count < 1) {
            SYSLOW_HLT();
        }
    framebuffer = framebuffer_request.response->framebuffers[0];
    
    // begin!!
    pushstr("Copter loaded");
    initKeyboard();
    pushstr("Keyboard initialized");
    
    pushstri("Timestamp: %i", SYSLOW_TIMESTAMP());
    pushstri("Timestamp: %i", SYSLOW_TIMESTAMP());
    pushstri("Pitch: %i", framebuffer->pitch);
    pushstri("Width: %i", framebuffer->width);
    pushstri("Height: %i", framebuffer->height);

    pushstr("Tetris loading");
    SYSLOW_DELAY(1000000000); // this is a deliberate pause to allow the presentees to visualize the terminal
    pushstr("...");
    SYSLOW_DELAY(1000000000); // this one is too, deliberate 30000000000
    SYSRUN_RUN(pTETRIS);



    
    pushstr("Copter hanging");
    SYSLOW_HLT();
}
