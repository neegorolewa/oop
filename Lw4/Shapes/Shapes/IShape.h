#pragma once
#include <cstdint>
#include <sstream>
#include <string>
#include <iomanip>
class IShape
{
public:
	IShape(uint32_t outlineColor)
		: m_outlineColor(outlineColor)
	{}

	virtual double GetArea() const = 0;

	virtual double GetPerimeter() const = 0;

	virtual uint32_t GetOutlineColor() const = 0;

	virtual std::string ToString() const
	{
		std::stringstream output;
		output << "Area: " << GetArea() << std::endl;
		output << "Perimeter: " << GetPerimeter() << std::endl;
		output << "OutlineColor: " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << std::endl;
		
		return output.str();
	}

	virtual ~IShape() = default;

protected:
	uint32_t m_outlineColor;
};