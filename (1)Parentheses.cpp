#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 100

typedef struct
{
    char data[max];
    int top;
}stackType;

int check(char* exp);
void init(stackType* s);
void push(stackType* s, int x);
int pop(stackType* s);
int is_full(stackType* s);
int is_empty(stackType* s);

int main()
{
    stackType s;
    char exp[20];
    fgets(exp, sizeof(exp), stdin);
    if (check(exp) == 1)
        puts("Yes");
    else
        puts("No");
    return 0;
}
void init(stackType* s)
{
    s->top = -1;
}
int is_full(stackType* s)
{
    return s->top == max - 1;
}
int is_empty(stackType* s)
{
    return s->top == -1;
}
void push(stackType* s, int x)
{
    if (is_full(s))
    {
        fprintf(stderr, "원소가 다 찼습니다.\n");
        return;
    }
    s->data[++(s->top)] = x;
}
int pop(stackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "원소가 없습니다\n");
        exit(1);
    }
    return s->data[(s->top)--];
}
int check(char* exp)
{
    stackType s;
    char ch, open_ch;
    int n = strlen(exp);
    init(&s);
    for (int i = 0; i < n; i++)
    {
        ch = exp[i];
        switch (ch)
        {
        case '(':case '[':case'{':
            push(&s, ch);
            break;
        case ')':case']':case'}':
            if (is_empty(&s))return 0;
            else
            {
                open_ch = pop(&s);
                if ((open_ch == '(' && ch != ')') || (open_ch == '{' && ch != '}') ||
                    (open_ch == '[' && ch != ']'))
                    return 0;

            }
            break;
        }
    }

    if (!is_empty(&s))return 0;
    return 1;
}