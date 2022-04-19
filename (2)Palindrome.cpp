#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main()
{
    char word[30];
    char temp[30];
    int length;
    bool check = true;

    printf("Enter a string: ");
    scanf("%[^\n]s", temp);

    int i, k = 0;

    for (i = 0; i < strlen(temp); i++) {
        if (temp[i] >= 'a' && temp[i] <= 'z') word[k++] = temp[i];
        else if (temp[i] >= 'A' && temp[i] <= 'Z') word[k++] = temp[i] - 'A' + 'a';
    }
    word[k] = '\0';

    length = strlen(word);

    for (int i = 0; i < length / 2; i++)
    {
        if (word[i] != word[length - 1 - i])
        {
            check = false;
            break;
        }
    }

    if (check == true) {
        printf("Palindrome!");
    }
    else {
        printf("Not Palindrome!");

    }

    return 0;
}