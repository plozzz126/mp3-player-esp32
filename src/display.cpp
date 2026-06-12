#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include "config.h"

SPIClass tftSPI(FSPI);

Adafruit_ST7789 tft(
    &tftSPI,
    TFT_CS,
    TFT_DC,
    TFT_RST
);

int selectedItem = 0;
int menuOffset = 0;

const char* menuItems[] =
{
    "Music Player",
    "Bluetooth Audio",
    "Video Player",
    "Images",
    "Settings",
    "About"
};

void initDisplay()
{
    tftSPI.begin(
        TFT_SCLK,
        -1,
        TFT_MOSI,
        TFT_CS
    );

    tft.init(240, 320);

    tft.setRotation(3);

    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(3);

    tft.setCursor(20,20);
    tft.print("TOP LEFT");

    tft.setCursor(180,200);
    tft.print("BR");
}

void drawMenu()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(60, 10);
    tft.print("MEDIA PLAYER");

    for (int i = menuOffset; i < menuOffset + 5 && i < 6; i++)
    {
        int y = 55 + ((i - menuOffset) * 35);

        if (i == selectedItem)
        {
            tft.fillRoundRect(
                10,
                y - 5,
                220,
                28,
                6,
                ST77XX_BLUE
            );

            tft.setTextColor(ST77XX_WHITE);
        }
        else
        {
            tft.setTextColor(0x8410);
        }

        tft.setCursor(20, y);
        tft.print(menuItems[i]);
    }

    tft.drawFastHLine(
        0,
        40,
        tft.width(),
        ST77XX_BLUE
    );

    tft.setTextColor(0x8410);
    tft.setTextSize(1);

    tft.setCursor(5, 225);
    tft.print("UP/DOWN - Navigate");

    tft.setCursor(170, 225);
    tft.print("OK - Select");
}