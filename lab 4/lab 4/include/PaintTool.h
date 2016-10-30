#pragma once
#ifndef PAINTTOOL_H
#define PAINTTOOL_H
#include <windows.h>
#include "BrushStyle.h"
#include <memory>

class PaintTool
{
public:
	static std::shared_ptr<PaintTool> getInstance();
	void draw(HDC hdc, int x, int y);
	void setColour(COLORREF newColour);
	COLORREF getColour();
	void setBrushStyle(BrushStyle newStyle);
	BrushStyle getBrushStyle();
private:
	PaintTool();
	COLORREF m_Colour;
	BrushStyle m_Style;
	static std::shared_ptr<PaintTool> m_Instance;
	static bool m_Initiated;
};

#endif // !PAINTTOOL_H

