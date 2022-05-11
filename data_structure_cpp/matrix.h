#pragma once
#include<iostream>
#include<ostream>
#include<string>
#include<cstdlib>
#include<algorithm>

template<typename T>
class matrix
{
public:
	matrix(int row = 0, int column = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[] element; };

	void show();
	int row() const { return theRow; };
	int column() const { return theColumn; };
	T& operator()(int row, int column) const;
	matrix<T>& operator=(const matrix<T>&);
	matrix<T> operator+(matrix<T>&)const;
	matrix<T> operator*(matrix<T>&)const;

private:
	int theRow;
	int theColumn;
	T* element;
};

template<typename T>
matrix<T>::matrix(int row, int column)
{
	if (row < 0 || column < 0) throw "Rows and columns must be > 0";
	if ((row == 0 || column == 0) && (row != 0 || column != 0)) throw "Either both or neither rows and columns should be zero";
	this->theColumn = column;
	this->theRow = row;
	this->element = new T[row * column];
}

template<typename T>
matrix<T>::matrix(const matrix<T>& m)
{
	theRow = m.theRow;
	theColumn = m.theColumn;
	element = new T[theRow * theColumn];

	std::copy(m.element, m.element + theColumn * theRow, element);
}

template<typename T>
inline void matrix<T>::show()
{
	int r = this->theRow, col = this->theColumn;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < col; j++) std::cout << element[i * col + j] << "	";
		std::cout << std::endl;
	}
}

template<typename T>
T& matrix<T>:: operator()(int row, int column) const
{
	if (row < 1 || row > theRow || column < 1 || column > theColumn)
		throw "the Index is wrong";
	return element[(row - 1) * theColumn + column - 1];
}

template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{// �Լ����ܸ����Լ�
	if (&m != this)
	{
		delete[] element;
		theRow = m.theRow;
		theColumn = m.theColumn;
		element = new T[theRow * theColumn];
		std::copy(m.element, m.element + theRow * theColumn, element);
	}
	return *this;
}

template<typename T>
inline matrix<T> matrix<T>::operator+(matrix<T>& m) const
{// ���ؾ��� w = *this + m
	if (theRow != m.theRow || theColumn != m.theColumn) throw "rows or columns are error";

	matrix<T> w(theRow, theColumn); //���ɾ���
	for (int i = 0; i < theRow * theColumn; i++)
		w.element[i] = element[i] + m.element[i];
	return w;
}

template<typename T>
matrix<T> matrix<T>::operator*(matrix<T>& m) const
{
	if (theColumn != m.theRow) throw"matrixs's row and column are not matched";

	matrix<T> w(theRow ,m.theColumn); 

	int ct = 0, cm = 0, cw = 0;
	for (int i = 1; i <= theRow; i++) // ����this�ĵ�i�г���m�ĵ�j��
	{
		for (int j = 1; j <= m.theColumn; j++)
		{
			T sum = element[ct] * m.element[cm]; // ֮���Խ���һ�γ˷�������������Ϊ��֪��sum�����ͣ����Բ�֪����ô��ֵ��ʼֵ
			// ������i�е�����Ԫ�أ�Ҳ����˵��m��j�е�����Ԫ��
			for (int k = 2; k <= theColumn; k++) 
			{
				ct++;                  // *this��i�е���һ��
				cm += m.theColumn - 1; // m�е�j�е���һ��
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // ������w(i,j)

		    // ���е�������һ�����¿�ʼ
			ct -= theColumn - 1; 
			cm = j;
		}

		// ����һ�к͵�һ�п�ʼ
		ct += theColumn;
		cm = 0;
	}
	return w;
}

