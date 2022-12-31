#include "../Headers/Window.h"

HI_Window* HI_CreateWindow(WCHAR* window_name, WCHAR* class_name, int width, int height, HI_Window* parent) {
    HI_Window* window = (HI_Window*)malloc(sizeof(HI_Window));
    if (window == NULL) {
        return NULL;
    }
    window->wc.cbSize = sizeof(WNDCLASSEX);
    window->wc.style = 0;
    if (parent) {
        window->WndProc = ChldWndProc;
    } else {
        window->WndProc = WndProc;
    }
    window->wc.lpfnWndProc = window->WndProc;
    window->wc.cbClsExtra = 0;
    window->wc.cbWndExtra = 0;

    HINSTANCE hInstance = GetModuleHandle( NULL );

    window->wc.hInstance     = hInstance;
    window->wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    window->wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    window->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    window->wc.lpszMenuName  = NULL;
    window->wc.lpszClassName = class_name;
    window->wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&window->wc)) {
        free(window);
        return NULL;
    }

    HWND _parent = parent == NULL? NULL : parent->hwnd;
    window->hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        class_name,
        window_name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        _parent, NULL, hInstance, NULL);

    ShowWindow(window->hwnd, SW_SHOW);
    UpdateWindow(window->hwnd);

    return window;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChldWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI HI_Run(void) {
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
