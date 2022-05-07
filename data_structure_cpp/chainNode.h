#pragma once
template<typename T>
class chainNode
{
public:
	chainNode() {};
	chainNode(const T& element) { m_element = element; };
	chainNode(const T& element, chainNode<T>* next)
	{
		m_element = element;
		this->next = next;
	}

	T m_element;
	chainNode<T>* next;
};

