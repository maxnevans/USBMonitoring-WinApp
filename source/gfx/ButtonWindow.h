#pragma once
#include "PaintBoxWindow.h"

class ButtonWindow :
	public PaintBoxWindow
{
public:
	ButtonWindow(PaintBoxProps *pbs);
	void SetCaption(const wchar_t *caption);
	void SetFont(const Gdiplus::Font *font);
	void SetColor(const Gdiplus::Color *color);
	void SetBGColor(const Gdiplus::Color *bgColor);
	void SetBGColorHover(const Gdiplus::Color *bgColorHover);
	void SetBGColorClick(const Gdiplus::Color *bgColorClick);

protected:
	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnPaint();
	virtual void OnLButtonUp();
	virtual void OnLButtonDown();
	virtual void OnMouseHover();
	virtual void OnMouseLeave();

protected:
	const wchar_t *caption;

	const Gdiplus::Font *font;
	const Gdiplus::Font *currentFont;
	
	const Gdiplus::Color *color;
	const Gdiplus::Color *currentColor;
	const Gdiplus::Color *prevColor;
	const Gdiplus::Color *bgColor;
	const Gdiplus::Color *currentBGColor;
	const Gdiplus::Color *prevBGColor;
	const Gdiplus::Color *bgColorHover;
	const Gdiplus::Color *bgColorClick;
};

