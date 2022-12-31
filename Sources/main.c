#include "../Headers/Window.h"

int main(int argc, char *argv[]) {
    HI_Window* win = HI_CreateWindow(L"Taste of", L"taste", 600, 400, NULL);
    HI_Window* win2 = HI_CreateWindow(L"Red", L"red", 300, 100, win);

    return HI_Run();
}
