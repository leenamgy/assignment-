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

	printf("n�� �Է� : ");
	scanf("%f", &n);


	printf("����� : %f", recursive(n));

	return 0;
}