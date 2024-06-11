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

void make_frame(int x, int y, int dx, int dy)//x, y좌표, 생성값(최대 117, 29)
{
	gotoxy(x, y);
	printf("┌");
	for (int i = 0; i < dx; ++i)
		printf("─");
	printf("┐");
	for (int i = y+1; i < y+dy; ++i)
	{
		gotoxy(x, i);
		printf("│");
		for (int i = 0; i < dx; ++i)
			printf(" ");
		printf("│");
	}
	gotoxy(x, y+dy);
	printf("└");
	for (int i = 0; i < dx; ++i)
		printf("─");
	printf("┘");
}
void make_cross(int x, int y)
{
	color(10);
	gotoxy(x, y++);
	printf("      ┌────┐\n");
	gotoxy(x, y++);
	printf("      │    │\n");
	gotoxy(x, y++);
	printf("      │    │\n");
	gotoxy(x, y++);
	printf("┌─────┘    └─────┐\n");
	gotoxy(x, y++);
	printf("│                │\n");
	gotoxy(x, y++);
	printf("└─────┐    ┌─────┘\n");
	gotoxy(x, y++);
	printf("      │    │\n");
	gotoxy(x, y++);
	printf("      │    │\n");
	gotoxy(x, y);
	printf("      └────┘\n");
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
				printf("●");
				gotoxy(75, i);
				printf("●");
			}
			else
			{
				gotoxy(41, i);
				printf("○");
				gotoxy(75, i);
				printf("○");
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
		{{"       사용자 권한 열람 및 변경"},{"func5"} },
		{{"                종료"},{"func0"} }
	};
	char hos_menu[6][2][50] = {
		{{"         내원 환자 현황 열람" },{"func6"}},
		{{"       타 병원 내원 현황 열람"},{"func2"}},
		{{"        병원 내 특이사항 알림"},{"func3"}},
		{{"            진료 기록 요청"},{"func4"}},
		{{"       내원 환자 진료완료 처리"},{"func7"}},
		{{"                종료"},{"func0"}}
	};
	char amb_menu[4][2][50] = {
		{{ "         응급환자 정보 전달" },{"func1"}},
		{ { "         병원 내원 현황 열람" },{"func2"} },
		{ { "            진료 기록 요청" },{"func4"} },
		{ { "                종료" }, {"func0"} }
	};
	char cit_menu[3][2][50] = {
		{{"            응급환자 신고"},{"func1"} },
		{{"         병원 내원 현황 열람"},{"func2"} },
		{{"                종료"}, {"func0"} }
	};
	if (author == 0)
	{
		gotoxy(85, 1);
		printf("당신의 권한은 \"관리자\" 입니다.");
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
		printf("당신의 권한은 \"병원\" 입니다.");
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
		printf("당신의 권한은 \"구급대원\" 입니다.");
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
		printf("당신의 권한은 \"개인\" 입니다.");
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
	//권한이 이상한거왔을때(예외처리해야됨)
}
/*여기부터 구현해야됨*/
char* interface_func1()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	char list1[17][50] = {
		{"물질오용"},
		{"정신건강"},
		{"신경과"},
		{"안과"},
		{"코질환"},
		{"귀질환"},
		{"이비인후과-입,인후,경부"},
		{"호흡기"},
		{"심혈관"},
		{"소화기"},
		{"산부인과"},
		{"비뇨기과"},
		{"정형외과"},
		{"외상"},
		{"환경손상"},
		{"피부"},
		{"일반"}
	};
	char tmp[100];
	int is_noti;
	char name[20], ident[15], sexual[5], noti[50], code[5], age[3];
	gotoxy(2, 1);
	printf("환자의 이름을 입력해주십시오 : ");
	scanf("%s", name);
	getchar();
	strcpy(tmp, name);
	strcat(tmp, " ");
	gotoxy(2, 3);
	printf("환자의 주민등록번호를 입력해주십시오 : ");
	scanf("%s", ident);
	strcat(tmp, ident);
	strcat(tmp, " ");
	gotoxy(2, 5);
	printf("환자의 나이를 입력해주십시오 : ");
	scanf("%s", age);
	strcat(tmp, age);
	strcat(tmp, " ");
	gotoxy(2, 7);
	printf("환자의 성별을 입력해주십시오 : ");
	scanf("%s", sexual);
	getchar();
	strcat(tmp, sexual);
	strcat(tmp, " ");
	system("cls"); //아래로는 code입력부
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("아래 중 해당하는 증상을 선택하여 주십시오");
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
				printf("●");
			}
			else
			{
				gotoxy(2, i);
				printf("○");
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
	printf("병원에 전달할 환자의 특이사항이 존재합니까?");
	gotoxy(4, 3);
	printf("예");
	gotoxy(4, 4);
	printf("아니오");
	
	cur = 0;
	while (1)
	{
		for (int i = 3; i < 5; i++)
		{
			if (i == cur + 3)
			{
				gotoxy(2, i);
				printf("●");
			}
			else
			{
				gotoxy(2, i);
				printf("○");
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
		printf("환자의 특이사항을 입력해주십시오 : ");
		gets_s(noti, sizeof(noti));
		strcat(tmp, " ");
		strcat(tmp, noti);
	}
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	char loc[2];
	printf("현재 위치를 입력하여 주십시오 : ");
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
	printf("해당 환자의 정보를 고려하여 병원을 선정하였습니다.");
	gotoxy(2, 2);
	printf("해당 병원으로 환자의 정보가 전송되었습니다.");
	gotoxy(4, 4);
	printf("병원 : %s ", name);
	gotoxy(4, 5);
	printf("소요시간(분) : %s", cost);
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
	printf("병원의 현황을 열람할 병원의 이름을 입력해주십시오 : ");
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
	printf("특이사항을 입력 할 병원의 이름을 입력하십시오 : ");
	scanf("%s", hos);
	while (getchar() != '\n');
	gotoxy(2, 3);
	printf("특이사항을 입력하십시오 : ");
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
	printf("검색 할 환자의 이름을 입력하십시오 : ");
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
	printf("해당 환자의 정보는 다음과 같습니다.");

	gotoxy(4, 3);
	printf("이름 : %s", p.name);
	gotoxy(4, 4);
	printf("주민등록번호 : %s", p.ident);
	gotoxy(4, 5);
	printf("나이 : %d", p.age);
	gotoxy(4, 6);
	printf("성별 : %s", p.sexual);
	gotoxy(4, 7);
	printf("질병명 : %s", p.disease);
	if (p.is_noti)
	{
		gotoxy(4, 8);
		printf("특이사항 : %s", p.noti);
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
	printf("권한을 변경 할 사용자를 선택하십시오.");
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
				printf("●");
			}
			else
			{
				gotoxy(2, i);
				printf("○");
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
	printf("사용자 \"%s\"의 변경 할 권한을 입력하여 주십시오 : ", user[cur].ID);
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
	printf("병원 \"%s\"의 환자현황은 다음과 같습니다.", hos);
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
	printf("병원 \"%s\"의 환자현황은 다음과 같습니다.", hos);
	gotoxy(2, 2);
	printf("진료완료 처리 할 환자를 선택하십시오.");
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
				printf("●");
			}
			else
			{
				gotoxy(2, i);
				printf("○");
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
	printf("\"%s\"환자의 진료가 완료 처리되었습니다.", hp[cur].name);
	return cur;
}
void interface_exit()
{
	system("cls");
	make_frame(0, 0, 117, 29);
	gotoxy(2, 1);
	printf("프로그램이 종료되었습니다.");
	return;
}
/*여기까지 구현해야됨*/
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