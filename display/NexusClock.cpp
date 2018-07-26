#include "NexusClock.h"

void NexusClock::loop(void)
{
    clockFace.initialize(BLACK);
    clockFace.draw(displayTime, BLACK);

    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(display.width() / 2 - 15, display.height() / 2 - 40);
    display.print("Nexus");

    display.refresh();
    delay(900); // to account for slow refresh rate

    clockFace.draw(displayTime, WHITE);
    display.refresh();

    pulse(displayTime);
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

NexusClock* GetNexusClock(tm& time)
{
    DisplayDriver* display = GetDisplayDriver();
    StandardClockFace* clockFace = new StandardClockFace(*display);
    NexusClock* clk = new NexusClock(*display, *clockFace, time);
    return clk;
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
