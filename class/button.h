#ifndef BUTTON_H
#define BUTTON_H

#include "initcontrols.h"


class button_c : public initcontrols_c
{
    public:
        button_c(HWND hWnd, const char * text, int lang, int left, int top, int width, int height);
        virtual ~button_c();
    protected:
    private:
};

#endif // BUTTON_H
