#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>

char array[20][20][3] = { "" }; // 공백 미로판 선언
char text[801] = "■■■■■■■■■■■■■■■■■■■■■☆　　　　　　　　　　□■■■　　　■■　■■■■■■■■■■　？■？　■？■■　■　　？■　　　■？■　　■　　■■■　■　■　■　■？■　　■　　■？　■■　　　■　　　■■■■　　■　　■　■■■■■■■■　■　　　■　　■　　　■■　　Ｆ　　■　■？■　　■　　■■　■■　■■■　■　■■■■　　　　　■　■■　　　　　■？■　　　　■■■　□　■■■■■■　■　■　■　■■？■■　■■■　　　　　■？■　■　　　　■　　　■■　■■■　■■■　■　■■　■　■■■■　　　　　■？　　■？■？　■　　　■■□■■■■■■■■■■■■■■■■　■■　　　　　　　　　　　　　■　　　　■■　■■■　■？■■■■■　■　■■■■■　■？■　■■■？■　　　■　　　■■■　　　■　　？■　　　■　　　■　？■■■■■■■■■■■■■■■■■■■■■";
int now_y = 1; // 캐릭터의 y축 위치
int now_x = 1; // 캐릭터의 x축 위치
int hp = 100; // 생명 포인트
char(*now_pointer)[3]; // 캐릭터의 현재 좌표를 가리키는 배열 포인터
int next_y = 1; // 탐색 y축 위치
int next_x = 1; // 탐색 x축 위치
char(*next_pointer)[3]; // 캐릭터가 이동할 위치를 탐색해 보는 배열 포인터

char massage[200] = "미로 게임을 시작합니다!!"; // 안내 메세지

void nextyoso(int* choice); // 함수의 원형 선언
void change_place(int* choice); // 함수의 원형 선언
void gotoxy(int y, int x); // 함수의 원형 선언
void newp(void); //함수의 원형 선언
void delete_trash(int y, int x); // 함수의 원형 선언
void new_hp(void); // 함수의 원형 선언
void new_massage(void); // 함수의 원형 선언

int main(void)
{
	int t = 0; // 반복문 노예변수
	int y = 0; // 반복문 노예변수
	int x = 0; // 반복문 노예변수
	int choice = 0; // 유저의 선택을 받아주는 변수

start:


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


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

re:

	if (hp <= 0) // 체력이 0이 되면
	{
	k:
		system("cls"); // 화면 말끔히 지우기
		printf("[%s]\n\n", massage); // 메세지 출력
		printf("게임 오버. Game Over. \n재도전 하시겠습니까? 재도전 하려면 9를 눌러주세요 : "); // 게임오버
		choice = _getch(); // 사용자의 입력 대기
		if (choice == '9') //사용자가 9를 누르면
		{
			now_y = 1;
			now_x = 1;
			t = 0;
			hp = 100;
			strcpy(massage, "미로 게임을 시작합니다!!"); // 등등 모든거 초기화
			goto start; // 게임의 처음으로 복귀
		}
		if (choice != '9')  // 9가 아닌수를 입력하면
		{
			goto k; // 9가 입력될때까지 9 입력 강요ㅎ
		}
	}

	now_pointer = &array[now_y][now_x]; // now_pointer는 캐릭터의 현재 위치를 가리켜라.
	next_y = now_y; //
	next_x = now_x; // next 좌표와 now 좌표 일치시키기


	gotoxy(23, 48);
	choice = _getch(); // 사용자 입력 대기
	if (!(choice == 75 || choice == 77 || choice == 72 || choice == 80 || choice == 13)) // 이상한 키를 눌렀다면
		goto re; // 처음으로 되돌아가라

	nextyoso(&choice); // 캐릭터가 이동하려고 시도하는 칸을 탐색하는 함수 호출

	if (choice != 13) // 사용자의 선택이 방향 조절이였다면 다음과 같은 행동을 해라
	{
		if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "☆") == 0) // 만약에 현재 위치도 공백이고 탐색했던 칸도 공백이라면
		{
			strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
			newp();
			change_place(&choice); // 캐릭터의 좌표를 옮기자
			strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
			newp();
			strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
			new_massage();
			goto re; // 다시 반복하기 위헤 돌아가자
		}

		else if (strcmp(*next_pointer, "■") == 0) // 만약에 탐색했던 칸이 벽이라면
		{
			strcpy(massage, "벽에 부딫쳤어요 ㅜㅜ"); // 벽에 부딫쳤다는 문구를 메세지로 지정
			new_massage();
			goto re; // 다시 반복하기 위헤 돌아가자
		}

		else if (strcmp(*next_pointer, "□") == 0) // 만약에 탐색했던 칸이 장애물이라면
		{
			if (next_y == 1 && next_x == 12) // (1,12) 좌표에 있는 장애물이라면
				strcpy(massage, "장애물 A를 만났군요. 이걸 부수기 위해 폭탄 19+51 을 찾아야 합니다."); // 장애물에 부딫쳤다는 안내 메세지
			if (next_y == 9 && next_x == 17) // (9,17) 좌표에 있는 장애물이라면
				strcpy(massage, "장애물 B를 만났군요. 이걸 부수기 위해 폭탄 168+275를 찾아야 합니다."); // 장애물에 부딫쳤다는 안내 메세지
			if (next_y == 14 && next_x == 1) // (14,1) 좌표에 있는 장애물이라면
				strcpy(massage, "장애물 C를 만났군요. 부수기 위해 폭탄 1+2+3+4+5+6+7+8+10×0 을 찾아야 합니다."); // 장애물에 부딫쳤다는 안내 메세지
			new_massage();
			goto re;
		}

		else if (strcmp(*next_pointer, "？") == 0) // 만약에 탐색하고 있던 칸에 ? 가 있으면
		{
			strcpy(*now_pointer, "　"); // 이전 장소의 별은 지우고
			newp();
			change_place(&choice); // 캐릭터의 좌표를 옮기자
			if (next_y == 11 && next_x == 7) // 폭탄마다 서로 다른 숫자가 적혀 있으므로....
				strcpy(massage, "장애물 A를 터뜨리기 위한 폭탄입니다. 70 이라고 쓰여 있습니다."); // 
			if (next_y == 3 && next_x == 5)
				strcpy(massage, "장애물 A를 터뜨리기 위한 폭탄입니다. 60 이라고 쓰여 있습니다."); // 
			if (next_y == 4 && next_x == 9)
				strcpy(massage, "장애물 A를 터뜨리기 위한 폭탄입니다. 71 이라고 쓰여 있습니다."); // 
			if (next_y == 2 && next_x == 13)
				strcpy(massage, "장애물 B를 터뜨리기 위한 폭탄입니다. 443 이라고 쓰여 있습니다."); //
			if (next_y == 2 && next_x == 15)
				strcpy(massage, "장애물 B를 터뜨리기 위한 폭탄입니다. 343 이라고 쓰여 있습니다."); //
			if (next_y == 2 && next_x == 18)
				strcpy(massage, "장애물 B를 터뜨리기 위한 폭탄입니다. 333 이라고 쓰여 있습니다."); //
			if (next_y == 9 && next_x == 7)
				strcpy(massage, "장애물 B를 터뜨리기 위한 폭탄입니다. 353 이라고 쓰여 있습니다."); //
			if (next_y == 4 && next_x == 17)
				strcpy(massage, "장애물 B를 터뜨리기 위한 폭탄입니다. 344 이라고 쓰여 있습니다."); //
			if (next_y == 3 && next_x == 11)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 36 이라고 쓰여 있습니다."); // 
			if (next_y == 7 && next_x == 9)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 0 이라고 쓰여 있습니다."); // 
			if (next_y == 13 && next_x == 7)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 55 이라고 쓰여 있습니다."); // 
			if (next_y == 13 && next_x == 11)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 45 이라고 쓰여 있습니다."); // 
			if (next_y == 13 && next_x == 13)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 46 이라고 쓰여 있습니다."); // 
			if (next_y == 10 && next_x == 14)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 66 이라고 쓰여 있습니다."); // 
			if (next_y == 16 && next_x == 7)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 37 이라고 쓰여 있습니다."); // 
			if (next_y == 18 && next_x == 7)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 54 이라고 쓰여 있습니다."); // 
			if (next_y == 17 && next_x == 3)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 56 이라고 쓰여 있습니다."); // 
			if (next_y == 17 && next_x == 9)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 32 이라고 쓰여 있습니다."); // 
			if (next_y == 18 && next_x == 18)
				strcpy(massage, "장애물 C를 터뜨리기 위한 폭탄입니다. 10 이라고 쓰여 있습니다."); // 

			new_massage();
			goto re; // 다시 반복하기 위헤 돌아가자
		}

		else if (strcmp(*next_pointer, "　") == 0 && strcmp(*now_pointer, "？") == 0) // 만약에 탐색 위치가 공백이고 현재 위치에 ? 가 있다면 
		{
			change_place(&choice); // 캐릭터의 좌표를 옮기자
			strcpy(*now_pointer, "☆"); // 옮겨진 새로운 위치에 별 그리기
			newp();
			strcpy(massage, "달려라 달려~"); // 달려라 달려 문구를 메세지로 지정
			new_massage();
			goto re; // 다시 반복하기 위헤 돌아가자
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

	if (choice == 13); // 사용자가 폭탄 터트리기 명령을 내렸을 경우에
	{
		if ((strcmp(*now_pointer, "？") == 0) && ((now_y == 11 && now_x == 7) || (now_y == 2 && now_x == 13) || (now_y == 3 && now_x == 11))) // 정답폭탄을 터뜨렸을 경우엔
		{
			if (now_y == 11 && now_x == 7)
			{
				strcpy(array[1][12], "　"); // 장애물 삭제
				delete_trash(1, 12);
			}
			if (now_y == 2 && now_x == 13)
			{
				strcpy(array[9][17], "　");
				delete_trash(9, 17);
			}
			if (now_y == 3 && now_x == 11)
			{
				strcpy(array[14][1], "　");
				delete_trash(14, 1);
			}

			strcpy(*now_pointer, "☆"); // 폭탄 그림대신 가려져있던 캐릭터의 모습을 출력
			newp();
			strcpy(massage, "장애물 하나를 무너뜨렸습니다."); // 메세지 출력
			new_massage();
			goto re; // 다시 반복하기 위해 돌아가자
		}

		if ((strcmp(*now_pointer, "？") == 0) && ((now_y == 3 && now_x == 5) || (now_y == 4 && now_x == 9) || (now_y == 2 && now_x == 15) || (now_y == 2 && now_x == 18) || (now_y == 9 && now_x == 7) || (now_y == 4 && now_x == 17) || (now_y == 7 && now_x == 9) || (now_y == 13 && now_x == 7) || (now_y == 13 && now_x == 11) || (now_y == 13 && now_x == 13) || (now_y == 10 && now_x == 14) || (now_y == 16 && now_x == 7) || (now_y == 18 && now_x == 7) || (now_y == 17 && now_x == 3) || (now_y == 17 && now_x == 9) || (now_y == 18 && now_x == 18)))
		{ // 오답 폭탄을 터뜨려버렸을 경우엔
			strcpy(*now_pointer, "☆"); // 폭탄 그림대신 가려져있던 캐릭터의 모습을 출력 
			newp();
			strcpy(massage, "펑!!! 폭탄에 의해 데미지 25를 입습니다."); // 무서운 메세지 출력
			new_massage();
			hp -= 25; // 체력 25 감소
			new_hp();
			goto re; // 다시 반복하기 위헤 돌아가자
		}

		else // 폭탄 터트리기 키는 눌렀지만 이 위치에 폭탄이 없을 때
		{
			strcpy(massage, "이 위치엔 터트릴 수 있는 폭탄이 없습니다."); // 
			new_massage();
			goto re; // 다시 반복하기 위헤 돌아가자
		}
	}

}



void nextyoso(int* choice) // 캐릭터가 이동하려고 시도하는 칸을 탐색하는 함수
{
	if (*choice == 13) // 폭탄 터트리는 키를 눌렀다면
	{
		next_pointer = &array[now_y][now_x]; // 이동을 시도하는것은 아니므로 현재 위치와 동일.
	}
	else if (*choice == 75) // 왼쪽을 택했다면
	{
		next_x -= 1; // 탐색 x축 좌표를 왼쪽으로 옮기고
		next_pointer = &array[now_y][now_x - 1]; // 캐릭터의 현재 위치보다 한칸 왼쪽에 있는 칸을 참조
	}
	else if (*choice == 77) // 오른쪽을 택했다면
	{
		next_x += 1; // 탐색 x축 좌표를 오른쪽으로 옮기고
		next_pointer = &array[now_y][now_x + 1]; // 캐릭터의 현재 위치보다 한칸 오른쪽에 있는 칸을 참조
	}
	else if (*choice == 72) // 위를 택했다면
	{
		next_y -= 1; // 탐색 y축 좌표를 위쪽으로 옮기고
		next_pointer = &array[now_y - 1][now_x]; // 캐릭터의 현재 위치보다 한칸 위쪽에 있는 칸을 참조
	}
	else if (*choice == 80)// 아래를 택했다면
	{
		next_y += 1; // 탐색 y축 좌표를 아래쪽으로 옮기고
		next_pointer = &array[now_y + 1][now_x]; // 캐릭터의 현재 위치보다 한칸 아랫쪽에 있는 칸을 참조
	}
}

void change_place(int* choice) // 캐릭터의 좌표를 옮겨주는 함수
{
	if (*choice == 75) // 왼쪽을 택했다면
	{
		now_x -= 1; // 캐릭터의 x축 좌표를 왼쪽으로 옮기고
		now_pointer = &array[now_y][now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자		
	}
	else if (*choice == 77) // 오른쪽을 택했다면
	{
		now_x += 1; // 캐릭터의 x축 좌표를 오른쪽으로 옮기고
		now_pointer = &array[now_y][now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자	
	}
	else if (*choice == 72) // 위를 택했다면
	{
		now_y -= 1; // 캐릭터의 y축 좌표를 위쪽으로 옮기고
		now_pointer = &array[now_y][now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자
	}
	else if (*choice == 80)// 아래를 택했다면
	{
		now_y += 1; // 캐릭터의 y축 좌표를 아래쪽으로 옮기고
		now_pointer = &array[now_y][now_x]; // 캐릭터의 위치를 가리키는 포인터도 새로고침 해주자
	}
}

void gotoxy(int y, int x)
{
	COORD Cur;
	Cur.Y = y;
	Cur.X = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void newp(void)
{
	gotoxy(now_y + 2, now_x * 2);
	printf("%s", array[now_y][now_x]);
}

void delete_trash(int y, int x)
{
	gotoxy(y + 2, x * 2);
	printf("%s", array[y][x]);
}

void new_hp()
{
	gotoxy(1, 76);
	printf("%d ", hp);
}

void new_massage()
{
	gotoxy(0, 0);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	gotoxy(0, 0);
	printf("[%s]", massage);
}