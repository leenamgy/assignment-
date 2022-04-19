#include "gugudan.h"

using namespace std;

void gugudan::googoo()
{
	cout << "출력할 단을 입력하세요 : ";
	cin >> a;

	for (int i = 1; i < 10; i++) {
		cout << a << "*" << i << "=" << a * i << endl;
	}
}