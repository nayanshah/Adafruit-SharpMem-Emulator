#pragma once

#include "Adafruit_GFX.h"
#include "IupDisplay.h"

class Adafruit_Iup : public Adafruit_GFX, public IupDisplay
{
public:
    Adafruit_Iup(int16_t w, int16_t h)
        : Adafruit_GFX(w, h), IupDisplay(w, h)
    {
    }

    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        IupDisplay::drawPixel(x, y, color);
    }
};
