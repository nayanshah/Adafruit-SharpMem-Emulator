#include "IupDisplay.h"

Pixels IupDisplay::_pixels;
int16_t IupDisplay::_width, IupDisplay::_height;

void IupDisplay::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    _pixels.push_back(make_pair(x, y));
}

int IupDisplay::canvas_action_cb(Ihandle* canvas)
{
    unsigned int ri, gi, bi;
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "cdCanvas");
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

    cdCanvasRect(cd_canvas, 0, IupDisplay::_width, 0, IupDisplay::_height);

    for (auto pixel : IupDisplay::_pixels)
    {
        cdCanvasPixel(cd_canvas, pixel.first, pixel.second, 0);
    }

    cdCanvasFlush(cd_canvas);

    return IUP_DEFAULT;
}

int IupDisplay::canvas_map_cb(Ihandle* canvas)
{
    cdCanvas* cd_canvas = cdCreateCanvas(CD_IUPDBUFFER, canvas);
    IupSetAttribute(canvas, "cdCanvas", (char*)cd_canvas);
    return IUP_DEFAULT;
}

int IupDisplay::canvas_unmap_cb(Ihandle* canvas)
{
    cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(canvas, "cdCanvas");
    cdKillCanvas(cd_canvas);
    return IUP_DEFAULT;
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
        NULL);

    dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "Virtual Display");
    IupSetAttribute(dlg, "SIZE", "150x200");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupSetAttribute(dlg, "USERSIZE", NULL);

    IupMainLoop();
    IupClose();

    return 0;
}

int IupDisplay::reset()
{
    return 0;
}
