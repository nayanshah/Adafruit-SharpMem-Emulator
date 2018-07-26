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

public:
    NexusClock(DisplayDriver& disp, IClockFace& clockFace, tm& time) : display(disp), clockFace(clockFace), displayTime(time) {};
    bool setup();
    void loop();
};

void pulse(tm& time);
IClockFace* GetClockFace(int id, DisplayDriver* display);
NexusClock* GetNexusClock(tm& time, int face = 0);
