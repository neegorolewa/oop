#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>

const char SLASH = '/';

class CRational
{
public:

	CRational();

	CRational(int value);

	CRational(int numerator, int denominator);

	int GetNumerator()const;

	int GetDenominator()const;

	double ToDouble()const;

	//Не возвращать const (+)
	//унарный +, -
	CRational const operator +()const;
	CRational const operator -()const;

	CRational operator +=(const CRational& number);
	CRational operator -=(const CRational& number);
	CRational operator *=(const CRational& number);
	CRational operator /=(const CRational& number);

	std::pair<int, CRational> ToCompoundFraction()const;

private:
	int m_numerator, m_denominator;
	void SetNormalizedNumber();
};

//бинарный +, - 
//Разобраться какой способ является более предпочтительным и почему? (смочь объяснить)
CRational operator +(const CRational& number1, const CRational& number2);
CRational operator -(const CRational& number1, const CRational& number2);

CRational operator *(const CRational& number1, const CRational& number2);
CRational operator /(const CRational& number1, const CRational& number2);

bool operator ==(const CRational& number1, const CRational& number2);
bool operator !=(const CRational& number1, const CRational& number2);

bool operator <(const CRational& number1, const CRational& number2);
bool operator >(const CRational& number1, const CRational& number2);

bool operator <=(const CRational& number1, const CRational& number2);
bool operator >=(const CRational& number1, const CRational& number2);

std::istream& operator >>(std::istream& iStream, CRational& number);
std::ostream& operator <<(std::ostream& oStream, const CRational& number);

int GetLeastCommonMultiple(int a, int b);
int GetGreatestCommonDivisor(int a, int b);