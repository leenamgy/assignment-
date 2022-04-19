#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    float item;
    struct StackNode* link;
} StackNode;
typedef struct
{
    StackNode* top;
} LinkedStackType;


void init(LinkedStackType* s)
{
    s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
    return (s->top == NULL);
}

void push(LinkedStackType* s, float item)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL)
    {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    }
    else
    {
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}

float pop(LinkedStackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택이 비어있음.\n");
        exit(1);
    }
    else
    {
        StackNode* temp = s->top;
        float item = temp->item;
        s->top = s->top->link;
        free(temp);
        return item;
    }
}

float peek(LinkedStackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택이 비어있음.\n");
        exit(1);
    }
    else
    {
        return s->top->item;
    }
}

float eval(char exp[])
{
    float op1, op2;
    float value;
    int i = 0;
    char ch;
    StackNode* s;

    init(&s);
    for (i = 0; exp[i] != '\0'; i++)
    {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
        {
            value = ch - '0';
            push(&s, value);
        }
        else
        {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch)
            {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }
    return pop(&s);
}


int main()
{
    char* data;
    char str[100] = { '\0' };
    float result;
    int i = 0;
    data = (char*)malloc(sizeof(char) * 100);
    gets(str);

    result = eval(str);
    printf("\n%.2f\n", result);

    return 0;
}