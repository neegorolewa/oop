#include "CMyString.h"

CMyString::CMyString(const char* pString, size_t length)
{
	if (pString == nullptr)
	{
		length = 0;
	}
	m_length = length;
	m_capacity = length * 2;
	m_symbols = new char[m_capacity + 1];
	//позволяет хранить в середине нулевой символ
	memcpy(m_symbols, pString, length);
	m_symbols[length] = END_OF_STRING;
}


CMyString::CMyString()
	: CMyString(nullptr, 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

//совместно с оператором присваивания
CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = 0;
	m_capacity = 0;
	delete[] m_symbols;
	m_symbols = new char[1];
	m_symbols[0] = END_OF_STRING;
	std::swap(m_length, other.m_length);
	std::swap(m_symbols, other.m_symbols);
	std::swap(m_capacity, other.m_capacity);
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_symbols;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_symbols;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start < 0 || start > m_length)
	{
		throw std::out_of_range("Start symbol is out of range");
	}

	if (length > m_length - start)
	{
		length = m_length - start;
	}

	return CMyString(&m_symbols[start], length);
}

void CMyString::Clear()
{
	delete[] m_symbols;
	m_length = 0;
	m_symbols = new char[1];
	m_symbols[0] = END_OF_STRING;
}

size_t CMyString::GetCapacity()
{
	return m_capacity;
}

//1 =
CMyString& CMyString::operator =(const CMyString& other)
{
	/*if (this != &other) {
		if (m_capacity >= other.m_length && m_symbols != END_OF_STRING)
		{
			std::destroy_n(m_symbols, m_length + 1);
			std::uninitialized_copy_n(other.m_symbols, m_length + 1, m_symbols);
			m_length = other.m_length;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_length, copy.m_length);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_symbols, copy.m_symbols);
		}
	}

	return *this;*/

	if (std::addressof(other) != this)
	{
		CMyString copy(other.GetStringData(), other.GetLength());
		std::swap(m_symbols, copy.m_symbols);
		std::swap(m_length, copy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other) {
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_symbols, other.m_symbols);
	}
	return *this;
}


CMyString operator+(const CMyString& str1, const CMyString& str2)
{
	size_t newLength = str1.GetLength() + str2.GetLength();
	char* newSymbols = new char[newLength + 1];

	memcpy(newSymbols, str1.GetStringData(), str1.GetLength());
	memcpy(newSymbols + str1.GetLength(), str2.GetStringData(), str2.GetLength());

	return CMyString(newSymbols, newLength);
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	*this = *this + other;

	return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
	if (this->GetLength() != other.GetLength())
	{
		return false;
	}

	return (memcmp(this->GetStringData(), other.GetStringData(), this->GetLength()) == 0);
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	size_t minLength = std::min(this->GetLength(), other.GetLength());
	return (memcmp(this->GetStringData(), other.GetStringData(), minLength) < 0);
}

bool CMyString::operator>(const CMyString& other) const
{
	return !((*this < other) || (*this == other));
}

bool CMyString::operator<=(const CMyString& other) const
{
	if (*this < other || *this == other)
	{
		return true;
	}

	return false;
}

bool CMyString::operator>=(const CMyString& other) const
{
	if (*this > other || *this == other)
	{
		return true;
	}

	return false;
}

//для чтения
//если условие ложное assert выбрасывает abort(), останавливая программу и выбрасывая ошибку
const char& CMyString::operator[](size_t index) const
{
	if (index < 0 || index > m_length)
	{
		throw(std::out_of_range("Index out of range"));
	}
	return m_symbols[index];
}

char& CMyString::operator[](size_t index)
{
	if (index < 0 || index > m_length)
	{
		throw(std::out_of_range("Index out of range"));
	}
	return m_symbols[index];
}

std::istream& operator>>(std::istream& input, CMyString& string)
{
	size_t strCapacity = 1;
	size_t strLen = 0;
	char* str = new char[strCapacity];
	char ch;

	while (input.get(ch) && ch != SPACE && ch != ENTER)
	{
		str[strLen] = ch;
		strLen++;
		if (strLen == strCapacity)
		{
			char* updateStr = new char[strCapacity * 2];
			memcpy(updateStr, str, strCapacity);
			delete[] str;
			str = updateStr;
			strCapacity *= 2;
		}
	}

	str[strLen] = END_OF_STRING;

	string = CMyString(str, strLen);

	return input;

}

std::ostream& operator<<(std::ostream& output, CMyString& string)
{
	output << string.GetStringData();
	return output;
}

