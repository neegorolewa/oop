#ifndef CMYLIST_H
#define CMYLIST_H
#include <iostream>
#include <memory>

template<typename T>
class CMyList
{
public:
	//конструктор по умолчанию
	CMyList();

	//конструктор копирования
	CMyList(const CMyList& list);

	//перемещающий конструктор (перем. оператор присваивания)
	CMyList(CMyList&& list) noexcept;

	CMyList& operator =(const CMyList& list);

	CMyList& operator =(CMyList&& list) noexcept;

	~CMyList();

	void push_front(const T& value);
	void push_front(T&& value);

	void push_back(const T& value);
	void push_back(T&& value);

	size_t GetSize() const;

	class CIt;

	CIt begin();
	CIt end();

	class CRevIt;

	CRevIt rbegin();
	CRevIt rend();

	CIt insert(CIt pos,const T& value);
	CIt insert(CIt pos, T&& value);

	CIt erase(CIt pos);
private:
	struct Node
	{
		T data;
		std::weak_ptr<Node> prev;
		std::shared_ptr<Node> next;

		Node(const T& value)
			: data(value)
			, prev()
			, next(nullptr)
		{}

		Node(T&& value)
			: data(std::move(value))
			, prev()
			, next(nullptr)
		{}
	};

	std::shared_ptr<Node> m_head;
	std::shared_ptr<Node> m_tail;
	size_t m_size;

	void Clear() noexcept;
	void CopyList(const CMyList& list);

};

template<typename T>
class CMyList<T>::CIt
{
public:
	explicit CIt(std::shared_ptr<Node> node);

	T& operator *() const;

	T* operator ->();

	CIt& operator ++();

	CIt operator ++(int);

	CIt& operator --();

	CIt operator --(int);

	friend bool operator ==(const CIt& a, const CIt& b) 
	{ 
		return a.m_current == b.m_current; 
	};

	friend bool operator !=(const CIt& a, const CIt& b) 
	{ 
		return a.m_current != b.m_current; 
	};

	std::shared_ptr<Node> getNode() const { return m_current; };

private:
	std::shared_ptr<Node> m_current;
};

template<typename T>
class CMyList<T>::CRevIt
{
public:
	explicit CRevIt(std::shared_ptr<Node> node);

	T& operator *() const;

	T* operator ->();

	CRevIt& operator ++();

	CRevIt operator ++(int);

	CRevIt& operator --();

	CRevIt operator --(int);

	friend bool operator ==(const CRevIt& a, const CRevIt& b)
	{
		return a.m_current == b.m_current;
	};

	friend bool operator !=(const CRevIt& a, const CRevIt& b)
	{
		return a.m_current != b.m_current;
	};

	std::shared_ptr<Node> getNode() const { return m_current; };

private:
	std::shared_ptr<Node> m_current;
};

#include "CMyList.cpp"

#endif