#pragma once
#ifndef _ARRAYLIST_
#define _ARRAYLIST

#include<iostream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include "linearList.h"

template<typename T>
class arrayList :
    public linearList<T>
{
public:
    arrayList(int initialCapicity = 10);
    arrayList(const arrayList<T>& theList);
    ~arrayList();

    bool empty() const;
    int size() const;
    void insert(const T& element, int index);
    int indexOf(const T& element) const;
    void erase(int theIndex);
    T& get(int theIndex) const;
    void push_back(T theElement);

    int capicity() const;
protected:
    void checkIndex(int theIndex) const;
    T* elements;
    int m_size;
    int m_capicity;
private:
    void doubleCapicity();
};

template<typename T>
arrayList<T>::arrayList(int initialCapicity)
{
    if (initialCapicity < 1)
    {
        std::stringstream s;
        s << "Initial capicity = " << initialCapicity << " must be > 0";
        throw s.str();
    }

    elements = new T[initialCapicity];
    m_size = 0;
    m_capicity = initialCapicity;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    m_capicity = theList.capicity();
    m_size = theList.size();
    elements = new T[m_capicity];
    copy(theList.elements, theList.elements + m_size, elements);
}

template<typename T>
arrayList<T>::~arrayList()
{
    delete[] elements;
}

template<typename T>
bool arrayList<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
int arrayList<T>::size() const
{
    return m_size;
}

template<typename T>
void arrayList<T>::insert(const T& element, int index)
{
    if (index < 0 || index > m_size)
    {
        std::stringstream s;
        s << "index = " << index << " size = " << m_size;
        throw s.str();
    }

    if (m_size == m_capicity) doubleCapicity();

    std::copy(elements + index, elements + m_size, elements + index + 1);
    elements[index] = element;
    m_size++;
}

template<typename T>
int arrayList<T>::indexOf(const T& element) const
{
    int theIndex = 0;
    for (; theIndex < m_size; theIndex++)
    {
        if (elements[theIndex] == element) break;
    }
    if (theIndex != m_size) return theIndex;
    return -1;
}

template<typename T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    std::copy(elements + theIndex + 1, elements + m_size, elements + theIndex);

    elements[--m_size].~T();
}

template<typename T>
T& arrayList<T>::get(int theIndex) const
{
    // ¼ì²éË÷ÒýÊÇ·ñ´íÎó
    checkIndex(theIndex);
    return elements[theIndex];
}

template<typename T>
void arrayList<T>::push_back(T theElement)
{
    if (m_size == m_capicity) doubleCapicity();
    elements[m_size] = theElement;
    m_size++;
}

template<typename T>
int arrayList<T>::capicity() const
{
    return m_capicity;
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= m_size)
    {
        std::stringstream s;
        s << "index = " << theIndex << "size = " << m_size;
        throw s.str();
    }
}

template<typename T>
inline void arrayList<T>::doubleCapicity()
{
    T* t = new T[m_capicity * 2];
    for (int i = 0; i < m_size; i++) t[i] = elements[i];
    m_capicity *= 2;
    delete[] elements;
    elements = t;
}

#endif // !_ARRAYLIST_