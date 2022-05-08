#include<iostream>
#include<string>
#include"arrayList.h"
#include"chain.h"


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
	try
	{
		/*std::string s = "test";
		chain<std::string> a;
		for (int i = 0; i < 5; i++)
		{
			s += 'a' + i;
			a.insert(s, i);
		}
		std::cout << a << std::endl;
		a.erase(2);
		std::cout << a;*/

		// binSort test code
		int arr[6] = { 4,1,3,2,2,1 };
		chain<studentScore> t;
		for (int i = 0; i < 6; i++)
		{
			studentScore s;
			char ch = 'a' + i;
			s.name = ch;
			s.score = arr[i];
			t.insert(s, i);
		}
		std::cout << "ÅÅÐòÇ°£º\n" << t;
		t.binSort(4);
		std::cout << "\nÅÅÐòºó£º\n" << t;
	}
	catch (const std::string& s)
	{
		std::cout << s;
	}

	return 0;
}

