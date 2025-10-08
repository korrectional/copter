#pragma once

void outd(short port, int dword);
char inb(short port);
inline void outb(unsigned int port, unsigned int val);