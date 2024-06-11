#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32")

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <windows.h>
#include <string.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void error_handling(char *message);
unsigned WINAPI handle_client(void *arg);
void execute_function(char *msg, SOCKET clientSock);

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];
HANDLE hMutex;

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    SOCKET serverSock, clientSock;
    SOCKADDR_IN serverAddr, clientAddr;
    int clientAddrSize;
    HANDLE hThread;
    int portNum;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    portNum = atoi(argv[1]);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");

    hMutex = CreateMutex(NULL, FALSE, NULL);
    serverSock = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET)
        error_handling("socket() error");

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(portNum);

    if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        error_handling("bind() error");
    if (listen(serverSock, 5) == SOCKET_ERROR)
        error_handling("listen() error");

    printf("Server is ready to accept clients on port %d\n", portNum);
    while (1) {
        clientAddrSize = sizeof(clientAddr);
        clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
        if (clientSock == INVALID_SOCKET)
            error_handling("accept() error");

        WaitForSingleObject(hMutex, INFINITE);
        clientSocks[clientCount++] = clientSock;
        ReleaseMutex(hMutex);

        hThread = (HANDLE)_beginthreadex(NULL, 0, handle_client, (void*)&clientSock, 0, NULL);
        printf("Connected client IP: %s\n", inet_ntoa(clientAddr.sin_addr));
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

unsigned WINAPI handle_client(void *arg) {
    SOCKET clientSock = *((SOCKET*)arg);
    int strLen = 0, i;
    char msg[BUF_SIZE];

    while ((strLen = recv(clientSock, msg, sizeof(msg) - 1, 0)) != 0) {
        if (strLen == SOCKET_ERROR)
            return -1;

        msg[strLen] = '\0';
        printf("Received message: %s\n", msg);
        execute_function(msg, clientSock);
    }

    WaitForSingleObject(hMutex, INFINITE);
    for (i = 0; i < clientCount; i++) {
        if (clientSock == clientSocks[i]) {
            while (i++ < clientCount - 1)
                clientSocks[i] = clientSocks[i + 1];
            break;
        }
    }
    clientCount--;
    ReleaseMutex(hMutex);
    closesocket(clientSock);
    return 0;
}

void execute_function(char *msg, SOCKET clientSock) {
    if (strcmp(msg, "func1") == 0) {
        send(clientSock, "Executing Function 1\n", 21, 0);
    } else if (strcmp(msg, "func2") == 0) {
        send(clientSock, "Executing Function 2\n", 21, 0);
    } else if (strcmp(msg, "func3") == 0) {
        send(clientSock, "Executing Function 3\n", 21, 0);
    } else if (strcmp(msg, "func4") == 0) {
        send(clientSock, "Executing Function 4\n", 21, 0);
    } else if (strcmp(msg, "func5") == 0) {
        send(clientSock, "Executing Function 5\n", 21, 0);
    } else {
        send(clientSock, "Unknown function\n", 17, 0);
    }
}
