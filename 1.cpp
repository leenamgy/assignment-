#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int countMatchedNumberLetterInString(const char* str, int digit)
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (digit == str[i] - '0')
            count++;
    }
    return count;
}

int main()
{
    int count = countMatchedNumberLetterInString("112233443311334913201234", 1);

    printf("%d", count);

    return 0;
    
}// ���ڿ� �߿��� 1�� ��µ� Ƚ�� (���� �� ����� : 6)
