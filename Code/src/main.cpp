#include <Arduino.h>
#include <Wire.h>
#include "Button.h"
#include "u8g2_oledPrint.h"
#include "counter_Frame.h"

// Pin definition
#define IR_OUT 18
#define BUTTON_PIN 23
Button myButton(BUTTON_PIN); // Button object created

// screen definition
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define FONT_LARGE u8g2_font_ncenB14_tr
#define FONT_SMALL u8g2_font_ncenB08_tr

// OLED Display Object
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Counting Logic
volatile unsigned long count = 0;
volatile bool objectDetect = false;

void IRAM_ATTR countPulse() {
    if (!objectDetect) {
        count++;
        objectDetect = true;
    }
}

// Animation function
void counter_Animation(unsigned long duration_ms) {
    unsigned long start = millis();
    while (millis() - start < duration_ms) {
        for (int i = 0; i < 27; i++) {
            display.clearBuffer();
            display.drawXBMP(39, 7, 50, 50, counterframes[i]);
            display.sendBuffer();
            delay(50);
        }
    }
}

void showWelcomeScreens() {
    display.clearBuffer();
    counter_Animation(3000);
    display.clearBuffer();

    // Screen 1
    oledPrint(display, u8g2_font_ncenR14_tr, 22, 28, "Welcome");
    oledPrint(display, u8g2_font_6x10_tr, 105, 56, "To:");
    display.sendBuffer();
    delay(2000);
    display.clearBuffer();

    // Screen 2
    oledPrint(display, u8g2_font_ncenR14_tr, 8, 28, "IR Counter");
    oledPrint(display, u8g2_font_6x10_tr, 0, 56, "Get Count Digitally");
    display.sendBuffer();
    delay(2000);
    display.clearBuffer();

    // Screen 3
    oledPrint(display, u8g2_font_ncenR14_tr, 4, 28, "Powered By");
    oledPrint(display, u8g2_font_6x10_tr, 72, 56, "Abhishek");
    display.sendBuffer();
    delay(2000);
    display.clearBuffer();
}

void yourDisplayFunction(uint32_t count) {
    // Dynamic Font Based on Count
    const uint8_t* selectedFont = (count < 10000) ? FONT_LARGE : FONT_SMALL;
    display.setFont(selectedFont);

    // Convert Count to String
    char countStr[10];
    sprintf(countStr, "%lu", count);

    // Get Text Width for Centering
    uint16_t textWidth = display.getStrWidth(countStr);
    uint16_t textHeight = display.getMaxCharHeight();

    int xPos = (SCREEN_WIDTH - textWidth) / 2;
    int yPos = (selectedFont == FONT_LARGE) ? 28 : 35;

    // Display on OLED
    display.clearBuffer();

    // Top Title
    oledPrint(display, u8g2_font_6x10_tr, 49, 45, "COUNT");

    // Dynamic Centered Count
    display.setFont(selectedFont);
    display.drawStr(xPos, yPos, countStr);

    display.sendBuffer();
}

void setup() {
    Wire.begin();
    display.begin();
    myButton.begin();

    pinMode(IR_OUT, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    showWelcomeScreens();

    attachInterrupt(digitalPinToInterrupt(IR_OUT), countPulse, FALLING);
}

void loop() {
    // Button Press Detect (Debounce)
    static bool lastButtonState = HIGH;
    bool currentButtonState = digitalRead(BUTTON_PIN);

    if (lastButtonState == HIGH && currentButtonState == LOW) {
        delay(50);
        if (digitalRead(BUTTON_PIN) == LOW) {
            count = 0;
        }
    }
    lastButtonState = currentButtonState;

    // Reset objectDetect when obstacle moves away
    if (digitalRead(IR_OUT) == HIGH) {
        objectDetect = false;
    }

    yourDisplayFunction(count);
}
