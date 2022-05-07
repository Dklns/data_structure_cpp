#pragma once
#include<iostream>
#include<sstream>
#include<ostream>
#include<cstdlib>
#include "linearList.h"
#include"chainNode.h"

template<typename T>
class chain :
    public linearList<T>
{
public:
    // 构造与销毁
    chain(int initialCapicity = 10); // 之所以有这个初识容量变量，是为了与arrayList相容
    chain(const chain<T>& theChain);
    ~chain();

    bool empty() const;
    int size() const;
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void insert(const T& theElement, int theIndex);
    void erase(int theIndex);
    void output(std::ostream& out) const;

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;
    int listSize;
};

template<typename T>
inline chain<T>::chain(int initialCapicity)
{
    if (initialCapicity < 1)
    {
        std::stringstream s;
        s << "Initial capicity = " << initialCapicity << " must be > 0";
        throw s.str();
    }
    firstNode = NULL;
    listSize = 0;
}

template<typename T>
inline chain<T>::chain(const chain<T>& theChain)
{
    listSize = theChain.listSize;

    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T>* sourceNode = theChain.firstNode;
    firstNode = new chainNode<T>(sourceNode->m_element);
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    while (sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->m_element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; // 链表结束
}

template<typename T>
inline chain<T>::~chain()
{// 删除所有节点，从头节点开始，即每次删除的都是头节点
    chainNode<T>* nextNode;
    while (firstNode != NULL)
    {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<typename T>
inline bool chain<T>::empty() const
{
    return firstNode == NULL;
}

template<typename T>
inline int chain<T>::size() const
{
    return listSize;
}

template<typename T>
T& chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) currentNode = currentNode->next;
    return currentNode->m_element;
}

template<typename T>
inline int chain<T>::indexOf(const T& theElement) const
{// 如果元素不存在返回-1，否则返回其下标
    chainNode<T>* currentNode = firstNode;
    int index = 0;
    while (currentNode != NULL && currentNode->m_element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == NULL) return -1;
    else return index;
}

template<typename T>
inline void chain<T>::insert(const T& theElement, int theIndex)
{// 插入代替指定下标位置的节点
    if (theIndex < 0 || theIndex > listSize)
    {
        std::stringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw s.str();
    }

    if (theIndex == 0)
    {// 在链表表头插入
        firstNode = new chainNode<T>(theElement, NULL);
    }
    else
    {
        int i = 0;
        chainNode<T>* targetNode = firstNode;
        while (i != theIndex - 1)
        {// 寻找节点的前驱
            targetNode = targetNode->next;
            i++;
        }
        targetNode->next = new chainNode<T>(theElement, targetNode->next);
    }
    listSize++;
}

template<typename T>
inline void chain<T>::erase(int theIndex)
{// 先寻找要删除的节点，分情况寻找，最后再删除
    checkIndex(theIndex);

    chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {// p代表要删除节点的前驱节点
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) p = p->next;
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    listSize--;
    delete deleteNode;
}

template<typename T>
inline void chain<T>::output(std::ostream& out) const
{// 把链表放入输入流中
    for (chainNode<T>* currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
        out << currentNode->m_element << "   ";
}

template<typename T>
std::ostream& operator<<(std::ostream& out, chain<T>& x)
{
    x.output(out);
    return out;
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::stringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw s.str();
    }
}
