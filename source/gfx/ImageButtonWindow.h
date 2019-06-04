#pragma once
#include "ButtonWindow.h"
class ImageButtonWindow :
	public ButtonWindow
{
public:
	ImageButtonWindow(PaintBoxProps *pbs);
	void SetBGImage(Gdiplus::Image *bgImage);
	void SetBGImageHover(Gdiplus::Image *bgImageHover);
	void SetBGImageClick(Gdiplus::Image *bgImageClick);

protected:
	virtual void OnPaint();
	virtual void OnMouseHover();
	virtual void OnMouseLeave();
	virtual void OnLButtonUp();
	virtual void OnLButtonDown();
	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	Gdiplus::Image *bgImage;
	Gdiplus::Image *prevBGImage;
	Gdiplus::Image *currentBGImage;
	Gdiplus::Image *bgImageHover;
	Gdiplus::Image *bgImageClick;
};

