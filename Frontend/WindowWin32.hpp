#pragma once

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite") //todo solve this properly

#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <string>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Window.hpp"

class WindowWin32 : public Window
{
public:
	WindowWin32();
	~WindowWin32();

	bool init() override;
	void run() override;

	void drawTexture(const std::string filename, int x, int y) override;

private:
	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();

	HRESULT DrawHelloWorld();

	// Process and dispatch messages
	void RunMessageLoop();

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Draw content.
	HRESULT OnRender();

	// Resize the render target.
	void OnResize(
		UINT width,
		UINT height
		);

	// The windows procedure.
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
		);

private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
};

