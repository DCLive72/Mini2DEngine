#pragma once

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Engine
{
private:
	HWND hwnd = nullptr;

	ID2D1Factory* factory = nullptr;
	ID2D1HwndRenderTarget* renderTarget = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

	bool running = true;

public:
	bool Initialize(HINSTANCE hInstance, int nCmdShow);
	int Run();

private:
	bool CreateWindowClass(HINSTANCE hInstance, int nCmdShow);
	bool InitializeDirect2D();

	void Update();
	void Render();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};