#include "Adafruit_Iup.h"
#include <algorithm>
#include <thread>

#define WIDTH 144
#define HEIGHT 168

#define BLACK 0
#define WHITE 1

#define PI 3.14159265

using namespace std::chrono_literals;

#include <ctime>

inline double deg(double degree)
{
    return (degree) * PI / 180;
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

tm getCurrentTime()
{
    time_t now = std::time(0);
    tm time;
    localtime_s(&time, &now);
    return time;
}

class IClockFace
{
public:
    virtual ~IClockFace() {}
    virtual void draw(struct tm const &time, uint16_t color) = 0;
};

class StandardClockFace : public IClockFace
{
    Adafruit_GFX &display;
    int16_t w, h;
    double mid_x, mid_y;
    int minorHalfSize;
    double hour, minute, second;

    static const int16_t DegHour = 30, DegMin = 6, DegSec = 6;

    void DrawHand(double degrees, double length, bool thick = false, uint16_t color = BLACK);

public:
    StandardClockFace(Adafruit_GFX &disp) : display(disp)
    {
        w = display.width(), h = display.height();
        mid_x = w / 2, mid_y = h / 2;
        minorHalfSize = min(w, h) / 2;
        hour = 0.6 * minorHalfSize, minute = 0.75 * minorHalfSize, second = 0.9 * minorHalfSize;
    }

    void initialize();
    void draw(struct tm const &time, uint16_t color);
};

void StandardClockFace::DrawHand(double degrees, double length, bool thick, uint16_t color)
{
    auto x = cos(deg(90 - degrees)) * length;
    auto y = sin(deg(90 - degrees)) * length;

    display.drawLine(mid_x, mid_y, mid_x + x, mid_y + y, color);
    if (thick)
    {
        display.drawLine(mid_x - 1, mid_y, mid_x - 1 + x, mid_y + y, color);
        display.drawLine(mid_x + 1, mid_y, mid_x + 1 + x, mid_y + y, color);
        display.drawLine(mid_x, mid_y - 1, mid_x + x, mid_y - 1 + y, color);
        display.drawLine(mid_x, mid_y + 1, mid_x + x, mid_y + 1 + y, color);
    }
}

void StandardClockFace::initialize()
{
    auto i = 5;

    display.drawRoundRect(i, i, w - 2 * i, h - 2 * i, minorHalfSize / 2, BLACK);
    display.fillCircle(mid_x, mid_y, 5, BLACK);
}

void StandardClockFace::draw(struct tm const &time, uint16_t color)
{
    DrawHand(((time.tm_hour % 12) * DegHour) + time.tm_min / 2, hour, true, color);
    DrawHand((time.tm_min) * DegMin + time.tm_sec / 10, minute, true, color);
    DrawHand((time.tm_sec) * DegSec, second, color);
}

Adafruit_Iup display(WIDTH, HEIGHT);
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
        clockFace.initialize(); // draws a box. need a better name.
        clockFace.draw(display_time, BLACK);
        display.refresh();

        pulse(display_time);

        std::this_thread::sleep_for(1s);
    }

    return 0;
}
