//����: http://remocon33.tistory.com/465
//���߸��� : �¶��� �л����� ���� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� �Է°��� ��� ���ÿ�
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������

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
	hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //�ϳ��� ������ �����Ѵ�.
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
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
		ReleaseMutex(hMutex);//���ؽ� ����
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
		// _beginthreadex�Լ��� ����° �Ķ���Ͱ� ������μ� ����� �Լ���, �׹�° �Ķ���Ͱ� �ش� �Լ� ȣ�� �� �ʿ��� �Ű������� 
		printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
	}
	closesocket(serverSock);//������ ������ ����.
	WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
	int strLen = 0, i;
	char msg[BUF_SIZE] = "";
	char result[30] = "";

	while (1) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���.
		strcpy(msg, "");
		strLen = 0;
		strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
		msg[strLen] = '\0';
		printf("Server : Resieved Message -> %s\n", msg);  //Ȯ�ο� 
		if (!strcmp(msg, "q")) {
			send(clientSock, "q", 1, 0);
			break;
		}

		else {          //Client�� ã���� �ϴ� �л��� �̸��� �����ٰ� ���� 
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
	//�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i < clientCount; i++) {//�迭�� ������ŭ
		if (clientSock == clientSocks[i]) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
			while (i++ < clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
				clientSocks[i] = clientSocks[i + 1];//������ �����.
			break;
		}
	}
	clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
	ReleaseMutex(hMutex);//���ؽ� ����
	closesocket(clientSock);//������ �����Ѵ�.
	return 0;
}