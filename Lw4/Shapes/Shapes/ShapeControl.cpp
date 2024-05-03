#include "ShapeControl.h"
#include "ShapeCreator.h"
#include <iostream>

void ShapeControl::ConstructShape(const std::string& line)
{
	std::shared_ptr<IShape> shape = ShapeCreator::CreateShape(line);

	if (shape == nullptr)
	{
		std::cout << "Failed to create this shape" << std::endl;
		return;
	}

	m_shapes.emplace_back(shape);
}

std::shared_ptr<IShape> ShapeControl::GetMaxAreaShape() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto maxAreaShape = *std::max_element(
		m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b)
		{return a->GetArea() < b->GetArea(); });

	return maxAreaShape;
}

std::shared_ptr<IShape> ShapeControl::GetMinPerimeterShape() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto minPerimeterShape = *std::min_element(
		m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b)
		{ return a->GetPerimeter() < b->GetPerimeter(); });

	return minPerimeterShape;
}

void ShapeControl::DrawShapes()
{
	auto window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW),
		NAME_WINDOW);

	m_canvas = std::make_shared<CCanvas>(window);

	while (window->isOpen())
	{
		sf::Event event{};
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		window->clear(sf::Color::White);

		for (auto const& shape : m_shapes)
		{
			shape->Draw(m_canvas);
		}

		window->display();
	}
}
