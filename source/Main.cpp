#include <windows.h>
#include <gdiplus.h>

#include "MainWindow.h"
#include "gfx/ButtonWindow.h"
#include "gfx/PanelWindow.h"
#include "gfx/GraphWindow.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hInstPrev,_In_opt_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	MainWindow::Register(hInstance);
	ButtonWindow::Register(hInstance);
	ImageButtonWindow::Register(hInstance);
	PanelWindow::Register(hInstance);
	GraphWindow::Register(hInstance);
	StaticWindow::Register(hInstance);

	MainWindow wnd(hInstance);

	MSG msg = {0};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}