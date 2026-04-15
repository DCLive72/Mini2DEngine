#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <chrono>

#pragma comment(lib, "d2d1.lib")

class Engine
{
private:
	HWND hwnd = nullptr;

	ID2D1Factory* factory = nullptr;
	ID2D1HwndRenderTarget* renderTarget = nullptr;
	ID2D1SolidColorBrush* brush = nullptr;

	bool running = true;

	float playerX = 100.0f;
	float playerY = 100.0f;
	float playerSpeed = 300.0f; // px por segundo

	bool keyLeft = false;
	bool keyRight = false;
	bool keyUp = false;
	bool keyDown = false;

	std::chrono::steady_clock::time_point lastFrameTime;
	float deltaTime = 0.0f;

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