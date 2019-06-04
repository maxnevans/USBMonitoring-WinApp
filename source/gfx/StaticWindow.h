#pragma once
#include "PaintBoxWindow.h"

class StaticWindow :
	public PaintBoxWindow
{
public:
	StaticWindow(PaintBoxProps *pbs);
	void SetCaption(const wchar_t *caption);
	void SetBGColor(const Gdiplus::Color *bgColor);
	void SetColor(const Gdiplus::Color *color);
	void SetFont(const Gdiplus::Font *font);
	void SetStringFormat(Gdiplus::StringFormat *stringFormat);

protected:
	virtual void OnPaint();
private:
	const Gdiplus::Color *bgColor;
	const Gdiplus::Color *color;
	const Gdiplus::Font *font;
	Gdiplus::StringFormat *stringFormat;
	const wchar_t *caption;
};

