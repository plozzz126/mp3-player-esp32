#include "sdmanager.h"

#include <SPI.h>
#include <SdFat.h>

#include "config.h"

SPIClass sdSPI(FSPI);
SdFat sd;

String mp3Files[100];
int mp3Count = 0;

bool initSD()
{
    sdSPI.begin(
        SD_SCK,
        SD_MISO,
        SD_MOSI,
        SD_CS
    );

    SdSpiConfig config(
        SD_CS,
        SHARED_SPI,
        SD_SCK_MHZ(20),
        &sdSPI
    );

    if(!sd.begin(config))
    {
        Serial.println("SD FAIL");
        return false;
    }

    Serial.println("SD OK");

    mp3Count = 0;

    FsFile dir;

    if(!dir.open("/music"))
    {
        Serial.println("/music not found");
        return false;
    }

    FsFile file;
    char filename[128];

    while(file.openNext(&dir, O_RDONLY))
    {
        file.getName(filename, sizeof(filename));

        String name = String(filename);
        String fullPath = "/music/";
        fullPath += name;

        if(name.endsWith(".mp3") || name.endsWith(".MP3"))
        {
            mp3Files[mp3Count] = fullPath;

            Serial.print("MP3: ");
            Serial.println(name);

            mp3Count++;

            if(mp3Count >= 100)
                break;
        }

        file.close();
    }

    dir.close();

    Serial.print("TOTAL MP3: ");
    Serial.println(mp3Count);

    return true;
}

int getMP3Count()
{
    return mp3Count;
}

String getMP3Name(int index)
{
    if(index < 0 || index >= mp3Count)
        return "";

    return mp3Files[index];
}