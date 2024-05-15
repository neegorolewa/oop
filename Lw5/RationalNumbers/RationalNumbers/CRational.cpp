#include "CRational.h"
#include <stdexcept>

CRational::CRational() :
	m_numerator(0),
	m_denominator(1)
{
}

CRational::CRational(int value) :
	m_numerator(value),
	m_denominator(1)
{
}

int GetLeastCommonMultiple(int a, int b)
{
	//std::lcm (+)
	return std::lcm(a, b);
}

int GetGreatestCommonDivisor(int a, int b)
{
	//std::gcd (+)
	return std::gcd(a, b);
}

void CRational::SetNormalizedNumber()
{
	int divisor = GetGreatestCommonDivisor(m_numerator, m_denominator);

	if (m_denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}

	m_numerator = m_numerator / divisor;
	m_denominator = m_denominator / divisor;
}

CRational::CRational(int numerator, int denominator) :
	m_numerator(numerator),
	m_denominator(denominator)
{
	if (denominator == 0)
	{
		//Добавить в тест
		throw std::invalid_argument("Denominator cannot be zero.");
	}
	else
	{
		SetNormalizedNumber();
	}
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
}

//унарные оператор +
CRational CRational::operator+()const
{
	return *this;
}

//унарные оператор - 
CRational CRational::operator-()
{
	return CRational(m_numerator * (-1), m_denominator);
}

CRational& CRational::operator+=(const CRational& number)
{
	m_numerator = m_numerator * number.m_denominator + number.m_numerator * m_denominator;
	m_denominator *= number.m_denominator;
	SetNormalizedNumber();
	return *this;
}

CRational& CRational::operator-=(const CRational& number)
{
	*this = *this - number;

	return *this;
}

CRational& CRational::operator*=(const CRational& number)
{
	*this = *this * number;

	return *this;
}

CRational& CRational::operator/=(const CRational& number)
{
	*this = *this / number;

	return *this;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int wholePart = m_numerator / m_denominator;

	return std::pair<int, CRational>(wholePart, CRational(m_numerator - (wholePart * m_denominator), m_denominator));
}

CRational operator+(const CRational& number1, const CRational& number2)
{
	int multipler = GetLeastCommonMultiple(number1.GetDenominator(), number2.GetDenominator());

	return CRational(number1.GetNumerator() * (multipler / number1.GetDenominator()) +
		number2.GetNumerator() * (multipler / number2.GetDenominator()), multipler);
}

CRational operator-(const CRational& number1, const CRational& number2)
{
	int multipler = GetLeastCommonMultiple(number1.GetDenominator(), number2.GetDenominator());

	return CRational(number1.GetNumerator() * (multipler / number1.GetDenominator()) -
		number2.GetNumerator() * (multipler / number2.GetDenominator()), multipler);
}

CRational operator*(const CRational& number1, const CRational& number2)
{
	return CRational(number1.GetNumerator() * number2.GetNumerator(),
		number1.GetDenominator() * number2.GetDenominator());
}

CRational operator/(const CRational& number1, const CRational& number2)
{
	return CRational(number1.GetNumerator() * number2.GetDenominator(),
		number1.GetDenominator() * number2.GetNumerator());
}

bool operator==(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() == number2.ToDouble());
}

bool operator!=(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() != number2.ToDouble());
}

bool operator<(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() < number2.ToDouble());
}

bool operator>(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() > number2.ToDouble());
}

bool operator<=(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() <= number2.ToDouble());
}

bool operator>=(const CRational& number1, const CRational& number2)
{
	return (number1.ToDouble() >= number2.ToDouble());
}

std::istream& operator>>(std::istream& iStream, CRational& number)
{
	int num;
	int den;

	if (iStream >> num && iStream.get() == SLASH && iStream >> den)
	{
		number = CRational(num, den);
	}
	else
	{
		iStream.setstate(std::ios_base::failbit);
	}

	return iStream;
}

std::ostream& operator<<(std::ostream& oStream, const CRational& number)
{
	oStream << number.GetNumerator() << SLASH << number.GetDenominator();

	return oStream;
}
