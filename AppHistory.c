#define _CRT_SECURE_NO_WARNINGS
#define TRUE (1)
#define FALSE (0)

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

typedef struct node {
    int data;
    struct node* link;
} Node;

void   add_node(Node* head, int item);
void   delete_node(Node* head, int item);
void   clear(Node* head);
int    is_in_list(Node* head, int item);
int    count_list(Node* head);
int    is_empty(Node* head);
void   print_list(Node* head);
void   print_menu();

Node* g_dummy_head;

int main()
{
    g_dummy_head = (Node*)malloc(sizeof(Node));
    g_dummy_head->link = NULL;
    int exit = 0;

    while (exit == 0)
    {
        print_menu();

        int num;

        printf("Select: ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
        {
            int data;

            scanf("%d", &data);
            rewind(stdin);
            add_node(g_dummy_head, data);
            break;
        }
        case 2:
        {
            int data;

            scanf("%d", &data);
            rewind(stdin);
            delete_node(g_dummy_head, data);
            break;
        }
        case 3:
            clear(g_dummy_head);
            break;
        case 4:
        {
            int data;

            scanf("%d", &data);
            rewind(stdin);
            printf("[Item: %d] is %s list\n", data, is_in_list(g_dummy_head, data) == TRUE ? "in" : "not in");
            break;
        }
        case 5:
            printf("List count: %d\n", count_list(g_dummy_head));
            break;
        case 6:
            printf("List %s empty\n", is_empty(g_dummy_head) == TRUE ? "is" : "is not");
            break;
        case 7:
            print_list(g_dummy_head);
            printf("\n");
            break;
        case 8:
            printf("exit\n");
            exit = 1;
            break;
        default:
            break;
        }
    }

    clear(g_dummy_head);

    free(g_dummy_head);

    return 0;
}

void add_node(Node* head, int item)
{
    Node* prev = head;
    Node* cur = head->link;

    while (cur != NULL)
    {
        if (cur->data > item)
        {
            break;
        }

        prev = cur;
        cur = cur->link;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->link = cur;

    prev->link = newNode;
}

void delete_node(Node* head, int item)
{
    Node* prev = head;
    Node* cur = head->link;

    while (cur != NULL)
    {
        if (cur->data == item)
        {
            prev->link = cur->link;

            free(cur);

            return;
        }

        prev = cur;
        cur = cur->link;
    }
}

void clear(Node* head)
{
    Node* cur = head->link;

    head->link = NULL;

    while (cur != NULL)
    {
        Node* temp = cur;

        cur = cur->link;
        free(temp);
    }
}

int is_in_list(Node* head, int item)
{
    Node* cur = head->link;

    while (cur != NULL)
    {
        if (cur->data == item)
        {
            return TRUE;
        }

        cur = cur->link;
    }

    return FALSE;
}

int count_list(Node* head)
{
    int      count = 0;
    Node* cur = head->link;

    while (cur != NULL)
    {
        cur = cur->link;
        count++;
    }

    return count;
}

int is_empty(Node* head)
{
    if (head->link == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void print_list(Node* head)
{
    Node* cur = head->link;

    while (cur != NULL)
    {
        printf("%d ", cur->data);

        cur = cur->link;
    }
}

void print_menu()
{
    printf("1. Add; 2.Delete; 3.Clear; 4. is_in_list; 5. count_list; 6. is_empty; 7. print_list; 8. exit;\n\n");
}