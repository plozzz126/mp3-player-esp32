#include <Arduino.h>

#include "audio.h"
#include "sdmanager.h"
#include "display.h"
#include "buttons.h"
#include "config.h"

unsigned long lastPress = 0;

bool inMusicScreen = false;

bool inTrackScreen = false;

int trackIndex = 0;
int trackOffset = 0;




void drawTrackList()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(10, 10);
    tft.print("TRACKS");

    int count = getMP3Count();

    for(int i = trackOffset; i < trackOffset + 5 && i < count; i++)
    {
        int y = 50 + ((i - trackOffset) * 35);

        if(i == trackIndex)
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
        tft.print(getMP3Name(i));
    }

    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(10, 220);
    tft.print("OK=OPEN");
}

// ffff

void showTrackScreen()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);

    tft.setCursor(10,10);
    tft.print("NOW PLAYING");

    tft.setTextSize(1);

    tft.setCursor(10,60);
    tft.print(getMP3Name(trackIndex));

    tft.setCursor(10,220);
    tft.print("BACK = TRACK LIST");
}


void setup()
{

Serial.begin(115200);
Serial.printf("Flash: %u MB\n", ESP.getFlashChipSize() / 1024 / 1024);
Serial.printf("PSRAM: %u bytes\n", ESP.getPsramSize());


initButtons();
initDisplay();
initAudio();

if(initSD())
    Serial.println("SD initialized");
else
    Serial.println("SD init failed");

drawMenu();


}

void loop()
{
    audioLoop();

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

            trackIndex = 0;
            trackOffset = 0;
            
            drawTrackList();
        }

        lastPress = millis();
    }
}
else
{
    if(!inTrackScreen)
    {
        if(upPressed())
        {
            trackIndex--;

            if(trackIndex < 0)
                trackIndex = getMP3Count() - 1;

            if(trackIndex < trackOffset)
                trackOffset--;

            if(trackOffset < 0)
                trackOffset = 0;

            drawTrackList();

            lastPress = millis();
        }

        if(downPressed())
        {
            trackIndex++;

            if(trackIndex >= getMP3Count())
                trackIndex = 0;

            if(trackIndex > trackOffset + 4)
                trackOffset++;

            drawTrackList();

            lastPress = millis();
        }

        if(okPressed())
        {
            inTrackScreen = true;

            String path = getMP3Name(trackIndex);

            Serial.print("PLAYING: ");
            Serial.println(path);

            playMP3(path.c_str());

            showTrackScreen();

            lastPress = millis();
        }

        if(digitalRead(BTN_BACK) == LOW)
        {
            inMusicScreen = false;

            drawMenu();

            lastPress = millis();
        }
    }
    else
    {
        if(digitalRead(BTN_BACK) == LOW)
        {
            inTrackScreen = false;

            drawTrackList();

            lastPress = millis();
        }
    }
}


}
