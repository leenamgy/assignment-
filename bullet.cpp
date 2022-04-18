#include<iostream>
#include<string>
#include<Windows.h>

using namespace std;

int main()
{
	string str = "-";
	
	for (int i = 0; i < 100; i++)
	{
		str = " " + str;
		printf("%s\r", str.c_str());
		Sleep(100);
	}
}