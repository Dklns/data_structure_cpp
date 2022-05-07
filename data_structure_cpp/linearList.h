#ifndef _LINEARLIST_
#define _LINEARLIST_



#include<iostream>
template<typename T>
class linearList
{
public:
	virtual bool empty() const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual int size() const = 0;
	virtual void insert(const T& theElement, int index) = 0;
	virtual void erase(int index) = 0;
	virtual T& get(int index) const = 0;
	//virtual void output(std::ostream& out) const = 0;
};

#endif // !_LINEARLIST_