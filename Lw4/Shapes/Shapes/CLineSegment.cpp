#include "CLineSegment.h"

const std::string CLineSegment::NAME = "line_segment";

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return std::sqrt(std::pow(m_startPoint.m_x - m_endPoint.m_x, 2) + std::pow(m_startPoint.m_y - m_endPoint.m_y, 2));
}

std::string CLineSegment::ToString() const
{
	std::stringstream output;
	output << "Name: " << NAME << std::endl;
	output << IShape::ToString();
	output << "Start point: (" << m_startPoint.m_x << ';' << m_startPoint.m_y << ')' << std::endl;
	output << "End point: (" << m_endPoint.m_x << ';' << m_endPoint.m_y << ')' << std::endl;
	output << "Length: " << GetPerimeter() << std::endl;

	return output.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartedPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::Draw(std::shared_ptr<ICanvas> canvas)
{
	canvas->DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
