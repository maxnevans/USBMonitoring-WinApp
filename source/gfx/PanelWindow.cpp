#include "PanelWindow.h"



PanelWindow::PanelWindow(PaintBoxProps *pbs)
	:
	PaintBoxWindow(pbs)
{
}

void PanelWindow::SetCaption(const wchar_t *caption)
{
	this->caption = caption;
}

void PanelWindow::SetColor(const Gdiplus::Color *color)
{
	this->color = color;
}

void PanelWindow::SetBGColor(const Gdiplus::Color *bgColor)
{
	this->bgColor = bgColor;
}

void PanelWindow::SetFont(const Gdiplus::Font *font)
{
	this->font = font;
}

void PanelWindow::OnPaint()
{
	using namespace Gdiplus;
	static HDC hdc;
	static PAINTSTRUCT ps;

	hdc = BeginPaint(this->hWnd, &ps);

	DIMS wDims = this->GetWDims();

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, wDims.width, wDims.height);

	RectF clRect(0.f, 0.f, wDims.width * 1.f, wDims.height * 1.f);
	RectF cptRect(0.f, 0.f, wDims.width * 1.f, 40.f);

	Graphics graphics(hdc);
	SolidBrush sb(Color(0));

	if (this->bgColor != NULL) {
		sb.SetColor(*this->bgColor);
		graphics.FillRectangle(&sb, clRect);
	}

	if (this->color != NULL) {
		StringFormat sf;
		sf.SetAlignment(StringAlignment::StringAlignmentCenter);
		sf.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		sb.SetColor(*this->color);
		graphics.DrawString(this->caption, -1, this->font, cptRect, &sf, &sb);
	}
	DeleteDC(hdcMem);
	DeleteObject(hBmp);

	EndPaint(this->hWnd, &ps);
}

int PanelWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_COMMAND:
		SendMessage(this->hWndParent, WM_COMMAND, wParam, lParam);
		break;
	case WM_NCHITTEST:
		return HTTRANSPARENT;
	default:
		return PaintBoxWindow::WndProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
