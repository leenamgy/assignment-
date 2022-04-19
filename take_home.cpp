#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1번 (실행 성공, 결과 : 4)
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
    int count = countMatchedNumberLetterInString("112233443311334913201234", 4);

    printf("%d", count);

    return 0;
}

// 2번 (실행은 되지만,, 원하는 결과 X)
void excludeRedundantLetters(char* str)
{
    int cnt[200];

    for (int i = 0; i < strlen(str); i++)
    {
        if (cnt[str[i]] == 0)
        {
            cnt[str[i]]++;
        } //else 이하를 모르겠습니다..
    }
}

int main()
{
    char data[100] = { "Hello World" };
    excludeRedundantLetters(data);

    printf("%s", data);

    return 0;
}

// 3번 (실행 성공, 결과 : 6)
int countWords(char* str)
{
    int cnt = 0;
    int findword = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!(str[i] == ' ' || str[i] == '\t') && findword == 0)
        {
            findword = 1;
            cnt++;
        }
        else if (str[i] == ' ' || str[i] == '\t')
            findword = 0;
    }
    return cnt;
}

int main()
{
    int nWords = countWords("Hello World.   Here    is the train\n");
    printf("%d", nWords);
    return 0;
}

// 4번 (실행 X)
bool examinePairedParenthesis(char* str)
{
    int opencnt = 0, closecnt = 0;

    for (int i = 0; i < strlen(str); i++)
    {

        if (str[i] == '(')
           
    }
    
}

int main()
{
    bool result = examinePairedParenthesis("((()))");
    printf("%s", result == true ? "true" : "false");
    return 0;
}

// 5번(실행은 되지만 결과 : 00000000000000)
void convertString(char* input)
{
    char temp[100];
    int i, j = 0;

    for (i = 0; i < strlen(input); i++)
        temp[i] = input[i];

    temp[i] = '\0';

    for (i = 0; i < strlen(temp); i++)
    {
        if (temp[i] != ' ')
            input[j++] = '%20';
     
    }
    input[j] = '\0';
}

int main()
{
    char input[100] = "Hello World. Nice to Meet   you.";
    convertString(input);
    printf("%s\n", input);

    return 0;
}