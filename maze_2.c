#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
#include <windows.h>

void start(void);
void re(char massage[200], int bomb[][3], int obst[][4], int heart[][3], int warp[][4], char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3]);
void init(int bomb[][3], int obst[][4], int heart[][3], int warp[][4], char array[20][20][3]);
void nextyoso(int* choice, int* now_y, int* now_x, int* next_y, int* next_x, char(**next_pointer)[3], char array[20][20][3]);
void change_place(int* choice, int* now_y, int* now_x, char(**now_pointer)[3], char array[20][20][3]);
void gotoxy(int y, int x);
void newp(int* now_y, int* now_x, char array[20][20][3]);
void break_obstacle(int y, int x, char array[20][20][3]);
void new_hp(int* hp);
void new_massage(char massage[200]);

int main(void)
{
    srand(time(NULL));
    start();
}

void start() {
    int t = 0;
    int y = 0;
    int x = 0;

    int bomb[20][3]; // 폭탄 위치와 답
    int obst[6][4]; // 장애물 위치와 인수
    int heart[8][3]; // 체력 아이템
    int warp[4][4];
    char array[20][20][3] = { "" }; // 공백 미로판 선언
    char text[801] = "■■■■■■■■■■■■■■■■■■■■■☆　　　　　　　　　　　■　　　　　■■　■■■■■■■■■■　■■■　■　■■　■　　　■　　　■■　■　　　　■■■　■　■　■　■　■■　■■　■　　■■　　　■　　　■■■■　　　　■■　■■■■■■■■　■　　　■■■■■■　■■■■Ｆ　　■　■　■　　■　　■■　■■■■■■　■　■■■■　　　　　■　■■　　　　　■　■　　　　■■■　　　■■■■■■　■　■　■　■■　■■　■■■　　　■　■　■　■　　　　■　　　■■　■　■　■■■　■　■■　■　■■■■　■　　　■　　　■　■　　■　　　■■　■■■■■■■■■■■■■■■■　■■　　　　　　　　　　　　　■　　　　■■　■■■　■■■■■■■　■　■■■■■　■　■　■■　　■　　　■　　　■■■　　　■　　　■　　　■　　　■　　■■■■■■■■■■■■■■■■■■■■■";

    char massage[200] = "미로 게임을 시작합니다!!"; // 안내 메세지
    int hp = 100; // 생명 포인트
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

    init(bomb, obst, heart, warp, array); //장애물과 폭탄 위치 랜덤으로 초기화하기

    /// ///////////////////////////////////////////////////////////////////////////////////////////////

    system("cls"); // 화면 말끔히 지우기

    printf("[%s]\n", massage);
    printf("                                                              생명 포인트 : %d\n", hp); // 안내 메세지와 생명 포인트 출력

    for (y = 0; y < 20; y++) // 미로판 출력 반복문
    {
        for (x = 0; x < 20; x++)
        {
            printf("%s", array[y][x]); // 미로판의 구석구석을 다 출력
        }
        printf("\n"); // 가로줄 한줄 출력이 끝날 때마다 한줄 띄워쓰기
    }

    printf("\n");
    printf("방향키 또는 폭탄 터트리기 = 엔터 를 누르세요. : "); // 사용자에게 키 입력 요구메세지 출력

    re(massage, bomb, obst, heart, warp, array, &hp, &now_y, &now_x, now_pointer, &next_y, &next_x, next_pointer);
}

void init(int bomb[][3], int obst[][4], int heart[][3], int warp[][4], char array[20][20][3])
{
    int y, x;

    do {
        y = 1;
        x = rand() % 7 + 3;
    } while (strcmp(array[y][x], "　"));
    obst[0][0] = y;
    obst[0][1] = x;
    strcpy(array[y][x], "□");

    obst[0][2] = rand() % 99 + 1;
    obst[0][3] = rand() % 99 + 1;

    do {
        y = rand() % 3 + 7;
        x = 18;
    } while (strcmp(array[y][x], "　"));
    obst[1][0] = y;
    obst[1][1] = x;
    strcpy(array[y][x], "□");

    obst[1][2] = rand() % 99 + 1;
    obst[1][3] = rand() % 99 + 1;

    do {
        y = rand() % 4 + 6;
        x = rand() % 4 + 9;
    } while (strcmp(array[y][x], "　"));
    obst[2][0] = y;
    obst[2][1] = x;
    strcpy(array[y][x], "□");

    obst[2][2] = rand() % 99 + 1;
    obst[2][3] = rand() % 99 + 1;

    do {
        y = 15;
        x = rand() % 4 + 14;
    } while (strcmp(array[y][x], "　"));
    obst[3][0] = y;
    obst[3][1] = x;
    strcpy(array[y][x], "□");

    obst[3][2] = rand() % 99 + 1;
    obst[3][3] = rand() % 99 + 1;


    do {
        y = rand() % 5 + 10;
        x = rand() % 6;
    } while (strcmp(array[y][x], "　"));
    obst[4][0] = y;
    obst[4][1] = x;
    strcpy(array[y][x], "□");

    obst[4][2] = rand() % 99 + 1;
    obst[4][3] = rand() % 99 + 1;

    for (int i = 0; i < 5; i++)
    {
        do {
            y = rand() % 3 + 2;
            x = rand() % 10;
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
    for (int i = 5; i < 10; i++)
    {
        do {
            y = rand() % 6;
            x = rand() % 9 + 11;
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
    for (int i = 10; i < 15; i++)
    {
        do {
            y = rand() % 8 + 6;
            x = rand() % 10 + 7;
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
    for (int i = 15; i < 20; i++)
    {
        do {
            y = rand() % 5 + 15;
            x = rand() % 12 + 5;
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
    ///////////////////////////////////////////////////////////////
    do {
        y = rand() % 6 + 6;
        x = 7;
    } while (strcmp(array[y][x], "　"));
    warp[0][0] = y;
    warp[0][1] = x;
    strcpy(array[y][x], "◎");
    do {
        y = rand() % 4;
        x = rand() % 5 + 15;
    } while (strcmp(array[y][x], "　"));
    warp[1][0] = y;
    warp[1][1] = x;
    strcpy(array[y][x], "◎");
    warp[0][2] = warp[1][0];
    warp[0][3] = warp[1][1];
    warp[1][2] = warp[0][0];
    warp[1][3] = warp[0][1];

    do {
        y = 13;
        x = rand() % 8 + 7;
    } while (strcmp(array[y][x], "　"));
    warp[2][0] = y;
    warp[2][1] = x;
    strcpy(array[y][x], "◎");
    do {
        y = rand() % 4 + 16;
        x = rand() % 8;
    } while (strcmp(array[y][x], "　"));
    warp[3][0] = y;
    warp[3][1] = x;
    strcpy(array[y][x], "◎");
    warp[2][2] = warp[3][0];
    warp[2][3] = warp[3][1];
    warp[3][2] = warp[2][0];
    warp[3][3] = warp[2][1];

    ///////////////////////////////////////////////////////////////
    for (int i = 0; i < 2; i++)
    {
        do {
            y = rand() % 10;
            x = rand() % 10;
        } while (strcmp(array[y][x], "　"));
        heart[i][0] = y;
        heart[i][1] = x;
        strcpy(array[y][x], "♡");
        if (i % 4 == 0)
        {
            heart[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;
            if (i % 2 == 0)
            {
                heart[i][2] = heart[i / 4 * 4][2] + diff;
            }
            else
            {
                heart[i][2] = heart[i / 4 * 4][2] - diff;
            }
        }
    }
    for (int i = 2; i < 4; i++)
    {
        do {
            y = rand() % 10;
            x = rand() % 10 + 10;
        } while (strcmp(array[y][x], "　"));
        heart[i][0] = y;
        heart[i][1] = x;
        strcpy(array[y][x], "♡");
        if (i % 4 == 0)
        {
            heart[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;
            if (i % 2 == 0)
            {
                heart[i][2] = heart[i / 4 * 4][2] + diff;
            }
            else
            {
                heart[i][2] = heart[i / 4 * 4][2] - diff;
            }
        }
    }
    for (int i = 4; i < 6; i++)
    {
        do {
            y = rand() % 10 + 10;
            x = rand() % 10;
        } while (strcmp(array[y][x], "　"));
        heart[i][0] = y;
        heart[i][1] = x;
        strcpy(array[y][x], "♡");
        if (i % 4 == 0)
        {
            heart[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;
            if (i % 2 == 0)
            {
                heart[i][2] = heart[i / 4 * 4][2] + diff;
            }
            else
            {
                heart[i][2] = heart[i / 4 * 4][2] - diff;
            }
        }
    }
    for (int i = 6; i < 8; i++)
    {
        do {
            y = rand() % 10 + 10;
            x = rand() % 10 + 10;
        } while (strcmp(array[y][x], "　"));
        heart[i][0] = y;
        heart[i][1] = x;
        strcpy(array[y][x], "♡");
        if (i % 4 == 0)
        {
            heart[i][2] = obst[i / 4][2] * obst[i / 4][3];
        }
        else
        {
            int diff = rand() % 100 + 1;
            if (i % 2 == 0)
            {
                heart[i][2] = heart[i / 4 * 4][2] + diff;
            }
            else
            {
                heart[i][2] = heart[i / 4 * 4][2] - diff;
            }
        }
    }

}

void re(char massage[200], int bomb[][3], int obst[][4], int heart[][3], int  warp[][4], char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3]) {
    int t = 0; // 반복문 노예변수
    int choice = 0;
    int i;     // 반복문 노예변수

    if (*hp <= 0) // 체력이 0이 되면
    {
        system("cls"); // 화면 말끔히 지우기
        printf("[%s]\n\n", massage); // 메세지 출력
        printf("게임 오버. Game Over. \n재도전 하시겠습니까? 재도전 하려면 9를 눌러주세요 : "); // 게임오버
        choice = _getch(); // 사용자의 입력 대기

        while (1) // 사용자가 9를 누를 때까지 반복
        {
            if (choice == '9') //사용자가 9를 누르면
            {
                *now_y = 1;
                *now_x = 1;
                t = 0;
                *hp = 100;
                strcpy(massage, "미로 게임을 시작합니다!!"); // 등등 모든거 초기화
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
            strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
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
                    sprintf(massage, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "♡") == 0 && strcmp(*now_pointer, "☆") == 0)
        {
            strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(massage, "체력을 회복시켜주는 물약입니다! 먹으면 10을 회복합니다!!");
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "◎") == 0 && strcmp(*now_pointer, "☆") == 0)
        {
            strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == warp[i][0] && *next_x == warp[i][1])
                {
                    sprintf(massage, "순간이동기입니다!! 좌표 %d, %d으로 이동합니다!!", warp[i][2], warp[i][3]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "？") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
        {
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "？") == 0 && strcmp(*now_pointer, "？") == 0)
        {
            strcpy(*now_pointer, "？"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(massage, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "♡") == 0 && strcmp(*now_pointer, "？") == 0)
        {
            strcpy(*now_pointer, "？"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(massage, "체력을 회복시켜주는 물약입니다! 먹으면 10을 회복합니다!!");
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "◎") == 0 && strcmp(*now_pointer, "？") == 0)
        {
            strcpy(*now_pointer, "？"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(massage, "순간이동기입니다!! 좌표 %d, %d으로 이동합니다!!", warp[i][2], warp[i][3]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }


        else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "♡") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
        {
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "？") == 0 && strcmp(*now_pointer, "♡") == 0)
        {
            strcpy(*now_pointer, "♡"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(massage, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "♡") == 0 && strcmp(*now_pointer, "♡") == 0)
        {
            strcpy(*now_pointer, "♡"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(massage, "체력을 회복시켜주는 물약입니다! 먹으면 10을 회복합니다!!");
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "◎") == 0 && strcmp(*now_pointer, "♡") == 0)
        {
            strcpy(*now_pointer, "♡"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(massage, "순간이동기입니다!! 좌표 %d, %d으로 이동합니다!!", warp[i][2], warp[i][3]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "◎") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
        {
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
            newp(now_y, now_x, array);
            strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "？") == 0 && strcmp(*now_pointer, "◎") == 0)
        {
            strcpy(*now_pointer, "◎"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
                {
                    sprintf(massage, "장애물 %c를 터뜨리기 위한 폭탄입니다. %d 이라고 쓰여 있습니다.", 'A' + i / 4, bomb[i][2]);
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "♡") == 0 && strcmp(*now_pointer, "◎") == 0)
        {
            strcpy(*now_pointer, "◎"); // 이전 장소의 별은 지우고
            newp(now_y, now_x, array);
            change_place(&choice, now_y, now_x, &now_pointer, array); // 캐릭터의 좌표를 옮기자
            for (int i = 0; i < 20; i++)
            {
                if (*next_y == heart[i][0] && *next_x == heart[i][1])
                {
                    sprintf(massage, "체력을 회복시켜주는 물약입니다! 먹으면 10을 회복합니다!!");
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "■") == 0) // 만약에 탐색했던 칸이 벽이라면
        {
            strcpy(massage, "벽에 부딫쳤어요 ㅜㅜ"); // 벽에 부딫쳤다는 문구를 메세지로 지정
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }

        else if (strcmp(*next_pointer, "□") == 0) // 만약에 탐색했던 칸이 장애물이라면
        {
            for (int i = 0; i < 5; i++)
            {
                if (*next_y == obst[i][0] && *next_x == obst[i][1])
                {
                    sprintf(massage, "장애물 %c를 만났군요. 이걸 부수기 위해 폭탄 %d*%d 을 찾아야 합니다.", 'A' + i, obst[i][2], obst[i][3]); // 장애물에 부딫쳤다는 안내 메세지
                    break;
                }
            }
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
        }

        else if (strcmp(*next_pointer, "Ｆ") == 0) // 피니쉬를 밟으면
        {
            for (;;)
            {
                system("cls"); // 화면 말끔히 지우기
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
                strcpy(massage, "장애물 하나를 무너뜨렸습니다."); // 메세지 출력
                new_massage(massage);
                re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위해 돌아가자
            }
            else
            {
                strcpy(massage, "펑!!! 폭탄에 의해 데미지 25를 입습니다."); // 무서운 메세지 출력
                new_massage(massage);
                *hp -= 25; // 체력 25 감소
                new_hp(hp);
                re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
            }
        }
        else if (strcmp(*now_pointer, "♡") == 0) {
            strcpy(*now_pointer, "☆");
            newp(now_y, now_x, array);
            strcpy(massage, "체력을 10회복했습니다!!"); // 메세지 출력
            new_massage(massage);
            *hp += 10;
            new_hp(hp);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }
        else if (strcmp(*now_pointer, "◎") == 0) {
            for (i = 0; i < 20; i++)
            {
                if (*now_y == warp[i][0] && *now_x == warp[i][1])
                {
                    *now_y = warp[i][2];
                    *now_x = warp[i][3];
                    break;
                }
            }
            strcpy(*now_pointer, "◎");
            newp(now_y, now_x, array);
            sprintf(massage, "순간이동했습니다!! 좌표 %d, %d으로 이동했습니다!!", warp[i][2], warp[i][3]);
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
        }
        else // 폭탄 터트리기 키는 눌렀지만 이 위치에 폭탄이 없을 때
        {
            strcpy(massage, "이 위치엔 터트릴 수 있는 폭탄이 없습니다."); // 
            new_massage(massage);
            re(massage, bomb, obst, heart, warp, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // 다시 반복하기 위헤 돌아가자
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

void new_massage(char massage[200])
{
    gotoxy(0, 0);
    printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
    gotoxy(0, 0);
    printf("[%s]", massage);
}