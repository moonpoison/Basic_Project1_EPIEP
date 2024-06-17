#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")

#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<process.h>
#include"func.h"
#include"interface.h"
#include"login.h"

#define BUF_SIZE 1024

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수

int main()
{
	/*connecting server*/
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char serverIp[100]="127.0.0.1";
	int  portNum=55555;

	printf("Input server IP : ");
	//gets_s(serverIp);

	printf("Input server port : ");
	//scanf("%d", &portNum);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	serverAddr.sin_port = htons(portNum);

	connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//접속에 성공하면 이 줄 아래가 실행된다.

	int author=-1; //권한등급
	char tmp[BUF_SIZE];
	char hos[10];

	int login_flag = 0;
	while (1)
	{
		login_show(sock, login_flag);
		int len=recv(sock, tmp, BUF_SIZE - 1, 0);
		tmp[len] = '\0';
		printf("%s", tmp);
		char* ptr;
		ptr=strtok(tmp, " ");
		author = atoi(ptr);
		if (author == 1)
		{
			ptr = strtok(NULL, " ");
			strcpy(hos, ptr);
		}
		printf("%d\n", author);
		if (author != 999) break;
		else login_flag = 1;
	}
	while (1)
	{
		strcpy(tmp, interface_menu(author)); //몇번째 창 선택한지
		send(sock, tmp, strlen(tmp), 0);
		if (!strcmp(tmp, "func1"))
		{
			strcpy(tmp, interface_enter(tmp));
			send(sock, tmp, strlen(tmp), 0);
			strcpy(tmp, "");
			int len=recv(sock, tmp, BUF_SIZE - 1, 0);
			tmp[len] = '\0';
			interface_func1_1(tmp);
		}
		else if(!strcmp(tmp, "func2"))
		{
			strcpy(tmp, interface_enter(tmp));
			send(sock, tmp, strlen(tmp), 0);
			int len = recv(sock, tmp, BUF_SIZE - 1, 0);
			tmp[len] = '\0';
			interface_func2_2(tmp);
		}
		else if (!strcmp(tmp, "func3"))
		{
			strcpy(tmp, interface_enter(tmp));
			send(sock, tmp, strlen(tmp), 0);
		}
		else if (!strcmp(tmp, "func4"))
		{
			int flag = 0;
			strcpy(tmp, interface_enter(tmp));
			send(sock, tmp, strlen(tmp), 0);
			int len = -1;
			while (len == -1)
				len = recv(sock, tmp, BUF_SIZE - 1, 0);
			tmp[len] = '\0';
			if (strcmp(tmp, "can't search that paitient")) interface_func4_1(tmp);
		}
		else if (!strcmp(tmp, "func5"))
		{
			int len = -1;
			User user[20];
			while (len ==-1)
			{
				len = recv(sock, tmp, BUF_SIZE - 1, 0);
			}
			system("cls");
			printf("%s", tmp);
			if(len>=0) tmp[len] = '\0';
			char* ptr = strtok(tmp, " ");
			int cnt=0;
			while(ptr!=NULL)
			{
				strcpy(user[cnt].ID, ptr);
				ptr=strtok(NULL, " ");
				user[cnt].author = atoi(ptr);
				ptr = strtok(NULL, " ");
				++cnt;
			}
			strcpy(tmp, interface_func5(user, cnt));
			send(sock, tmp, strlen(tmp), 0);
			strcpy(tmp, "");
		}
		else if (!strcmp(tmp, "func6"))
		{
			strcpy(tmp, hos);
			send(sock, tmp, strlen(tmp), 0);
			HPaitient hp[50];
			int len = -1;
			while (len == -1)
				len = recv(sock, tmp, BUF_SIZE - 1, 0);
			if (len >= 0) tmp[len] = '\0';
			printf("%s", tmp);
			char* ptr = strtok(tmp, " ");
			int cnt = 0;
			while (ptr != NULL)
			{
				strcpy(hp[cnt].name, ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].ident, ptr);
				ptr = strtok(NULL, " ");
				hp[cnt].age = atoi(ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].sexual, ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].disease, ptr);
				ptr = strtok(NULL, " ");
				hp[cnt].triage = atoi(ptr);
				ptr = strtok(NULL, " ");
				++cnt;
			}
			interface_func6(hp, hos, cnt);
		}
		else if (!strcmp(tmp, "func7"))
		{
			strcpy(tmp, hos);
			send(sock, tmp, strlen(tmp), 0);
			HPaitient hp[50];
			int len = -1;
			while (len == -1)
				len = recv(sock, tmp, BUF_SIZE - 1, 0);
			if (len >= 0) tmp[len] = '\0';
			char* ptr = strtok(tmp, " ");
			int cnt = 0;
			while (ptr != NULL)
			{
				strcpy(hp[cnt].name, ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].ident, ptr);
				ptr = strtok(NULL, " ");
				hp[cnt].age = atoi(ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].sexual, ptr);
				ptr = strtok(NULL, " ");
				strcpy(hp[cnt].disease, ptr);
				ptr = strtok(NULL, " ");
				hp[cnt].triage = atoi(ptr);
				ptr = strtok(NULL, " ");
				++cnt;
			}
			_itoa(interface_func7(hp, hos, cnt), tmp, 10);
			send(sock, tmp, strlen(tmp), 0);
		}
		else if (!strcmp(tmp, "func0"))
		{
			interface_exit();
			return 0;
		}
	}


	//sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	//recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	//WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다.
	//WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.

	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE] = "";
	while (1) {//반복
		gets_s(msg);
		send(sock, msg, strlen(msg), 0);//Msg를 서버에게 전송한다.
		strcpy(msg, "");
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE] = "";
	int strLen;
	while (1) {//반복
		strLen = recv(sock, msg, BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		msg[strLen] = '\0';//문자열의 끝을 알리기 위해 설정
		if (!strcmp(msg, "q")) {
			printf("Client : Disconnection\n");
			closesocket(sock);
			exit(0);
		}
		else {
			printf("Result : %s\n", msg);
		}
		strcpy(msg, "");
	}
	return 0;
}
