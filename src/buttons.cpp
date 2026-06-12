#include <Arduino.h>
#include "config.h"

void initButtons()
{
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);

    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);

    pinMode(BTN_OK, INPUT_PULLUP);
    pinMode(BTN_BACK, INPUT_PULLUP);

    pinMode(BTN_VOLUP, INPUT_PULLUP);
    pinMode(BTN_VOLDOWN, INPUT_PULLUP);
}

bool upPressed()
{
    return digitalRead(BTN_UP)==LOW;
}

bool downPressed()
{
    return digitalRead(BTN_DOWN)==LOW;
}

bool okPressed()
{
    return digitalRead(BTN_OK)==LOW;
}