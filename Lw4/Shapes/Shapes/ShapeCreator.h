#pragma once
#include <string>
#include <iostream>
#include "IShape.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"

class ShapeCreator
{
public:
	static std::shared_ptr<IShape> CreateShape(const std::string& line);

private:
    static std::shared_ptr<CLineSegment> CreateLineSegment(std::istringstream& input);

    static std::shared_ptr<CRectangle> CreateRectangle(std::istringstream& input);

    static std::shared_ptr<CTriangle> CreateTriangle(std::istringstream& input);

    static std::shared_ptr<CCircle> CreateCircle(std::istringstream& input);

};

