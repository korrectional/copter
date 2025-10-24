#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

uint32_t strlen(const char* str);
void clearStr(char* str, uint32_t len);
bool cmpStr(char* str0, char* str1);