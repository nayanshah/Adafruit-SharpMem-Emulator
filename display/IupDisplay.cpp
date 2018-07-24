#include "IupDisplay.h"
#include <iup_plus.h>

cdCanvas* IupDisplay::cd_canvas;
int16_t IupDisplay::_width, IupDisplay::_height;

void IupDisplay::begin()
{
    mainLoopThread = std::thread([this]()
    {
        printf("Starting render\n");
        render();
        printf("End render\n");
    });

    mainLoopThread.detach();

    // This is a hack. We need to wait for the render to complete before
    // we can return.
    std::this_thread::sleep_for(100ms);
}

void IupDisplay::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    cdCanvasPixel(cd_canvas, x, y, 0);
}

int IupDisplay::canvas_action_cb(Ihandle* canvas)
{
    printf("canvas action\n");

    unsigned int ri, gi, bi;
    cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "cdCanvas");
    Ihandle* config = (Ihandle*)IupGetAttribute(canvas, "CONFIG");
    const char* background = "208 208 208";

    cdCanvasActivate(cd_canvas);

    /* draw the background */
    sscanf_s(background, "%u %u %u", &ri, &gi, &bi);
    cdCanvasBackground(cd_canvas, cdEncodeColor((unsigned char)ri, (unsigned char)gi, (unsigned char)bi));
    cdCanvasClear(cd_canvas);

    /* black line around the image */
    cdCanvasForeground(cd_canvas, CD_BLACK);
    cdCanvasLineWidth(cd_canvas, 1);
    cdCanvasLineStyle(cd_canvas, CD_CONTINUOUS);

    cdCanvasFlush(cd_canvas);

    return IUP_DEFAULT;
}

int IupDisplay::canvas_map_cb(Ihandle* canvas)
{
    cd_canvas = cdCreateCanvas(CD_IUPDBUFFER, canvas);
    IupSetAttribute(canvas, "cdCanvas", (char*)cd_canvas);
    return IUP_DEFAULT;
}

int IupDisplay::canvas_unmap_cb(Ihandle* canvas)
{
    cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "cdCanvas");
    cdKillCanvas(cd_canvas);
    return IUP_DEFAULT;
}

void IupDisplay::refresh()
{
    cdCanvasFlush(cd_canvas);
}

int IupDisplay::render()
{
    Ihandle *dlg, *vbox, *canvas;

    IupOpen(0, NULL);

    canvas = IupCanvas(NULL);
    IupSetAttribute(canvas, "NAME", "CANVAS");
    IupSetAttribute(canvas, "SCROLLBAR", "No");
    IupSetCallback(canvas, "ACTION", (Icallback)IupDisplay::canvas_action_cb);
    IupSetCallback(canvas, "MAP_CB", (Icallback)IupDisplay::canvas_map_cb);
    IupSetCallback(canvas, "UNMAP_CB", (Icallback)IupDisplay::canvas_unmap_cb);

    vbox = IupVbox(
        canvas,
        NULL
    );

    dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "Simulated Display");
    IupSetAttribute(dlg, "SIZE", "150x200");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupSetAttribute(dlg, "USERSIZE", NULL);

    IupMainLoop();
    IupClose();

    return 0;
}

int IupDisplay::clearDisplay()
{
    cdCanvasClear(cd_canvas);
    return 0;
}
