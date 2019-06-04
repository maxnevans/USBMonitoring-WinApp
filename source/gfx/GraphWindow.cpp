#include "GraphWindow.h"



GraphWindow::GraphWindow(PaintBoxProps *pbs)
	:
	PaintBoxWindow(pbs)
{
	this->bgColor = NULL;
	this->ruleColor = NULL;
	this->maxValue = 100;
	this->minValue = 0;
	this->step = 1;
	this->maxSteps = this->GetWDims().width;
	this->slicer.color = NULL;
	this->slicer.visible = FALSE;
	this->slicer.x = 0;
	
	RECT rectWindow;
	GetWindowRect(this->hWnd, &rectWindow);
	this->wWidth = rectWindow.right - rectWindow.left;
	this->wHeight = rectWindow.bottom - rectWindow.top;

	this->maxSteps = this->wWidth / this->step;
	this->valueFactor = (this->maxValue - this->minValue) / (this->wHeight * 1.f);
}

void GraphWindow::SetBGColor(const Gdiplus::Color *bgColor)
{
	this->bgColor = bgColor;
}

void GraphWindow::SetRuleColor(const Gdiplus::Color *ruleColor)
{
	this->ruleColor = ruleColor;
}

void GraphWindow::SetMaxValue(int maxValue)
{
	this->maxValue = maxValue;
}

void GraphWindow::SetMinValue(int minValue)
{
	this->minValue = minValue;
}

void GraphWindow::SetStep(int step)
{
	this->step = step;
}

void GraphWindow::SetMaxSteps(int maxSteps)
{
	this->maxSteps = maxSteps;
}

void GraphWindow::Init(InitStruct *gis)
{
	this->bgColor = gis->bgColor;
	this->ruleColor = gis->ruleColor;
	this->maxValue = gis->maxValue;
	this->minValue = gis->minValue;
	this->step = gis->step;
	this->slicer.color = gis->slicerColor;
}

GraphWindow::GCH GraphWindow::SetCursor(const Gdiplus::Color *cursorColor, int cursorValue)
{
	CursorData cd;
	GCH hNewCursor = START_GCH + this->cData.size();
	cd.color = cursorColor;
	cd.value = cursorValue;
	cd.handle = hNewCursor;
	this->cData.push_back(cd);
	return hNewCursor;
}

void GraphWindow::SetCursorColor(GCH gch, const Gdiplus::Color *cursorColor)
{
	CursorData *cur = this->GetCursor(gch);
	if (cur == NULL) return;
	cur->color = cursorColor;
}

void GraphWindow::SetCursorValue(GCH gch, int value)
{
	CursorData *cur = this->GetCursor(gch);
	if (cur == NULL) return;
	cur->value = value;
}

int GraphWindow::GetCurrentSlicerValue(GCH gch)
{
	CursorData *cur = this->GetCursor(gch);
	if (cur == NULL)
		return 0;

	int retval = 0;
	int x = 0;

	for (CursorData& cur : cData)
	{
		int value = cur.value;

		if (this->slicer.x >= x && this->slicer.x < x + this->step)
			retval = value;

		x += this->step;
	}

	return retval;
}

bool GraphWindow::IsSlicerActive()
{
	return this->slicer.visible;
}

void GraphWindow::Update()
{
	this->UpdateGraph();
	PaintBoxWindow::Update();
}

void GraphWindow::SetSlicerColor(const Gdiplus::Color *slicerColor)
{
	this->slicer.color = slicerColor;
}

GraphWindow::CursorData* GraphWindow::GetCursor(GCH gch)
{
	if (this->cData[gch - START_GCH].handle != gch) return NULL;
	return &(this->cData[gch - START_GCH]);
}

void GraphWindow::UpdateGraph()
{
	for (CursorData& cursor : this->cData)
	{
		cursor.list.push_front(cursor.value);
		while (cursor.list.size() > this->maxSteps)
			cursor.list.pop_back();
	

		this->UpdateGFXData(cursor);
	}
}

void GraphWindow::UpdateGFXData(CursorData& cur)
{
	if (cur.list.size() != cur.gfxPts.size())
		cur.gfxPts.resize(cur.list.size());

	int itr = 0;
	for (int value : cur.list)
	{
		cur.gfxPts[itr] = Gdiplus::Point(itr * this->step, int(value * this->valueFactor));
		itr++;
	}
}

void GraphWindow::OnPaint()
{
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(this->hWnd, &ps);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmp = CreateCompatibleBitmap(hdc, this->wWidth, this->wHeight);
	SelectObject(hdcMem, hBmp);

	RECT rect;
	GetClientRect(this->hWnd, &rect);
	Gdiplus::RectF clRect(0.f, 0.f, rect.right * 1.f, rect.bottom * 1.f);

	Gdiplus::Graphics graphics(hdcMem);

	Gdiplus::SolidBrush sb(Gdiplus::Color(0));
	Gdiplus::Pen pen(Gdiplus::Color(0));

	if (this->bgColor != NULL) {
		sb.SetColor(*this->bgColor);
		graphics.FillRectangle(&sb, clRect);
	}

	float factor = rect.bottom / ((this->maxValue - this->minValue) * 1.f);
	
	for (CursorData cur: this->cData) {
		
		if (cur.color != NULL) {
			pen.SetColor(*cur.color);
			graphics.DrawLines(&pen, cur.gfxPts.data(), cur.gfxPts.size());
		}
	}

	if (this->slicer.visible && (this->slicer.color != NULL)) {
		pen.SetColor(*this->slicer.color);
		graphics.DrawLine(&pen, this->slicer.x, 0, this->slicer.x, this->wHeight);
	}

	BitBlt(hdc, 0, 0, this->wWidth, this->wHeight, hdcMem, 0, 0, SRCCOPY);
	DeleteDC(hdcMem);
	DeleteObject(hBmp);
	EndPaint(this->hWnd, &ps);
}

void GraphWindow::OnMouseMove(DWORD x, DWORD y)
{
	this->slicer.x = x;
}

void GraphWindow::OnMouseHover()
{
	this->slicer.visible = TRUE;
}

void GraphWindow::OnMouseLeave()
{
	this->slicer.visible = FALSE;
}

int GraphWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static WORD mouseTracking = TRUE;
	switch (uMsg) {
	case WM_MOUSEHOVER:
		mouseTracking = FALSE;
		this->OnMouseHover();
		break;
	case WM_MOUSELEAVE:
		mouseTracking = TRUE;
		this->OnMouseLeave();
		break;
	case WM_MOUSEMOVE:
		this->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		if (mouseTracking) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = 1;
			tme.hwndTrack = this->hWnd;
			TrackMouseEvent(&tme);
		}
		break;
	case WM_ERASEBKGND:
		return TRUE;
	default:
		return PaintBoxWindow::WndProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}