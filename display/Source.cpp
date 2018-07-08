#include "Adafruit_Iup.h"
#include <algorithm>

#define WIDTH 144
#define HEIGHT 168

#define BLACK 0
#define WHITE 1

int minorHalfSize;

Adafruit_Iup display(WIDTH, HEIGHT);

void testdrawroundrect(void) {
    for (int i = 0; i<minorHalfSize / 2; i += 2) {
        display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i, minorHalfSize / 2, BLACK);
        display.refresh();
    }
}

int main()
{
    minorHalfSize = min(display.width(), display.height()) / 2;
    testdrawroundrect();

    display.render();
    return 0;
}
