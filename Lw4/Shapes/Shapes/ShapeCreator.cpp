#include "ShapeCreator.h"

std::shared_ptr<IShape> ShapeCreator::CreateShape(const std::string& line)
{
	std::istringstream input(line);
	std::string nameShape;
	input >> nameShape;

    if (nameShape == CLineSegment::NAME)
    {
        return ShapeCreator::CreateLineSegment(input);
    }
    else if (nameShape == CCircle::NAME)
    {
        return ShapeCreator::CreateCircle(input);
    }
    else if (nameShape == CTriangle::NAME)
    {
        return ShapeCreator::CreateTriangle(input);
    }
    else if (nameShape == CRectangle::NAME)
    {
        return ShapeCreator::CreateRectangle(input);
    }

    return nullptr;
}

std::shared_ptr<CLineSegment> ShapeCreator::CreateLineSegment(std::istringstream& iss)
{
    double startX, startY, endX, endY;
    if (!(iss >> startX >> endX >> startY >> endY))
    {
        std::cout << "Invalid line segment coordinates" << std::endl;
        return nullptr;
    }

    CPoint startPoint = { startX, endX };
    CPoint endPoint = { startY, endY };

    uint32_t outlineColor;
    if (!(iss >> std::hex >> outlineColor))
    {
        std::cout << "Invalid color value" << std::endl;
        return nullptr;
    }

    return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<CCircle> ShapeCreator::CreateCircle(std::istringstream& iss)
{
    double centerX, centerY, radius;
    if (!(iss >> centerX >> centerY >> radius))
    {
        std::cout << "Invalid circle coordinates or sizes" << std::endl;
        return nullptr;
    }

    CPoint center = { centerX, centerY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

std::shared_ptr<CRectangle> ShapeCreator::CreateRectangle(std::istringstream& iss)
{
    double leftTopX, leftTopY, width, height;
    if (!(iss >> leftTopX >> leftTopY >> width >> height))
    {
        std::cout << "Invalid rectangle coordinates or sizes" << std::endl;
        return nullptr;
    }

    CPoint leftTop = { leftTopX, leftTopY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> ShapeCreator::CreateTriangle(std::istringstream& iss)
{
    double top1X, top1Y;
    double top2X, top2Y;
    double top3X, top3Y;
    if (!(iss >> top1X >> top1Y >>
        top2X >> top2Y >>
        top3X >> top3Y))
    {
        std::cout << "Invalid triangle coordinates" << std::endl;
        return nullptr;
    }

    CPoint top1 = { top1X, top1Y };
    CPoint top2 = { top2X, top2Y };
    CPoint top3 = { top3X, top3Y };
    
    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CTriangle>(top1, top2, top3, outlineColor, fillColor);
}
