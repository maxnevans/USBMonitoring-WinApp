#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>

#include "gfx/PanelWindow.h"
#include "gfx/ButtonWindow.h"
#include "gfx/ImageButtonWindow.h"
#include "gfx/GraphWindow.h"
#include "gfx/StaticWindow.h"
#include "ConnectionProto.h"

#define IDB_SYSCLOSE	0x1000
#define IDB_SYSMINIMIZE	0x1001
#define IDB_STMSELECT	0x2000

class AppView
{
private:
	typedef struct _Panel {
		const Gdiplus::Color * bgColor;
		const Gdiplus::Color * color;
		const Gdiplus::Font * font;
		const wchar_t * caption;
		PanelWindow *obj;
		int initWidth;
		int initHeight;
		int initX;
		int initY;
		HWND hWndParent;
	} Panel, *PPanel;

	typedef struct _ImageButton {
		Gdiplus::Image * bgImage;
		Gdiplus::Image * bgImageHover;
		Gdiplus::Image * bgImageClick;
		const Gdiplus::Color * bgColor;
		const Gdiplus::Color * bgColorHover;
		const Gdiplus::Color * bgColorClick;
		const Gdiplus::Color * color;
		const Gdiplus::Font * font;
		const wchar_t * caption;
		ImageButtonWindow *obj;
		int initWidth;
		int initHeight;
		int initX;
		int initY;
		DWORD ID;
		HWND hWndParent;
	} ImageButton, *PImageButton;

	typedef struct _Button {
		const Gdiplus::Color * bgColor;
		const Gdiplus::Color * bgColorHover;
		const Gdiplus::Color * bgColorClick;
		const Gdiplus::Color * color;
		const Gdiplus::Font * font;
		const wchar_t * caption;
		ButtonWindow *obj;
		int initWidth;
		int initHeight;
		int initX;
		int initY;
		DWORD ID;
		HWND hWndParent;
	} Button, *PButton;

	typedef struct _Graph {
		const Gdiplus::Color * bgColor;
		const Gdiplus::Color * ruleColor;
		const Gdiplus::Color * slicerColor;
		const Gdiplus::Color * voltageColor;
		const Gdiplus::Color * amperageColor;
		GraphWindow::GCH gchVoltage;
		GraphWindow::GCH gchAmperage;
		GraphWindow *obj;
		int initWidth;
		int initHeight;
		int initX;
		int initY;
		int maxValue;
		int minValue;
		int step;
		int maxSteps;
		HWND hWndParent;
	} Graph, *PGraph;

	typedef struct _Static {
		const Gdiplus::Color * bgColor;
		const Gdiplus::Color * color;
		const Gdiplus::Font * font;
		const wchar_t * caption;
		Gdiplus::StringFormat *stringFormat;
		StaticWindow *obj;
		int initWidth;
		int initHeight;
		int initX;
		int initY;
		HWND hWndParent;
	} Static, *PStatic;

	struct AppFonts {
		const Gdiplus::Font *Normal;
		const Gdiplus::Font *Header1;
		const Gdiplus::Font *Header2;
		const Gdiplus::Font *Header3;
		const Gdiplus::Font *Caption;
	};
	struct AppColors {
		const Gdiplus::Color *Main;
		const Gdiplus::Color *FirstDominant;
		const Gdiplus::Color *SecondDominant;
		const Gdiplus::Color *NormalFont;
		const Gdiplus::Color *Header1Font;
		const Gdiplus::Color *Header2Font;
		const Gdiplus::Color *Header3Font;
		const Gdiplus::Color *CaptionFont;
	};

	struct AppIcons {
		const wchar_t * smallIconPath;
		const wchar_t * bigIconPath;
	};
public:
	AppView(HINSTANCE hInstance, HWND hWnd, int wndInitWidth, int wndInitHeight);
	void SetAppIcons();
	void SetAppWindowSize();
	void UpdateFrame();
	void ShowTitleBar();
	void HideTitleBar();
	static bool InTitleBarArea(int x, int y, int wndWidth, int wndHeight);
	void ShowStatusBar();
	void HideStatusBar();
	void ShowWorkScreen();
	void HideWorkScreen();
	void SetCurrentVoltage(float value);
	void SetCurrentAmperage(float value);
	void SetCurrentPower(float value);
	int GetSlicerVoltageUnconverted();
	int GetSlicerAmperageUnconverted();
	void SetGraphControlVoltage(float value);
	void SetGraphControlAmperage(float value);
	void SetGraphControlPower(float value);
	void SetGraphVoltage(int value);
	void SetGraphAmperage(int value);
	bool IsCursorInGraphArea();

private:
	
	void CreatePanel(Panel *pnl);
	void CreateButton(Button *btn);
	void CreateImageButton(ImageButton *ibtn);
	void CreateGraph(Graph *gph);
	void CreateStatic(Static *stc);

public:
	HINSTANCE hInstance;
	HWND hWnd;
	int wndWidth;
	int wndHeight;

	AppFonts *Fonts;
	AppColors *Colors;
	AppIcons *Icons;

	//Window Title
	Panel *pnlTitleBar;
		ImageButton *ibtnClose;
		ImageButton *ibtnMinimize;

	//Window Status Bar
	Panel *pnlStatusBar;
		Static *sAppStatusMessage;

	//Window Work Screen
	Panel *pnlWorkScreen;
		Panel *pnlMainData;
			Panel *pnlCurrentData;
				Static *sCurrentDataPanelCaption;
				Static *sCurrentVoltageDesc;
				Static *sCurrentVoltageValue;
				Static *sCurrentAmperageDesc;
				Static *sCurrentAmperageValue;
				Static *sCurrentPowerDesc;
				Static *sCurrentPowerValue;
		Graph *gphGraph;
		Panel *pnlGraphControls;
			Panel *pnlSlicerValues;
				Static *sSlicerVoltageDesc;
				Static *sSlicerVoltageValue;
				Static *sSlicerAmperageDesc;
				Static *sSlicerAmperageValue;
				Static *sSlicerPowerDesc;
				Static *sSlicerPowerValue;
};
