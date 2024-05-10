#include "CRational.h"

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
	return (a * b) / GetGreatestCommonDivisor(a, b);
}

int GetGreatestCommonDivisor(int a, int b)
{
	if (a < 0)
	{
		a *= -1;
	}

	if (b < 0)
	{
		b *= -1;
	}

	while (a > 0 && b > 0)
	{
		if (a > b)
		{
			a %= b;
		}
		else
		{
			b %= a;
		}
	}

	return a + b;
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
		CRational();
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
	std::ostringstream output;

	output << std::fixed << std::setprecision(3) << static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
	std::string os = output.str();

	return std::stod(os);
}

//унарные оператор +
CRational const CRational::operator+() const
{
	return CRational(m_numerator, m_denominator);
}

//унарные оператор -
CRational const CRational::operator-() const
{
	return CRational(m_numerator * (-1), m_denominator);
}

CRational CRational::operator+=(const CRational& number)
{
	*this = *this + number;

	return *this;
}

CRational CRational::operator-=(const CRational& number)
{
	*this = *this - number;

	return *this;
}

CRational CRational::operator*=(const CRational& number)
{
	*this = *this * number;

	return *this;
}

CRational CRational::operator/=(const CRational& number)
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

