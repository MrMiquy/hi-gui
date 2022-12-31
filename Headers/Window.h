#ifndef _main_h
#define _main_h

#undef UNICODE
#define UNICODE

#include <windows.h>

MSG Msg;

typedef struct HI_Window {
    WNDCLASSEX wc;
    HWND hwnd;
    LRESULT CALLBACK (*WndProc)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
} HI_Window;

LRESULT CALLBACK ChldWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
HI_Window* HI_CreateWindow(WCHAR* window_name, WCHAR* class_name, int width, int height, HI_Window* parent);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI HI_Run(void);

#endif // _main_h
