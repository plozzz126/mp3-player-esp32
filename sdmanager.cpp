#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "config.h"

SPIClass sdSPI(FSPI);

bool initSD()
{
    sdSPI.begin(
        SD_SCK,
        SD_MISO,
        SD_MOSI,
        SD_CS
    );

    if(!SD.begin(SD_CS, sdSPI))
    {
        Serial.println("SD FAIL");
        return false;
    }

    Serial.println("SD OK");
    return true;
}

String findFirstMP3()
{
    File dir = SD.open("/music");

    if(!dir)
    {
        Serial.println("/music not found");
        return "";
    }

    while(true)
    {
        File file = dir.openNextFile();

        if(!file)
            break;

        String name = file.name();

        name.toLowerCase();

        if(name.endsWith(".mp3"))
        {
            file.close();
            return String("/music/") + String(file.name());
        }

        file.close();
    }

    return "";
}