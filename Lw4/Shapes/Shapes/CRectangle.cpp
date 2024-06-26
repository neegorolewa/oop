#include "CRectangle.h"
#include <cmath>
const std::string CRectangle::NAME = "rectangle";

double CRectangle::GetArea() const
{
    return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
    return  (m_height + m_width) * 2;
}

std::string CRectangle::ToString() const
{
    std::stringstream output;
    output << "Name: " << NAME << std::endl;
    output << ISolidShape::ToString();
    output << "Left top: (" << m_leftTop.m_x << ';' << m_leftTop.m_y << ')' << std::endl;
    output << "Width: " << m_width << std::endl;
    output << "Height: " << m_height << std::endl;

    return output.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return CPoint(m_leftTop.m_x + m_width, m_leftTop.m_y + m_height);
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

void CRectangle::Draw(std::shared_ptr<ICanvas> canvas)
{
    CPoint rightTop(GetRightBottom().m_x, m_leftTop.m_y);
    CPoint leftBottom(m_leftTop.m_x, GetRightBottom().m_y);
    std::vector<CPoint> points = { m_leftTop, rightTop, GetRightBottom(), leftBottom };

    canvas->FillPolygon(points, m_outlineColor, m_fillColor);

    canvas->DrawLine(m_leftTop, rightTop, m_outlineColor);
    canvas->DrawLine(rightTop, GetRightBottom(), m_outlineColor);
    canvas->DrawLine(GetRightBottom(), leftBottom, m_outlineColor);
    canvas->DrawLine(leftBottom, m_leftTop, m_outlineColor);
}