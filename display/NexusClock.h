#pragma once
#include "ClockFace.h"
#include "DisplayDriver.h"

#define BLACK 0
#define WHITE 1

#ifndef ARDUINO

using namespace std::chrono_literals;
#define delay(time) std::this_thread::sleep_for(0.5s)

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
NexusClock* GetNexusClock(tm& time);
