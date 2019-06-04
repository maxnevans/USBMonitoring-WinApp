#pragma once
#include "BaseWindow.h"
#include <gdiplus.h>

class PaintBoxWindow :
	public BaseWindow
{
public:
	typedef struct _PaintBoxProps {
		HINSTANCE hInstance;
		int x;
		int y;
		int nWidth;
		int nHeight;
		HWND hWndParent;
	} PaintBoxProps, *PPaintBoxProps;
public:
	PaintBoxWindow(PaintBoxProps *pbs);
	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static int Register(HINSTANCE hInstance);
	virtual void OnPaint();
	virtual void Update();
private:
	static constexpr wchar_t CLASS_NAME[] = L"PaintBox";
};

