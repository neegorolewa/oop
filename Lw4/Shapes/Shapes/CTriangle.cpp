#include "CTriangle.h"
#include <cmath>

const std::string CTriangle::NAME = "triangle";

double CTriangle::GetSide(const CPoint& top1, const CPoint& top2) const
{
	return std::sqrt(std::pow(top1.m_x - top2.m_x, 2) + std::pow(top1.m_y - top2.m_y, 2));
}

double CTriangle::GetArea() const
{
	return 0.5 * abs(
        (m_top2.m_x - m_top1.m_x) *
        (m_top3.m_y - m_top1.m_y) -
        (m_top3.m_x - m_top1.m_x) *
        (m_top2.m_y - m_top1.m_y)
    );
}

double CTriangle::GetPerimeter() const
{
    return CTriangle::GetSide(m_top1, m_top2) +
        CTriangle::GetSide(m_top2, m_top3) +
        CTriangle::GetSide(m_top3, m_top1);
}

std::string CTriangle::ToString() const
{
    std::stringstream output;
    output << "Name: " << NAME << std::endl;
    output << ISolidShape::ToString();
    output << "Top 1: (" << m_top1.m_x << ';' << m_top1.m_y << ')' << std::endl;
    output << "Top 2: (" << m_top2.m_x << ';' << m_top2.m_y << ')' << std::endl;
    output << "Top 3: (" << m_top3.m_x << ';' << m_top3.m_y << ')' << std::endl;
    output << "Side 11: " << GetSide(m_top1, m_top2) << std::endl;
    output << "Side 23: " << GetSide(m_top2, m_top3) << std::endl;
    output << "Side 31: " << GetSide(m_top3, m_top1) << std::endl;

    return output.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetTop1() const
{
    return m_top1;
}

CPoint CTriangle::GetTop2() const
{
    return m_top2;
}

CPoint CTriangle::GetTop3() const
{
    return m_top3;
}

