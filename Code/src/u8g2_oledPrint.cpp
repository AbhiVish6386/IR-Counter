#include "u8g2_oledPrint.h"

//for simple text
void oledPrint(U8G2 &display, const uint8_t *font, int x, int y, const char *message) {
    display.setFont(font);             // Font set (no setTextSize in U8G2)
    display.setDrawColor(1);           // Ensure white text
    display.setCursor(x, y);           // Set position
    display.print(message);            // Print message
   
}

// For float + precision
void oledPrint(U8G2 &display, const uint8_t *font, int x, int y, float value, int digits) {
    display.setFont(font);
    display.setCursor(x, y);
    display.print(value, digits);
}