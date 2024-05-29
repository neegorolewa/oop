#ifndef CMYLIST_IMPL
#define CMYLIST_IMPL
#include "CMyList.h"

template <typename T>
CMyList<T>::CMyList()
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{}

template<typename T>
CMyList<T>::CMyList(const CMyList& list)
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
	try
	{
		CopyList(list);
	}
	catch (...)
	{
		Clear();
	}
}


template<typename T>
CMyList<T>::CMyList(CMyList&& list) noexcept
	: m_head(list.m_head)
	, m_tail(list.m_tail)
	, m_size(list.m_size)
{
	list.m_head = nullptr;
	list.m_tail = nullptr;
	list.m_size = 0;
}

//копирование
template<typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& list)
{
	if (this != &list)
	{
		Clear();
		CMyList copy(list);
		std::swap(m_head, copy.m_head);
		std::swap(m_tail, copy.m_tail);
		std::swap(m_size, copy.m_size);
	}

	return *this;
}

//перемещение
template<typename T>
CMyList<T>& CMyList<T>::operator=(CMyList&& list) noexcept
{
	if (this != &list)
	{
		Clear();
		std::swap(m_head, list.m_head);
		std::swap(m_tail, list.m_tail);
		std::swap(m_size, list.m_size);
		list.m_head = nullptr;
		list.m_tail = nullptr;
		list.m_size = 0;
	}

	return *this;
}

template<typename T>
CMyList<T>::~CMyList()
{
	Clear();
}

template<typename T>
void CMyList<T>::push_front(const T& value)
{
	auto newNode = std::make_shared<Node>(value);
	if (m_head)
	{
		newNode->next = m_head;
		m_head->prev = newNode;
	}
	else
	{
		m_tail = newNode;
	}
	m_head = newNode;
	++m_size;
}

template<typename T>
void CMyList<T>::push_front(T&& value)
{
	auto newNode = std::make_shared<Node>(std::move(value));
	if (m_head)
	{
		newNode->next = m_head;
		m_head->prev = newNode;
	}
	else
	{
		m_tail = newNode;
	}
	m_head = newNode;
	++m_size;
}

template<typename T>
void CMyList<T>::push_back(const T& value)
{
	auto newNode = std::make_shared<Node>(value);
	if (m_tail)
	{
		newNode->prev = m_tail;
		m_tail->next = newNode;
	}
	else
	{
		m_head = newNode;
	}
	m_tail = newNode;
	++m_size;
}

template<typename T>
void CMyList<T>::push_back(T&& value)
{
	auto newNode = std::make_shared<Node>(std::move(value));
	if (m_tail)
	{
		newNode->prev = m_tail;
		m_tail->next = newNode;
	}
	else
	{
		m_head = newNode;
	}
	m_tail = newNode;
	++m_size;
}

template<typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::begin()
{
	return CIt(m_head);
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::end()
{
	return CIt(nullptr);
}

template<typename T>
typename CMyList<T>::CRevIt CMyList<T>::rbegin()
{
	return CRevIt(m_tail);
}

template<typename T>
typename CMyList<T>::CRevIt CMyList<T>::rend()
{
	return CRevIt(nullptr);
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::insert(CIt pos, const T& value) {
	auto newNode = std::make_shared<Node>(std::move(value));
	auto posNode = pos.getNode();

	if (!posNode) {
		push_back(std::move(value));
		return CIt(m_tail);
	}

	newNode->next = posNode;
	newNode->prev = posNode->prev;

	if (auto prevNode = posNode->prev.lock()) {
		prevNode->next = newNode;
	}
	else {
		m_head = newNode;
	}

	posNode->prev = newNode;

	++m_size;

	return CIt(newNode);
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::insert(CIt pos, T&& value) {
	auto newNode = std::make_shared<Node>(std::forward<T>(value));
	auto posNode = pos.getNode();

	if (!posNode) {
		push_back(std::forward<T>(value));
		return CIt(m_tail);
	}

	newNode->next = posNode;
	newNode->prev = posNode->prev;

	if (auto prevNode = posNode->prev.lock()) {
		prevNode->next = newNode;
	}
	else {
		m_head = newNode;
	}

	posNode->prev = newNode;

	++m_size;

	return CIt(newNode);
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::erase(CIt pos)
{
	auto posNode = pos.getNode();

	if (!posNode)
	{
		return end();
	}

	if (auto prevNode = posNode->prev.lock()) 
	{
		prevNode->next = posNode->next;
	}
	else 
	{
		m_head = posNode->next;
	}

	if (posNode->next) 
	{
		posNode->next->prev = posNode->prev;
	}
	else 
	{
		m_tail = posNode->prev.lock();
	}

	CIt nextIt(posNode->next);

	--m_size;

	return nextIt;
}

template<typename T>
void CMyList<T>::Clear() noexcept
{
	while (m_head)
	{
		m_head = m_head->next;
	}
	m_tail.reset();
	m_size = 0;
}

template<typename T>
void CMyList<T>::CopyList(const CMyList& list)
{
	for (auto it = list.m_head; it != nullptr; it = it->next) {
		push_back(it->data);
	}
}

template<typename T>
CMyList<T>::CIt::CIt(std::shared_ptr<Node> node)
	: m_current(node)
{}

template<typename T>
T& CMyList<T>::CIt::operator*() const
{
	return m_current->data;
}

template<typename T>
T* CMyList<T>::CIt::operator->()
{
	return &(m_current->data);
}

template<typename T>
typename CMyList<T>::CIt& CMyList<T>::CIt::operator++()
{
		m_current = m_current->next;

	return *this;
}
template<typename T>
typename CMyList<T>::CIt CMyList<T>::CIt::operator++(int)
{
	CIt temp = *this;
	m_current = m_current->next;

	return temp;
}

template<typename T>
typename CMyList<T>::CIt& CMyList<T>::CIt::operator--()
{
	m_current = m_current->prev.lock();

	return *this;
}

template<typename T>
typename CMyList<T>::CIt CMyList<T>::CIt::operator--(int)
{
	CIt temp = *this;
	m_current = m_current->prev.lock();

	return temp;
}

//template<typename T>
//std::shared_ptr<typename CMyList<T>::Node> CMyList<T>::CIt::getNode() const
//{
//	return m_current;
//}

//template<typename T>
//bool operator==(const typename CMyList<T>::CIt& a, const typename CMyList<T>::CIt& b)
//{
//	return a.m_current == b.m_current;
//}
//
//template<typename T>
//bool operator!=(const typename CMyList<T>::CIt& a, const typename CMyList<T>::CIt& b)
//{
//	return a.m_current != b.m_current;
//}

template<typename T>
CMyList<T>::CRevIt::CRevIt(std::shared_ptr<Node> node)
	: m_current(node)
{}

template<typename T>
T& CMyList<T>::CRevIt::operator*() const
{
	return m_current->data;
}

template<typename T>
T* CMyList<T>::CRevIt::operator->()
{
	return &(m_current->data);
}

template<typename T>
typename CMyList<T>::CRevIt& CMyList<T>::CRevIt::operator++()
{
	m_current = m_current->prev.lock();

	return *this;
}
template<typename T>
typename CMyList<T>::CRevIt CMyList<T>::CRevIt::operator++(int)
{
	CRevIt temp = *this;
	m_current = m_current->prev.lock();

	return temp;
}

template<typename T>
typename CMyList<T>::CRevIt& CMyList<T>::CRevIt::operator--()
{
	m_current = m_current->next;

	return *this;
}

template<typename T>
typename CMyList<T>::CRevIt CMyList<T>::CRevIt::operator--(int)
{
	CRevIt temp = *this;
	m_current = m_current->next;

	return temp;
}

//template<typename T>
//std::shared_ptr<typename CMyList<T>::Node> CMyList<T>::CRevIt::getNode() const
//{
//	return m_current;
//}

#endif

