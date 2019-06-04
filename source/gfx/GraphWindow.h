#pragma once
#include "PaintBoxWindow.h"
#include <windowsx.h>
#include <list>
#include <vector>

class GraphWindow :
	public PaintBoxWindow
{
public:
	typedef int GCH; // Graph Cursor Handle
	struct InitStruct {
		const Gdiplus::Color *bgColor;
		const Gdiplus::Color *ruleColor;
		const Gdiplus::Color *slicerColor;
		int minValue;
		int maxValue;
		int step;
	};

private:
	struct CursorData {
		GCH handle;
		const Gdiplus::Color* color;
		int value;
		std::list<int> list;
		std::vector<Gdiplus::Point> gfxPts;
	};

	struct Slicer {
		int x;
		WORD visible;
		const Gdiplus::Color *color;
	};
public:
	GraphWindow(PaintBoxProps *pbs);
	void SetBGColor(const Gdiplus::Color *bgColor);
	void SetRuleColor(const Gdiplus::Color *ruleColor);
	void SetMaxValue(int maxValue);
	void SetMinValue(int minValue);
	void SetStep(int step);
	void SetMaxSteps(int maxSteps);
	void SetSlicerColor(const Gdiplus::Color *slicerColor);
	void Init(InitStruct *gis);
	GCH SetCursor(const Gdiplus::Color *cursorColor = new Gdiplus::Color(0), int cursorValue = 0);
	void SetCursorColor(GCH gch, const Gdiplus::Color *cursorColor);
	void SetCursorValue(GCH gch, int cursorValue);
	int GetCurrentSlicerValue(GCH gch);
	bool IsSlicerActive();
	virtual void Update();

protected:

	virtual int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnPaint();
	virtual void OnMouseMove(DWORD x, DWORD y);
	virtual void OnMouseHover();
	virtual void OnMouseLeave();

private:

	CursorData* GetCursor(GCH gch);
	void UpdateGFXData(CursorData& cur);
	void UpdateGraph();

private:
	const Gdiplus::Color *bgColor;
	const Gdiplus::Color *ruleColor;
	int minValue;
	int maxValue;
	float valueFactor;
	int step;
	int maxSteps;
	std::vector<CursorData> cData;
	static constexpr GCH START_GCH = 0x221F;
	int wWidth;
	int wHeight;
	Slicer slicer;
};

