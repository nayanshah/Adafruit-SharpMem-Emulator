#pragma once
#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <vector>
#include <iup.h>
#include <cd.h>
#include <cdiup.h>
#include <thread>

using namespace std;

typedef vector<pair<int16_t, int16_t>> Pixels;

class IupDisplay
{
public:
    IupDisplay(int16_t width, int16_t height)
    {
        _width = width;
        _height = height;
    }

    bool begin();
    int render();
    int clearDisplay();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void refresh();

private:
    static cdCanvas *cd_canvas;

    static Pixels _pixels;
    static int16_t _width;
    static int16_t _height;

    static int canvas_action_cb(Ihandle* canvas);
    static int canvas_map_cb(Ihandle* canvas);
    static int canvas_unmap_cb(Ihandle* canvas);
    static int timer_cb(Ihandle*);

    std::thread mainLoopThread;
};
