#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"interface.h"
#include"func.h"
#include<winsock2.h>

void login_frame()
{
	make_frame(42, 13, 35, 6);
	gotoxy(45, 15);
	printf("USER ID : ");
	gotoxy(45, 17);
	printf("USER PW : ");
	gotoxy(55, 13);
	printf("   LOGIN   ");
}

void login_input(SOCKET sock)
{
	char ID[50];
	char PW[50];
	gotoxy(55, 15);
	scanf("%s", ID);
	send(sock, ID, strlen(ID), 0);
	gotoxy(55, 17);
	scanf("%s", PW);
	send(sock, PW, strlen(PW), 0);
}

void login_show(SOCKET sock, int tmp)
{
	system("cls");
	if (tmp == 1)
	{
		gotoxy(47, 21);
		color(4);
		printf("* 잘못된 ID 혹은 PW 입니다. *");
		color(7);
	}
	login_frame();
	gotoxy(35, 10);
	printf("* EMERGENCY PATIENT INFORMATION EXCHANGE PROGRAM *");
	login_input(sock);
}