#include <Arduino.h>

#include "sdmanager.h"
#include "display.h"
#include "buttons.h"
#include "config.h"

unsigned long lastPress = 0;

bool inMusicScreen = false;

void showMusicScreen()
{
tft.fillScreen(ST77XX_BLACK);

tft.setTextColor(ST77XX_WHITE);
tft.setTextSize(2);

tft.setCursor(10, 10);
tft.print("MUSIC PLAYER");

String track = findFirstMP3();

tft.setTextSize(1);

if(track.length())
{
    tft.setCursor(10, 60);
    tft.print("Found track:");

    tft.setCursor(10, 80);
    tft.print(track);

    Serial.print("Found: ");
    Serial.println(track);
}
else
{
    tft.setCursor(10, 60);
    tft.print("No MP3 found");

    Serial.println("No MP3 found");
}

tft.setCursor(10, 220);
tft.print("BACK = MENU");


}

void setup()
{
Serial.begin(115200);


initButtons();
initDisplay();

if(initSD())
    Serial.println("SD initialized");
else
    Serial.println("SD init failed");

drawMenu();


}

void loop()
{
if(millis() - lastPress < 200)
return;


if(!inMusicScreen)
{
    if(upPressed())
    {
        selectedItem--;

        if(selectedItem < 0)
            selectedItem = 5;

        if(selectedItem < menuOffset)
            menuOffset--;

        if(menuOffset < 0)
            menuOffset = 0;

        drawMenu();

        lastPress = millis();
    }

    if(downPressed())
    {
        selectedItem++;

        if(selectedItem > 5)
            selectedItem = 0;

        if(selectedItem > menuOffset + 4)
            menuOffset++;

        if(menuOffset > 1)
            menuOffset = 1;

        drawMenu();

        lastPress = millis();
    }

    if(okPressed())
    {
        if(selectedItem == 0)
        {
            inMusicScreen = true;
            showMusicScreen();
        }

        lastPress = millis();
    }
}
else
{
    if(digitalRead(BTN_BACK) == LOW)
    {
        inMusicScreen = false;
        drawMenu();

        lastPress = millis();
    }
}


}
