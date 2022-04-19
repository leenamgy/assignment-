#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Board_X 20 // ���� ũ��
#define Board_Y 20 // ���� ũ��
#define Board_X_W 2 // ������ ���� ��ġ
#define Board_Y_W 2 // ������ ���� ��ġ

#define ESC 27 // ESC
#define UP 72 // ��
#define DOWN 80 // ��
#define LEFT 75 // ��
#define RIGHT 77 // ��
#define P 50 // �빮�� P 
#define p 70 // �ҹ��� p

#define EMPTY 0 // ��ĭ
#define PLAYER 1 // �÷��̾�
#define ITEM 2 // ������
#define WALL 3 // ��
#define BOMB 4 // ��ź

bool isGameover = false; // ���ӿ��� �÷���
bool isEatitem = false; // ������ �÷���
bool isEatbomb = false; // ������ �÷���
bool isLengthMinus = false; // ���� ���� �÷���
bool isPause = false; // ���� �÷���

typedef struct scoreInfo {
    char name[20];
    int score;
}scoreInfo;

void reset_board(int Board[20][20]); // ������ �ʱ�ȭ
void reset_snake(int snake_X[], int snake_Y[]);
void push_snake(int* length, int snake_X[], int snake_Y[]); // snake_X, snake_Y�ȿ� �迭�� �������� �б�
void cursor_delete(void); // Ŀ�� ����� �Լ�
void gotoxy(int x, int y); // ��ǥ �Լ�
void print_Board(int Board[20][20]); // ������ ���
void UI(int score); // UI
void check_key(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length); // Ű �Է¹޴� �Լ� 
void pause(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length); // pause
void title(scoreInfo playerInfo[], int* playerSize, int* menu); // Ÿ��Ʋ
void gameover(scoreInfo playerinfo[], int* playerSize, int score, char* key); // ���� ����
void item_spawner(int Board[20][20], int* item_X, int* item_Y, int* score, int* length); // ������ ����
void bomb_spawner(int Board[20][20], int* bomb_X, int* bomb_Y, int snake_X[], int snake_Y[], int* score, int* length); // ������ ����
void game_check(int Board[20][20], int snake_X[]); // ���� üũ
void player(int Board[20][20], int* Player_Y, int* Player_X, int* length, int snake_X[], int snake_Y[]); // �÷��̾�

void init(int Board[20][20], int snake_X[], int snake_Y[]); // �ʱ�ȭ
void Update(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* item_X, int* item_Y, int* bomb_X, int* bomb_Y, int* score, int* length); // ������ ����
void Render(int Board[20][20], int score); // ȭ�� ���

int main(void)
{
    int Board[20][20] = { 0, }; // ������
    int Player_X = 9, Player_Y = 9; // �÷��̾� �ʱ� ��ġ
    int item_X = 5, item_Y = 5; // ������ �ʱ� ��ġ
    int bomb_X = 10, bomb_Y = 10;
    int score = 0; // ����
    int snake_X[100], snake_Y[100]; // �첿�� ��ġ ���� 
    int length = 0; // �첿�� ����

    char key = '0'; // Ű 
    int menu, playerSize = 0;
    scoreInfo playerInfo[100];

    while (1) {
        Player_X = 9, Player_Y = 9;
        item_X = 5, item_Y = 5;
        bomb_X = 10, bomb_Y = 10;
        score = 0;
        length = 0;
        init(Board, snake_X, snake_Y); // �ʱ�ȭ
        title(playerInfo, &playerSize, &menu); // Ÿ��Ʋ
        if (menu == 2)
            break;
        while (1)
        {
            Update(playerInfo, &playerSize, &key, Board, &Player_Y, &Player_X, snake_X, snake_Y, &item_X, &item_Y, &bomb_X, &bomb_Y, &score, &length); // ������ ���� 
            if (isGameover == true) {
                isGameover = false;
                break;
            }
        }
    }

    return 0;
}

void reset_board(int Board[20][20]) // ������ �ʱ�ȭ
{
    int i;

    for (i = 0; i < Board_X; i++)
    {
        Board[0][i] = WALL;
        Board[Board_Y - 1][i] = WALL;
    }

    for (i = 0; i < Board_Y; i++)
    {
        Board[i][0] = WALL;
        Board[i][Board_X - 1] = WALL;
    }

    for (i = 1; i < Board_X - 1; i++) {
        for (int j = 1; j < Board_Y - 1; j++) {
            Board[i][j] = 0;
        }
    }
}

void reset_snake(int snake_X[], int snake_Y[])
{
    int i;

    for (i = 0; i < 100; i++)
    {
        snake_X[i] = -1;
        snake_Y[i] = -1;
    }
}

void push_snake(int* length, int snake_X[], int snake_Y[]) // snake_X, snake_Y�ȿ� �迭�� �������� �б�
{
    int i = 0;

    i = *length;
    while (i >= 0) {
        snake_X[i + 1] = snake_X[i];
        snake_Y[i + 1] = snake_Y[i];
        i--;
    }
}

void cursor_delete(void) // Ŀ�� ����� �Լ�
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) // ��ǥ �Լ�
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void print_Board(int Board[20][20]) // ������ ���
{
    int i, j, k = 0;

    for (i = 0; i < Board_X; i++) // ������ ��Ȳ ���
    {
        for (j = 0; j < Board_Y; j++)
        {
            gotoxy(Board_X_W + j + k, Board_Y_W + i);

            switch (Board[i][j])
            {
            case EMPTY:
                printf("  ");
                break;
            case PLAYER:
                printf("��");
                break;
            case ITEM:
                printf("��");
                break;
            case WALL:
                printf("��");
                break;
            case BOMB:
                printf("��");
                break;
            }
            k++;
        }
        k = 0;
    }
}

void UI(int score) // UI
{
    gotoxy(46, 2);
    printf("SNAKE GAME");

    gotoxy(46, 4);
    printf("�첿����� ����");

    gotoxy(46, 6);
    printf("score = %07d", score); // �ǽð����� ���� ���

    gotoxy(46, 12);
    printf("> ���۹� <");

    gotoxy(46, 13);
    printf("���� ���� : ����Ű");

    gotoxy(46, 14);
    printf("����Ű�� ������ ���Ű : pause");

    gotoxy(46, 15);
    printf("ESC : ���� ����");

    gotoxy(46, 17);
    printf("> ���� <");

    gotoxy(46, 18);
    printf("ITEM : ��");
    gotoxy(46, 19);
    printf("BOMB : ��");
    gotoxy(46, 20);
    printf("PLAYER : ��");
}

void check_key(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length) // Ű �Է¹޴� �Լ� 
{
    isPause = false;
    switch (*key)
    {
    case UP:
        Sleep(70);
        switch (Board[*Player_Y - 1][*Player_X])
        {
        case EMPTY:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y - 1; // �̵�
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y - 1; // �̵�
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y - 1; // �̵�
            isEatbomb = true;
            break;
        case WALL:
        case PLAYER:
            isGameover = true;
            break;
        }
        break;
    case DOWN:
        Sleep(70);
        switch (Board[*Player_Y + 1][*Player_X])
        {
        case EMPTY:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y + 1; // �̵�
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y + 1; // �̵�
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_Y = *Player_Y + 1; // �̵�
            isEatbomb = true;
            break;
        case WALL:
        case PLAYER:
            isGameover = true;
            break;
        }
        break;
    case LEFT:
        Sleep(70);
        switch (Board[*Player_Y][*Player_X - 1])
        {
        case EMPTY:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X - 1; // �̵�
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X - 1; // �̵�
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X - 1; // �̵�
            isEatbomb = true;
            break;
        case WALL:
        case PLAYER:
            isGameover = true;
            break;
        }
        break;
    case RIGHT:
        Sleep(70);
        switch (Board[*Player_Y][*Player_X + 1])
        {
        case EMPTY:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X + 1; // �̵�
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X + 1; // �̵�
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0���� �ʱ�ȭ
            *Player_X = *Player_X + 1; // �̵�
            isEatbomb = true;
            break;
        case WALL:
        case PLAYER:
            isGameover = true;
            break;
        }
        break;
    case ESC:
        isGameover = true;
    default:
        isPause = true;
        break;
    }
}

void pause(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length) // pause
{
    gotoxy(46, 9);
    printf("Press any key to continue");
    check_key(key, Board, Player_Y, Player_X, snake_X, snake_Y, length);

    isPause = false;
}

void title(scoreInfo playerInfo[], int* playerSize, int* menu) // Ÿ��Ʋ
{
    while (1) {
        gotoxy(20, 9);
        printf("���־�Ʃ������� �������ּ���");

        gotoxy(30, 10);
        printf("SNAKE GAME");

        gotoxy(28, 12);
        printf("�첿�� ��� ����");

        gotoxy(26, 16);
        printf("> 1. ���� ���� <");
        gotoxy(26, 18);
        printf("> 2. ���� ���� <");

        gotoxy(26, 20);
        printf("�� �޴� �Է� : ");
        scanf_s("%d", menu);
        system("cls");
        if (*menu == 2) {
            gotoxy(26, 10);
            printf("> ���� ���� <\n\n\n");
            return;
        }
        else if (*menu == 1) {
            break;
        }
        else continue;
    }
    gotoxy(30, 10);
    printf("�÷��̾� �̸��� �Է����ּ���");
    gotoxy(30, 12);
    scanf("%s", playerInfo[*playerSize].name);
    system("cls");
    gotoxy(2, 2);
    printf("�ƹ�Ű�� �����ּ���.");

    gotoxy(2, 3);
    printf("Ű�� �Է��ϸ� �����մϴ�.");
}

void gameover(scoreInfo playerInfo[], int* playerSize, int score, char* key) // ���� ����
{
    system("cls");

    gotoxy(10, 6);
    printf("GAME OVER");

    playerInfo[*playerSize].score = score;
    gotoxy(8, 8);
    printf("NAME : %s / SCORE : %d", playerInfo[*playerSize].name, playerInfo[*playerSize].score);

    (*playerSize) += 1;

    for (int i = 0; i < *playerSize - 1; i++) {
        for (int j = 0; j < *playerSize - 1 - i; j++) {
            if (playerInfo[j].score < playerInfo[j + 1].score) {
                scoreInfo temp = playerInfo[j];
                playerInfo[j] = playerInfo[j + 1];
                playerInfo[j + 1] = temp;
            }
        }
    }

    gotoxy(44, 2);
    printf("Player Score Board");
    gotoxy(44, 3);
    printf("========================");
    gotoxy(44, 4);
    printf("    NAME\tSCORE");
    gotoxy(44, 5);
    printf("========================");

    for (int i = 0; i < *playerSize; i++) {
        gotoxy(44, i + 6);
        printf("    %s\t%d", playerInfo[i].name, playerInfo[i].score);
    }

    gotoxy(8, 10);
    printf("�ƹ�Ű�� �����ּ���.");
    *key = _getch();
    gotoxy(6, 10);
    printf("3�� �� �ʱ� ȭ������ �̵��մϴ�.");
    Sleep(3000);
    system("cls");
}

void item_spawner(int Board[20][20], int* item_X, int* item_Y, int* score, int* length) // ������ ����
{
    if (isEatitem == false) // �������� �ȸԾ��� ���
    {
        Board[*item_X][*item_Y] = ITEM; // ���� ����
        Board[*item_X][*item_Y] = ITEM; // ���� ����
    }
    else // �������� �Ծ��� ���
    {
        *score += 100; // ���� 100�� �߰�
        (*length)++; // �첿�� ���� ����

        *item_X = rand() % 18 + 1; // ����
        *item_Y = rand() % 18 + 1; // ����
        if (Board[*item_X][*item_Y] == PLAYER)
        {
            *item_X = rand() % 18 + 1; // ����
            *item_Y = rand() % 18 + 1; // ����
        }
        Board[*item_X][*item_Y] = ITEM; // ���� ����

        isEatitem = false; // ������ �÷��� false�� ��ȯ
    }
}
void bomb_spawner(int Board[20][20], int* bomb_X, int* bomb_Y, int snake_Y[], int snake_X[], int* score, int* length) // ������ ����
{
    if (isEatbomb == false) // �������� �ȸԾ��� ���
    {
        Board[*bomb_X][*bomb_Y] = BOMB; // ���� ����
        Board[*bomb_X][*bomb_Y] = BOMB; // ���� ����
    }
    else // �������� �Ծ��� ���
    {
        *score -= 100; // ���� 100�� ����
        isLengthMinus = true;
        *bomb_X = rand() % 18 + 1; // ����
        *bomb_Y = rand() % 18 + 1; // ����
        if (Board[*bomb_X][*bomb_Y] == PLAYER)
        {
            *bomb_X = rand() % 18 + 1; // ����
            *bomb_Y = rand() % 18 + 1; // ����
        }
        Board[*bomb_X][*bomb_Y] = BOMB; // ���� ����

        isEatbomb = false; // ������ �÷��� false�� ��ȯ
    }
}

void game_check(int Board[20][20], int snake_X[]) // ���� üũ
{
    int i, j, k = 0;

    for (i = 0; i < Board_X; i++)
    {
        for (j = 0; j < Board_X; j++)
        {
            gotoxy(Board_X_W + j, Board_Y_W + i + 21);
            printf("%d", Board[i][j]);

            k++;
        }
        k = 0;
    }

    for (i = 0; i < 10; i++)
    {
        gotoxy(46 + i, 10);
        printf("%d", snake_X[i]);
    }
}

void player(int Board[20][20], int* Player_Y, int* Player_X, int* length, int snake_X[], int snake_Y[]) // �÷��̾�
{
    int i;

    Board[*Player_Y][*Player_X] = PLAYER; // �÷��̾� ��ġ
    if (isLengthMinus == true) {
        if (*length > 0)
            (*length) -= 1;
        for (i = 0; i < *length; i++)
        {
            Board[snake_Y[i]][snake_X[i]] = PLAYER; // �÷��̾� ��ġ
            Board[snake_Y[*length]][snake_X[*length]] = EMPTY;
        }
        Board[snake_Y[*length + 1]][snake_X[*length + 1]] = EMPTY;
        isLengthMinus = false;
    }
    if (*length > 0)
    {
        for (i = 0; i < *length; i++)
        {
            Board[snake_Y[i]][snake_X[i]] = PLAYER; // �÷��̾� ��ġ
            Board[snake_Y[*length]][snake_X[*length]] = EMPTY;
        }
    }
}

void init(int Board[20][20], int snake_X[], int snake_Y[]) // �ʱ�ȭ
{
    cursor_delete(); // Ŀ�� ����
    reset_board(Board); // ������ �ʱ�ȭ

    reset_snake(snake_X, snake_Y); // snake_X, snake_Y �ʱ�ȭ
}

void Update(scoreInfo playerInfo[], int* playerSize, char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* item_X, int* item_Y, int* bomb_X, int* bomb_Y, int* score, int* length) // ������ ����
{
    *key = _getch(); // �Է�

    do
    {
        check_key(key, Board, Player_Y, Player_X, snake_X, snake_Y, length);
        player(Board, Player_Y, Player_X, length, snake_X, snake_Y); // �÷��̾�
        item_spawner(Board, item_X, item_Y, score, length); // ������ ����
        bomb_spawner(Board, bomb_X, bomb_Y, snake_X, snake_Y, score, length);
        Render(Board, *score); //���
        if (isGameover == true) {// ���ӿ����� ���ϰ�� ���ӿ���
            gameover(playerInfo, playerSize, *score, key);
            return;
        }
        if (isPause == true) // ��� ���ϰ�� 
            pause(key, Board, Player_Y, Player_X, snake_X, snake_Y, length);

    } while (!_kbhit());
}

void Render(int Board[20][20], int score) // ȭ�� ���
{
    print_Board(Board); // ���� ���
    UI(score); // UI

   //game_check(); // ����üũ
    if (isPause != true)
    {
        gotoxy(46, 9);
        printf("                            ");
    }
}