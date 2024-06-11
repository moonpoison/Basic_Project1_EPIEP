//참조: http://remocon33.tistory.com/465
//개발목적 : 온라인 학생정보 서비스 서버
#define _WINSOCK_DEPRECATED_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 소켓관련 경고 무시용
#define _CRT_SECURE_NO_WARNINGS  //비주얼스튜디오 환경에서 개발시 입력관련 경고 무시용
#pragma comment(lib, "ws2_32")  //비주얼스튜디오 환경에서 개발시 소켓 라이브러리 지정용

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <process.h>
#include <Windows.h>
#include <string.h>


#define BUF_SIZE 1024
#define MAX_CLNT 256
#define STD_MAX_NUM 100
#define WHITE 15
#define YELLOW 6
#define BLUE 9
#define GREEN 2

typedef struct
{
	char ID[20];
	char PW[20];
	int author;
	char hos[10];
}User;

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

typedef struct
{
	char name[20];
	char ident[20];
	int age;
	char sexual[10];
	char disease[50];
	int triage;
}HPaitient;

typedef struct
{
	char name[20];
	int dep;
	char locate;
	int bed_all;
	int bed_use;
	int is_noti;
	char noti[30];
}Hospital;

char distance_min[9][9] = { //각 노드의 최단거리를 나타내는 배열(node to node)
	{0, 1, 3, 7, 9, 12, 19, 20, 22},
	{1, 0, 2, 8, 8, 11, 20, 19, 21},
	{3, 2, 0, 10, 10, 9, 22, 21, 19},
	{7, 8, 10, 0, 3, 7, 12, 14, 17},
	{9, 8, 10, 3, 0, 4, 15, 11, 14},
	{12, 11, 9, 7, 4, 0, 19, 15, 10},
	{19, 20, 22, 12, 15, 19, 0, 5, 11},
	{20, 19, 21, 14, 11, 15, 5, 0, 6},
	{22, 21, 19, 17, 14, 10, 11, 6, 0}
};

void setUserData(FILE* fp);
void setPaitData(FILE* fp);
void setHosData(FILE* fp);

unsigned WINAPI HandleClient(void* arg);//Thread for Each CLient

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];// Array for sockets which are connected to clients
HANDLE hMutex;// Mudex Handle

User user[STD_MAX_NUM];
Paitient paitient[STD_MAX_NUM];
HPaitient hp[STD_MAX_NUM];
Hospital hospital[STD_MAX_NUM];
int H_cnt = 0;
int P_cnt = 0;
int HP_cnt = 0;
int U_cnt = 0;
FILE* FHos, * FPait, * FUser;//파일포인터변수의선언

int main(int argc, char* argv[]) {

	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread;
	int portNum=55555;

	// Start of Students Information Loading form the file
	if ((FHos = fopen("HospitalDB.txt", "r+")) == NULL) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("File open error...\n");
		exit(-1);
	}
	setHosData(FHos);
	if ((FPait = fopen("Paitient.txt", "r+")) == NULL) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("File open error...\n");
		exit(-1);
	}
	setPaitData(FPait);
	if ((FUser = fopen("UserID.txt", "r+")) == NULL) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("File open error...\n");
		exit(-1);
	}
	setUserData(FUser);
	// End of Students Information Load

	// Start of Server Socket Preparation
	printf("Server : Set Server Port number (Please use integer number between 49152 to 65535) : ");
	//scanf("%d", &portNum);
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
	return 0;
}

void setUserData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Initiation of USER Data Load \n");
	while (!feof(fp)) {
		fscanf(fp, "%s\t%s\t%d\t%[^\n]", &user[U_cnt].ID, &user[U_cnt].PW, &user[U_cnt].author, user[U_cnt].hos); //파일로부터읽기
		++U_cnt;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void setPaitData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Initiation of PAITIENT Data Load \n");
	while (!feof(fp)) {
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%d\t%[^\n]", paitient[P_cnt].name, paitient[P_cnt].ident, &paitient[P_cnt].age, paitient[P_cnt].sexual, &paitient[P_cnt].disease, &paitient[P_cnt].is_noti, paitient[P_cnt].noti, paitient[H_cnt].noti); //파일로부터읽기
		++P_cnt;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void setHosData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Initiation of HOSPITAL Data Load \n");
	while (!feof(fp)) {
		fscanf(fp, "%s\t%d\t%c\t%d\t%d\t%d\t%[^\n]", hospital[H_cnt].name, &hospital[H_cnt].dep, &hospital[H_cnt].locate, &hospital[H_cnt].bed_all, &hospital[H_cnt].bed_use, &hospital[H_cnt].is_noti, hospital[H_cnt].noti); //파일로부터읽기
		++H_cnt;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void setHpData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Initiation of Hos Paitient Data Load \n");
	while (!feof(fp)) {
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%d", hp[HP_cnt].name, hp[HP_cnt].ident, &hp[HP_cnt].age, hp[HP_cnt].sexual, hp[HP_cnt].disease, &hp[HP_cnt].triage); //파일로부터읽기
		if(strcmp(hp[HP_cnt].name, hp[HP_cnt-1].name)) ++HP_cnt;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
/*주경수	123123-1234123	31	남	안와골절	3
김지수	123323-1245152	23	여	비문증	5*/
void reHPData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Rewrite Hos Paitient Data Load \n");
	int i = 0;
	while (i!=HP_cnt) {
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%s\t%d", hp[i].name, hp[i].ident, &hp[i].age, hp[i].sexual, hp[i].disease, &hp[i].triage); //파일로부터읽기
		if (i + 1 != HP_cnt) fprintf(fp, "\n");
		i++;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

int check_ID(char *id, char *pw)
{
	for (int i = 0; i < U_cnt; ++i)
	{
		printf("%s %s\n", id, user[i].ID);
		if (!strcmp(id, user[i].ID))
		{
			printf("%s %s\n", pw, user[i].PW);
			if (!strcmp(pw, user[i].PW))
			{
				return i;
			}
		}
	}
	return 999;
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
	int strLen = 0, i;
	char msg[BUF_SIZE] = "";
	char result[1024] = "";
	char location;
	char in_id[20], in_pw[20];
	int author = -1;
	while (1)
	{
		strcpy(msg, "");
		strLen = 0;
		strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
		msg[strLen] = '\0';
		printf("Server : Resieved Message -> %s\n", msg);  //확인용 
		if (strcmp(msg, ""))
		{
			strcpy(in_id, msg);
			while (1)
			{
				strcpy(msg, "");
				strLen = 0;
				strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
				msg[strLen] = '\0';
				printf("Server : Resieved Message -> %s\n", msg);  //확인용 
				if (strcmp(msg, ""))
				{
					strcpy(in_pw, msg);
					int i = check_ID(in_id, in_pw);
					strcpy(result, "");
					if (i == 999) _itoa(999, result, 10);
					else _itoa(user[i].author, result, 10);
					if (user[i].author == 1)
					{
						strcat(result, " ");
						strcat(result, user[i].hos);
					}
					send(clientSock, result, strlen(result), 0);
					break;
				}
			}
			if (author != 999) break;
		}
	}
	if (author != 999)
	{
		while (1) { //클라이언트로부터 메시지를 받을때까지 기다린다.
			strLen = -1;
			strcpy(msg, "");
			char dis[100];
			while(strLen==-1)
				strLen=recv(clientSock, msg, BUF_SIZE - 1, 0);
			msg[strLen] = '\0';
			printf("Server : Resieved Message -> %s\n", msg);  //확인용 
			if (!strcmp(msg, "func1"))//환자정보전달
			{
				Paitient p;
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					if (strcmp(msg, ""))
					{
						char* ptr = strtok(msg, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
						strcpy(p.name, ptr);
						ptr = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
						strcpy(p.ident, ptr);
						ptr = strtok(NULL, " ");
						p.age = atoi(ptr);
						ptr = strtok(NULL, " ");
						strcpy(p.sexual, ptr);
						ptr = strtok(NULL, " ");
						strcpy(p.code, ptr);
						ptr = strtok(NULL, " ");
						p.triage = atoi(ptr);
						ptr = strtok(NULL, " ");
						p.is_noti = atoi(ptr);
						if (p.is_noti == 0)
						{
							ptr = strtok(NULL, " ");
							strcpy(p.noti, ptr);
						}
						ptr = strtok(NULL, " ");
						location = *ptr;
						ptr = strtok(NULL, "\n");
						strcpy(dis, ptr);
						printf("%s, %s, %d, %s, %s, %d, %d, %s, %c, %s", p.name, p.ident, p.age, p.sexual, p.code, p.triage, p.is_noti, p.noti, location, dis);
						break;
					}
				}
				int min_cost=999;//거리대비
				char target[20]="asd";//병원이름
				/*연산부*/
				if (p.triage == 1 || p.triage == 2)
				{
					for (int i = 0; i < H_cnt; ++i)
					{
						if (hospital[i].dep == 1)
						{
							int a = location - 'A';
							int b = hospital[i].locate - 'A';
							if (min_cost > distance_min[a][b])
							{
								if (hospital[i].bed_use != hospital[i].bed_all)
								{
									min_cost = distance_min[a][b];
									strcpy(target, hospital[i].name);
								}
							}
						}
					}
				}
				else if (p.triage == 2 || p.triage == 3)
				{
					for (int i = 0; i < H_cnt; ++i)
					{
						if (hospital[i].dep == 2)
						{
							int a = location - 'A';
							int b = hospital[i].locate - 'A';
							if (min_cost > distance_min[a][b])
							{
								if (hospital[i].bed_use != hospital[i].bed_all)
								{
									min_cost = distance_min[a][b];
									strcpy(target, hospital[i].name);
								}
							}
						}
					}
				}
				else
				{
					for (int i = 0; i < H_cnt; ++i)
					{
						if (hospital[i].dep == 3)
						{
							int a = location - 'A';
							int b = hospital[i].locate - 'A';
							if (min_cost > distance_min[a][b])
							{
								if (hospital[i].bed_use != hospital[i].bed_all)
								{
									min_cost = distance_min[a][b];
									strcpy(target, hospital[i].name);
								}
							}
						}
					}
				}
				/*출력부*/
				min_cost = min_cost * 10 / 6;
				sprintf(result, "%d %s", min_cost, target);
				send(clientSock, result, strlen(result), 0);
				printf("Send Result\n");

				strcat(target, ".txt");
				FILE* fp = fopen(target, "a+");
				if (ftell(fp) != 0) fprintf(fp, "\n");
				fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%d", p.name, p.ident, p.age, p.sexual, dis, p.triage);
			}
			else if (!strcmp(msg, "func2"))//내원현황전달
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					int flag = 0;
					if (strcmp(msg, ""))
					{
						for (i = 0; i < H_cnt; ++i)
						{
							if (!strcmp(hospital[i].name, msg))
							{
								if(hospital[i].is_noti) sprintf(result, "\"%s\"병원의 내원 현황은 %d/%d입니다.\n특이사항 : %s", hospital[i].name, hospital[i].bed_use, hospital[i].bed_all, hospital[i].noti);
								else sprintf(result, "\"%s\"병원의 내원 현황은 %d/%d입니다.\n특이사항 : 없음", hospital[i].name, hospital[i].bed_use, hospital[i].bed_all);
								flag++;
								break;
							}
						}
						if (flag)
						{
							send(clientSock, result, strlen(result), 0);
							printf("Send Result\n");
						}
						else
						{
							send(clientSock, "can't search that hospital", strlen(result), 0);
							printf("Send Result...can't search that hospital\n");
						}
					}
				}
			}
			else if (!strcmp(msg, "func3"))//병원특이사항 전달
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용
					char in_hos[20], in_noti[30];
					char* ptr = strtok(msg, " ");     
					strcpy(in_hos, ptr);
					ptr = strtok(NULL, "\n");
					strcpy(in_noti, ptr);
					printf("병원 : %s, 특이사항 : %s", in_hos, in_noti);
					for (i = 0; i < H_cnt; ++i)
					{
						if (!strcmp(hospital[i].name, in_hos))
						{
							strcpy(hospital[i].noti, in_noti);
							hospital[i].is_noti = 1;
						}
					}
					break;
				}
			}
			else if (!strcmp(msg, "func4"))//진료기록요청
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					int flag = 0;
					if (strcmp(msg, ""))
					{
						for (i = 0; i < P_cnt; ++i)
						{
							if (!strcmp(paitient[i].name, msg))
							{
								sprintf(result, "%s %s %d %s %s %d %s", paitient[i].name, paitient[i].ident, paitient[i].age, paitient[i].sexual, paitient[i].disease, paitient[i].is_noti, paitient[i].noti);
								flag++;
								break;
							}
						}
						if (flag!=0)
						{
							send(clientSock, result, strlen(result), 0);
							printf("Send Result\n");
						}
						else
						{
							send(clientSock, "can't search that paitient", strlen("can't search that paitient"), 0);
							printf("Send Result...can't search that paitient\n");
						}
						break;
					}
				}
			}
			else if (!strcmp(msg, "func5"))//권한변경(관리자용)
			{
				strcpy(result, "");
				for (i = 0; i < U_cnt; ++i)
				{
					char tmp[50];
					strcpy(tmp, user[i].ID);
					strcat(tmp, " ");
					char ptr[2];
					_itoa(user[i].author, ptr, 10);
					strcat(tmp, ptr);
					if(i+1!=U_cnt) strcat(tmp, " ");
					strcat(result, tmp);
				}
				send(clientSock, result, strlen(result), 0);
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					int flag = 0;
					if (strcmp(msg, ""))
					{
						char *ptr=strtok(msg, " ");
						int in_author;
						char in_id[20];
						strcpy(in_id, ptr);
						ptr=strtok(NULL, " ");
						in_author = atoi(ptr);
						for (i = 0; i < U_cnt; ++i)
						{
							if (!strcmp(user[i].ID, in_id))
							{
								user[i].author = in_author;
							}
						}
						break;
					}
				}
			}
			else if (!strcmp(msg, "func6")) //내원환자 현황조회
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					if (strcmp(msg, ""))
					{
						char hos[10];
						strcpy(hos, msg);
						strcat(hos, ".txt");
						FILE* fp = fopen(hos, "r+");
						HP_cnt = 0;
						setHpData(fp);
						strcpy(result, "");
						for (int i = 0; i < HP_cnt; ++i)
						{
							char tmp[BUF_SIZE];
							sprintf(tmp, "%s %s %d %s %s %d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
							if (i + 1 != HP_cnt) strcat(tmp, " ");
							strcat(result, tmp);
						}
						printf("Send Result\n", result);
						send(clientSock, result, strlen(result), 0);
						break;
					}
				}
			}
			else if (!strcmp(msg, "func7")) //내원환자 현황조회
			{
				char hos[10];
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					if (strcmp(msg, ""))
					{
						strcpy(hos, msg);
						strcat(hos, ".txt");
						FILE* fp = fopen(hos, "r+");
						HP_cnt = 0;
						setHpData(fp);
						strcpy(result, "");
						for (int i = 0; i < HP_cnt; ++i)
						{
							char tmp[BUF_SIZE];
							sprintf(tmp, "%s %s %d %s %s %d", hp[i].name, hp[i].ident, hp[i].age, hp[i].sexual, hp[i].disease, hp[i].triage);
							if (i + 1 != HP_cnt) strcat(tmp, " ");
							strcat(result, tmp);
						}
						printf("Send Result\n", result);
						send(clientSock, result, strlen(result), 0);
						break;
					}
				}
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //확인용 
					if (strcmp(msg, ""))
					{
						int a;
						a = atoi(msg);
						for (int i = a; i < HP_cnt-1; ++i)
						{
							strcpy(hp[i].name, hp[i + 1].name);
							strcpy(hp[i].ident, hp[i + 1].ident);
							hp[i].age = hp[i + 1].age;
							strcpy(hp[i].sexual, hp[i + 1].sexual);
							strcpy(hp[i].disease, hp[i + 1].disease);
							hp[i].triage = hp[i + 1].triage;
						}
						HP_cnt--;
						FILE* fp = fopen(hos, "w");
						reHPData(fp);
						break;
					}
				}
			}
			else if (!strcmp(msg, "func0")) //종료
			{
				break;
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