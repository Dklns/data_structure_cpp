#include<iostream>
#include<string>
#include"arrayList.h"
#include"chain.h"
#include"matrix.h"

// chain: binSort test code
struct studentScore {
	std::string name;
	int score;

	operator int() const { return score; };
};

std::ostream& operator<<(std::ostream& out, const studentScore& s)
{
	out << "	" << s.name << "	" << s.score << std::endl;
	return out;
}

int main()
{
	// arrayList test code

	/*try
	{
		arrayList<int> arr;
		for (int i = 0; i < 11; i++) arr.push_back(i);
		arr.erase(11);
	}
	catch (const std::string& s)
	{
		std::cout << s;
	}*/
	
	// chain test code
	//try
	//{
	//	/*std::string s = "test";
	//	chain<std::string> a;
	//	for (int i = 0; i < 5; i++)
	//	{
	//		s += 'a' + i;
	//		a.insert(s, i);
	//	}
	//	std::cout << a << std::endl;
	//	a.erase(2);
	//	std::cout << a;*/

	//	// binSort test code
	//	int arr[6] = { 4,1,3,2,2,1 };
	//	chain<studentScore> t;
	//	for (int i = 0; i < 6; i++)
	//	{
	//		studentScore s;
	//		char ch = 'a' + i;
	//		s.name = ch;
	//		s.score = arr[i];
	//		t.insert(s, i);
	//	}
	//	std::cout << "ÅÅÐòÇ°£º\n" << t;
	//	t.binSort(4);
	//	std::cout << "\nÅÅÐòºó£º\n" << t;
	//}
	//catch (const std::string& s)
	//{
	//	std::cout << s;
	//}

	// matrix
	try
	{
		matrix<int> m(2, 2);
		m(1, 1) = 8;
		m(1, 2) = 9;
		m(2, 1) = 3;
		m(2, 2) = 4;
		m.show();
		matrix<int> n(4, 3);
		n = m;
		n.show();
		matrix<int> w(2, 2);
		w = n + m;
		w.show();
		matrix<int> y(4, 2);
		int arr[8] = { 1,2,3,4,5,6,7,8 };
		int k = 0;
		for (int i = 1; i <= y.row(); i++)
		{
			for (int j = 1; j <= y.column(); j++) y(i, j) = arr[k++];
		}
		matrix<int> x = y * m;
		y.show();
		x.show();
	}
	catch (const std::string& s)
	{
		std::cout << s;
	}
	return 0;
}

