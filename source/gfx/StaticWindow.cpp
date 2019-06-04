#include "StaticWindow.h"

StaticWindow::StaticWindow(PaintBoxProps *pbs)
	:
	PaintBoxWindow(pbs)
{
	this->bgColor = NULL;
	this->color = new Gdiplus::Color(0xFFFFFFFF);
	this->font = new Gdiplus::Font(&Gdiplus::FontFamily(L"Tahoma"), 12);
	this->caption = NULL;
	this->stringFormat = new Gdiplus::StringFormat();
	this->stringFormat->SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	this->stringFormat->SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
}

void StaticWindow::SetCaption(const wchar_t * caption)
{
	if (caption == NULL) return;
	this->caption = caption;
}

void StaticWindow::SetBGColor(const Gdiplus::Color * bgColor)
{
	if (bgColor == NULL) return;
	this->bgColor = bgColor;
}

void StaticWindow::SetColor(const Gdiplus::Color * color)
{
	if (color == NULL) return;
	this->color = color;
}

void StaticWindow::SetFont(const Gdiplus::Font * font)
{
	if (font == NULL) return;
	this->font = font;
}

void StaticWindow::SetStringFormat(Gdiplus::StringFormat * stringFormat)
{
	if (stringFormat == NULL) return;
	this->stringFormat = stringFormat;
}

void StaticWindow::OnPaint()
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

	if (this->bgColor != NULL) {
		sb.SetColor(*this->bgColor);
		graphics.FillRectangle(&sb, clRect);
	}
	if (this->color != NULL && this->caption != NULL && this->font != NULL && this->stringFormat != NULL) {
		sb.SetColor(*this->color);
		graphics.DrawString(this->caption, -1, this->font, clRect, this->stringFormat, &sb);
	}

	BitBlt(hdc, 0, 0, wDims.width, wDims.height, hdcMem, 0, 0, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBmp);
	EndPaint(this->hWnd, &ps);
}