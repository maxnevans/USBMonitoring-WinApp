#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE hInstance)
	:
	BaseWindow()
{
	this->wWidth = WND_INIT_WIDTH;
	this->wHeight = WND_INIT_HEIGHT;


	HWND hDesk = GetDesktopWindow();
	RECT rect;
	GetWindowRect(hDesk, &rect);

	this->dWidth = rect.right;
	this->dHeight = rect.bottom;

	CWS cws = { 0 };
	cws.lpClassName = CLASS_NAME;
	cws.lpWindowName = WND_NAME;
	cws.dwStyle = WND_STYLE;
	cws.x = (this->dWidth - this->wWidth) / 2;
	cws.y = (this->dHeight - this->wHeight) / 2;
	cws.nWidth = WND_INIT_WIDTH;
	cws.nHeight = WND_INIT_HEIGHT;
	cws.hWndParent = NULL;
	cws.hInstance = hInstance;
	cws.lpParam = 0;
	this->ResetCWS(&cws);
	this->CreateWnd();

	GetClientRect(this->hWnd, &rect);
	this->cWidth = rect.right;
	this->cHeight = rect.bottom;
	
	this->OnCreate();

	UpdateWindow(this->hWnd);
}

int MainWindow::Register(HINSTANCE hInstance) {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.lpszClassName = CLASS_NAME;
	wcex.lpfnWndProc = (WNDPROC)BaseWindow::_WndProc;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	return (int)RegisterClassEx(&wcex);
}

int MainWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_NCHITTEST:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		RECT wRect;
		GetWindowRect(this->hWnd, &wRect);
		x -= wRect.left;
		y -= wRect.top;
		int wndWidth = wRect.right - wRect.left;
		int wndHeight = wRect.bottom - wRect.top;

		if (AppView::InTitleBarArea(x, y, wndWidth, wndHeight)) return HTCAPTION;

		return HTNOWHERE;
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDB_SYSCLOSE:
			SendMessage(this->hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
			break;
		case IDB_SYSMINIMIZE:
			SendMessage(this->hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			break;
		}
		break;
	case WM_TIMER:
		this->OnTimer((int)wParam, (TIMERPROC)lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void MainWindow::OnCreate()
{
	this->AV = new AppView(this->hInstance, this->hWnd, this->WND_INIT_WIDTH, this->WND_INIT_HEIGHT);
	this->AM = new AppModel(AVG_PRECISION);

	AV->SetAppIcons();

	AV->ShowTitleBar();
	AV->ShowStatusBar();
	AV->ShowWorkScreen();

	SetTimer(this->hWnd, IDT_RETRIEVEDATA, T_RETRIEVEDATA, NULL);
	SetTimer(this->hWnd, IDT_UPDATECURRENT, T_UPDATECURRENT, NULL);
	SetTimer(this->hWnd, IDT_FRAMERATE, T_FRAMERATE, NULL);
}

void MainWindow::OnTimer(int TIMERID, TIMERPROC cbTimerFunc) {
	switch (TIMERID) {
	case IDT_FRAMERATE:
		AV->SetGraphVoltage(AM->GetUVoltage());
		AV->SetGraphAmperage(AM->GetUAmperage());
		if (AV->IsCursorInGraphArea()) {
			int uVoltage = AV->GetSlicerVoltageUnconverted();
			int uAmperage = AV->GetSlicerAmperageUnconverted();
			float realVoltage = uVoltage * MAX_VOLTAGE / 4096.f + VOLTAGE_CORRECTION;
			float realAmperage = uAmperage * MAX_AMPERAGE / 4096.f + AMPERAGE_CORRECTION;
			float realPower = realVoltage * realAmperage * POWER_CORRECTION_FACTOR;
			AV->SetGraphControlVoltage(realVoltage);
			AV->SetGraphControlAmperage(realAmperage);
			AV->SetGraphControlPower(realPower);
		}
		AV->UpdateFrame();
		break;
	case IDT_UPDATECURRENT:
		{
			float realVoltage = AM->GetUVoltage() * MAX_VOLTAGE / 4096.f + VOLTAGE_CORRECTION;
			float realAmperage = AM->GetUAmperage() * MAX_AMPERAGE / 4096.f + AMPERAGE_CORRECTION;
			float realPower = realVoltage * realAmperage * POWER_CORRECTION_FACTOR;
			AV->SetCurrentVoltage(realVoltage);
			AV->SetCurrentAmperage(realAmperage);
			AV->SetCurrentPower(realPower);
		}
		break;
	case IDT_RETRIEVEDATA:
		AM->RetrieveData();
		break;
	}
}