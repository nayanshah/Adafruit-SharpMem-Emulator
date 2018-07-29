#pragma once
#include "ClockFace.h"
#include "DisplayDriver.h"

#define BLACK 0
#define WHITE 1

#ifndef ARDUINO
inline void delay(uint16_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
};
#endif

class NexusClock
{
    DisplayDriver& display;
    tm& displayTime;
    IClockFace& clockFace;
    bool dark;
    uint16_t foreground, background;

public:
    NexusClock(DisplayDriver& disp, IClockFace& clockFace, tm& time, uint16_t foreground, uint16_t background) : display(disp), clockFace(clockFace), displayTime(time), foreground(foreground), background(background) {};
    bool setup();
    void loop();
};

void pulse(tm& time);
IClockFace* GetClockFace(int id, DisplayDriver* display);
NexusClock* GetNexusClock(tm& time, int face = 0, bool dark = false);
