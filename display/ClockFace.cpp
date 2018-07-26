#include "ClockFace.h"

void StandardClockFace::DrawHand(double degrees, double length, bool thick, uint16_t color)
{
    auto x = cos(deg(90 - degrees)) * length;
    auto y = sin(deg(90 - degrees)) * length;

    display.drawLine(static_cast<int16_t>(mid_x), static_cast<int16_t>(mid_y), static_cast<int16_t>(mid_x + x), static_cast<int16_t>(mid_y - y), color);

    if (thick)
    {
        display.drawLine(static_cast<int16_t>(mid_x - 1), static_cast<int16_t>(mid_y), static_cast<int16_t>(mid_x - 1 + x), static_cast<int16_t>(mid_y - y), color);
        display.drawLine(static_cast<int16_t>(mid_x + 1), static_cast<int16_t>(mid_y), static_cast<int16_t>(mid_x + 1 + x), static_cast<int16_t>(mid_y - y), color);
        display.drawLine(static_cast<int16_t>(mid_x), static_cast<int16_t>(mid_y - 1), static_cast<int16_t>(mid_x + x), static_cast<int16_t>(mid_y - 1 - y), color);
        display.drawLine(static_cast<int16_t>(mid_x), static_cast<int16_t>(mid_y + 1), static_cast<int16_t>(mid_x + x), static_cast<int16_t>(mid_y + 1 - y), color);
    }
}

void StandardClockFace::initialize(uint16_t color)
{
    auto i = 5;

    display.drawRoundRect(i, i, w - 2 * i, h - 2 * i, minorHalfSize / 2, color);
    display.fillCircle(static_cast<int16_t>(mid_x), static_cast<int16_t>(mid_y), static_cast<int16_t>(5), color);
}

void StandardClockFace::draw(const tm& time, uint16_t color)
{
    DrawHand(((time.tm_hour % 12) * DegHour) + time.tm_min / 2, hour, true, color);
    DrawHand((time.tm_min) * DegMin + time.tm_sec / 10, minute, true, color);
    DrawHand((time.tm_sec) * DegSec, second, false, color);

    display.setTextSize(1);
    display.setTextColor(color);
    display.setCursor(display.width() / 2 - 15, display.height() / 2 - 40);
    display.print("Nexus");
}

void DigitalClockFace::initialize(uint16_t color)
{
}

void DigitalClockFace::draw(const tm& time, uint16_t color)
{
    char tm[9];
    sprintf_s(tm, "%02d:%02d:%02d", time.tm_hour, time.tm_min, time.tm_sec);
    tm[8] = '\0';

    display.setTextSize(2);
    display.setTextColor(color);
    display.setCursor(25, display.height() / 2 - 40);
    display.print(tm);
}
