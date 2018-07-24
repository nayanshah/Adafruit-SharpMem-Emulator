#include "DisplayDriver.h"
#include "ClockFace.h"

#define WIDTH 144
#define HEIGHT 168

#define BLACK 0
#define WHITE 1

using namespace std::chrono_literals;

#include <ctime>

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

tm getCurrentTime()
{
    time_t now = std::time(0);
    tm time;
    localtime_s(&time, &now);
    return time;
}

DisplayDriver display(WIDTH, HEIGHT);
StandardClockFace clockFace(display);

int main()
{
    //display.print("0x"); //display.println(0xDEADBEEF, HEX);

    auto display_time = getCurrentTime();

    display.begin();

    for (;;)
    {
        printf("Drawing...\n");

        display.clearDisplay();
        clockFace.initialize(BLACK); // draws a box. need a better name.
        clockFace.draw(display_time, BLACK);

        display.print("Hello"); //display.println(0xDEADBEEF, HEX);
        display.refresh();

        pulse(display_time);

        std::this_thread::sleep_for(1s);
    }

    return 0;
}
