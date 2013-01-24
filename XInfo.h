#ifndef XINFO_H
#define XINFO_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct XInfo 
{
    Display *display;
    int     screen;
    Window  window;
    GC      gc[4];

    Pixmap  pixmap;     // double buffer
    int     width;      // size of pixmap
    int     height;
    int     prevWidth;
    int     prevHeight;
};

#endif