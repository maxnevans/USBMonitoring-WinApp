#include "PaintBoxWindow.h"



PaintBoxWindow::PaintBoxWindow(PaintBoxProps *pbs)
	:
	BaseWindow()
{
	CWS cws = { 0 };
	cws.lpClassName = CLASS_NAME;
	cws.lpWindowName = NULL;
	cws.dwStyle = WS_CHILD;
	cws.x = pbs->x;
	cws.y = pbs->y;
	cws.nWidth = pbs->nWidth;
	cws.nHeight = pbs->nHeight;
	cws.hWndParent = pbs->hWndParent;
	cws.hInstance = pbs->hInstance;
	cws.lpParam = 0;
	this->ResetCWS(&cws);
	this->CreateWnd();
}

int PaintBoxWindow::Register(HINSTANCE hInstance) {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.lpszClassName = CLASS_NAME;
	wcex.lpfnWndProc = (WNDPROC)BaseWindow::_WndProc;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	return (int)RegisterClassEx(&wcex);
}

int PaintBoxWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
		this->OnPaint();
		break;
	case WM_ERASEBKGND:
		return TRUE;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void PaintBoxWindow::OnPaint() {
	return;
}

void PaintBoxWindow::Update() {
	RedrawWindow(this->hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}
