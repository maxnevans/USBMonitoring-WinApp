#pragma once
#include <windows.h>

class BaseWindow
{
public:
	typedef struct _CreateWindowStruct {
		LPCTSTR lpClassName;
		LPCTSTR lpWindowName;
		DWORD dwStyle;
		int x;
		int y;
		int nWidth;
		int nHeight;
		HWND hWndParent;
		HMENU hMenu;
		HINSTANCE hInstance;
		LPVOID lpParam;
	} CWS, *PCWS;
	typedef struct _Dimensions {
		int width;
		int height;
		int x;
		int y;
	} DIMS, *PDIMS;
protected:
	BaseWindow();
	BaseWindow(CWS *cws);
	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	void CreateWnd();
	void ResetCWS(CWS *cws);
public:
	HWND GetHWND();
	DIMS GetWDims();
	DIMS GetCDims();
	void SetID(DWORD ID);
	void Show();
	void Hide();
protected:
	CWS cws;
	HWND hWnd;
	HINSTANCE hInstance;
	DWORD ID;
	HWND hWndParent;
};

