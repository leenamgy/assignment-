#include <iostream>
#include <string>

using namespace std;

bool Palindrome(string _s);

int main()
{
	cout << boolalpha;
	cout << Palindrome(str2) << endl;
}

bool Palindrome(string _s)
{
	int len = _s.size();

	for (int i = 0; i < len / 2; i++)
	{
		if (_s[i] != _s[len - i - 1])
		{
			return false;
		}
	}

	return true;
}