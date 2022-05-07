#include<iostream>
#include<string>
#include"arrayList.h"
#include"chain.h"


int main()
{
	// arrayList

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
	
	// chain
	try
	{
		std::string s = "test";
		chain<std::string> a;
		for (int i = 0; i < 5; i++)
		{
			s += 'a' + i;
			a.insert(s, i);
		}
		std::cout << a << std::endl;
		a.erase(2);
		std::cout << a;
	}
	catch (const std::string& s)
	{
		std::cout << s;
	}

	return 0;
}