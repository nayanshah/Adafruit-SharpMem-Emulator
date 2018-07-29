#pragma once
#include <ctime>

#ifdef ARDUINO
#include <Adafruit_GFX.h>
#else
#include "Adafruit_GFX.h"
#endif

class IClockFace
{
public:
    virtual ~IClockFace() {}
    virtual void initialize(uint16_t color) = 0;
    virtual void draw(const tm& time, uint16_t color) = 0;
};

class StandardClockFace : public IClockFace
{
    Adafruit_GFX &display;
    int16_t w, h;
    double mid_x, mid_y;
    int minorHalfSize;
    double hour, minute, second;

    static const int16_t DegHour = 30, DegMin = 6, DegSec = 6;

    void DrawHand(double degrees, double length, bool thick, uint16_t color);

public:
    StandardClockFace(Adafruit_GFX &disp) : display(disp)
    {
        w = display.width(), h = display.height();
        mid_x = w / 2, mid_y = h / 2;
        minorHalfSize = min(w, h) / 2;
        hour = 0.6 * minorHalfSize, minute = 0.75 * minorHalfSize, second = 0.9 * minorHalfSize;
    }

    void initialize(uint16_t color);
    void draw(const tm& time, uint16_t color);
};

class DigitalClockFace : public IClockFace
{
    Adafruit_GFX &display;
    int16_t w, h;
    double mid_x, mid_y;
    int minorHalfSize;
    double hour, minute, second;

    static const int16_t DegHour = 30, DegMin = 6, DegSec = 6;

public:
    DigitalClockFace(Adafruit_GFX &disp) : display(disp)
    {
        w = display.width(), h = display.height();
        mid_x = w / 2, mid_y = h / 2;
        minorHalfSize = min(w, h) / 2;
        hour = 0.6 * minorHalfSize, minute = 0.75 * minorHalfSize, second = 0.9 * minorHalfSize;
    }

    void initialize(uint16_t color);
    void draw(const tm& time, uint16_t color);
};
