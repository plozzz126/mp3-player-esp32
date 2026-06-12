#include "sdmanager.h"

#include <SPI.h>
#include <SdFat.h>

#include "config.h"

SPIClass sdSPI(FSPI);
SdFat sd;

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
    return true;
}

String findFirstMP3()
{
    Serial.println("Searching MP3...");

    FsFile dir;

    if(!dir.open("/music"))
    {
        Serial.println("/music not found");
        return "";
    }

    FsFile file;
    char filename[128];

    while(file.openNext(&dir, O_RDONLY))
    {
        file.getName(filename, sizeof(filename));

        Serial.print("FOUND FILE: ");
        Serial.println(filename);

        String name = String(filename);

        file.close();

        dir.close();

        return name;
    }

    dir.close();

    Serial.println("Folder empty");

    return "";
}