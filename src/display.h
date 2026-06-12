#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

extern Adafruit_ST7789 tft;

extern int selectedItem;
extern int menuOffset;

void initDisplay();
void drawMenu();