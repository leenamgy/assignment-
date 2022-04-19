#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include <time.h>

void start(void);
void re(char message[200], int bomb[][3], int obst[][4], int heart[][3],/*체력아이템*/ char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3]);
void init(int bomb[][3], int obst[][4], int heart[][3], char array[20][20][3]);
void nextyoso(int* choice, int* now_y, int* now_x, int* next_y, int* next_x, char(**next_pointer)[3], char array[20][20][3]);
void change_place(int* choice, int* now_y, int* now_x, char(**now_pointer)[3], char array[20][20][3]);
void gotoxy(int y, int x);
void newp(int* now_y, int* now_x, char array[20][20][3]);
void break_obstacle(int y, int x, char array[20][20][3]);
void new_hp(int* hp);
void new_message(char message[200]);

int main(void)
{
    srand(time(NULL));
    start();
}

void start(void)
{
    int t = 0;
    int y = 0;
    int x = 0;

    int bomb[20][3]; // 폭탄 위치와 답
    int obst[20][4]; // 장애물 위치와 인수
    int heart[20][3]; ///*체력아이템*/

    char array[20][20][3] = { "" }; // 공백 미로판 선언
    char text[801] = "■■■■■■■■■■■■■■■■■■■■■☆　　　　　　　　　　　■■■　　　■■　■■■■■■■■■■　　■　　■　■■　■　　　■　　　■　■　　■　　■■■　■　■　■　■　■　　■　　■　　■■　　　■　　　■■■■　　■　　■　■■■■■■■■　■　　　■　　■　　　■■　　Ｆ　　■　■　■　　■　　■■　■■　■■■　■　■■■■　　　　　■　■■　　　　　■　■　　　　■■■　　　■■■■■■　■　■　■　■■　■■　■■■　　　　　■　■　■　　　　■　　　■■　■■■　■■■　■　■■　■　■■■■　　　　　■　　　■　■　　■　　　■■　■■■■■■■■■■■■■■■■　■■　　　　　　　　　　　　　■　　　　■■　■■■　■　■■■■■　■　■■■■■　■　■　■■■　■　　　■　　　■■■　　　■　　　■　　　■　　　■　　■■■■■■■■■■■■■■■■■■■■■";

    char message[200] = "미로 게임을 시작합니다!!";
    int hp = 100;
    int now_y = 1; // 캐릭터의 y축 위치
    int now_x = 1; // 캐릭터의 x축 위치
    char(*now_pointer)[3] = &array[now_y][now_x]; // 캐릭터의 현재 좌표를 가리키는 배열 포인터
    int next_y = 1; // 탐색 y축 위치
    int next_x = 1; // 탐색 x축 위치
    char(*next_pointer)[3] = &array[next_y][next_x]; // 캐릭터가 이동할 위치를 탐색해 보는 배열 포인터


    for (y = 0; y < 20; y++) // 텍스트에 있는 미로판 그림을 공백 미로판에 붙여넣기 하는 반복문
    {
        for (x = 0; x < 20; x++)
        {
            array[y][x][0] = text[t]; // 미로판 요소의 왼쪽 반쪽을 미로판에 대입
            t += 1;
            array[y][x][1] = text[t]; // 미로판 요소의 오른쪽 반쪽을 미로판에 대입
            t += 1;
            array[y][x][2] = 0; // 널 문자 삽입
        }
    }

    init(bomb, obst, heart, array); //장애물과 폭탄 위치 랜덤으로 초기화


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////


    system("cls"); // 화면 말끔히 지우기

    printf("[%s]\n", message);
    printf("                                                              생명 포인트 : %d\n", hp);

    for (y = 0; y < 20; y++) // 미로판 출력 반복문
    {
        for (x = 0; x < 20; x++)
        {
            printf("%s", array[y][x]); // 미로판의 구석구석을 다 출력
        }
        printf("\n"); // 가로줄 한줄 출력이 끝날 때마다 한줄 띄워쓰기
    }

    printf("\n");

    printf("방향키 또는 폭탄 터트리기 = 엔터 를 누르세요. : ");

    re(message, bomb, obst, heart, array, &hp, &now_y, &now_x, now_pointer, &next_y, &next_x, next_pointer);
}

void init(int bomb[][3], int obst[][4], int heart[][3], char array[20][20][3])
{
    int y, x;

    for (int i = 0; i < 5; i++)
    {
        do
        {
            y = rand() % 30;
            x = rand() % 20; // 장애물 위치 랜덤
        } while (strcmp(array[y][x], "　"));

        obst[i][0] = y;
        obst[i][1] = x;

        strcpy(array[y][x], "□");

        obst[i][2] = rand() % 99;
        obst[i][3] = rand() % 99;
    }
    for (int i = 0; i < 20; i++)
    {
        do
        {
            y = rand() % 20;
            x = rand() % 20;
        } while (strcmp(array[y][x], "　"));

        bomb[i][0] = y;
        bomb[i][1] = x;

        strcpy(array[y][x], "？");

        if (i % 4 == 0)
        {
            bomb[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;

            if (i % 2 == 0)
            {
                bomb[i][2] = bomb[i / 4 * 4][2] + diff;
            }
            else
            {
                bomb[i][2] = bomb[i / 4 * 4][2] - diff;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        do
        {
            y = rand() % 20;
            x = rand() % 20;
        } while (strcmp(array[y][x], "　"));

        heart[i][0] = y;
        heart[i][1] = x;

        strcpy(array[y][x], "♥");

        if (i % 4 == 0)
        {
            heart[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;

            if (i % 2 == 0)
            {
                heart[i][2] = obst[i / 4 * 4][2] + diff;
            }
            else
            {
                heart[i][2] = obst[i / 4 * 4][2] - diff;
            }
        }
    }
}

void re(char message[200], int bomb[][3], int obst[][4], int heart[][3], char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3])
{
    int t = 0;
    int choice = 0;
    int i;

    if (*hp <= 0)
    {
        system("cls");
        printf("[%s]\n\n", message);
        printf("게임 오버. Game Over.\n 재도전 하시겠습니까? 재도전 하려면 9를 눌러주세요 : ");
        choice = _getch(); // 사용자의 입력 대기

        while (1) // 사용자가 9를 누를 때까지 반복
        {
            if (choice == '9') //사용자가 9를 누르면
            {
                *now_y = 1;
                *now_x = 1;
                t = 0;
                *hp = 100;
                strcpy(message, "미로 게임을 시작합니다!!"); // 등등 모든거 초기화
                start();
                break;
            }
            else {
                choice = _getch();
            }
        }
    }

    now_pointer = &array[*now_y][*now_x]; // now_pointer는 캐릭터의 현재 위치를 가리켜라.
    *next_y = *now_y; //
    *next_x = *now_x; // next 좌표와 now 좌표 일치시키기


    gotoxy(23, 48);
    choice = _getch(); // 사용자 입력 대기

    while (1)
    {
        if (choice == 75 || choice == 77 || choice == 72 || choice == 80 || choice == 13)
            break;
        else
            choice = _getch();
    }

    nextyoso(&choice, now_y, now_x, next_y, next_x, &next_pointer, array); // 캐릭터가 이동하려고 시도하는 칸을 탐색하는 함수 호출

    if (choice != 13) // 사용자의 선택이 방향 조절이였다면 다음과 같은 행동을 해라
    {
        if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "☆") == 0) // 만약에 현재 위치도 공백이고 탐색했던 칸도 공백이라면
        {
            strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(message, "달려라 달려~");
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위해 돌아가자
        }

        else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "？") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
        {
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(message, "달려라 달려~");
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }
        else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "♥") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
        {
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(message, "달려라 달려~");
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "■") == 0)
        {
            strcpy(message, "벽에 부딪혔어요! ");
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "□") == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                if (*next_y == obst[i][0] && *next_x == obst[i][1])
                {
                    sprintf(message, "장애물 %c를 만났군요. 이걸 부수기 위해 폭탄 %dx%d 을 찾아야 합니다.", 'A' + i, obst[i][2], obst[i][3]); // 장애물에 부딪혔다는 안내 메세지
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "？") == 0 && strcmp(*now_pointer, "☆") == 0)
        {
            strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(message, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "？") == 0 && strcmp(*now_pointer, "？") == 0)
        {
            strcpy(*now_pointer, "？");
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array);
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(message, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }
        else if (strcmp(*next_pointer, "?") == 0 && strcmp(*now_pointer, "♥") == 0)
        {
            strcpy(*now_pointer, "♥");
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(message, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }
        else if (strcmp(*next_pointer, "♥") == 0 && strcmp(*now_pointer, "?") == 0)
        {
            strcpy(*now_pointer, "?");
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array);
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(message, "생명력을 회복시켜 줍니다.");
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }
        else if (strcmp(*next_pointer, "♥") == 0 && strcmp(*now_pointer, "☆") == 0)
        {
            strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(message, "생명력을 회복시켜 줍니다.");
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "♥") == 0 && strcmp(*now_pointer, "♥") == 0)
        {
            strcpy(*now_pointer, "♥");
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array);
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(message, "생명력을 회복시켜 줍니다.");
                    break;
                }
            }
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "Ｆ") == 0)
        {
            for (;;)
            {
                system("cls");
                printf("클리어를 축하드립니다!!!");
                scanf("%d", &choice); // 키를 입력해도 프로그램을 종료할 때까지 같은 화면 유지
            }
        }
    }

    if (choice == 13) // 사용자가 폭탄 터트리기 명령을 내렸을 경우에
    {
        if (strcmp(*now_pointer, "？") == 0) // 폭탄이 자리에 있을 경우엔
        {
            for (i = 0; i < 20; i++)
            {
                if (*now_y == bomb[i][0] && *now_x == bomb[i][1])
                {
                    break;
                }
            }
            strcpy(*now_pointer, "☆"); // 폭탄 그림대신 가려져있던 캐릭터의 모습을 출력
            newp(now_y, now_x, array);

            if (i % 4 == 0)
            {
                break_obstacle(obst[i / 4][0], obst[i / 4][1], array);
                strcpy(message, "장애물 하나를 무너뜨렸습니다."); // 메세지 출력
                new_message(message);
                re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
            }
            else
            {
                strcpy(message, "펑!!! 폭탄에 의해 데미지 25를 입습니다.");
                new_message(message);
                *hp -= 25; // 체력 25 감소
                new_hp(hp);
                re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
            }
        }
        else if (strcmp(*now_pointer, "♥") == 0) {
            strcpy(*now_pointer, "☆");
            newp(now_y, now_x, array);
            strcpy(message, "회복 아이템을 사용했습니다.");
            new_message(message);
            *hp += 10; // 체력 10 증가
            new_hp(hp);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else // 엔터를 눌렀지만 이 위치에 폭탄이 없을 때
        {
            strcpy(message, "이 위치엔 터트릴 수 있는 폭탄이 없습니다."); // 
            new_message(message);
            re(message, bomb, obst, heart, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }
    }
}

void nextyoso(int* choice, int* now_y, int* now_x, int* next_y, int* next_x, char(**next_pointer)[3], char array[20][20][3]) // 캐릭터가 이동하려고 시도하는 칸을 탐색하는 함수
{
    if (*choice == 13) // 폭탄 터트리는 키를 눌렀다면
    {
        *next_pointer = &array[*now_y][*now_x]; // 이동을 시도하는것은 아니므로 현재 위치와 동일.
    }
    else if (*choice == 75) // 왼쪽을 택했다면
    {
        *next_x -= 1; // 탐색 x축 좌표를 왼쪽으로 옮기고
        *next_pointer = &array[*now_y][*now_x - 1]; // 캐릭터의 현재 위치보다 한칸 왼쪽에 있는 칸을 참조
    }
    else if (*choice == 77) // 오른쪽을 택했다면
    {
        *next_x += 1; // 탐색 x축 좌표를 오른쪽으로 옮기고
        *next_pointer = &array[*now_y][*now_x + 1]; // 캐릭터의 현재 위치보다 한칸 오른쪽에 있는 칸을 참조
    }
    else if (*choice == 72) // 위를 택했다면
    {
        *next_y -= 1; // 탐색 y축 좌표를 위쪽으로 옮기고
        *next_pointer = &array[*now_y - 1][*now_x]; // 캐릭터의 현재 위치보다 한칸 위쪽에 있는 칸을 참조
    }
    else if (*choice == 80)// 아래를 택했다면
    {
        *next_y += 1; // 탐색 y축 좌표를 아래쪽으로 옮기고
        *next_pointer = &array[*now_y + 1][*now_x]; // 캐릭터의 현재 위치보다 한칸 아랫쪽에 있는 칸을 참조
    }
}

void change_place(int* choice, int* now_y, int* now_x, char(**now_pointer)[3], char array[20][20][3]) // 캐릭터의 좌표를 옮겨주는 함수
{
    if (*choice == 75) // 왼쪽을 택했다면
    {
        *now_x -= 1; // 캐릭터의 x축 좌표를 왼쪽으로 옮기고
        *now_pointer = &array[*now_y][*now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자      
    }
    else if (*choice == 77) // 오른쪽을 택했다면
    {
        *now_x += 1; // 캐릭터의 x축 좌표를 오른쪽으로 옮기고
        *now_pointer = &array[*now_y][*now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자   
    }
    else if (*choice == 72) // 위를 택했다면
    {
        *now_y -= 1; // 캐릭터의 y축 좌표를 위쪽으로 옮기고
        *now_pointer = &array[*now_y][*now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자
    }
    else if (*choice == 80)// 아래를 택했다면
    {
        *now_y += 1; // 캐릭터의 y축 좌표를 아래쪽으로 옮기고
        *now_pointer = &array[*now_y][*now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자
    }
}

void gotoxy(int y, int x)
{
    COORD Cur;
    Cur.Y = y;
    Cur.X = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void newp(int* now_y, int* now_x, char array[20][20][3])
{
    gotoxy(*now_y + 2, *now_x * 2);
    printf("%s", array[*now_y][*now_x]);
}

void break_obstacle(int y, int x, char array[20][20][3])
{
    strcpy(array[y][x], "　");
    gotoxy(y + 2, x * 2);
    printf("%s", array[y][x]);
}

void new_hp(int* hp)
{
    gotoxy(1, 76);
    printf("%d ", *hp);
}

void new_message(char message[200])
{
    gotoxy(0, 0);
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
    gotoxy(0, 0);
    printf("[%s]", message);
}