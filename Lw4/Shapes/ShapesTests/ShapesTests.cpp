#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Shapes/CPoint.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/ShapeControl.h"


const uint32_t OUTLINE_COLOR = 0xFF0000;
const uint32_t FILL_COLOR = 0x808080;

TEST_CASE("Check valid argumnets line segment")
{
	WHEN("Arguments is valid")
	{
		CPoint start{ 0, 0 };
		CPoint end{ 0, 4 };
		CLineSegment line = { start, end, OUTLINE_COLOR };

		THEN("Area and perimetr should be 0 and 4")
		{
			REQUIRE(line.GetArea() == 0);
			REQUIRE(line.GetPerimeter() == 4);
			REQUIRE(line.GetOutlineColor() == OUTLINE_COLOR);
		}
	}

	WHEN("Arguments is not valid")
	{
		ShapeCreator line;
		auto ptr = line.CreateShape("line_segment 0 0 0 a ffffff");

		THEN("Pointer = nullptr")
		{
			REQUIRE(ptr == nullptr);
		}
	}
}

TEST_CASE("Check valid argumnets rectangle")
{
	WHEN("Arguments is valid")
	{
		CPoint start{ 0, 0 };
		double width = 3;
		double height = 3;
		CRectangle rect = { start, width, height, OUTLINE_COLOR, FILL_COLOR };

		THEN("Area and perimetr should be 0 and 4")
		{
			REQUIRE(rect.GetArea() == 9);
			REQUIRE(rect.GetPerimeter() == 12);
			REQUIRE(rect.GetOutlineColor() == OUTLINE_COLOR);
			REQUIRE(rect.GetFillColor() == FILL_COLOR);
		}
	}

	WHEN("Arguments is not valid")
	{
		ShapeCreator rect;
		auto ptr = rect.CreateShape("rectangle 2 0 A 3 ffffff 111111");

		THEN("Pointer = nullptr")
		{
			REQUIRE(ptr == nullptr);
		}
	}
}

TEST_CASE("Check valid argumnets circle")
{
	WHEN("Arguments is valid")
	{
		CPoint center{ 0, 0 };
		double radius = 3;
		CCircle circle = { center, radius, OUTLINE_COLOR, FILL_COLOR };

		THEN("Area and perimetr should be 0 and 4")
		{
			REQUIRE(std::ceil(circle.GetArea()) == 29);
			REQUIRE(std::ceil(circle.GetPerimeter()) == 19);
			REQUIRE(circle.GetOutlineColor() == OUTLINE_COLOR);
			REQUIRE(circle.GetFillColor() == FILL_COLOR);
		}
	}

	WHEN("Arguments is not valid")
	{
		ShapeCreator circle;
		auto ptr = circle.CreateShape("circle 2 0 A ff-fff 1()11111");

		THEN("Pointer = nullptr")
		{
			REQUIRE(ptr == nullptr);
		}
	}
}

TEST_CASE("Check valid argumnets triangle")
{
	WHEN("Arguments is valid")
	{
		CPoint top1{ 0, 0 };
		CPoint top2{ 0, 2 };
		CPoint top3{ 3, 0 };

		CTriangle triangle = { top1, top2, top3,  OUTLINE_COLOR, FILL_COLOR };

		THEN("Area and perimetr should be 0 and 4")
		{
			REQUIRE(triangle.GetArea() == 3);
			REQUIRE(std::ceil(triangle.GetPerimeter()) == 9);
			REQUIRE(triangle.GetOutlineColor() == OUTLINE_COLOR);
			REQUIRE(triangle.GetFillColor() == FILL_COLOR);
		}
	}

	WHEN("Arguments is not valid")
	{
		ShapeCreator circle;
		auto ptr = circle.CreateShape("triangle 0 3 0 ffffff 1s11111");

		THEN("Pointer = nullptr")
		{
			REQUIRE(ptr == nullptr);
		}
	}
}

TEST_CASE("Check right work with shapes")
{
	std::string trueMaxArea =
		R"(Name: rectangle
Area: 20
Perimeter: 18
OutlineColor: 123456
FillColor: 123456
Left top: (3;3)
Width: 4
Height: 5
)";
	std::string trueMinPerimeter =
		R"(Name: line_segment
Area: 0
Perimeter: 1
OutlineColor: ffffff
Start point: (0;0)
End point: (0;1)
Length: 1
)";

	ShapeControl control;
	std::string line = "line_segment 0 0 0 1 ffffff";
	std::string circle = "circle 1 1 2 000000 111111";
	std::string triangle = "triangle 0 0 0 2 3 0 aaaaaa bbbbbb";
	std::string rectangle = "rectangle 3 3 4 5 123456 123456";

	control.ConstructShape(line);
	control.ConstructShape(circle);
	control.ConstructShape(triangle);
	control.ConstructShape(rectangle);

	std::string maxArea = control.GetMaxAreaShape()->ToString();
	auto minPerimeter = control.GetMinPerimeterShape()->ToString();

	REQUIRE(trueMaxArea == maxArea);
	REQUIRE(trueMinPerimeter == minPerimeter);
}