#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
#include <windows.h>

void start(void); // �Լ��� ���� ����
void re(char massage[200], int bomb[][3], int obst[][4], char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3]); // �Լ��� ���� ����
void init(int bomb[][3], int obst[][4], char array[20][20][3]); // �Լ��� ���� ����
void nextyoso(int* choice, int* now_y, int* now_x, int* next_y, int* next_x, char(**next_pointer)[3], char array[20][20][3]); // �Լ��� ���� ����
void change_place(int* choice, int* now_y, int* now_x, char(**now_pointer)[3], char array[20][20][3]); // �Լ��� ���� ����
void gotoxy(int y, int x); // �Լ��� ���� ����
void newp(int* now_y, int* now_x, char array[20][20][3]); //�Լ��� ���� ����
void break_obstacle(int y, int x, char array[20][20][3]); // �Լ��� ���� ����
void new_hp(int* hp); // �Լ��� ���� ����
void new_massage(char massage[200]); // �Լ��� ���� ����

int main(void)
{
	srand(time(NULL));
	start();
}

void start() {
	int t = 0; // �ݺ��� �뿹����
	int y = 0; // �ݺ��� �뿹����
	int x = 0; // �ݺ��� �뿹����

	int bomb[20][3]; // ��ź ��ġ�� ��
	int obst[5][4]; // ��ֹ� ��ġ�� �μ�
	char array[20][20][3] = { "" }; // ���� �̷��� ����
	char text[801] = "����������������������١������������������������ᡡ������ᡡ����������ᡡ���ᡡ���ᡡ��ᡡ�ᡡ�����ᡡ�����ᡡ�ᡡ���ᡡ�����ᡡ�ᡡ�ᡡ�ᡡ�ᡡ�ᡡ���ᡡ���ᡡ����ᡡ�����ᡡ��������ᡡ���ᡡ���ᡡ��������ᡡ�ᡡ�����ᡡ���ᡡ������ᡡ���ơ����ᡡ�ᡡ�ᡡ���ᡡ����ᡡ��ᡡ���ᡡ�ᡡ����ᡡ���������ᡡ��ᡡ���������ᡡ�ᡡ���������ᡡ����������ᡡ�ᡡ�ᡡ�ᡡ��ᡡ��ᡡ���ᡡ���������ᡡ�ᡡ�ᡡ�������ᡡ������ᡡ���ᡡ���ᡡ�ᡡ��ᡡ�ᡡ����ᡡ���������ᡡ�����ᡡ�ᡡ���ᡡ������ᡡ����������������ᡡ��ᡡ�������������������������ᡡ��������ᡡ���ᡡ�ᡡ�����ᡡ�ᡡ�����ᡡ�ᡡ�ᡡ���ᡡ�ᡡ�����ᡡ�������ᡡ�����ᡡ�����ᡡ�����ᡡ�����ᡡ������������������������";

	char massage[200] = "�̷� ������ �����մϴ�!!"; // �ȳ� �޼���
	int hp = 100; // ���� ����Ʈ
	int now_y = 1; // ĳ������ y�� ��ġ
	int now_x = 1; // ĳ������ x�� ��ġ
	char(*now_pointer)[3] = &array[now_y][now_x]; // ĳ������ ���� ��ǥ�� ����Ű�� �迭 ������
	int next_y = 1; // Ž�� y�� ��ġ
	int next_x = 1; // Ž�� x�� ��ġ
	char(*next_pointer)[3] = &array[next_y][next_x]; // ĳ���Ͱ� �̵��� ��ġ�� Ž���� ���� �迭 ������


	for (y = 0; y < 20; y++) // �ؽ�Ʈ�� �ִ� �̷��� �׸��� ���� �̷��ǿ� �ٿ��ֱ� �ϴ� �ݺ���
	{
		for (x = 0; x < 20; x++)
		{
			array[y][x][0] = text[t]; // �̷��� ����� ���� ������ �̷��ǿ� ����
			t += 1;
			array[y][x][1] = text[t]; // �̷��� ����� ������ ������ �̷��ǿ� ����
			t += 1;
			array[y][x][2] = 0; // �� ���� ����
		}
	}

	init(bomb, obst, array); //��ֹ��� ��ź ��ġ �������� �ʱ�ȭ�ϱ�


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////


	system("cls"); // ȭ�� ������ �����

	printf("[%s]\n", massage);
	printf("                                                              ���� ����Ʈ : %d\n", hp); // �ȳ� �޼����� ���� ����Ʈ ���

	for (y = 0; y < 20; y++) // �̷��� ��� �ݺ���
	{
		for (x = 0; x < 20; x++)
		{
			printf("%s", array[y][x]); // �̷����� ���������� �� ���
		}
		printf("\n"); // ������ ���� ����� ���� ������ ���� �������
	}

	printf("\n");
	printf("����Ű �Ǵ� ��ź ��Ʈ���� = ���� �� ��������. : "); // ����ڿ��� Ű �Է� �䱸�޼��� ���

	re(massage, bomb, obst, array, &hp, &now_y, &now_x, now_pointer, &next_y, &next_x, next_pointer);
}

void init(int bomb[][3], int obst[][4], char array[20][20][3])
{
	int y, x;
	for (int i = 0; i < 5; i++)
	{
		do {
			y = rand() % 15 + 5;
			x = rand() % 15 + 5;
		} while (strcmp(array[y][x], "��"));
		obst[i][0] = y;
		obst[i][1] = x;
		strcpy(array[y][x], "��");

		obst[i][2] = rand() % 99 + 1;
		obst[i][3] = rand() % 99 + 1;
	}
	for (int i = 0; i < 20; i++)
	{
		do {
			y = rand() % 20;
			x = rand() % 20;
		} while (strcmp(array[y][x], "��"));
		bomb[i][0] = y;
		bomb[i][1] = x;
		strcpy(array[y][x], "��");
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
}

void re(char massage[200], int bomb[][3], int obst[][4], char array[20][20][3], int* hp, int* now_y, int* now_x, char(*now_pointer)[3], int* next_y, int* next_x, char(*next_pointer)[3]) {
	int t = 0; // �ݺ��� �뿹����
	int choice = 0;
	int i;     // �ݺ��� �뿹����

	if (*hp <= 0) // ü���� 0�� �Ǹ�
	{
		system("cls"); // ȭ�� ������ �����
		printf("[%s]\n\n", massage); // �޼��� ���
		printf("���� ����. Game Over. \n�絵�� �Ͻðڽ��ϱ�? �絵�� �Ϸ��� 9�� �����ּ��� : "); // ���ӿ���
		choice = _getch(); // ������� �Է� ���

		while (true) // ����ڰ� 9�� ���� ������ �ݺ�
		{
			if (choice == '9') //����ڰ� 9�� ������
			{
				*now_y = 1;
				*now_x = 1;
				t = 0;
				*hp = 100;
				strcpy(massage, "�̷� ������ �����մϴ�!!"); // ��� ���� �ʱ�ȭ
				start();
				break;
			}
			else {
				choice = _getch();
			}
		}
	}

	now_pointer = &array[*now_y][*now_x]; // now_pointer�� ĳ������ ���� ��ġ�� �����Ѷ�.
	*next_y = *now_y; //
	*next_x = *now_x; // next ��ǥ�� now ��ǥ ��ġ��Ű��


	gotoxy(23, 48);
	choice = _getch(); // ����� �Է� ���

	while (true)
	{
		if (choice == 75 || choice == 77 || choice == 72 || choice == 80 || choice == 13)
			break;
		else
			choice = _getch();
	}

	nextyoso(&choice, now_y, now_x, next_y, next_x, &next_pointer, array); // ĳ���Ͱ� �̵��Ϸ��� �õ��ϴ� ĭ�� Ž���ϴ� �Լ� ȣ��

	if (choice != 13) // ������� ������ ���� �����̿��ٸ� ������ ���� �ൿ�� �ض�
	{
		if (strcmp(*next_pointer, "��") == 0 && strcmp(*now_pointer, "��") == 0) // ���࿡ ���� ��ġ�� �����̰� Ž���ߴ� ĭ�� �����̶��
		{
			strcpy(*now_pointer, "��"); // ���� ����� ���� �����
			newp(now_y, now_x, array);
			change_place(&choice, now_y, now_x, &now_pointer, array); // ĳ������ ��ǥ�� �ű���
			strcpy(*now_pointer, "��"); // �Ű��� ���ο� ��ġ�� �� �׸���
			newp(now_y, now_x, array);
			strcpy(massage, "�޷��� �޷�~"); // �޷��� �޷� ������ �޼����� ����
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}

		else if (strcmp(*next_pointer, "��") == 0 && strcmp(*now_pointer, "��") == 0) // ���࿡ Ž�� ��ġ�� �����̰� ���� ��ġ�� ? �� �ִٸ� 
		{
			change_place(&choice, now_y, now_x, &now_pointer, array); // ĳ������ ��ǥ�� �ű���
			strcpy(*now_pointer, "��"); // �Ű��� ���ο� ��ġ�� �� �׸���
			newp(now_y, now_x, array);
			strcpy(massage, "�޷��� �޷�~"); // �޷��� �޷� ������ �޼����� ����
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}

		else if (strcmp(*next_pointer, "��") == 0) // ���࿡ Ž���ߴ� ĭ�� ���̶��
		{
			strcpy(massage, "���� �΋H�ƾ�� �̤�"); // ���� �΋H�ƴٴ� ������ �޼����� ����
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}

		else if (strcmp(*next_pointer, "��") == 0) // ���࿡ Ž���ߴ� ĭ�� ��ֹ��̶��
		{
			for (int i = 0; i < 5; i++)
			{
				if (*next_y == obst[i][0] && *next_x == obst[i][1])
				{
					sprintf(massage, "��ֹ� %c�� ��������. �̰� �μ��� ���� ��ź %d*%d �� ã�ƾ� �մϴ�.", 'A' + i, obst[i][2], obst[i][3]); // ��ֹ��� �΋H�ƴٴ� �ȳ� �޼���
					break;
				}
			}
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer);
		}

		else if (strcmp(*next_pointer, "��") == 0 && strcmp(*now_pointer, "��") == 0)
		{
			strcpy(*now_pointer, "��"); // ���� ����� ���� �����
			newp(now_y, now_x, array);
			change_place(&choice, now_y, now_x, &now_pointer, array); // ĳ������ ��ǥ�� �ű���
			for (int i = 0; i < 20; i++)
			{
				if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
				{
					sprintf(massage, "��ֹ� %c�� �Ͷ߸��� ���� ��ź�Դϴ�. %d �̶�� ���� �ֽ��ϴ�.", 'A' + i / 4, bomb[i][2]);
					break;
				}
			}
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}

		else if (strcmp(*next_pointer, "��") == 0 && strcmp(*now_pointer, "��") == 0)
		{
			strcpy(*now_pointer, "��"); // ���� ����� ���� �����
			newp(now_y, now_x, array);
			change_place(&choice, now_y, now_x, &now_pointer, array); // ĳ������ ��ǥ�� �ű���
			for (int i = 0; i < 20; i++)
			{
				if (*next_y == bomb[i][0] && *next_x == bomb[i][1])
				{
					sprintf(massage, "��ֹ� %c�� �Ͷ߸��� ���� ��ź�Դϴ�. %d �̶�� ���� �ֽ��ϴ�.", 'A' + i / 4, bomb[i][2]);
					break;
				}
			}
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}

		else if (strcmp(*next_pointer, "��") == 0) // �ǴϽ��� ������
		{
			for (;;)
			{
				system("cls"); // ȭ�� ������ �����
				printf("Ŭ��� ���ϵ帳�ϴ�!!!");
				scanf("%d", &choice); // Ű�� �Է��ص� ���α׷��� ������ ������ ���� ȭ�� ����
			}
		}
	}

	if (choice == 13) // ����ڰ� ��ź ��Ʈ���� ����� ������ ��쿡
	{
		if (strcmp(*now_pointer, "��") == 0) // ��ź�� �ڸ��� ���� ��쿣
		{
			for (i = 0; i < 20; i++)
			{
				if (*now_y == bomb[i][0] && *now_x == bomb[i][1])
				{
					break;
				}
			}
			strcpy(*now_pointer, "��"); // ��ź �׸���� �������ִ� ĳ������ ����� ���
			newp(now_y, now_x, array);
			if (i % 4 == 0)
			{
				break_obstacle(obst[i / 4][0], obst[i / 4][1], array);
				strcpy(massage, "��ֹ� �ϳ��� ���ʶ߷Ƚ��ϴ�."); // �޼��� ���
				new_massage(massage);
				re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
			}
			else
			{
				strcpy(massage, "��!!! ��ź�� ���� ������ 25�� �Խ��ϴ�."); // ������ �޼��� ���
				new_massage(massage);
				*hp -= 25; // ü�� 25 ����
				new_hp(hp);
				re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
			}
		}

		else // ��ź ��Ʈ���� Ű�� �������� �� ��ġ�� ��ź�� ���� ��
		{
			strcpy(massage, "�� ��ġ�� ��Ʈ�� �� �ִ� ��ź�� �����ϴ�."); // 
			new_massage(massage);
			re(massage, bomb, obst, array, hp, now_y, now_x, now_pointer, next_y, next_x, next_pointer); // �ٽ� �ݺ��ϱ� ���� ���ư���
		}
	}
}

void nextyoso(int* choice, int* now_y, int* now_x, int* next_y, int* next_x, char(**next_pointer)[3], char array[20][20][3]) // ĳ���Ͱ� �̵��Ϸ��� �õ��ϴ� ĭ�� Ž���ϴ� �Լ�
{
	if (*choice == 13) // ��ź ��Ʈ���� Ű�� �����ٸ�
	{
		*next_pointer = &array[*now_y][*now_x]; // �̵��� �õ��ϴ°��� �ƴϹǷ� ���� ��ġ�� ����.
	}
	else if (*choice == 75) // ������ ���ߴٸ�
	{
		*next_x -= 1; // Ž�� x�� ��ǥ�� �������� �ű��
		*next_pointer = &array[*now_y][*now_x - 1]; // ĳ������ ���� ��ġ���� ��ĭ ���ʿ� �ִ� ĭ�� ����
	}
	else if (*choice == 77) // �������� ���ߴٸ�
	{
		*next_x += 1; // Ž�� x�� ��ǥ�� ���������� �ű��
		*next_pointer = &array[*now_y][*now_x + 1]; // ĳ������ ���� ��ġ���� ��ĭ �����ʿ� �ִ� ĭ�� ����
	}
	else if (*choice == 72) // ���� ���ߴٸ�
	{
		*next_y -= 1; // Ž�� y�� ��ǥ�� �������� �ű��
		*next_pointer = &array[*now_y - 1][*now_x]; // ĳ������ ���� ��ġ���� ��ĭ ���ʿ� �ִ� ĭ�� ����
	}
	else if (*choice == 80)// �Ʒ��� ���ߴٸ�
	{
		*next_y += 1; // Ž�� y�� ��ǥ�� �Ʒ������� �ű��
		*next_pointer = &array[*now_y + 1][*now_x]; // ĳ������ ���� ��ġ���� ��ĭ �Ʒ��ʿ� �ִ� ĭ�� ����
	}
}

void change_place(int* choice, int* now_y, int* now_x, char(**now_pointer)[3], char array[20][20][3]) // ĳ������ ��ǥ�� �Ű��ִ� �Լ�
{
	if (*choice == 75) // ������ ���ߴٸ�
	{
		*now_x -= 1; // ĳ������ x�� ��ǥ�� �������� �ű��
		*now_pointer = &array[*now_y][*now_x]; // ĳ������ ��ġ�� ����Ű�� �����͵� ���ΰ�ħ ������      
	}
	else if (*choice == 77) // �������� ���ߴٸ�
	{
		*now_x += 1; // ĳ������ x�� ��ǥ�� ���������� �ű��
		*now_pointer = &array[*now_y][*now_x]; // ĳ������ ��ġ�� ����Ű�� �����͵� ���ΰ�ħ ������   
	}
	else if (*choice == 72) // ���� ���ߴٸ�
	{
		*now_y -= 1; // ĳ������ y�� ��ǥ�� �������� �ű��
		*now_pointer = &array[*now_y][*now_x]; // ĳ������ ��ġ�� ����Ű�� �����͵� ���ΰ�ħ ������
	}
	else if (*choice == 80)// �Ʒ��� ���ߴٸ�
	{
		*now_y += 1; // ĳ������ y�� ��ǥ�� �Ʒ������� �ű��
		*now_pointer = &array[*now_y][*now_x]; // ĳ������ ��ġ�� ����Ű�� �����͵� ���ΰ�ħ ������
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
	strcpy(array[y][x], "��");
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
	printf("��������������������������������������������������������������������������������");
	gotoxy(0, 0);
	printf("[%s]", massage);
}