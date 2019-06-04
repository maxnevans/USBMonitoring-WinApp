#include "ImageButtonWindow.h"



ImageButtonWindow::ImageButtonWindow(PaintBoxProps *pbs)
	:
	ButtonWindow(pbs)
{
	this->bgImage = NULL;
	this->bgImageClick = NULL;
	this->bgImageHover = NULL;
	this->currentBGImage = NULL;
	this->prevBGImage = NULL;
}


void ImageButtonWindow::OnPaint() {
	using namespace Gdiplus;
	static HDC hdc;
	static PAINTSTRUCT ps;

	DIMS wDims = this->GetWDims();
	hdc = BeginPaint(this->hWnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, wDims.width , wDims.height);
	SelectObject(hdcMem, hBmp);
	Graphics graphics(hdcMem);

	SolidBrush sb(Color(0));
	if (this->currentBGColor != NULL) {
		sb.SetColor(*this->currentBGColor);
		graphics.FillRectangle(&sb, Rect(0, 0, wDims.width, wDims.height));
	}
	if (this->currentBGImage != NULL) {
		graphics.DrawImage(this->currentBGImage, Rect(0, 0, wDims.width, wDims.height));
	}
	if (this->currentColor != NULL) {
		StringFormat sf;
		sf.SetAlignment(StringAlignment::StringAlignmentCenter);
		sf.SetLineAlignment(StringAlignment::StringAlignmentCenter);
		sb.SetColor(*this->currentColor);
		graphics.DrawString(this->caption, -1, this->font, RectF(0.f, 0.f, wDims.width * 1.f, wDims.height * 1.f), &sf, &sb);
	}

	BitBlt(hdc, 0,0, wDims.width, wDims.height, hdcMem, 0,0, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBmp);
	EndPaint(this->hWnd, &ps);
}

void ImageButtonWindow::OnMouseHover()
{
	if (this->bgImageHover != NULL)
		this->currentBGImage = this->bgImageHover;
	ButtonWindow::OnMouseHover();
}

void ImageButtonWindow::OnMouseLeave()
{
	if (this->bgImageHover != NULL)
		this->currentBGImage = this->bgImage;
	ButtonWindow::OnMouseLeave();
}

void ImageButtonWindow::OnLButtonDown()
{
	if (this->bgImageClick != NULL) {
		this->prevBGImage = this->currentBGImage;
		this->currentBGImage = this->bgImageClick;
	}
	ButtonWindow::OnLButtonDown();
}

void ImageButtonWindow::OnLButtonUp()
{
	if (this->bgImageClick != NULL)
		this->currentBGImage = this->prevBGImage;
	ButtonWindow::OnLButtonUp();
}

void ImageButtonWindow::SetBGImage(Gdiplus::Image *bgImage)
{
	this->bgImage = bgImage;
	this->currentBGImage = bgImage;
}

void ImageButtonWindow::SetBGImageHover(Gdiplus::Image *bgImageHover)
{
	this->bgImageHover = bgImageHover;
}

void ImageButtonWindow::SetBGImageClick(Gdiplus::Image *bgImageClick)
{
	this->bgImageClick = bgImageClick;
}


int ImageButtonWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ButtonWindow::WndProc(hWnd, uMsg, wParam, lParam);
}