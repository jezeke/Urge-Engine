#include <stdlib.h>
#include <unistd.h> //debug
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//#include <X11/extensions/Xshm.h>

#include "logging.h"
#include "init_threads.h"

Window createWindow(Display *display, int hoz, int vert, int xOffset, int yOffset);

void* render_main(void *data)
{
  Display *display;
  Window win;
  int done = 0;

  renderData *rData = (renderData*)data;
  const int hoz = rData->hoz;
  const int vert = rData->vert;
  const int fps = rData->fps;

  display = XOpenDisplay(getenv("DISPLAY"));
  if(display == NULL)
  {
    logging("Render error: cannot connect to X server.");
    rData->returnCode = 1;
  }

  const unsigned int display_width = DisplayWidth(display, DefaultScreen(display));
  const unsigned int display_height = DisplayHeight(display, DefaultScreen(display));

  if(hoz > display_width || vert > display_height)
  { //oversized windows spawn within bounds of display
    logging("Render warning: Oversized window, continuing.");
    win = createWindow(display, hoz, vert, 0, 0);
  }
  else
  { //spawn in middle of screen if it'll fit
    const int xOffset = (display_width - hoz) / 2;
    const int yOffset = (display_height - vert) / 2;

    win = createWindow(display, hoz, vert, xOffset, yOffset);
  }

  sleep(3); //debug

  XCloseDisplay(display);
  rData->returnCode = 0;

  return NULL;
}

Window createWindow(Display *display, int hoz, int vert, int xOffset, int yOffset)
{
  const int screen = DefaultScreen(display);
  Window win;
  XSizeHints hint; //hack to get window spawning in middle of screen

  win = XCreateSimpleWindow(display, RootWindow(display, screen), xOffset, yOffset, hoz, vert, 2, BlackPixel(display, screen), WhitePixel(display, screen));

  hint.x = xOffset;
  hint.y = yOffset;
  hint.flags = PPosition;

  XSetNormalHints(display, win, &hint);
  XMapWindow(display, win);
  XFlush(display);

  return win;
}
