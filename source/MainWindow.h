#pragma once
#include <windows.h>
#include "gfx/BaseWindow.h"
#include "AppModel.h"
#include "AppView.h"

#define STD_COMPORT			0x0004
#define AVG_PRECISION		20
#define MAX_AMPERAGE		235
#define MAX_VOLTAGE			5.01f
#define VOLTAGE_CORRECTION	0
#define AMPERAGE_CORRECTION 0
#define POWER_CORRECTION_FACTOR	0.01f

#define IDT_FRAMERATE		0xF00F
#define T_FRAMERATE			USER_TIMER_MINIMUM
#define IDT_UPDATECURRENT	0xF00E
#define T_UPDATECURRENT		0x0128
#define IDT_DEVICESCAN		0xF00D
#define T_DEVICESCAN		0x0128
#define IDT_RETRIEVEDATA	0xF00C
#define T_RETRIEVEDATA		USER_TIMER_MINIMUM

class MainWindow : public BaseWindow {
public:
	MainWindow(HINSTANCE hInstance);
	static int Register(HINSTANCE hInstance);

protected:
	int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void OnCreate();
	void OnTimer(int TIMERID, TIMERPROC cbTimerFunc);

private:
	int wWidth;
	int wHeight;
	int dWidth;
	int dHeight;
	int cWidth;
	int cHeight;

	AppModel *AM;
	AppView  *AV;

	static constexpr wchar_t CLASS_NAME[]	= L"MainWindow";
	static constexpr wchar_t WND_NAME[]		= L"USB Monitor";
	static constexpr int WND_INIT_WIDTH		= 1280;
	static constexpr int WND_INIT_HEIGHT	= 720;
	static constexpr DWORD WND_STYLE		= WS_POPUP | WS_VISIBLE;
};