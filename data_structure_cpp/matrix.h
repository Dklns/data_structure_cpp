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
{// 自己不能复制自己
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
{// 返回矩阵 w = *this + m
	if (theRow != m.theRow || theColumn != m.theColumn) throw "rows or columns are error";

	matrix<T> w(theRow, theColumn); //生成矩阵
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
	for (int i = 1; i <= theRow; i++) // 计算this的第i行乘以m的第j列
	{
		for (int j = 1; j <= m.theColumn; j++)
		{
			T sum = element[ct] * m.element[cm]; // 之所以将第一次乘法独立出来是因为不知道sum的类型，所以不知道怎么赋值初始值
			// 遍历第i行的所有元素，也可以说是m第j列的所有元素
			for (int k = 2; k <= theColumn; k++) 
			{
				ct++;                  // *this第i行的下一项
				cm += m.theColumn - 1; // m中第j列的下一项
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum;  // 储存在w(i,j)

		    // 从行的起点和下一列重新开始
			ct -= theColumn - 1; 
			cm = j;
		}

		// 从下一行和第一列开始
		ct += theColumn;
		cm = 0;
	}
	return w;
}

