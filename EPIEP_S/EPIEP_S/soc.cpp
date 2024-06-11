//참조: http://remocon33.tistory.com/465
//개발목적 : 온라인 학생정보 서비스 서버
#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용

#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include"soc.h"

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];// Array for sockets which are connected to clients
HANDLE hMutex;// Mudex Handle
int std_cnt = 0;

void initiating_server()
{
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread;
	int portNum;
	printf("Server : Set Server Port number (Please use integer number between 49152 to 65535) : ");
	scanf("%d", &portNum);
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //하나의 소켓을 생성한다.
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(portNum);
	bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	// End of Server Socket Preparation and Activation	
	listen(serverSock, 5);  // 5 refers the size of queue which is waiting area of connection requestion from client
	printf("Server : Ready to Client Connection\n");
	while (1) {
		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
		ReleaseMutex(hMutex);//뮤텍스 중지
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
		// _beginthreadex함수는 세번째 파라메터가 스레드로서 실행될 함수명, 네번째 파라메터가 해당 함수 호출 시 필요한 매개변수임 
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}
	closesocket(serverSock);//생성한 소켓을 끈다.
	WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
	int strLen = 0, i;
	char msg[BUF_SIZE] = "";
	char result[30] = "";

	while (1) { //클라이언트로부터 메시지를 받을때까지 기다린다.
		strcpy(msg, "");
		strLen = 0;
		strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
		msg[strLen] = '\0';
		printf("Server : Resieved Message -> %s\n", msg);  //확인용 
		if (!strcmp(msg, "q")) {
			send(clientSock, "q", 1, 0);
			break;
		}

		else {          //Client는 찾고자 하는 학생의 이름만 보낸다고 가정 
			for (i = 0; i < std_cnt; i++) {
				if (strcmp(msg, students[i].name) == 0) {
					sprintf(result, "%s,%d,%s,%s", students[i].name, students[i].age, students[i].nation, students[i].depart);
					send(clientSock, result, strlen(result), 0);
					printf("Send Result\n");
					break;
				}
			}
			if (i == std_cnt) {
				sprintf(result, "No Result");
				send(clientSock, result, strlen(result), 0);
				printf("Send No Result Message\n");
			}
		}
	}

	printf("client left the Server\n");
	//이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i < clientCount; i++) {//배열의 갯수만큼
		if (clientSock == clientSocks[i]) {//만약 현재 clientSock값이 배열의 값과 같다면
			while (i++ < clientCount - 1)//클라이언트 개수 만큼
				clientSocks[i] = clientSocks[i + 1];//앞으로 땡긴다.
			break;
		}
	}
	clientCount--;//클라이언트 개수 하나 감소
	ReleaseMutex(hMutex);//뮤텍스 중지
	closesocket(clientSock);//소켓을 종료한다.
	return 0;
}