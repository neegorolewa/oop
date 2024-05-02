#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:
	static const std::string NAME;

	CTriangle(CPoint top1, CPoint top2, CPoint top3, uint32_t outlineColor, uint32_t fillColor)
		:ISolidShape(outlineColor, fillColor)
		, m_top1(top1)
		, m_top2(top2)
		, m_top3(top3)
	{
		double side12 = GetSide(top1, top2);
		double side23 = GetSide(top2, top3);
		double side31 = GetSide(top3, top1);

		if (side12 + side23 <= side31 ||
			side23 + side31 <= side12 ||
			side31 + side12 <= side23)
		{
			throw std::invalid_argument("Invalid arguments: error length sides of triangle");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetTop1() const;

	CPoint GetTop2() const;

	CPoint GetTop3() const;

protected:
	CPoint m_top1, m_top2, m_top3;

	double GetSide(const CPoint& top1, const CPoint& top2) const;
};

