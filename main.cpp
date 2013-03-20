#if run
#include <windows.h>
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x502
#include <stdio.h>
#endif

#include "resource.h"
#include "class/systemdefault.h"
#include "class/language.h"
#include "class/dropdownlist.h"
#include "class/font.h"
#include "class/controlcollections.h"
#include "class/staticlabel.h"
#include "class/button.h"
#include "class/setupfile.h"


HINSTANCE hInstance;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

dropdownlist_c * langlist;
controlcollections_c * controls;
button_c * closebutton;
setupfile_c * setup;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
//////////////////////////////////////////////////////////////
  WNDCLASS wnd;
  wnd.style = CS_HREDRAW | CS_VREDRAW; //we will explain this later
  wnd.lpfnWndProc = WndProc;
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hInstance = hInstance;
  wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION); //default icon
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);   //default arrow mouse cursor
  wnd.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wnd.lpszMenuName = NULL;                     //no menu
  wnd.lpszClassName = TEXT("HTTPSiteCheck");
  if(!RegisterClass(&wnd)) {
    MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
    return 0;
  }
///////////////////////////////////////////////////////////////
  hInstance = hInst;
  MSG msg;
  HWND hwnd;

  RECT rc;
  GetWindowRect(GetDesktopWindow(), &rc);

  hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
                        TEXT("HTTPSiteCheck"),
                        TEXT("HTTP Site Check"),
                        WS_VISIBLE | WS_SYSMENU | WS_CAPTION ,
                        (rc.right-400)/2,
                        (rc.bottom-300)/2,
                        400,
                        300,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
  ShowWindow(hwnd, iCmdShow);              //display the window on the screen
///////////////////////////////////////////////////////////////
  InitSystem();
  setup = new setupfile_c;
  InitLang();
  language->setSetup(setup);
  controls = new controlcollections_c;
  font_c * font = new font_c;
  font->setSizeName(10,"Tahoma");
  font->create();
  controls->setFont(font);
  controls->addControl(new staticlabel_c(hwnd, "Language:", 1, 10, 10, 200, 24));
  langlist = (dropdownlist_c*)controls->addControl(new dropdownlist_c(hwnd, 10, 35, 370, 12));
  controls->addControl(new button_c(hwnd, "Back", 2, 107, 237, 85, 24));
  controls->addControl(new button_c(hwnd, "Next", 3, 202, 237, 85, 24));
  closebutton = (button_c*)controls->addControl(new button_c(hwnd, "Finish", 4, 297, 237, 85, 24));
  language->allLangToCombo(langlist);
  controls->setLanguage(language);
///////////////////////////////////////////////////////////////
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch(msg) {
    case WM_COMMAND: {
      if ((DWORD)lParam == (DWORD)langlist->Wnd) {
        if (CBN_SELCHANGE == HIWORD(wParam)) {
          delete language->setCurrentByLabel(langlist->getCurText());
          controls->setLanguage(language);
        }
      } else if ((DWORD)lParam == (DWORD)closebutton->Wnd) {
        SendMessage(hwnd,WM_DESTROY,0,0);
      }
      return 0;
    }
    case WM_CREATE:
      SendMessage(hwnd, (UINT)WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(ICON_MAIN)));
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
