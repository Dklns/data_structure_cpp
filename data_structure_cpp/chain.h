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
    // ����������
    chain(int initialCapicity = 10); // ֮�����������ʶ������������Ϊ����arrayList����
    chain(const chain<T>& theChain);
    ~chain();

    bool empty() const;
    int size() const;
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void insert(const T& theElement, int theIndex);
    void erase(int theIndex);
    void output(std::ostream& out) const;

    // Ӧ��
    void binSort(int range); // ��������range�������Ӹ���������Ҫ�ֶ�����

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
    targetNode->next = NULL; // �������
}

template<typename T>
inline chain<T>::~chain()
{// ɾ�����нڵ㣬��ͷ�ڵ㿪ʼ����ÿ��ɾ���Ķ���ͷ�ڵ�
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
{// ���Ԫ�ز����ڷ���-1�����򷵻����±�
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
{// �������ָ���±�λ�õĽڵ�
    if (theIndex < 0 || theIndex > listSize)
    {
        std::stringstream s;
        s << "theIndex = " << theIndex << " listSize = " << listSize;
        throw s.str();
    }

    if (theIndex == 0)
    {// �������ͷ����
        firstNode = new chainNode<T>(theElement, NULL);
    }
    else
    {
        int i = 0;
        chainNode<T>* targetNode = firstNode;
        while (i != theIndex - 1)
        {// Ѱ�ҽڵ��ǰ��
            targetNode = targetNode->next;
            i++;
        }
        targetNode->next = new chainNode<T>(theElement, targetNode->next);
    }
    listSize++;
}

template<typename T>
inline void chain<T>::erase(int theIndex)
{// ��Ѱ��Ҫɾ���Ľڵ㣬�����Ѱ�ң������ɾ��
    checkIndex(theIndex);

    chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {// p����Ҫɾ���ڵ��ǰ���ڵ�
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
{// �����������������
    for (chainNode<T>* currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
        out << currentNode->m_element << "   ";
}

template<typename T>
inline void chain<T>::binSort(int range)
{
    auto head = new chainNode<T>* [range + 1];// ��¼ÿ�����ӵĵ�һ���ڵ�
    auto rear = new chainNode<T>* [range + 1];// ��¼ÿ�����ӵ����һ���ڵ�
    for (int b = 0; b <= range; b++) head[b] = NULL; // ��ʼ��

    int theBin = 0;
    for (; firstNode != NULL; firstNode = firstNode->next)
    {
        theBin = firstNode->m_element; // ���ڵ�������Ԫ�ز�������ʱ����Ҫ�ýṹ�Լ��ṩת��Ϊ���͵ĺ������������
        if (head[theBin] == NULL)
        {// ����Ϊ��
            head[theBin] = rear[theBin] = firstNode;
        }
        else
        {// ���Ӳ�Ϊ�� �����������ڵ㣬rear[theBin]ʼ�ռ�¼�����ӵ�β���
            rear[theBin]->next = firstNode;
            rear[theBin] = firstNode;
        }
    }

    chainNode<T>* y = NULL; // ��ʼ��˳�����ӽڵ�, y�����þ��Ǳ���ÿ���ǿ����ӵ�β�ڵ㣬�����¸��ǿ����ӵ�ͷ�ڵ�
    for (int b = 0; b <= range; b++)
    {
        if (head[b] != NULL) // ��һ���ǿ����ӣ���ô������ӵĵ�һ���ڵ���ǰ�˳������ĵ�һ���ڵ�
        {
            if (y == NULL) firstNode = head[b];
            else y->next = head[b];
            y = rear[b];
        }
    }
    if (y != NULL) y->next = NULL; // �������һ���ڵ��nextӦ��ָ��NULL
    delete[] head;
    delete[] rear;
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
