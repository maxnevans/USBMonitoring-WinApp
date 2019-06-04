#include "AppView.h"

using namespace Gdiplus;

AppView::AppView(HINSTANCE hInstance, HWND hWnd, int wndInitWidth, int wndInitHeight)
	:
	Icons(new AppIcons()),
	Fonts(new AppFonts()),
	Colors(new AppColors()),
	pnlTitleBar(new Panel()),
	ibtnClose(new ImageButton()),
	ibtnMinimize(new ImageButton()),
	pnlStatusBar(new Panel()),
	sAppStatusMessage(new Static()),
	pnlWorkScreen(new Panel()),
	pnlMainData(new Panel()),
	pnlCurrentData(new Panel()),
	sCurrentDataPanelCaption(new Static()),
	sCurrentVoltageDesc(new Static()),
	sCurrentVoltageValue(new Static()),
	sCurrentAmperageDesc(new Static()),
	sCurrentAmperageValue(new Static()),
	sCurrentPowerDesc(new Static()),
	sCurrentPowerValue(new Static()),
	gphGraph(new Graph()),
	pnlGraphControls(new Panel()),
	pnlSlicerValues(new Panel()),
	sSlicerVoltageDesc(new Static()),
	sSlicerVoltageValue(new Static()),
	sSlicerAmperageDesc(new Static()),
	sSlicerAmperageValue(new Static()),
	sSlicerPowerDesc(new Static()),
	sSlicerPowerValue(new Static())
{
	using namespace Gdiplus;

	this->hWnd = hWnd;
	this->hInstance = hInstance;
	this->wndWidth = wndInitWidth;
	this->wndHeight = wndInitHeight;

	this->Icons->smallIconPath = L"images\\icon.ico";
	this->Icons->bigIconPath = L"images\\icon.ico";

	this->Fonts->Normal = new Font(&FontFamily(L"Tahoma"), 9);
	this->Fonts->Header1 = new Font(&FontFamily(L"Tahoma"), 14);
	this->Fonts->Header2 = new Font(&FontFamily(L"Tahoma"), 11);
	this->Fonts->Header3 = new Font(&FontFamily(L"Tahoma"), 10);
	this->Fonts->Caption = new Font(&FontFamily(L"Tahoma"), 7);
	
	this->Colors->Main = new Color(0xFF113344);
	this->Colors->FirstDominant = new Color(0xFF001122);
	this->Colors->SecondDominant = new Color(0xFF224455);
	this->Colors->NormalFont = new Color(0xFFFFFFFF);
	this->Colors->Header1Font = new Color(0xFFFFFFFF);
	this->Colors->Header2Font = new Color(0xFFFFFFFF);
	this->Colors->Header3Font = new Color(0xFFFFFFFF);
	this->Colors->CaptionFont = new Color(0xFFFFFFFF);

	this->pnlTitleBar->bgColor = this->Colors->FirstDominant;
	this->pnlTitleBar->color = this->Colors->CaptionFont;
	this->pnlTitleBar->font = this->Fonts->Caption;
	this->pnlTitleBar->hWndParent = this->hWnd;
	this->pnlTitleBar->obj = NULL;
	this->pnlTitleBar->caption = L"Usb Monitor";
	this->pnlTitleBar->initWidth = this->wndWidth;
	this->pnlTitleBar->initHeight = 25;
	this->pnlTitleBar->initX = 0;
	this->pnlTitleBar->initY = 0;
	this->CreatePanel(this->pnlTitleBar);

	this->ibtnClose->bgColor = this->Colors->FirstDominant;
	this->ibtnClose->bgColorClick = NULL;
	this->ibtnClose->bgColorHover = new Color(0xFFB42828);
	this->ibtnClose->bgImage = NULL;
	this->ibtnClose->bgImageClick = NULL;
	this->ibtnClose->bgImageHover = NULL;
	this->ibtnClose->color = this->Colors->NormalFont;
	this->ibtnClose->font = this->Fonts->Normal;
	this->ibtnClose->hWndParent = this->pnlTitleBar->obj->GetHWND();
	this->ibtnClose->obj = NULL;
	this->ibtnClose->caption = L"x";
	this->ibtnClose->initWidth = 25;
	this->ibtnClose->initHeight = 25;
	this->ibtnClose->initX = this->wndWidth - 25;
	this->ibtnClose->initY = 0;
	this->ibtnClose->ID = IDB_SYSCLOSE;
	this->CreateImageButton(this->ibtnClose);

	this->ibtnMinimize->bgColor = this->Colors->FirstDominant;
	this->ibtnMinimize->bgColorClick = NULL;
	this->ibtnMinimize->bgColorHover = this->Colors->Main;
	this->ibtnMinimize->bgImage = NULL;
	this->ibtnMinimize->bgImageClick = NULL;
	this->ibtnMinimize->bgImageHover = NULL;
	this->ibtnMinimize->color = this->Colors->NormalFont;
	this->ibtnMinimize->font = this->Fonts->Normal;
	this->ibtnMinimize->hWndParent = this->pnlTitleBar->obj->GetHWND();
	this->ibtnMinimize->obj = NULL;
	this->ibtnMinimize->caption = L"_";
	this->ibtnMinimize->initWidth = 25;
	this->ibtnMinimize->initHeight = 25;
	this->ibtnMinimize->initX = this->wndWidth - 50;
	this->ibtnMinimize->initY = 0;
	this->ibtnMinimize->ID = IDB_SYSMINIMIZE;
	this->CreateImageButton(this->ibtnMinimize);

	this->pnlStatusBar->bgColor = this->Colors->FirstDominant;
	this->pnlStatusBar->color = this->Colors->CaptionFont;
	this->pnlStatusBar->font = this->Fonts->Caption;
	this->pnlStatusBar->hWndParent = this->hWnd;
	this->pnlStatusBar->obj = NULL;
	this->pnlStatusBar->caption = L"Status Bar";
	this->pnlStatusBar->initWidth = this->wndWidth;
	this->pnlStatusBar->initHeight = 25;
	this->pnlStatusBar->initX = 0;
	this->pnlStatusBar->initY = this->wndHeight - this->pnlStatusBar->initHeight;
	this->CreatePanel(this->pnlStatusBar);

	this->sAppStatusMessage->bgColor = this->Colors->FirstDominant;
	this->sAppStatusMessage->color = this->Colors->CaptionFont;
	this->sAppStatusMessage->font = this->Fonts->Caption;
	this->sAppStatusMessage->stringFormat = new StringFormat();
	this->sAppStatusMessage->stringFormat->SetAlignment(StringAlignment::StringAlignmentNear);
	this->sAppStatusMessage->stringFormat->SetLineAlignment(StringAlignment::StringAlignmentCenter);
	this->sAppStatusMessage->hWndParent = this->pnlStatusBar->obj->GetHWND();
	this->sAppStatusMessage->obj = NULL;
	this->sAppStatusMessage->caption = L"Status";
	this->sAppStatusMessage->initWidth = this->pnlStatusBar->obj->GetWDims().width;
	this->sAppStatusMessage->initHeight = this->pnlStatusBar->obj->GetWDims().height;
	this->sAppStatusMessage->initX = 20;
	this->sAppStatusMessage->initY = 0;
	this->CreateStatic(this->sAppStatusMessage);

	this->pnlWorkScreen->bgColor = this->Colors->FirstDominant;
	this->pnlWorkScreen->color = this->Colors->CaptionFont;
	this->pnlWorkScreen->font = this->Fonts->Caption;
	this->pnlWorkScreen->hWndParent = this->hWnd;
	this->pnlWorkScreen->obj = NULL;
	this->pnlWorkScreen->caption = L"Work Screen";
	this->pnlWorkScreen->initWidth = this->wndWidth;
	this->pnlWorkScreen->initHeight = this->wndHeight - 50;
	this->pnlWorkScreen->initX = 0;
	this->pnlWorkScreen->initY = 25;
	this->CreatePanel(this->pnlWorkScreen);

	this->pnlMainData->bgColor = this->Colors->Main;
	this->pnlMainData->color = this->Colors->CaptionFont;
	this->pnlMainData->font = this->Fonts->Caption;
	this->pnlMainData->hWndParent = this->pnlWorkScreen->obj->GetHWND();
	this->pnlMainData->obj = NULL;
	this->pnlMainData->caption = NULL;
	this->pnlMainData->initWidth = 300;
	this->pnlMainData->initHeight = 720 - 50;
	this->pnlMainData->initX = 0;
	this->pnlMainData->initY = 0;
	this->CreatePanel(this->pnlMainData);

	this->pnlCurrentData->bgColor = this->Colors->Main;
	this->pnlCurrentData->color = NULL;
	this->pnlCurrentData->font = NULL;
	this->pnlCurrentData->hWndParent = this->pnlMainData->obj->GetHWND();
	this->pnlCurrentData->obj = NULL;
	this->pnlCurrentData->caption = NULL;
	this->pnlCurrentData->initWidth = 300;
	this->pnlCurrentData->initHeight = this->pnlMainData->obj->GetWDims().height / 2;
	this->pnlCurrentData->initX = 0;
	this->pnlCurrentData->initY = 0;
	this->CreatePanel(this->pnlCurrentData);

	this->sCurrentDataPanelCaption->bgColor = this->Colors->FirstDominant;
	this->sCurrentDataPanelCaption->color = this->Colors->CaptionFont;
	this->sCurrentDataPanelCaption->font = this->Fonts->Caption;
	this->sCurrentDataPanelCaption->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentDataPanelCaption->obj = NULL;
	this->sCurrentDataPanelCaption->caption = L"Current Metrix";
	this->sCurrentDataPanelCaption->initWidth = 100;
	this->sCurrentDataPanelCaption->initHeight = 25;
	this->sCurrentDataPanelCaption->initX = (this->pnlCurrentData->obj->GetWDims().width - 100) / 2;
	this->sCurrentDataPanelCaption->initY = 20;
	this->CreateStatic(this->sCurrentDataPanelCaption);

	this->sCurrentVoltageDesc->bgColor = this->Colors->FirstDominant;
	this->sCurrentVoltageDesc->color = this->Colors->CaptionFont;
	this->sCurrentVoltageDesc->font = this->Fonts->Caption;
	this->sCurrentVoltageDesc->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentVoltageDesc->obj = NULL;
	this->sCurrentVoltageDesc->caption = L"Voltage";
	this->sCurrentVoltageDesc->initWidth = 100;
	this->sCurrentVoltageDesc->initHeight = 25;
	this->sCurrentVoltageDesc->initX = 0;
	this->sCurrentVoltageDesc->initY = 50;
	this->CreateStatic(this->sCurrentVoltageDesc);

	this->sCurrentVoltageValue->bgColor = this->Colors->FirstDominant;
	this->sCurrentVoltageValue->color = this->Colors->CaptionFont;
	this->sCurrentVoltageValue->font = this->Fonts->Caption;
	this->sCurrentVoltageValue->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentVoltageValue->obj = NULL;
	this->sCurrentVoltageValue->caption = L"XXX";
	this->sCurrentVoltageValue->initWidth = 100;
	this->sCurrentVoltageValue->initHeight = 25;
	this->sCurrentVoltageValue->initX = this->pnlCurrentData->obj->GetWDims().width - 100;
	this->sCurrentVoltageValue->initY = 50;
	this->CreateStatic(this->sCurrentVoltageValue);

	this->sCurrentAmperageDesc->bgColor = this->Colors->FirstDominant;
	this->sCurrentAmperageDesc->color = this->Colors->CaptionFont;
	this->sCurrentAmperageDesc->font = this->Fonts->Caption;
	this->sCurrentAmperageDesc->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentAmperageDesc->obj = NULL;
	this->sCurrentAmperageDesc->caption = L"Amperage";
	this->sCurrentAmperageDesc->initWidth = 100;
	this->sCurrentAmperageDesc->initHeight = 25;
	this->sCurrentAmperageDesc->initX = 0;
	this->sCurrentAmperageDesc->initY = 80;
	this->CreateStatic(this->sCurrentAmperageDesc);

	this->sCurrentAmperageValue->bgColor = this->Colors->FirstDominant;
	this->sCurrentAmperageValue->color = this->Colors->CaptionFont;
	this->sCurrentAmperageValue->font = this->Fonts->Caption;
	this->sCurrentAmperageValue->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentAmperageValue->obj = NULL;
	this->sCurrentAmperageValue->caption = L"XXX";
	this->sCurrentAmperageValue->initWidth = 100;
	this->sCurrentAmperageValue->initHeight = 25;
	this->sCurrentAmperageValue->initX = this->pnlCurrentData->obj->GetWDims().width - 100;
	this->sCurrentAmperageValue->initY = 80;
	this->CreateStatic(this->sCurrentAmperageValue);

	this->sCurrentPowerDesc->bgColor = this->Colors->FirstDominant;
	this->sCurrentPowerDesc->color = this->Colors->CaptionFont;
	this->sCurrentPowerDesc->font = this->Fonts->Caption;
	this->sCurrentPowerDesc->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentPowerDesc->obj = NULL;
	this->sCurrentPowerDesc->caption = L"Power";
	this->sCurrentPowerDesc->initWidth = 100;
	this->sCurrentPowerDesc->initHeight = 25;
	this->sCurrentPowerDesc->initX = 0;
	this->sCurrentPowerDesc->initY = 110;
	this->CreateStatic(this->sCurrentPowerDesc);

	this->sCurrentPowerValue->bgColor = this->Colors->FirstDominant;
	this->sCurrentPowerValue->color = this->Colors->CaptionFont;
	this->sCurrentPowerValue->font = this->Fonts->Caption;
	this->sCurrentPowerValue->hWndParent = this->pnlCurrentData->obj->GetHWND();
	this->sCurrentPowerValue->obj = NULL;
	this->sCurrentPowerValue->caption = L"XXX";
	this->sCurrentPowerValue->initWidth = 100;
	this->sCurrentPowerValue->initHeight = 25;
	this->sCurrentPowerValue->initX = this->pnlCurrentData->obj->GetWDims().width - 100;
	this->sCurrentPowerValue->initY = 110;
	this->CreateStatic(this->sCurrentPowerValue);

	this->gphGraph->bgColor = new Color(0xFFAAAAAA);
	this->gphGraph->ruleColor = new Color(0xFFFFAAAA);
	this->gphGraph->slicerColor = new Color(0xFF000000);
	this->gphGraph->voltageColor = new Color(0xFFFF0000);
	this->gphGraph->amperageColor = new Color(0xFF00FF00);
	this->gphGraph->minValue = 0;
	this->gphGraph->maxValue = 4096;
	this->gphGraph->step = 1;
	this->gphGraph->maxSteps = (this->wndWidth - 300) / this->gphGraph->step;
	this->gphGraph->hWndParent = this->pnlWorkScreen->obj->GetHWND();
	this->gphGraph->obj = NULL;
	this->gphGraph->initWidth = this->wndWidth - 300;
	this->gphGraph->initHeight = 720 - 75;
	this->gphGraph->initX = 300;
	this->gphGraph->initY = 0;
	this->CreateGraph(this->gphGraph);

	this->pnlGraphControls->bgColor = this->Colors->Main;
	this->pnlGraphControls->color = this->Colors->CaptionFont;
	this->pnlGraphControls->font = this->Fonts->Caption;
	this->pnlGraphControls->hWndParent = this->pnlWorkScreen->obj->GetHWND();
	this->pnlGraphControls->obj = NULL;
	this->pnlGraphControls->caption = L"Graph Controls";
	this->pnlGraphControls->initWidth = this->wndWidth - 300;
	this->pnlGraphControls->initHeight = 25;
	this->pnlGraphControls->initX = 300;
	this->pnlGraphControls->initY = 720 - 75;
	this->CreatePanel(this->pnlGraphControls);

	this->pnlSlicerValues->bgColor = this->Colors->Main;
	this->pnlSlicerValues->color = this->Colors->CaptionFont;
	this->pnlSlicerValues->font = this->Fonts->Caption;
	this->pnlSlicerValues->hWndParent = this->pnlGraphControls->obj->GetHWND();
	this->pnlSlicerValues->obj = NULL;
	this->pnlSlicerValues->caption = NULL;
	this->pnlSlicerValues->initWidth = 300;
	this->pnlSlicerValues->initHeight = 25;
	this->pnlSlicerValues->initX = 0;
	this->pnlSlicerValues->initY = 0;
	this->CreatePanel(this->pnlSlicerValues);

	this->sSlicerVoltageDesc->bgColor = this->Colors->FirstDominant;
	this->sSlicerVoltageDesc->color = this->Colors->CaptionFont;
	this->sSlicerVoltageDesc->font = this->Fonts->Caption;
	this->sSlicerVoltageDesc->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerVoltageDesc->obj = NULL;
	this->sSlicerVoltageDesc->caption = L"Voltage:";
	this->sSlicerVoltageDesc->initWidth = 57;
	this->sSlicerVoltageDesc->initHeight = 25;
	this->sSlicerVoltageDesc->initX = 0;
	this->sSlicerVoltageDesc->initY = 0;
	this->CreateStatic(this->sSlicerVoltageDesc);

	this->sSlicerVoltageValue->bgColor = this->Colors->FirstDominant;
	this->sSlicerVoltageValue->color = this->Colors->CaptionFont;
	this->sSlicerVoltageValue->font = this->Fonts->Caption;
	this->sSlicerVoltageValue->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerVoltageValue->obj = NULL;
	this->sSlicerVoltageValue->caption = L"X.XXX";
	this->sSlicerVoltageValue->initWidth = 40;
	this->sSlicerVoltageValue->initHeight = 25;
	this->sSlicerVoltageValue->initX = 57;
	this->sSlicerVoltageValue->initY = 0;
	this->CreateStatic(this->sSlicerVoltageValue);

	this->sSlicerAmperageDesc->bgColor = this->Colors->FirstDominant;
	this->sSlicerAmperageDesc->color = this->Colors->CaptionFont;
	this->sSlicerAmperageDesc->font = this->Fonts->Caption;
	this->sSlicerAmperageDesc->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerAmperageDesc->obj = NULL;
	this->sSlicerAmperageDesc->caption = L"Amperage:";
	this->sSlicerAmperageDesc->initWidth = 63;
	this->sSlicerAmperageDesc->initHeight = 25;
	this->sSlicerAmperageDesc->initX = 100;
	this->sSlicerAmperageDesc->initY = 0;
	this->CreateStatic(this->sSlicerAmperageDesc);

	this->sSlicerAmperageValue->bgColor = this->Colors->FirstDominant;
	this->sSlicerAmperageValue->color = this->Colors->CaptionFont;
	this->sSlicerAmperageValue->font = this->Fonts->Caption;
	this->sSlicerAmperageValue->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerAmperageValue->obj = NULL;
	this->sSlicerAmperageValue->caption = L"X.XXX";
	this->sSlicerAmperageValue->initWidth = 40;
	this->sSlicerAmperageValue->initHeight = 25;
	this->sSlicerAmperageValue->initX = 163;
	this->sSlicerAmperageValue->initY = 0;
	this->CreateStatic(this->sSlicerAmperageValue);

	this->sSlicerPowerDesc->bgColor = this->Colors->FirstDominant;
	this->sSlicerPowerDesc->color = this->Colors->CaptionFont;
	this->sSlicerPowerDesc->font = this->Fonts->Caption;
	this->sSlicerPowerDesc->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerPowerDesc->obj = NULL;
	this->sSlicerPowerDesc->caption = L"Power:";
	this->sSlicerPowerDesc->initWidth = 45;
	this->sSlicerPowerDesc->initHeight = 25;
	this->sSlicerPowerDesc->initX = 206;
	this->sSlicerPowerDesc->initY = 0;
	this->CreateStatic(this->sSlicerPowerDesc);

	this->sSlicerPowerValue->bgColor = this->Colors->FirstDominant;
	this->sSlicerPowerValue->color = this->Colors->CaptionFont;
	this->sSlicerPowerValue->font = this->Fonts->Caption;
	this->sSlicerPowerValue->hWndParent = this->pnlSlicerValues->obj->GetHWND();
	this->sSlicerPowerValue->obj = NULL;
	this->sSlicerPowerValue->caption = L"X.XXX";
	this->sSlicerPowerValue->initWidth = 40;
	this->sSlicerPowerValue->initHeight = 25;
	this->sSlicerPowerValue->initX = 251;
	this->sSlicerPowerValue->initY = 0;
	this->CreateStatic(this->sSlicerPowerValue);
}

void AppView::SetAppIcons()
{
	HANDLE iconSmall = LoadImage(NULL, this->Icons->smallIconPath, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	HANDLE iconBig = LoadImage(NULL, this->Icons->bigIconPath, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	SendMessage(this->hWnd, WM_SETICON, ICON_SMALL, (LPARAM)iconSmall);
	SendMessage(this->hWnd, WM_SETICON, ICON_BIG, (LPARAM)iconBig);
}

void AppView::SetAppWindowSize()
{
	RECT wRect;
	GetWindowRect(this->hWnd, &wRect);
	MoveWindow(this->hWnd, wRect.left, wRect.top, this->wndWidth, this->wndHeight, TRUE);
}

void AppView::UpdateFrame()
{
	this->gphGraph->obj->Update();
}

void AppView::ShowTitleBar()
{
	this->pnlTitleBar->obj->Show();
	this->ibtnClose->obj->Show();
	this->ibtnMinimize->obj->Show();
}

void AppView::HideTitleBar()
{
	this->pnlTitleBar->obj->Hide();
	this->ibtnClose->obj->Hide();
	this->ibtnMinimize->obj->Hide();
}

bool AppView::InTitleBarArea(int x, int y, int wndWidth, int wndHeight)
{
	return (x >= 0  && x <= wndWidth && y >= 0 && y <= 25);
}


void AppView::ShowStatusBar()
{
	this->pnlStatusBar->obj->Show();
	this->sAppStatusMessage->obj->Show();
}

void AppView::HideStatusBar()
{
	this->pnlStatusBar->obj->Hide();
}

void AppView::ShowWorkScreen()
{
	this->pnlWorkScreen->obj->Show();
	this->pnlMainData->obj->Show();
	this->pnlCurrentData->obj->Show();
	this->sCurrentDataPanelCaption->obj->Show();
	this->sCurrentVoltageDesc->obj->Show();
	this->sCurrentVoltageValue->obj->Show();
	this->sCurrentAmperageDesc->obj->Show();
	this->sCurrentAmperageValue->obj->Show();
	this->sCurrentPowerDesc->obj->Show();
	this->sCurrentPowerValue->obj->Show();
	this->gphGraph->obj->Show();
	this->pnlGraphControls->obj->Show();
	this->pnlSlicerValues->obj->Show();
	this->sSlicerVoltageDesc->obj->Show();
	this->sSlicerVoltageValue->obj->Show();
	this->sSlicerAmperageDesc->obj->Show();
	this->sSlicerAmperageValue->obj->Show();
	this->sSlicerPowerDesc->obj->Show();
	this->sSlicerPowerValue->obj->Show();
}

void AppView::HideWorkScreen()
{
	this->pnlWorkScreen->obj->Hide();
}

void AppView::SetCurrentVoltage(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.3f", value);
	this->sCurrentVoltageValue->obj->SetCaption(bufStr);
	this->sCurrentVoltageValue->obj->Update();
}

void AppView::SetCurrentAmperage(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.3f", value);
	this->sCurrentAmperageValue->obj->SetCaption(bufStr);
	this->sCurrentAmperageValue->obj->Update();
}

void AppView::SetCurrentPower(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.3f", value);
	this->sCurrentPowerValue->obj->SetCaption(bufStr);
	this->sCurrentPowerValue->obj->Update();
}

int AppView::GetSlicerVoltageUnconverted()
{
	return this->gphGraph->obj->GetCurrentSlicerValue(this->gphGraph->gchVoltage);
}

int AppView::GetSlicerAmperageUnconverted()
{
	return this->gphGraph->obj->GetCurrentSlicerValue(this->gphGraph->gchAmperage);
}

void AppView::SetGraphControlVoltage(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.2f", value);
	this->sSlicerVoltageValue->obj->SetCaption(bufStr);
	this->sSlicerVoltageValue->obj->Update();
}

void AppView::SetGraphControlAmperage(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.2f", value);
	this->sSlicerAmperageValue->obj->SetCaption(bufStr);
	this->sSlicerAmperageValue->obj->Update();
}

void AppView::SetGraphControlPower(float value)
{
	static wchar_t bufStr[256];
	swprintf_s(bufStr, L"%.2f", value);
	this->sSlicerPowerValue->obj->SetCaption(bufStr);
	this->sSlicerPowerValue->obj->Update();
}

void AppView::SetGraphVoltage(int value)
{
	this->gphGraph->obj->SetCursorValue(this->gphGraph->gchVoltage, value);
}

void AppView::SetGraphAmperage(int value)
{
	this->gphGraph->obj->SetCursorValue(this->gphGraph->gchAmperage, value);
}

bool AppView::IsCursorInGraphArea()
{
	return this->gphGraph->obj->IsSlicerActive();
}


void AppView::CreatePanel(Panel *pnl)
{
	PaintBoxWindow::PaintBoxProps pbs;
	pbs.hInstance = this->hInstance;
	pbs.hWndParent = pnl->hWndParent;
	pbs.nWidth = pnl->initWidth;
	pbs.nHeight = pnl->initHeight;
	pbs.x = pnl->initX;
	pbs.y = pnl->initY;
	pnl->obj = new PanelWindow(&pbs);
	pnl->obj->SetBGColor(pnl->bgColor);
	pnl->obj->SetCaption(pnl->caption);
	pnl->obj->SetColor(pnl->color);
	pnl->obj->SetFont(pnl->font);
}

void AppView::CreateButton(Button *btn)
{
	PaintBoxWindow::PaintBoxProps pbs;
	pbs.hInstance = this->hInstance;
	pbs.hWndParent = btn->hWndParent;
	pbs.nWidth = btn->initWidth;
	pbs.nHeight = btn->initHeight;
	pbs.x = btn->initX;
	pbs.y = btn->initY;
	btn->obj = new ButtonWindow(&pbs);
	btn->obj->SetBGColor(btn->bgColor);
	btn->obj->SetBGColorClick(btn->bgColorClick);
	btn->obj->SetBGColorHover(btn->bgColorHover);
	btn->obj->SetCaption(btn->caption);
	btn->obj->SetColor(btn->color);
	btn->obj->SetFont(btn->font);
	btn->obj->SetID(btn->ID);
}

void AppView::CreateImageButton(ImageButton *ibtn)
{
	PaintBoxWindow::PaintBoxProps pbs;
	pbs.hInstance = this->hInstance;
	pbs.hWndParent = ibtn->hWndParent;
	pbs.nWidth = ibtn->initWidth;
	pbs.nHeight = ibtn->initHeight;
	pbs.x = ibtn->initX;
	pbs.y = ibtn->initY;
	ibtn->obj = new ImageButtonWindow(&pbs);
	ibtn->obj->SetBGColor(ibtn->bgColor);
	ibtn->obj->SetBGColorClick(ibtn->bgColorClick);
	ibtn->obj->SetBGColorHover(ibtn->bgColorHover);
	ibtn->obj->SetBGImage(ibtn->bgImage);
	ibtn->obj->SetBGImageClick(ibtn->bgImageClick);
	ibtn->obj->SetBGImageHover(ibtn->bgImageHover);
	ibtn->obj->SetCaption(ibtn->caption);
	ibtn->obj->SetColor(ibtn->color);
	ibtn->obj->SetFont(ibtn->font);
	ibtn->obj->SetID(ibtn->ID);
}

void AppView::CreateGraph(Graph *gph)
{
	PaintBoxWindow::PaintBoxProps pbs;
	pbs.hInstance = this->hInstance;
	pbs.hWndParent = gph->hWndParent;
	pbs.nWidth = gph->initWidth;
	pbs.nHeight = gph->initHeight;
	pbs.x = gph->initX;
	pbs.y = gph->initY;
	gph->obj = new GraphWindow(&pbs);
	gph->obj->SetBGColor(gph->bgColor);
	gph->obj->SetRuleColor(gph->ruleColor);
	gph->obj->SetSlicerColor(gph->slicerColor);
	gph->obj->SetMinValue(gph->minValue);
	gph->obj->SetMaxValue(gph->maxValue);
	gph->obj->SetStep(gph->step);
	gph->obj->SetMaxSteps(gph->maxSteps);
	gph->gchVoltage = gph->obj->SetCursor();
	gph->gchAmperage = gph->obj->SetCursor();
	gph->obj->SetCursorColor(gph->gchVoltage, gph->voltageColor);
	gph->obj->SetCursorColor(gph->gchAmperage, gph->amperageColor);
}

void AppView::CreateStatic(Static *stc)
{
	PaintBoxWindow::PaintBoxProps pbs;
	pbs.hInstance = this->hInstance;
	pbs.hWndParent = stc->hWndParent;
	pbs.nWidth = stc->initWidth;
	pbs.nHeight = stc->initHeight;
	pbs.x = stc->initX;
	pbs.y = stc->initY;
	stc->obj = new StaticWindow(&pbs);
	stc->obj->SetStringFormat(stc->stringFormat);
	stc->obj->SetBGColor(stc->bgColor);
	stc->obj->SetCaption(stc->caption);
	stc->obj->SetColor(stc->color);
	stc->obj->SetFont(stc->font);
}
