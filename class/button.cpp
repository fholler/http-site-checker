#include "button.h"

button_c::button_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height)
{
   Wnd = CreateWindow("BUTTON",
                      text,
                      WS_VISIBLE | WS_CHILD,
                      left,
                      top,
                      width,
                      height,
                      hWnd,
                      NULL,
                      NULL,
                      NULL);    //ctor
  langId = lang;
}

button_c::~button_c()
{
    //dtor
}
