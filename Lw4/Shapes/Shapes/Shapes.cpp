#include <iostream>
#include "ShapeControl.h"
#include "SFML/Graphics.hpp"

int main()
{
    ShapeControl shapeController;
    std::string dataShape;
    while (std::getline(std::cin, dataShape))
    {
        if (dataShape.empty())
        {
            continue;
        }

        shapeController.ConstructShape(dataShape);
    }

    if (shapeController.GetMaxAreaShape() == nullptr)
    {
        return 0;
    }

    std::cout << "Shape with max area:\n" << shapeController.GetMaxAreaShape()->ToString() << std::endl;
    std::cout << "Shape with min perimeter:\n" << shapeController.GetMinPerimeterShape()->ToString() << std::endl;

    shapeController.DrawShapes();

    return 0;
}