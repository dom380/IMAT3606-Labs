#include "..\include\PaintTool.h"

PaintTool::PaintTool()
{
	
}

std::shared_ptr<PaintTool> PaintTool::m_Instance;
bool PaintTool::m_Initiated = false;

std::shared_ptr<PaintTool> PaintTool::getInstance()
{
	if (m_Initiated == NULL || !m_Initiated) {
		m_Instance = std::shared_ptr<PaintTool>(new PaintTool());
		m_Initiated = true;
	}
	return m_Instance;
}

void PaintTool::draw(HDC hdc, int x, int y)
{
	HBRUSH brush = CreateSolidBrush(m_Colour);
	HPEN pen = CreatePen(PS_SOLID, 1, m_Colour);
	if (m_Style == BrushStyle::ELLIPSE)
	{
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
		Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);
		
	}
	else if (m_Style == BrushStyle::RECTANGLE)
	{
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
		Rectangle(hdc, x - 20, y - 10, x + 20, y + 10);
	}
	else
	{
		SelectObject(hdc, pen);
		LineTo(hdc, x, y);
	}
	DeleteObject(pen);
	DeleteObject(brush);
}

void PaintTool::setColour(COLORREF newColour)
{
	m_Colour = newColour;
}

COLORREF PaintTool::getColour()
{
	return m_Colour;
}

void PaintTool::setBrushStyle(BrushStyle newStyle)
{
	m_Style = newStyle;
}

BrushStyle PaintTool::getBrushStyle()
{
	return m_Style;
}
