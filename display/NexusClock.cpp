#include "NexusClock.h"

void NexusClock::loop(void)
{
    clockFace.initialize(BLACK);

    clockFace.draw(displayTime, WHITE);
    pulse(displayTime);
    clockFace.draw(displayTime, BLACK);

    display.refresh();
    delay(900); // to account for slow refresh rate
}

bool NexusClock::setup(void)
{
    // start & clear the display
    if (!display.begin())
    {
        return false;
    }

    display.clearDisplay();

    clockFace.initialize(BLACK);
    display.refresh();

    return true;
}

void pulse(tm& time)
{
    time.tm_sec++;
    if (time.tm_sec >= 60)
    {
        time.tm_sec -= 60;
        time.tm_min++;
    }

    if (time.tm_min > 60)
    {
        time.tm_min -= 60;
        time.tm_hour++;
    }

    if (time.tm_hour > 23)
    {
        time.tm_hour -= 24;
    }
}

NexusClock* GetNexusClock(tm& time, int face)
{
    DisplayDriver* display = GetDisplayDriver();
    IClockFace* clockFace = GetClockFace(face, display);
    NexusClock* clk = new NexusClock(*display, *clockFace, time);
    return clk;
}

IClockFace* GetClockFace(int id, DisplayDriver* display)
{
    switch (id)
    {
    case 1:
        return new DigitalClockFace(*display);
    default:
        return new StandardClockFace(*display);
    }
}

DisplayDriver* GetDisplayDriver()
{
#ifdef ARDUINO
    // any pins can be used
#define SHARP_SCK  4
#define SHARP_MOSI 5
#define SHARP_SS   6

    DisplayDriver* display = new DisplayDriver(SHARP_SCK, SHARP_MOSI, SHARP_SS, WIDTH, HEIGHT);
#else
    DisplayDriver* display = new DisplayDriver(WIDTH, HEIGHT);
#endif // ARDUINO

    return display;
}
