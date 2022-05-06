#include<iostream>
#include"arrayList.h"


int main()
{
	try
	{
		arrayList<int> arr;
		for (int i = 0; i < 11; i++) arr.push_back(i);
		arr.erase(11);
	}
	catch (const std::string& s)
	{
		std::cout << s;
	}
	
	return 0;
}