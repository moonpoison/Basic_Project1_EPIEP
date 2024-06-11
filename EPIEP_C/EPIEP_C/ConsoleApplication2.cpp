#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <string.h>

#define BUF_SIZE 100

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char serverIp[100];
	int  portNum;

	printf("Input server IP : ");
	gets_s(serverIp);

	printf("Input server port : ");
	scanf("%d", &portNum);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverIp);
	serverAddr.sin_port = htons(portNum);

	connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	//접속에 성공하면 이 줄 아래가 실행된다.

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다.
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.
	//클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.

	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char msg[BUF_SIZE] = "";
	while (1) {//반복
		gets_s(msg);//입력을 받는다.
		if (!strcmp(msg, "q")) {//q를 입력하면 종료한다.
			send(sock, "q", 1, 0);//Msg를 서버에게 전송한다.
			strcpy(msg, "");
		}
		else {
			send(sock, msg, strlen(msg), 0);//Msg를 서버에게 전송한다.
			strcpy(msg, "");
		}

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


