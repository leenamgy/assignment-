#include <stdio.h>


float recursive(float n)
{
	if (n == 1)
	{
		return 1;
	}
	else
	{
		return (1 / n + recursive(n - 1));
	}
}

int main()
{
	float n;

	printf("n값 입력 : ");
	scanf("%f", &n);


	printf("결과값 : %f", recursive(n));

	return 0;
}