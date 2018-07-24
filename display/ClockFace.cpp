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

void StandardClockFace::draw(struct tm const &time, uint16_t color)
{
    DrawHand(((time.tm_hour % 12) * DegHour) + time.tm_min / 2, hour, true, color);
    DrawHand((time.tm_min) * DegMin + time.tm_sec / 10, minute, true, color);
    DrawHand((time.tm_sec) * DegSec, second, false, color);
}
