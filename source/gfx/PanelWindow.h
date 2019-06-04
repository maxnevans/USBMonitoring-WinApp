#pragma once
#include "PaintBoxWindow.h"


class PanelWindow :
	public PaintBoxWindow
{
public:
	PanelWindow(PaintBoxProps *pbs);
	void SetCaption(const wchar_t *caption);
	void SetColor(const Gdiplus::Color *color);
	void SetBGColor(const Gdiplus::Color *bgColor);
	void SetFont(const Gdiplus::Font *font);

protected:
	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnPaint();
private:

	const Gdiplus::Color *bgColor;
	const Gdiplus::Color *color;
	const Gdiplus::Font *font;
	const wchar_t *caption;
};

