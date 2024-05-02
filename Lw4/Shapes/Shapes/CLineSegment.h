#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	static const std::string NAME;

	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
		:IShape(outlineColor)
		,m_startPoint(startPoint)
		,m_endPoint(endPoint)
	{}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	CPoint GetStartedPoint() const;

	CPoint GetEndPoint() const;

protected:
	CPoint m_startPoint, m_endPoint;
};