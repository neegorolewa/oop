#pragma once
#include <vector>
#include "ShapeCreator.h"
#include <memory>


class ShapeControl
{
public:
	void ConstructShape(const std::string& line);

	std::shared_ptr<IShape> GetMaxAreaShape() const;

	std::shared_ptr<IShape> GetMinPerimeterShape() const;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes = {};
};

