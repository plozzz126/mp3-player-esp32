#include "audio.h"
#include "config.h"

#include <AudioTools.h>

I2SStream i2s;

void initAudio()
{
    auto config = i2s.defaultConfig(TX_MODE);

    config.pin_bck = I2S_BCLK;
    config.pin_ws  = I2S_LRC;
    config.pin_data = I2S_DIN;

    config.sample_rate = 44100;
    config.bits_per_sample = 16;
    config.channels = 2;

    i2s.begin(config);

    Serial.println("I2S OK");
}

void audioLoop()
{
}

void playMP3(const char* path)
{
    Serial.print("PLAY: ");
    Serial.println(path);
}

void stopAudio()
{
}

bool isPlaying()
{
    return false;
}