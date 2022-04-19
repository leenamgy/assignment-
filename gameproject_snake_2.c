#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Board_X 20 // 가로 크기
#define Board_Y 20 // 세로 크기
#define Board_X_W 2 // 게임판 시작 위치
#define Board_Y_W 2 // 게임판 시작 위치

#define ESC 27 // ESC
#define UP 72 // 상
#define DOWN 80 // 하
#define LEFT 75 // 좌
#define RIGHT 77 // 우
#define P 50 // 대문자 P 
#define p 70 // 소문자 p

#define EMPTY 0 // 빈칸
#define PLAYER 1 // 플레이어
#define ITEM 2 // 아이템
#define WALL 3 // 벽
#define BOMB 4 // 폭탄

bool isGameover = false; // 게임오버 플래그
bool isEatitem = false; // 아이템 플래그
bool isEatbomb = false; // 아이템 플래그
bool isLengthMinus = false; // 길이 감소 플래그
bool isPause = false; // 퍼즈 플래그

typedef struct scoreInfo {
    char name[20];
    int score;
}scoreInfo;

void reset_board(int Board[20][20]); // 게임판 초기화
void reset_snake(int snake_X[], int snake_Y[]);
void push_snake(int* length, int snake_X[], int snake_Y[]); // snake_X, snake_Y안에 배열을 뒤쪽으로 밀기
void cursor_delete(void); // 커서 지우는 함수
void gotoxy(int x, int y); // 좌표 함수
void print_Board(int Board[20][20]); // 게임판 출력
void UI(int score); // UI
void check_key(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length); // 키 입력받는 함수 
void pause(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length); // pause
void title(scoreInfo playerInfo[], int* playerSize, int* menu); // 타이틀
void gameover(scoreInfo playerinfo[], int* playerSize, int score, char* key); // 게임 오버
void item_spawner(int Board[20][20], int* item_X, int* item_Y, int* score, int* length); // 아이템 스폰
void bomb_spawner(int Board[20][20], int* bomb_X, int* bomb_Y, int snake_X[], int snake_Y[], int* score, int* length); // 아이템 스폰
void game_check(int Board[20][20], int snake_X[]); // 게임 체크
void player(int Board[20][20], int* Player_Y, int* Player_X, int* length, int snake_X[], int snake_Y[]); // 플레이어

void init(int Board[20][20], int snake_X[], int snake_Y[]); // 초기화
void Update(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* item_X, int* item_Y, int* bomb_X, int* bomb_Y, int* score, int* length); // 데이터 갱신
void Render(int Board[20][20], int score); // 화면 출력

int main(void)
{
    int Board[20][20] = { 0, }; // 게임판
    int Player_X = 9, Player_Y = 9; // 플레이어 초기 위치
    int item_X = 5, item_Y = 5; // 아이템 초기 위치
    int bomb_X = 10, bomb_Y = 10;
    int score = 0; // 점수
    int snake_X[100], snake_Y[100]; // 뱀꼬리 위치 저장 
    int length = 0; // 뱀꼬리 길이

    char key = '0'; // 키 
    int menu, playerSize = 0;
    scoreInfo playerInfo[100];

    while (1) {
        Player_X = 9, Player_Y = 9;
        item_X = 5, item_Y = 5;
        bomb_X = 10, bomb_Y = 10;
        score = 0;
        length = 0;
        init(Board, snake_X, snake_Y); // 초기화
        title(playerInfo, &playerSize, &menu); // 타이틀
        if (menu == 2)
            break;
        while (1)
        {
            Update(playerInfo, &playerSize, &key, Board, &Player_Y, &Player_X, snake_X, snake_Y, &item_X, &item_Y, &bomb_X, &bomb_Y, &score, &length); // 데이터 갱신 
            if (isGameover == true) {
                isGameover = false;
                break;
            }
        }
    }

    return 0;
}

void reset_board(int Board[20][20]) // 게임판 초기화
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

void push_snake(int* length, int snake_X[], int snake_Y[]) // snake_X, snake_Y안에 배열을 뒤쪽으로 밀기
{
    int i = 0;

    i = *length;
    while (i >= 0) {
        snake_X[i + 1] = snake_X[i];
        snake_Y[i + 1] = snake_Y[i];
        i--;
    }
}

void cursor_delete(void) // 커서 지우는 함수
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) // 좌표 함수
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void print_Board(int Board[20][20]) // 게임판 출력
{
    int i, j, k = 0;

    for (i = 0; i < Board_X; i++) // 게임판 상황 출력
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
                printf("▣");
                break;
            case ITEM:
                printf("◆");
                break;
            case WALL:
                printf("□");
                break;
            case BOMB:
                printf("◎");
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
    printf("뱀꼬리잡기 게임");

    gotoxy(46, 6);
    printf("score = %07d", score); // 실시간으로 점수 출력

    gotoxy(46, 12);
    printf("> 조작법 <");

    gotoxy(46, 13);
    printf("방향 조절 : 방향키");

    gotoxy(46, 14);
    printf("방향키를 제외한 모든키 : pause");

    gotoxy(46, 15);
    printf("ESC : 게임 종료");

    gotoxy(46, 17);
    printf("> 설명 <");

    gotoxy(46, 18);
    printf("ITEM : ◆");
    gotoxy(46, 19);
    printf("BOMB : ◎");
    gotoxy(46, 20);
    printf("PLAYER : ▣");
}

void check_key(char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* length) // 키 입력받는 함수 
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
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y - 1; // 이동
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y - 1; // 이동
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y - 1; // 이동
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
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y + 1; // 이동
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y + 1; // 이동
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_Y = *Player_Y + 1; // 이동
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
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X - 1; // 이동
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X - 1; // 이동
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X - 1; // 이동
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
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X + 1; // 이동
            break;
        case ITEM:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X + 1; // 이동
            isEatitem = true;
            break;
        case BOMB:
            push_snake(length, snake_X, snake_Y);
            snake_X[0] = *Player_X;
            snake_Y[0] = *Player_Y;
            Board[*Player_Y][*Player_X] = 0; // 0으로 초기화
            *Player_X = *Player_X + 1; // 이동
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

void title(scoreInfo playerInfo[], int* playerSize, int* menu) // 타이틀
{
    while (1) {
        gotoxy(20, 9);
        printf("비주얼스튜디오에서 실행해주세요");

        gotoxy(30, 10);
        printf("SNAKE GAME");

        gotoxy(28, 12);
        printf("뱀꼬리 잡기 게임");

        gotoxy(26, 16);
        printf("> 1. 게임 시작 <");
        gotoxy(26, 18);
        printf("> 2. 게임 종료 <");

        gotoxy(26, 20);
        printf("▷ 메뉴 입력 : ");
        scanf_s("%d", menu);
        system("cls");
        if (*menu == 2) {
            gotoxy(26, 10);
            printf("> 게임 종료 <\n\n\n");
            return;
        }
        else if (*menu == 1) {
            break;
        }
        else continue;
    }
    gotoxy(30, 10);
    printf("플레이어 이름을 입력해주세요");
    gotoxy(30, 12);
    scanf("%s", playerInfo[*playerSize].name);
    system("cls");
    gotoxy(2, 2);
    printf("아무키나 눌러주세요.");

    gotoxy(2, 3);
    printf("키를 입력하면 시작합니다.");
}

void gameover(scoreInfo playerInfo[], int* playerSize, int score, char* key) // 게임 오버
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
    printf("아무키나 눌러주세요.");
    *key = _getch();
    gotoxy(6, 10);
    printf("3초 뒤 초기 화면으로 이동합니다.");
    Sleep(3000);
    system("cls");
}

void item_spawner(int Board[20][20], int* item_X, int* item_Y, int* score, int* length) // 아이템 스폰
{
    if (isEatitem == false) // 아이템을 안먹었을 경우
    {
        Board[*item_X][*item_Y] = ITEM; // 새로 스폰
        Board[*item_X][*item_Y] = ITEM; // 새로 스폰
    }
    else // 아이템을 먹었을 경우
    {
        *score += 100; // 점수 100점 추가
        (*length)++; // 뱀꼬리 길이 증가

        *item_X = rand() % 18 + 1; // 랜덤
        *item_Y = rand() % 18 + 1; // 랜덤
        if (Board[*item_X][*item_Y] == PLAYER)
        {
            *item_X = rand() % 18 + 1; // 랜덤
            *item_Y = rand() % 18 + 1; // 랜덤
        }
        Board[*item_X][*item_Y] = ITEM; // 새로 스폰

        isEatitem = false; // 아이템 플래그 false로 전환
    }
}
void bomb_spawner(int Board[20][20], int* bomb_X, int* bomb_Y, int snake_Y[], int snake_X[], int* score, int* length) // 아이템 스폰
{
    if (isEatbomb == false) // 아이템을 안먹었을 경우
    {
        Board[*bomb_X][*bomb_Y] = BOMB; // 새로 스폰
        Board[*bomb_X][*bomb_Y] = BOMB; // 새로 스폰
    }
    else // 아이템을 먹었을 경우
    {
        *score -= 100; // 점수 100점 감소
        isLengthMinus = true;
        *bomb_X = rand() % 18 + 1; // 랜덤
        *bomb_Y = rand() % 18 + 1; // 랜덤
        if (Board[*bomb_X][*bomb_Y] == PLAYER)
        {
            *bomb_X = rand() % 18 + 1; // 랜덤
            *bomb_Y = rand() % 18 + 1; // 랜덤
        }
        Board[*bomb_X][*bomb_Y] = BOMB; // 새로 스폰

        isEatbomb = false; // 아이템 플래그 false로 전환
    }
}

void game_check(int Board[20][20], int snake_X[]) // 게임 체크
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

void player(int Board[20][20], int* Player_Y, int* Player_X, int* length, int snake_X[], int snake_Y[]) // 플레이어
{
    int i;

    Board[*Player_Y][*Player_X] = PLAYER; // 플레이어 위치
    if (isLengthMinus == true) {
        if (*length > 0)
            (*length) -= 1;
        for (i = 0; i < *length; i++)
        {
            Board[snake_Y[i]][snake_X[i]] = PLAYER; // 플레이어 위치
            Board[snake_Y[*length]][snake_X[*length]] = EMPTY;
        }
        Board[snake_Y[*length + 1]][snake_X[*length + 1]] = EMPTY;
        isLengthMinus = false;
    }
    if (*length > 0)
    {
        for (i = 0; i < *length; i++)
        {
            Board[snake_Y[i]][snake_X[i]] = PLAYER; // 플레이어 위치
            Board[snake_Y[*length]][snake_X[*length]] = EMPTY;
        }
    }
}

void init(int Board[20][20], int snake_X[], int snake_Y[]) // 초기화
{
    cursor_delete(); // 커서 삭제
    reset_board(Board); // 게임판 초기화

    reset_snake(snake_X, snake_Y); // snake_X, snake_Y 초기화
}

void Update(scoreInfo playerInfo[], int* playerSize, char* key, int Board[20][20], int* Player_Y, int* Player_X, int snake_X[], int snake_Y[], int* item_X, int* item_Y, int* bomb_X, int* bomb_Y, int* score, int* length) // 데이터 갱신
{
    *key = _getch(); // 입력

    do
    {
        check_key(key, Board, Player_Y, Player_X, snake_X, snake_Y, length);
        player(Board, Player_Y, Player_X, length, snake_X, snake_Y); // 플레이어
        item_spawner(Board, item_X, item_Y, score, length); // 아이템 스폰
        bomb_spawner(Board, bomb_X, bomb_Y, snake_X, snake_Y, score, length);
        Render(Board, *score); //출력
        if (isGameover == true) {// 게임오버가 참일경우 게임오버
            gameover(playerInfo, playerSize, *score, key);
            return;
        }
        if (isPause == true) // 퍼즈가 참일경우 
            pause(key, Board, Player_Y, Player_X, snake_X, snake_Y, length);

    } while (!_kbhit());
}

void Render(int Board[20][20], int score) // 화면 출력
{
    print_Board(Board); // 보드 출력
    UI(score); // UI

   //game_check(); // 게임체크
    if (isPause != true)
    {
        gotoxy(46, 9);
        printf("                            ");
    }
}