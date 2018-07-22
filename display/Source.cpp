#include "Adafruit_Iup.h"
#include <algorithm>

#define WIDTH 144
#define HEIGHT 168

#define BLACK 0
#define WHITE 1

#define PI 3.14159265

struct Point
{
public:
    int16_t X, Y;
    Point(int16_t x, int16_t y)
    {
        X = x;
        Y = y;
    }
};

struct ClockHand;
#include <chrono>
using namespace std::chrono;

tm getCurrentTime()
{
    auto now = system_clock::to_time_t(system_clock::now());

    tm time;
    localtime_s(&time, &now);

    return time;
}


inline double deg(double degree)
{
    return (degree) * PI / 180;
}


class IClockFace
{
public:
    virtual ~IClockFace() {}
    virtual void draw(struct tm const &time) = 0;
};

class StandardClockFace : public IClockFace
{
    Adafruit_GFX &display;
    int16_t w, h;
    double mid_x, mid_y;
    static const int16_t DegHour = 30, DegMin = 6, DegSec = 6;

    void DrawHand(double degrees, double length, bool thick = false);

public:
    StandardClockFace(Adafruit_GFX &disp) : display(disp)
    {
        w = display.width(), h = display.height();
        mid_x = w / 2, mid_y = h / 2;
    }

    void draw(struct tm const &time);
};

void StandardClockFace::DrawHand(double degrees, double length, bool thick)
{
    auto x = cos(deg(90 - degrees)) * length;
    auto y = sin(deg(90 - degrees)) * length;

    display.drawLine(mid_x, mid_y, mid_x + x, mid_y + y, BLACK);
    if (thick)
    {
        display.drawLine(mid_x - 1, mid_y, mid_x - 1 + x, mid_y + y, BLACK);
        display.drawLine(mid_x + 1, mid_y, mid_x + 1 + x, mid_y + y, BLACK);
        display.drawLine(mid_x, mid_y - 1, mid_x + x, mid_y - 1 + y, BLACK);
        display.drawLine(mid_x, mid_y + 1, mid_x + x, mid_y + 1 + y, BLACK);
    }
}

void StandardClockFace::draw(struct tm const &time)
{
    auto i = 5;
    auto minorHalfSize = min(w, h) / 2;

    display.drawRoundRect(i, i, w - 2 * i, h - 2 * i, minorHalfSize / 2, BLACK);
    display.fillCircle(mid_x, mid_y, 5, BLACK);

    auto hour = 0.6 * minorHalfSize, minute = 0.75 * minorHalfSize, second = 0.9 * minorHalfSize;

    DrawHand(((time.tm_hour % 12) * DegHour) + time.tm_min / 2, hour, true);
    DrawHand((time.tm_min) * DegMin, minute, true);
    DrawHand((time.tm_sec) * DegSec, second);
}


void ShowClock()
{
    Adafruit_Iup display(WIDTH, HEIGHT);
    StandardClockFace clockFace(display);

    auto time = getCurrentTime();

    clockFace.draw(time);
    display.render();

    display.reset();
}


int main()
{
    //display.print("0x"); //display.println(0xDEADBEEF, HEX);

    for (int i = 0; i < 5; i++)
    {
        ShowClock();
    }

    return 0;
}
