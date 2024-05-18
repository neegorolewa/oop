#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <cassert>
#include <sstream>

const char END_OF_STRING = '\0';
const char SPACE = ' ';
const char ENTER = '\n';

class CMyString
{
public:
    // ����������� �� ���������
    CMyString();

    // �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
    CMyString(const char* pString);

    // �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
    CMyString(const char* pString, size_t length);

    // ����������� �����������
    CMyString(CMyString const& other);

    // ������������ �����������
    //  ����������� ��������� � ������������ ���������� ������������ 
    CMyString(CMyString&& other) noexcept;

    // �����������, ���������������� ������ ������� �� 
    // ������ ����������� ���������� C++
    CMyString(std::string const& stlString);

    // ���������� ������ - ����������� ������, ���������� ��������� ������
    ~CMyString();

    // ���������� ����� ������ (��� ����� ������������ �������� �������)
    size_t GetLength()const;

    // ���������� ��������� �� ������ �������� ������.
    // � ����� ������� ����������� ������ ���� ����������� ������� ������
    // ���� ���� ������ ������ 
    const char* GetStringData()const;

    // ���������� ��������� � �������� ������� ������ �� ������ length ��������
    CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

    // ������� ������ (������ ���������� ����� ������� �����)
    void Clear();

    // ���������� ����������� ������
    size_t GetCapacity();

    CMyString& operator =(const CMyString& other);
    CMyString& operator =(CMyString&& other) noexcept;
    CMyString& operator +=(const CMyString& other);
    bool operator ==(const CMyString& other)const; 
    bool operator !=(const CMyString& other)const;
    bool operator <(const CMyString& other)const;
    bool operator >(const CMyString& other)const;
    bool operator <=(const CMyString& other)const;
    bool operator >=(const CMyString& other)const;
    //����������� ������ ������ ������
    //��� ������
    const char& operator[](size_t index)const;
    //��� ������
    char& operator[](size_t index);



private:
   /* inline static char m_emptyString[] = { '\0' };*/
    size_t m_length;
    size_t m_capacity;
    char* m_symbols;

};

CMyString operator +(const CMyString& str1, const CMyString& str2);
std::istream& operator >>(std::istream& input, CMyString& string);
std::ostream& operator <<(std::ostream& output, CMyString& string);
