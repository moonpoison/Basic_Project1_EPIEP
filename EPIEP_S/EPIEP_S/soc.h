#pragma once
#include<winsock2.h>

#define BUF_SIZE 100 
#define MAX_CLNT 256
#define STD_MAX_NUM 100
#define WHITE 15
#define YELLOW 6
#define BLUE 9

void initiating_server();
unsigned WINAPI HandleClient(void* arg);