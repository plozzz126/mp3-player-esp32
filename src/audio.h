#pragma once

void initAudio();
void audioLoop();
void playMP3(const char* path);
void stopAudio();
bool isPlaying();