#include "ButtonWindow.h"



ButtonWindow::ButtonWindow(PaintBoxProps *pbs)
	:
	PaintBoxWindow(pbs)
{
	this->caption = NULL;
	this->bgColor = NULL;
	this->bgColorHover = NULL;
	this->bgColorClick = NULL;
	this->currentBGColor = NULL;
	this->color = NULL;
	this->currentColor = NULL;
	this->prevColor = NULL;
	this->font = NULL;
	this->currentFont = this->font;
}

void ButtonWindow::OnPaint()
{
	using namespace Gdiplus;
	static HDC hdc;
	static PAINTSTRUCT ps;

	hdc = BeginPaint(this->hWnd, &ps);

	DIMS wDims = this->GetWDims();
	RectF clRect(0.f, 0.f, wDims.width * 1.f, wDims.height * 1.f);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, wDims.width, wDims.height);
	SelectObject(hdcMem, hBmp);
	Graphics graphics(hdcMem);

	SolidBrush sb(Color(0));
	
	if (this->currentBGColor != NULL) {
		sb.SetColor(*this->currentBGColor);
		graphics.FillRectangle(&sb, clRect);
	}
	if (this->currentColor != NULL) {
		StringFormat sf;
		sf.SetAlignment(StringAlignment::StringAlignmentCenter);
		sf.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		sb.SetColor(*this->currentColor);
		graphics.DrawString(this->caption, -1, this->font, clRect, &sf, &sb);
	}

	BitBlt(hdc, 0,0, wDims.width, wDims.height, hdcMem, 0,0, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBmp);
	EndPaint(this->hWnd, &ps);
}

void ButtonWindow::OnLButtonDown()
{
	if (this->bgColorClick != NULL) {
		this->prevBGColor = this->currentBGColor;
		this->currentBGColor = this->bgColorClick;
	}
	RedrawWindow(this->hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void ButtonWindow::OnLButtonUp()
{
	if (this->bgColorClick != NULL)
		this->currentBGColor = this->prevBGColor;
	RedrawWindow(this->hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void ButtonWindow::OnMouseHover()
{
	if (this->bgColorHover != NULL)
		this->currentBGColor = this->bgColorHover;
	RedrawWindow(this->hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void ButtonWindow::OnMouseLeave()
{
	if (this->bgColorHover != NULL)
		this->currentBGColor = this->bgColor;
	RedrawWindow(this->hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void ButtonWindow::SetCaption(const wchar_t *caption)
{
	this->caption = caption;
}

void ButtonWindow::SetFont(const Gdiplus::Font *font)
{
	this->font = font;
}

void ButtonWindow::SetColor(const Gdiplus::Color *color)
{
	this->color = color;
	this->currentColor = color;
}

void ButtonWindow::SetBGColor(const Gdiplus::Color *bgColor)
{
	this->bgColor = bgColor;
	this->currentBGColor = bgColor;
}

void ButtonWindow::SetBGColorHover(const Gdiplus::Color *bgColorHover)
{
	this->bgColorHover = bgColorHover;
}

void ButtonWindow::SetBGColorClick(const Gdiplus::Color *bgColorClick)
{
	this->bgColorClick = bgColorClick;
}

int ButtonWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static WORD mouseTracking = TRUE;

	switch (uMsg) {
	case WM_MOUSEMOVE:
		if (mouseTracking) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = 1;
			tme.hwndTrack = this->hWnd;
			TrackMouseEvent(&tme);
		}
		break;
	case WM_MOUSEHOVER:
		mouseTracking = FALSE;
		this->OnMouseHover();
		break;
	case WM_MOUSELEAVE:
		mouseTracking = TRUE;
		this->OnMouseLeave();
		break;
	case WM_LBUTTONDOWN:
		this->OnLButtonDown();
		SendMessage(this->hWndParent, WM_COMMAND, 0x0000 << 16 | this->ID, (LPARAM)this->hWnd);
		break;
	case WM_LBUTTONUP:
		this->OnLButtonUp();
		break;
	default:
		return PaintBoxWindow::WndProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}