#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include"interface.h"
#include"func.h"
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
void skip_utf8_bom(FILE* file) {
	unsigned char bom[3];
	if (fread(bom, 1, 3, file) == 3) {
		if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
			// BOM이 존재함
			return;
		}
		else {
			// BOM이 존재하지 않음, 파일 포인터를 처음으로 되돌림
			fseek(file, 0, SEEK_SET);
		}
	}
}
void remove_blank(FILE* file) {
	char tmp[1024];
	fgets(tmp, 1024, file);
	if (!strcmp(tmp, ""))
	{

		return;
	}
	else {
		// BOM이 존재하지 않음, 파일 포인터를 처음으로 되돌림
		fseek(file, 0, SEEK_SET);
	}
}
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void color(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
char func_KTAS1(char* root)
{
	FILE* fp = fopen(root, "rb+");
	if (fp == NULL) {
		printf("%s", root);
		system("pause");
	}
	skip_utf8_bom(fp);

	char code[20];
	char asd;
	char data[20][200];
	char tmp[1024];
	int cnt = 0;
	while (!feof(fp)) {
		fgets(tmp, 1023, fp);
		printf("%s", tmp);
		char* ptr = strtok(tmp, ",");
		ptr = strtok(NULL, ",");
		strcpy(data[cnt], ptr);
		ptr = strtok(NULL, ",");
		code[cnt] = *ptr;
		++cnt;
	}
	fclose(fp);
	system("cls");

	make_frame(0, 0, 118, 29);	// 테두리 인터페이스
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 9, 55, 14);		// 중형 사이즈 인터페이스 2
	gotoxy(43, 9);
	printf("  An Emergency Patient Report   ");

	gotoxy(52, 2);	// 현 카테고리 표시 인터페이스 + 노랑 글씨
	color(14);
	printf("응급환자 신고");
	color(15);	// 컬러 전환

	gotoxy(35, 11);
	printf("* 아래 중 해당하는 증상을 선택하여 주십시오 *");
	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(35, 13 + i);
		printf("%s", data[i]);
	}
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 13; i < cnt + 13; i++)					// 버튼 고쳐야할 부분!
		{
			if (i == cur + 13)
			{
				gotoxy(33, i);
				printf("●");
			}
			else
			{
				gotoxy(33, i);
				printf("○");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) return code[cur];
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
}
char* func_KTAS2(char* root)
{
	FILE* fp = fopen(root, "rb+");
	if (fp == NULL) {
		printf("%s", root);
		system("pause");
	}
	skip_utf8_bom(fp);

	char code[20][3];
	char asd;
	char data[20][200];
	char tmp[1024];
	int cnt = 0;
	while (!feof(fp)) {
		fgets(tmp, 1023, fp);
		printf("%s", tmp);
		char* ptr = strtok(tmp, ",");
		ptr = strtok(NULL, ",");
		strcpy(data[cnt], ptr);
		ptr = strtok(NULL, ",");
		strcpy(code[cnt], ptr);
		code[cnt][2] = '\0';
		++cnt;
	}
	fclose(fp);
	system("cls");

	make_frame(0, 0, 118, 29);	// 테두리 인터페이스
	gotoxy(33, 28);
	printf("* Emergency Patient Information Exchange Program *");

	make_frame(30, 5, 55, 20);		// 중형 사이즈 인터페이스 3
	gotoxy(43, 5);
	printf("  An Emergency Patient Report   ");

	gotoxy(52, 2);	// 현 카테고리 표시 인터페이스 + 노랑 글씨
	color(14);
	printf("응급환자 신고");
	color(15);	// 컬러 전환

	gotoxy(35, 7);
	printf("* 아래 중 해당하는 증상을 선택하여 주십시오 *");		// 버튼 고쳐야 할 부분!
	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(35, 9 + i);
		printf("%s", data[i]);
	}
	int cur = 0;//41 75 14~+2
	char in;
	while (1)
	{
		for (int i = 9; i < cnt + 9; i++)
		{
			if (i == cur + 9)
			{
				gotoxy(33, i);
				printf("●");
			}
			else
			{
				gotoxy(33, i);
				printf("○");
			}
			gotoxy(0, 0);
		}
		in = _getch();
		if (in == ENTER) return code[cur];
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
}
triage func_KTAS3(char* code)
{
	triage tri;
	FILE* fp = fopen(".\\disease_code\\code.csv", "rb");
	if (fp == NULL) {
		printf("NO FILE");
		system("pause");
	}
	skip_utf8_bom(fp);
	char data[200];
	char tmp[1024];
	while (!feof(fp)) {
		fgets(tmp, 1023, fp);
		char* ptr = strtok(tmp, ",");
		if (!strcmp(ptr, code))
		{
			ptr = strtok(NULL, ",");
			strcpy(data, ptr);
			ptr = strtok(NULL, ",");
			tri.sev = atoi(ptr);
			strcpy(tri.dis, data);
			return tri;
		}
	}
}