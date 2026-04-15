#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	if (!CreateWindowClass(hInstance, nCmdShow))
		return false;
	if (!InitializeDirect2D())
		return false;

	return true;
}

bool Engine::CreateWindowClass(HINSTANCE hInstance, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Mini2DEngineWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Mini 2D Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd)
        return false;

    ShowWindow(hwnd, nCmdShow);

    return true;
}

bool Engine::InitializeDirect2D()
{
    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &factory
    );

    if (FAILED(hr))
        return false;

    RECT rc;
    GetClientRect(hwnd, &rc);

    hr = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hwnd,
            D2D1::SizeU(
                rc.right - rc.left,
                rc.bottom - rc.top
            )
        ),
        &renderTarget
    );

    if (FAILED(hr))
        return false;

    hr = renderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &brush
    );

    return SUCCEEDED(hr);
}

int Engine::Run()
{
    MSG msg = {};

    while (running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                running = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Update();
        Render();
    }

    return 0;
}

void Engine::Update()
{
    // lógica del juego
}

void Engine::Render()
{
    renderTarget->BeginDraw();

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    renderTarget->DrawRectangle(
        D2D1::RectF(100, 100, 200, 200),
        brush,
        3.0f
    );

    renderTarget->EndDraw();
}

LRESULT CALLBACK Engine::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}