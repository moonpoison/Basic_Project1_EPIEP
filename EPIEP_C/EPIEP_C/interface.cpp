#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"func.h"
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
typedef struct //�α��������� �����ϴ� ����ü
{
	char ID[20];
	char PW[20];
	int author;
}User;

typedef struct // ȯ���� ������ �����ϴ� ����ü
{
	char name[20];
	char ident[20];
	int age;
	char sexual[10];
	char disease[50];
	int triage;
}HPaitient;

void make_frame(int x, int y, int dx, int dy)//x, y��ǥ, ������(�ִ� 117, 29)
{
	gotoxy(x, y);
	printf("��");
	for (int i = 0; i < dx; ++i)
		printf("��");
	printf("��");
	for (int i = y + 1; i < y + dy; ++i)
	{
		gotoxy(x, i);
		printf("��");
		for (int i = 0; i < dx; ++i)
			printf(" ");
		printf("��");
	}
	gotoxy(x, y + dy);
	printf("��");
	for (int i = 0; i < dx; ++i)
		printf("��");
	printf("��");
}

int menu_select(int size) // �α��� ���� �޴�ȭ�� ���ù�ư ����Լ�
{
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 14; i < 14 + size * 2; i += 2)
		{
			if (i == (14 + cur * 2)) //���� ����ڰ� �ǵ��� ��ġ�ϰ�� ��ĥ�� ���� ���
			{
				gotoxy(41, i);
				printf("��");
				gotoxy(75, i);
				printf("��");
			}
			else
			{
				gotoxy(41, i);
				printf("��");
				gotoxy(75, i);
				printf("��");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) return cur;
		else if (in == -32)
		{
			in = _getch();
			switch (in)
			{
			case UP:
				if (cur > 0) cur--;
				break;
			case DOWN:
				if (cur < size - 1) cur++;
				break;
			}
		}
	}
}

char* interface_menu(int author)
{
	system("cls");
	char admin_menu[2][2][50] = {
		{{"       ����� ���� ���� �� ����"},{"func5"} },
		{{"                ����"},{"func0"} }
	};
	char hos_menu[6][2][50] = {
		{{"         ���� ȯ�� ��Ȳ ����" },{"func6"}},
		{{"      Ÿ ���� ���� ��Ȳ ����"},{"func2"}},
		{{"       ����  �� Ư�̻��� �˸�"},{"func3"}},
		{{"           ���� ��� ��û"},{"func4"}},
		{{"      ���� ȯ�� ����Ϸ� ó��"},{"func7"}},
		{{"                ����"},{"func0"}}
	};
	char amb_menu[4][2][50] = {
		{{ "         ���� ȯ�� ���� ����" },{"func1"}},
		{ { "         ���� ���� ��Ȳ ����" },{"func2"} },
		{ { "            ���� ��� ��û" },{"func4"} },
		{ { "                ����" }, {"func0"} }
	};
	char cit_menu[3][2][50] = {
		{{"            ����ȯ�� �Ű�"},{"func1"} },
		{{"         ���� ���� ��Ȳ ����"},{"func2"} },
		{{"                ����"}, {"func0"} }
	};
	if (author == 0) //������
	{
		make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
		gotoxy(33, 28);
		printf("* Emergency Patient Information Exchange Program *");

		color(14);
		gotoxy(42, 2);
		printf(" * ����� ������ \"������\" �Դϴ� * ");	// Clear
		color(15);

		make_frame(39, 12, 38, 6);		// ���� �޴�â
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(40, 14);
		printf("%s", admin_menu[0][0]);
		gotoxy(41, 16);
		printf("%s", admin_menu[1][0]);
		gotoxy(50, 20);
		return admin_menu[menu_select(2)][1];
	}
	else if (author == 1) //����
	{

		make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
		gotoxy(33, 28);
		printf("* Emergency Patient Information Exchange Program *");

		color(14);
		gotoxy(43, 2);
		printf(" * ����� ������ \"����\" �Դϴ� * ");		// Clear
		color(15);

		make_frame(39, 12, 38, 14);		// ���� �޴�â
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(41, 14);
		printf("%s", hos_menu[0][0]);
		gotoxy(41, 16);
		printf(" %s", hos_menu[1][0]);
		gotoxy(41, 18);
		printf("%s", hos_menu[2][0]);
		gotoxy(40, 20);
		printf(" %s", hos_menu[3][0]);
		gotoxy(41, 22);
		printf("%s", hos_menu[4][0]);
		gotoxy(41, 24);
		printf("%s", hos_menu[5][0]);
		gotoxy(50, 30);
		return hos_menu[menu_select(6)][1];

	}
	else if (author == 2) //���޴��
	{
		make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
		gotoxy(33, 28);
		printf("* Emergency Patient Information Exchange Program *");

		color(14);
		gotoxy(41, 2);
		printf(" * ����� ������ \"���޴��\" �Դϴ� * ");	// Clear
		color(15);

		make_frame(39, 12, 38, 10);		// ���� �޴�â
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(40, 14);
		printf(" %s", amb_menu[0][0]);
		gotoxy(40, 16);
		printf(" %s", amb_menu[1][0]);
		gotoxy(40, 18);
		printf("%s", amb_menu[2][0]);
		gotoxy(41, 20);
		printf("%s", amb_menu[3][0]);
		gotoxy(50, 30);
		return amb_menu[menu_select(4)][1];
	}
	else if (author == 3) //����
	{


		make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
		gotoxy(33, 28);
		printf("* Emergency Patient Information Exchange Program *");

		color(14);
		gotoxy(44, 3);
		printf("* ����� ������ \"����\" �Դϴ� *");
		color(15);

		make_frame(39, 12, 38, 8);
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(41, 14);
		printf("%s", cit_menu[0][0]);
		gotoxy(41, 16);
		printf("%s", cit_menu[1][0]);
		gotoxy(41, 18);
		printf("%s", cit_menu[2][0]);
		gotoxy(50, 30);
		return cit_menu[menu_select(3)][1];
	}
}
char* interface_func1()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	char list1[17][50] = {
		{"�̺����İ�-��,����,���"}, //3 ~
		{"����ΰ�"},
		{"�񴢱��"},
		{"�����ܰ�"},
		{"�Ű��"},
		{"�Ȱ�"}, // ~8

		{"����ȯ"},	// 9~
		{"��ȭ��"},
		{"������"},
		{"����ȯ"},
		{"ȣ���"},
		{"���Űǰ�"}, // ~14

		{"��������"}, //15~
		{"ȯ��ջ�"},
		{"�ܻ�"},
		{"�Ǻ�"},
		{"�Ϲ�"} // ~19
	};
	char tmp[100];
	int is_noti;
	char name[20], ident[15], sexual[5], noti[50], code[5], age[3];

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(43, 9);
	printf("  An Emergency Patient Report   ");

	gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����ȯ�� �Ű�");
	color(15);	// �÷� ��ȯ

	gotoxy(42, 11);
	printf("* ȯ���� �̸��� �Է����ֽʽÿ� *");									// Clear
	gotoxy(41, 12);
	printf("\t\t..");
	scanf("%s", name);
	getchar();
	strcpy(tmp, name);
	strcat(tmp, " ");

	gotoxy(38, 14);
	printf("* ȯ���� �ֹε�Ϲ�ȣ�� �Է����ֽʽÿ� * ");						// Clear
	gotoxy(41, 15);
	printf("\t\t..");
	scanf("%s", ident);
	strcat(tmp, ident);
	strcat(tmp, " ");

	gotoxy(42, 17);
	printf("* ȯ���� ���̸� �Է����ֽʽÿ� * ");								// Clear
	gotoxy(41, 18);
	printf("\t\t..");
	scanf("%s", age);
	strcat(tmp, age);
	strcat(tmp, " ");

	gotoxy(42, 20);
	printf("* ȯ���� ������ �Է����ֽʽÿ� * ");								// Clear
	gotoxy(41, 21);
	printf("\t\t..");
	scanf("%s", sexual);
	getchar();
	strcat(tmp, sexual);
	strcat(tmp, " ");
	system("cls"); //�Ʒ��δ� code�Էº�


	make_frame(0, 0, 117, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(21, 9, 75, 15);		// �� �������̽� 
	gotoxy(43, 9);
	printf("  An Emergency Patient Report   ");

	gotoxy(53, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����ȯ�� �Ű�");
	color(15);	// �÷� ��ȯ

	gotoxy(35, 11);
	printf("** �Ʒ� �� �ش��ϴ� ������ �����Ͽ� �ֽʽÿ� **");
	int j = 0;
	for (int i = 0; i < 17; ++i)
	{
		if (i >= 0 && i <= 5)
		{
			gotoxy(25, 13 + 2 * j);
			printf("%s", list1[i]);
		}
		else if (i >= 6 && i <= 11)
		{
			gotoxy(56, 13 + 2 * j);
			printf("%s", list1[i]);
		}
		else
		{
			gotoxy(77, 13 + 2 * j);
			printf("%s", list1[i]);
		}
		j++;
		if (j == 6) j = 0;
	}

	int dx[3] = { 25, 56, 77 }; //������� �Է°��� ���� ��ġ�� ��Ÿ�������� �μ�
	int dy[6] = { 13, 15, 17, 19, 21, 23 };
	int curx = 0;
	int cury = 0;
	char in;
	while (1)
	{
		j = 0;
		for (int i = 0; i < 17; ++i)
		{
			if (i >= 0 && i <= 5)
			{
				gotoxy(23, 13 + 2 * j);
				printf("��");
			}
			else if (i >= 6 && i <= 11)
			{
				gotoxy(54, 13 + 2 * j);
				printf("��");
			}
			else
			{
				gotoxy(75, 13 + 2 * j);
				printf("��");
			}
			j++;
			if (j == 6) j = 0;
		}
		gotoxy(dx[curx] - 2, dy[cury]); printf("��");
		in = _getch();
		if (in == ENTER) break;
		else if (in == -32)
		{
			in = _getch();
			switch (in)
			{
			case UP:
				if (cury > 0) cury--;
				break;
			case DOWN:
				if (curx == 2)
				{
					if (cury < 4) cury++;
				}
				else
					if (cury < 5) cury++;
				break;
			case LEFT:
				if (curx > 0) curx--;
				break;
			case RIGHT:
				if (curx < 2) curx++;
				break;
			}
		}
	}

	if (curx == 0&&cury==0) code[0] = 'A'; else if (curx == 0 && cury == 1) code[0] = 'B'; else if (curx == 0 && cury == 2) code[0] = 'C'; else if (curx == 0 && cury == 3) code[0] = 'D'; else if (curx == 0 && cury == 4) code[0] = 'E'; else if (curx == 0 && cury == 5) code[0] = 'F'; else if (curx == 1 && cury == 0) code[0] = 'G'; else if (curx == 1 && cury == 1) code[0] = 'H'; else if (curx == 1 && cury == 2) code[0] = 'I'; else if (curx == 1 && cury == 3) code[0] = 'J'; else if (curx == 1 && cury == 4) code[0] = 'K'; else if (curx == 1 && cury == 5) code[0] = 'L'; else if (curx == 2 && cury == 0) code[0] = 'M'; else if (curx == 2 && cury == 1) code[0] = 'N'; else if (curx == 2 && cury == 2) code[0] = 'O'; else if (curx == 2 && cury == 3) code[0] = 'P'; else if (curx == 2 && cury == 4) code[0] = 'Q';
	char file_tmp[30] = ".\\disease_code\\"; //���丮���� �� disease_code�� �����ϴ� csv������ �о����
	code[1] = '\0';
	strcat(file_tmp, code);
	strcat(file_tmp, ".csv"); // .csv�� �ٿ� ���ϸ�.Ȯ���� ������ ����
	code[1] = func_KTAS1(file_tmp);
	code[2] = '\0';
	strcpy(file_tmp, ".\\disease_code\\");
	strcat(file_tmp, code);
	strcat(file_tmp, ".csv");
	strcat(code, func_KTAS2(file_tmp));
	triage tri;
	tri = func_KTAS3(code);//tri.sev, tri.dis
	strcat(tmp, code);
	strcat(tmp, " ");
	char sev[2];
	_itoa(tri.sev, sev, 10);
	strcat(tmp, sev);
	strcat(tmp, " ");
	printf("%s", tmp);
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(43, 9);
	printf("  An Emergency Patient Report   ");

	gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����ȯ�� �Ű�");
	color(15);	// �÷� ��ȯ

	gotoxy(35, 12);
	printf("* ������ ������ ȯ���� Ư�̻����� �����մϱ�? *");
	gotoxy(56, 19);
	printf("��");
	gotoxy(56, 20);
	printf("�ƴϿ�");

	int cur = 0;														// ��ư �����ؾ� �� �κ�!
	while (1)
	{
		for (int i = 19; i < 21; i++)
		{
			if (i == cur + 19)
			{
				gotoxy(54, i);
				printf("��");
			}
			else
			{
				gotoxy(54, i);
				printf("��");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) break;
		else if (in == -32)
		{
			in = _getch();
			switch (in)
			{
			case UP:
				if (cur > 0) cur--;
				break;
			case DOWN:
				if (cur < 1) cur++;
				break;
			}
		}
	}
	char is[2];
	_itoa(cur, is, 10);
	strcat(tmp, is);
	if (cur != 1)
	{
		system("cls");
		make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
		gotoxy(33, 28);
		printf("* Emergency Patient Information Exchange Program *");

		make_frame(30, 9, 55, 14);		// �� �������̽� 1
		gotoxy(43, 9);
		printf("  An Emergency Patient Report   ");

		gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
		color(14);
		printf("����ȯ�� �Ű�");
		color(15);	// �÷� ��ȯ

		gotoxy(40, 12);
		printf("* ȯ���� Ư�̻����� �Է����ֽʽÿ� *");						// clear
		gotoxy(41, 19);
		printf("\t\t..");

		gets_s(noti, sizeof(noti));
		strcat(tmp, " ");
		strcat(tmp, noti);
	}
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(43, 9);
	printf("  An Emergency Patient Report   ");

	gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����ȯ�� �Ű�");
	color(15);	// �÷� ��ȯ

	char loc[2];
	gotoxy(42, 12);
	printf("* ���� ��ġ�� �Է��Ͽ� �ֽʽÿ� *");							// Clear
	gotoxy(41, 19);
	printf("\t\t..");

	scanf("%s", loc);
	strcat(tmp, " ");
	strcat(tmp, loc);

	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	strcat(tmp, " ");
	strcat(tmp, tri.dis);
	strcat(tmp, "\n");
	return tmp;
}
void interface_func1_1(char* tmp)
{
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(29, 9, 57, 14);		// �� �������̽� 3
	gotoxy(43, 9);
	printf("  An Emergency Patient Report  ");

	gotoxy(46, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����ȯ�� �Ű����� ���ۿϷ�");									// Clear
	color(15);	// �÷� ��ȯ

	char* ptr;
	char name[20], cost[4];
	ptr = strtok(tmp, " ");
	strcpy(cost, ptr);
	ptr = strtok(NULL, " ");
	strcpy(name, ptr);

	gotoxy(32, 12);
	printf("*  �ش� ȯ���� ������ ����Ͽ� ������ �����Ͽ����ϴ�.");			// Clear
	gotoxy(32, 13);
	printf("** �ش� �������� ȯ���� ������ ���۵Ǿ����ϴ�.");
	color(14);
	gotoxy(51, 17);
	printf("���� ���� ����");
	color(15);
	gotoxy(50, 20);
	printf("���� : %s ", name);
	gotoxy(50, 21);
	printf("�ҿ�ð�(��) : %s", cost);
	char in;
	while (1)
	{
		in = 0;
		in = _getch();
		if (in != 0) break;
	}
}
char* interface_func2()											// Clear
{
	system("cls");


	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(49, 9);
	printf("  Hospital Status  ");

	gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("���� ��Ȳ ����");
	color(15);	// �÷� ��ȯ

	char hos[4];
	gotoxy(32, 12);
	printf("* ������ ��Ȳ�� ������ ������ �̸��� �Է����ֽʽÿ� *");
	gotoxy(41, 19);
	printf("\t\t..");
	scanf("%s", hos);
	return hos;
}
void interface_func2_2(char* tmp)								// Clear
{
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(49, 9);
	printf("  Hospital Status  ");

	gotoxy(52, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("���� ��Ȳ ����");
	color(15);	// �÷� ��ȯ

	char* ptr = strtok(tmp, "\n"); //���޹��� tmp�� ���Ĵ�� �ɰ�
	gotoxy(40, 15);
	printf("%s", ptr);
	ptr = strtok(NULL, "\n");
	gotoxy(40, 17);
	printf("%s", ptr);
	int in;
	while (1)
	{
		in = 0;
		in = _getch();
		if (in != 0) break;
	}
}
char* interface_func3()
{
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(48, 9);
	printf("  Hospital Details  ");

	gotoxy(48, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("���� �� Ư�̻��� �˸�");
	color(15);	// �÷� ��ȯ

	char hos[4], noti[1024];
	gotoxy(34, 12);
	printf("* Ư�̻����� �Է� �� ������ �̸��� �Է��Ͻʽÿ� *");
	gotoxy(41, 14);
	printf("\t\t..");
	scanf("%s", hos);
	while (getchar() != '\n');
	gotoxy(46, 16);
	printf("* Ư�̻����� �Է��Ͻʽÿ� *");
	gotoxy(41, 18);
	printf("\t\t..");
	scanf("%[^\n]", noti);
	while (getchar() != '\n');
	char tmp[1024];
	strcpy(tmp, hos);
	strcat(tmp, " ");
	strcat(tmp, noti);//�����̸��� Ư�̻����� �������� ������ tmp�� ��ȯ
	return tmp;
}
char* interface_func4()
{
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// �� �������̽� 1
	gotoxy(43, 9);
	printf("  Request For Medical Records  ");

	gotoxy(51, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("���� ��� ��û");
	color(15);	// �÷� ��ȯ

	char pait[10];
	gotoxy(39, 12);
	printf("* �˻� �� ȯ���� �̸��� �Է��Ͻʽÿ� *");
	gotoxy(41, 19);
	printf("\t\t..");

	scanf("%s", pait); //ȯ���� �̸��� ��ȯ
	return pait;
}
void interface_func4_1(char* tmp)
{
	system("cls");
	make_frame(0, 0, 117, 29);
	typedef struct
	{
		char name[20];
		char ident[20];
		int age;
		char sexual[10];
		char disease[50];
		int is_noti;
		char noti[50];
		char code[6];
		int triage;
	}Paitient;
	Paitient p;
	char* ptr = strtok(tmp, " "); //ȯ���� ������ ���� ������ �ɰ��� ����(����и�)
	strcpy(p.name, ptr);
	ptr = strtok(NULL, " ");
	strcpy(p.ident, ptr);
	ptr = strtok(NULL, " ");
	p.age = atoi(ptr);
	ptr = strtok(NULL, " ");
	strcpy(p.sexual, ptr);
	ptr = strtok(NULL, " ");
	strcpy(p.disease, ptr);
	ptr = strtok(NULL, " ");
	p.is_noti = atoi(ptr);
	if (p.is_noti)
	{
		ptr = strtok(NULL, " ");
		strcpy(p.noti, ptr);
	}

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 17);		// �� �������̽� 2
	gotoxy(43, 9);
	printf("  Request For Medical Records  ");

	gotoxy(51, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("���� ��� ��û");
	color(15);	// �÷� ��ȯ

	color(14);
	gotoxy(39, 11);
	printf("* �ش� ȯ���� ������ ������ �����ϴ� *");
	color(15);

	gotoxy(45, 14);
	printf("�̸� : %s", p.name);
	gotoxy(45, 16);
	printf("�ֹε�Ϲ�ȣ : %s", p.ident);
	gotoxy(45, 18);
	printf("���� : %d", p.age);
	gotoxy(45, 20);
	printf("���� : %s", p.sexual);
	gotoxy(45, 22);
	printf("������ : %s", p.disease);
	if (p.is_noti)
	{
		gotoxy(45, 24);
		printf("Ư�̻��� : %s", p.noti);
	}

	int in;
	while (1)
	{
		in = 0;
		in = _getch();
		if (in != 0) break;
	}
}
char* interface_func5(User* user, int cnt)
{
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(29, 9, 56, 14);		// �� �������̽� 4
	gotoxy(47, 9);
	printf("  Change Permissions  ");

	gotoxy(50, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����� ���� ����");

	gotoxy(38, 11);
	printf("* ������ ���� �� ����ڸ� �����Ͻʽÿ� *");
	color(15);

	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(33, i + 13);
		printf("%s\t%d", user[i].ID, user[i].author);
	}
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 13; i < cnt + 13; i++)
		{
			if (i == cur + 13)
			{
				gotoxy(31, i);
				printf("��");
			}
			else
			{
				gotoxy(31, i);
				printf("��");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) break;
		else if (in == -32)
		{
			in = _getch();
			switch (in)
			{
			case UP:
				if (cur > 0) cur--;
				break;
			case DOWN:
				if (cur < cnt - 1) cur++;
				break;
			}
		}
	}
	system("cls");

	make_frame(0, 0, 118, 29);	// �׵θ� �������̽�
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(29, 9, 56, 14);		// �� �������̽� 4
	gotoxy(47, 9);
	printf("  Change Permissions  ");

	gotoxy(50, 2);	// �� ī�װ� ǥ�� �������̽� + ��� �۾�
	color(14);
	printf("����� ���� ����");

	gotoxy(31, 12);
	printf("* ����� \"%s\"�� ���� �� ������ �Է��Ͽ� �ֽʽÿ� *", user[cur].ID);
	color(15);
	gotoxy(47, 19);
	printf("\t\t..");

	int author;
	scanf("%d", &author);
	char tmp[50];
	strcpy(tmp, user[cur].ID);
	char ptr[2];
	_itoa(author, ptr, 10);
	strcat(tmp, " ");
	strcat(tmp, ptr);
	return tmp;
}
void interface_func6(HPaitient* hp, char* hos, int cnt)
{
	system("cls");


	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("���� \"%s\"�� ȯ����Ȳ�� ������ �����ϴ�.", hos);
	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(4, 3 + i);
		printf("%s\t%s\t%d\t%s\t%s  \t%d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
	}
	int in;
	while (1)
	{
		in = 0;
		in = _getch();
		if (in != 0) break;
	}
}
int interface_func7(HPaitient* hp, char* hos, int cnt)
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("���� \"%s\"�� ȯ����Ȳ�� ������ �����ϴ�.", hos);
	gotoxy(2, 2);
	printf("����Ϸ� ó�� �� ȯ�ڸ� �����Ͻʽÿ�.");
	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(4, 3 + i);
		printf("%s\t%s\t%d\t%s\t%s  \t%d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
	}
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 3; i < cnt + 3; i++)
		{
			if (i == cur + 3)
			{
				gotoxy(2, i);
				printf("��");
			}
			else
			{
				gotoxy(2, i);
				printf("��");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) break;
		else if (in == -32)
		{
			in = _getch();
			switch (in)
			{
			case UP:
				if (cur > 0) cur--;
				break;
			case DOWN:
				if (cur < cnt - 1) cur++;
				break;
			}
		}
	}
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("\"%s\"ȯ���� ���ᰡ �Ϸ� ó���Ǿ����ϴ�.", hp[cur].name);
	return cur;
}
void interface_exit()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("���α׷��� ����Ǿ����ϴ�.");
	return;
}
/*������� �����ؾߵ�*/
char* interface_enter(char* stat)
{
	char tmp[1024];
	if (!strcmp(stat, "func1"))
	{
		strcpy(tmp, interface_func1());
		return tmp;
	}
	else if (!strcmp(stat, "func0")) interface_exit();
	else if (!strcmp(stat, "func2")) interface_func2();
	else if (!strcmp(stat, "func3")) interface_func3();
	else if (!strcmp(stat, "func4")) interface_func4();
}