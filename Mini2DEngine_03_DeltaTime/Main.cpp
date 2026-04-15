#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow)
    {
        Engine engine;

        if (!engine.Initialize(hInstance, nCmdShow))
            return -1;

        return engine.Run();
    }