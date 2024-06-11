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
typedef struct
{
	char ID[20];
	char PW[20];
	int author;
}User;

typedef struct
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
	for (int i = y+1; i < y+dy; ++i)
	{
		gotoxy(x, i);
		printf("��");
		for (int i = 0; i < dx; ++i)
			printf(" ");
		printf("��");
	}
	gotoxy(x, y+dy);
	printf("��");
	for (int i = 0; i < dx; ++i)
		printf("��");
	printf("��");
}
void make_cross(int x, int y)
{
	color(10);
	gotoxy(x, y++);
	printf("      ������������\n");
	gotoxy(x, y++);
	printf("      ��    ��\n");
	gotoxy(x, y++);
	printf("      ��    ��\n");
	gotoxy(x, y++);
	printf("��������������    ��������������\n");
	gotoxy(x, y++);
	printf("��                ��\n");
	gotoxy(x, y++);
	printf("��������������    ��������������\n");
	gotoxy(x, y++);
	printf("      ��    ��\n");
	gotoxy(x, y++);
	printf("      ��    ��\n");
	gotoxy(x, y);
	printf("      ������������\n");
	color(15);
}

int menu_select(int size)
{
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 14; i < 14 + size*2; i += 2)
		{
			if (i == (14 + cur * 2))
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
					if (cur < size-1) cur++;
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
		{{"       Ÿ ���� ���� ��Ȳ ����"},{"func2"}},
		{{"        ���� �� Ư�̻��� �˸�"},{"func3"}},
		{{"            ���� ��� ��û"},{"func4"}},
		{{"       ���� ȯ�� ����Ϸ� ó��"},{"func7"}},
		{{"                ����"},{"func0"}}
	};
	char amb_menu[4][2][50] = {
		{{ "         ����ȯ�� ���� ����" },{"func1"}},
		{ { "         ���� ���� ��Ȳ ����" },{"func2"} },
		{ { "            ���� ��� ��û" },{"func4"} },
		{ { "                ����" }, {"func0"} }
	};
	char cit_menu[3][2][50] = {
		{{"            ����ȯ�� �Ű�"},{"func1"} },
		{{"         ���� ���� ��Ȳ ����"},{"func2"} },
		{{"                ����"}, {"func0"} }
	};
	if (author == 0)
	{
		gotoxy(85, 1);
		printf("����� ������ \"������\" �Դϴ�.");
		make_frame(39, 12, 38, 6);
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(41, 14);
		printf("%s", admin_menu[0][0]);
		gotoxy(41, 16);
		printf("%s", admin_menu[1][0]);
		gotoxy(50, 20);
		return admin_menu[menu_select(2)][1];
	}
	else if (author == 1)
	{
		gotoxy(85, 1);
		printf("����� ������ \"����\" �Դϴ�.");
		make_frame(39, 12, 38, 14);
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(41, 14);
		printf("%s", hos_menu[0][0]);
		gotoxy(41, 16);
		printf("%s", hos_menu[1][0]);
		gotoxy(41, 18);
		printf("%s", hos_menu[2][0]);
		gotoxy(41, 20);
		printf("%s", hos_menu[3][0]);
		gotoxy(41, 22);
		printf("%s", hos_menu[4][0]);
		gotoxy(41, 24);
		printf("%s", hos_menu[5][0]);
		gotoxy(50, 30);
		return hos_menu[menu_select(6)][1];
	}
	else if (author == 2)
	{
		gotoxy(80, 1);
		printf("����� ������ \"���޴��\" �Դϴ�.");
		make_frame(39, 12, 38, 10);
		gotoxy(53, 12);
		printf("   OPTION   ");
		gotoxy(41, 14);
		printf("%s", amb_menu[0][0]);
		gotoxy(41, 16);
		printf("%s", amb_menu[1][0]);
		gotoxy(41, 18);
		printf("%s", amb_menu[2][0]);
		gotoxy(41, 20);
		printf("%s", amb_menu[3][0]);
		gotoxy(50, 30);
		return amb_menu[menu_select(4)][1];
	}
	else if (author == 3)
	{
		gotoxy(90, 1);
		printf("����� ������ \"����\" �Դϴ�.");
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
	//������ �̻��Ѱſ�����(����ó���ؾߵ�)
}
/*������� �����ؾߵ�*/
char* interface_func1()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	char list1[17][50] = {
		{"��������"},
		{"���Űǰ�"},
		{"�Ű��"},
		{"�Ȱ�"},
		{"����ȯ"},
		{"����ȯ"},
		{"�̺����İ�-��,����,���"},
		{"ȣ���"},
		{"������"},
		{"��ȭ��"},
		{"����ΰ�"},
		{"�񴢱��"},
		{"�����ܰ�"},
		{"�ܻ�"},
		{"ȯ��ջ�"},
		{"�Ǻ�"},
		{"�Ϲ�"}
	};
	char tmp[100];
	int is_noti;
	char name[20], ident[15], sexual[5], noti[50], code[5], age[3];
	gotoxy(2, 1);
	printf("ȯ���� �̸��� �Է����ֽʽÿ� : ");
	scanf("%s", name);
	getchar();
	strcpy(tmp, name);
	strcat(tmp, " ");
	gotoxy(2, 3);
	printf("ȯ���� �ֹε�Ϲ�ȣ�� �Է����ֽʽÿ� : ");
	scanf("%s", ident);
	strcat(tmp, ident);
	strcat(tmp, " ");
	gotoxy(2, 5);
	printf("ȯ���� ���̸� �Է����ֽʽÿ� : ");
	scanf("%s", age);
	strcat(tmp, age);
	strcat(tmp, " ");
	gotoxy(2, 7);
	printf("ȯ���� ������ �Է����ֽʽÿ� : ");
	scanf("%s", sexual);
	getchar();
	strcat(tmp, sexual);
	strcat(tmp, " ");
	system("cls"); //�Ʒ��δ� code�Էº�
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("�Ʒ� �� �ش��ϴ� ������ �����Ͽ� �ֽʽÿ�");
	for (int i = 0; i < 17; ++i)
	{
		gotoxy(4, 3 + i);
		printf("%s", list1[i]);
	}

	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 3; i < 20; i ++)
		{
			if (i == cur+3)
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
				if (cur < 16) cur++;
				break;
			}
		}
	}
	if (cur == 0) code[0] = 'A'; else if (cur == 1) code[0] = 'B'; else if (cur == 2) code[0] = 'C'; else if (cur == 3) code[0] = 'D'; else if (cur == 4) code[0] = 'E'; else if (cur == 5) code[0] = 'F'; else if (cur == 6) code[0] = 'G'; else if (cur == 7) code[0] = 'H'; else if (cur == 8) code[0] = 'I'; else if (cur == 9) code[0] = 'J'; else if (cur == 10) code[0] = 'K'; else if (cur == 11) code[0] = 'L'; else if (cur == 12) code[0] = 'M'; else if (cur == 13) code[0] = 'N'; else if (cur == 14) code[0] = 'O'; else if (cur == 15) code[0] = 'P'; else if (cur == 16) code[0] = 'Q';
	char file_tmp[30]=".\\disease_code\\";
	code[1] = '\0';
	strcat(file_tmp, code);
	strcat(file_tmp, ".csv");
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
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("������ ������ ȯ���� Ư�̻����� �����մϱ�?");
	gotoxy(4, 3);
	printf("��");
	gotoxy(4, 4);
	printf("�ƴϿ�");
	
	cur = 0;
	while (1)
	{
		for (int i = 3; i < 5; i++)
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
		make_frame(0, 0, 117, 29);
		gotoxy(2, 1);
		printf("ȯ���� Ư�̻����� �Է����ֽʽÿ� : ");
		gets_s(noti, sizeof(noti));
		strcat(tmp, " ");
		strcat(tmp, noti);
	}
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char loc[2];
	printf("���� ��ġ�� �Է��Ͽ� �ֽʽÿ� : ");
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
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char* ptr;
	char name[20], cost[4];
	ptr = strtok(tmp, " ");
	strcpy(cost, ptr);
	ptr = strtok(NULL, " ");
	strcpy(name, ptr);
	printf("�ش� ȯ���� ������ ����Ͽ� ������ �����Ͽ����ϴ�.");
	gotoxy(2, 2);
	printf("�ش� �������� ȯ���� ������ ���۵Ǿ����ϴ�.");
	gotoxy(4, 4);
	printf("���� : %s ", name);
	gotoxy(4, 5);
	printf("�ҿ�ð�(��) : %s", cost);
	char in;
	while (1)
	{
		in = 0;
		in = _getch();
		if (in != 0) break;
	}
}
char* interface_func2()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char hos[4];
	printf("������ ��Ȳ�� ������ ������ �̸��� �Է����ֽʽÿ� : ");
	scanf("%s", hos);
	return hos;
}
void interface_func2_2(char *tmp)
{
	system("cls");
	make_frame(0, 0, 117, 29);
	char* ptr=strtok(tmp, "\n");
	gotoxy(2, 1);
	printf("%s", ptr);
	ptr = strtok(NULL, "\n");
	gotoxy(2, 2);
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
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char hos[4], noti[1024];
	printf("Ư�̻����� �Է� �� ������ �̸��� �Է��Ͻʽÿ� : ");
	scanf("%s", hos);
	while (getchar() != '\n');
	gotoxy(2, 3);
	printf("Ư�̻����� �Է��Ͻʽÿ� : ");
	scanf("%[^\n]", noti);
	while(getchar()!='\n');
	char tmp[1024];
	strcpy(tmp, hos);
	strcat(tmp, " ");
	strcat(tmp, noti);
	return tmp;
}
char* interface_func4()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char pait[10];
	printf("�˻� �� ȯ���� �̸��� �Է��Ͻʽÿ� : ");
	scanf("%s", pait);
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
	char* ptr = strtok(tmp, " ");
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
	
	gotoxy(2, 1);
	printf("�ش� ȯ���� ������ ������ �����ϴ�.");

	gotoxy(4, 3);
	printf("�̸� : %s", p.name);
	gotoxy(4, 4);
	printf("�ֹε�Ϲ�ȣ : %s", p.ident);
	gotoxy(4, 5);
	printf("���� : %d", p.age);
	gotoxy(4, 6);
	printf("���� : %s", p.sexual);
	gotoxy(4, 7);
	printf("������ : %s", p.disease);
	if (p.is_noti)
	{
		gotoxy(4, 8);
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
char* interface_func5(User *user, int cnt)
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("������ ���� �� ����ڸ� �����Ͻʽÿ�.");
	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(4, i + 3);
		printf("%s\t%d", user[i].ID, user[i].author);
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
	printf("����� \"%s\"�� ���� �� ������ �Է��Ͽ� �ֽʽÿ� : ", user[cur].ID);
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
		printf("%s\t%s\t%d\t%s\t%s\t%d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
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
		printf("%s\t%s\t%d\t%s\t%s\t%d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
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