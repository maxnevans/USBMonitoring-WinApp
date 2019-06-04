#include "BaseWindow.h"

BaseWindow::BaseWindow() {
	this->ID = NULL;
	this->cws = { 0 };
	this->hInstance = 0;
	this->hWnd = NULL;
	this->hWndParent = NULL;
}

BaseWindow::BaseWindow(CWS *cws)
{
	this->cws = *cws;
	this->hInstance = cws->hInstance;
	this->hWnd = NULL;
	this->hWndParent = cws->hWndParent;
	this->ID = NULL;
}

LRESULT CALLBACK BaseWindow::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BaseWindow *c = reinterpret_cast<BaseWindow*>(GetWindowLong(hWnd, GWLP_USERDATA));

	if (c == NULL)
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	return c->WndProc(hWnd, uMsg, wParam, lParam);
}

void BaseWindow::CreateWnd()
{
	this->hWnd = CreateWindow(
		cws.lpClassName,
		cws.lpWindowName,
		cws.dwStyle,
		cws.x, cws.y,
		cws.nWidth, cws.nHeight,
		cws.hWndParent,
		cws.hMenu,
		cws.hInstance,
		cws.lpParam
	);
	if (this->hWnd == NULL) {
		wchar_t strBuf[256];
		DWORD err = GetLastError();
		wsprintf(strBuf, L"Could not create window [%s] '%s'. Error: %d.", cws.lpClassName , cws.lpWindowName, err);
		MessageBox(NULL, strBuf, L"Create Window Error", MB_OK | MB_ICONERROR);
		return;
	}
	SetWindowLong(this->hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));
}

void BaseWindow::ResetCWS(CWS *cws)
{
	this->cws = *cws;
	this->hInstance = cws->hInstance;
	this->hWndParent = cws->hWndParent;
}

HWND BaseWindow::GetHWND()
{
	return this->hWnd;
}

BaseWindow::DIMS BaseWindow::GetWDims()
{
	if (this->hWnd == NULL) return { 0 };

	DIMS dims;
	RECT wndRect;
	GetWindowRect(this->hWnd, &wndRect);
	dims.width = wndRect.right - wndRect.left;
	dims.height = wndRect.bottom - wndRect.top;
	dims.x = wndRect.left;
	dims.y = wndRect.top;
	return dims;
}

BaseWindow::DIMS BaseWindow::GetCDims()
{
	if (this->hWnd == NULL) return { 0 };

	DIMS dims;
	RECT cltRect;
	GetClientRect(this->hWnd, &cltRect);
	dims.width = cltRect.right - cltRect.left;
	dims.height = cltRect.bottom - cltRect.top;
	dims.x = cltRect.left;
	dims.y = cltRect.top;
	return dims;
}


void BaseWindow::SetID(DWORD ID)
{
	this->ID = ID;
}

void BaseWindow::Show()
{
	ShowWindow(this->hWnd, SW_SHOW);
}

void BaseWindow::Hide()
{
	ShowWindow(this->hWnd, SW_HIDE);
}
