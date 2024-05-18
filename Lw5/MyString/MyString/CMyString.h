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
    // конструктор по умолчанию
    CMyString();

    // конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
    CMyString(const char* pString);

    // конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
    CMyString(const char* pString, size_t length);

    // конструктор копирования
    CMyString(CMyString const& other);

    // перемещающий конструктор
    //  реализуется совместно с перемещающим оператором присваивания 
    CMyString(CMyString&& other) noexcept;

    // конструктор, инициализирующий строку данными из 
    // строки стандартной библиотеки C++
    CMyString(std::string const& stlString);

    // деструктор класса - освобождает память, занимаемую символами строки
    ~CMyString();

    // возвращает длину строки (без учета завершающего нулевого символа)
    size_t GetLength()const;

    // возвращает указатель на массив символов строки.
    // В конце массива обязательно должен быть завершающий нулевой символ
    // даже если строка пустая 
    const char* GetStringData()const;

    // возвращает подстроку с заданной позиции длиной не больше length символов
    CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

    // очистка строки (строка становится снова нулевой длины)
    void Clear();

    // Возвращает вместимость строки
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
    //объявляется только внутри класса
    //для чтения
    const char& operator[](size_t index)const;
    //для записи
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
