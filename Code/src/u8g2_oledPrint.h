#pragma once
#include <U8g2lib.h>

// Function Prototype
void oledPrint(U8G2 &display, const uint8_t *font, int x, int y, const char *message);
void oledPrint(U8G2 &display, const uint8_t *font, int x, int y, float value, int digits);
