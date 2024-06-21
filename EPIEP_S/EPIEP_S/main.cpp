//����: http://remocon33.tistory.com/465
//���߸��� : �¶��� �л����� ���� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� ���ϰ��� ��� ���ÿ�
#define _CRT_SECURE_NO_WARNINGS  //���־�Ʃ��� ȯ�濡�� ���߽� �Է°��� ��� ���ÿ�
#pragma comment(lib, "ws2_32")  //���־�Ʃ��� ȯ�濡�� ���߽� ���� ���̺귯�� ������

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

typedef struct //����� ID/PW�� �����ϴ� ����ü
{
	char ID[20];
	char PW[20];
	int author;
	char hos[10];
}User;

typedef struct //ȯ���� ������ �����ϴ� ����ü
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

typedef struct //���� ȯ���� ������ �����ϴ� ����ü
{
	char name[20];
	char ident[20];
	int age;
	char sexual[10];
	char disease[50];
	int triage;
}HPaitient;

typedef struct //������ ������ �����ϴ� ����ü
{
	char name[20];
	int dep;
	char locate;
	int bed_all;
	int bed_use;
	int is_noti;
	char noti[30];
}Hospital;

char distance_min[9][9] = { //�� ����� �ִܰŸ��� ��Ÿ���� �迭(node to node)
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
int H_cnt = 0; //������ ��
int P_cnt = 0; //ȯ���� ��
int HP_cnt = 0; //���� ȯ���� ��
int U_cnt = 0; //������� ��
FILE* FHos, * FPait, * FUser;//���������ͺ����Ǽ���

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
	return 0;
}
//���Ϸκ����б�
void setUserData(FILE* fp)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Initiation of USER Data Load \n");
	while (!feof(fp)) {
		fscanf(fp, "%s\t%s\t%d\t%[^\n]", &user[U_cnt].ID, &user[U_cnt].PW, &user[U_cnt].author, user[U_cnt].hos); 
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
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%d\t%[^\n]", paitient[P_cnt].name, paitient[P_cnt].ident, &paitient[P_cnt].age, paitient[P_cnt].sexual, &paitient[P_cnt].disease, &paitient[P_cnt].is_noti, paitient[P_cnt].noti, paitient[H_cnt].noti); //���Ϸκ����б�
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
		fscanf(fp, "%s\t%d\t%c\t%d\t%d\t%d\t%[^\n]", hospital[H_cnt].name, &hospital[H_cnt].dep, &hospital[H_cnt].locate, &hospital[H_cnt].bed_all, &hospital[H_cnt].bed_use, &hospital[H_cnt].is_noti, hospital[H_cnt].noti); //���Ϸκ����б�
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
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%d", hp[HP_cnt].name, hp[HP_cnt].ident, &hp[HP_cnt].age, hp[HP_cnt].sexual, hp[HP_cnt].disease, &hp[HP_cnt].triage); //���Ϸκ����б�
		if(strcmp(hp[HP_cnt].name, hp[HP_cnt-1].name)) ++HP_cnt;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

void reHPData(FILE* fp) //���� ȯ���� ������ ���輺�ϴ� �Լ�(1~5�� �� 3���� �������� �ٲܼ� ���� ��ü�� ���ۼ��ϴ� ���
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("Server : Rewrite Hos Paitient Data Load \n");
	int i = 0;
	while (i!=HP_cnt) {
		fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%s\t%d", hp[i].name, hp[i].ident, &hp[i].age, hp[i].sexual, hp[i].disease, &hp[i].triage); //���Ϸκ����б�
		if (i + 1 != HP_cnt) fprintf(fp, "\n");
		i++;
	}
	printf("Server : End of Data Loading \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

int check_ID(char *id, char *pw)  //ID, PW�� Ȯ���ϴ� �Լ�
{
	for (int i = 0; i < U_cnt; ++i)
	{
		printf("%s %s\n", id, user[i].ID);
		if (!strcmp(id, user[i].ID)) //ID�� ��ġ�ϸ�...
		{
			if (!strcmp(pw, user[i].PW))//PW�� ��ġ�Ѵٸ�...
			{
				return i;
			}
		}
	}
	return 999; //UserID.txt�� ��ġ�ϴ� ������ ���� ��� ��ȯ�ϴ� ��(�α��� ���� ��ȯ)
}

unsigned WINAPI HandleClient(void* arg) {
	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
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
		strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);//ID���޹���
		msg[strLen] = '\0';
		printf("Server : Resieved Message -> %s\n", msg);
		if (strcmp(msg, ""))
		{
			strcpy(in_id, msg);
			while (1)
			{
				strcpy(msg, "");
				strLen = 0;
				strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);//PW���޹���
				msg[strLen] = '\0';
				printf("Server : Resieved Message -> %s\n", msg);
				if (strcmp(msg, ""))
				{
					strcpy(in_pw, msg);
					int i = check_ID(in_id, in_pw); //ID, PW ����
					strcpy(result, "");
					if (i == 999) _itoa(999, result, 10);//999�� ��ȯ
					else _itoa(user[i].author, result, 10);//author�� ��ȯ
					if (user[i].author == 1)
					{
						strcat(result, " ");
						strcat(result, user[i].hos);
					}
					send(clientSock, result, strlen(result), 0);
					break;
				}
			}
			if (author != 999) break; //�α��� ������ �ƴ϶�� �α�����Ʈ Ż��
		}
	}
	if (author != 999)
	{
		while (1) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���.
			strLen = -1;
			strcpy(msg, "");
			char dis[100];
			while(strLen==-1)
				strLen=recv(clientSock, msg, BUF_SIZE - 1, 0); //����� ����� �Է¹���
			msg[strLen] = '\0';
			printf("Server : Resieved Message -> %s\n", msg);
			if (!strcmp(msg, "func1"))//ȯ����������
			{
				Paitient p;
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
					if (strcmp(msg, ""))
					{
						char* ptr = strtok(msg, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
						strcpy(p.name, ptr);
						ptr = strtok(NULL, " ");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
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
				int min_cost=999;//�Ÿ����
				char target[20]="asd";//�����̸�
				/*�����*/
				if (p.triage == 1 || p.triage == 2) //�ǿ��ǷἾ�ͷ� �����Ѵٸ�
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
				else if (p.triage == 2 || p.triage == 3) //�����ǷἾ�ͷ� �����Ѵٸ�
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
				else  //�����Ƿ������� �����Ѵٸ�
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
				/*��º�*/
				min_cost = min_cost * 10 / 6;
				sprintf(result, "%d %s", min_cost, target);
				send(clientSock, result, strlen(result), 0);
				printf("Send Result\n");

				strcat(target, ".txt");
				FILE* fp = fopen(target, "a+");
				if (ftell(fp) != 0) fprintf(fp, "\n");
				fprintf(fp, "%s\t%s\t%d\t%s\t%s\t%d", p.name, p.ident, p.age, p.sexual, dis, p.triage);
			}
			else if (!strcmp(msg, "func2"))//������Ȳ����
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0); //�������� �Է¹���
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
					int flag = 0;
					if (strcmp(msg, ""))
					{
						for (i = 0; i < H_cnt; ++i)
						{
							if (!strcmp(hospital[i].name, msg)) //������ ������Ȳ�� ������
							{
								if(hospital[i].is_noti) sprintf(result, "\"%s\"������ ���� ��Ȳ�� %d/%d�Դϴ�.\nƯ�̻��� : %s", hospital[i].name, hospital[i].bed_use, hospital[i].bed_all, hospital[i].noti);
								else sprintf(result, "\"%s\"������ ���� ��Ȳ�� %d/%d�Դϴ�.\nƯ�̻��� : ����", hospital[i].name, hospital[i].bed_use, hospital[i].bed_all);
								flag++;
								break;
							}
						}
						if (flag)
						{
							send(clientSock, result, strlen(result), 0);
							printf("Send Result\n");
						}
						else //�������� ã�� ���Ͽ��� ���(����ó��)
						{
							send(clientSock, "can't search that hospital", strlen(result), 0);
							printf("Send Result...can't search that hospital\n");
						}
					}
					break;
				}
			}
			else if (!strcmp(msg, "func3"))//����Ư�̻��� ����
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0); //�������� ���޹���
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
					char in_hos[20], in_noti[30];
					char* ptr = strtok(msg, " ");     
					strcpy(in_hos, ptr);
					ptr = strtok(NULL, "\n");
					strcpy(in_noti, ptr);
					printf("���� : %s, Ư�̻��� : %s", in_hos, in_noti); //Ư�̻����� �ش� ������ ���
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
			else if (!strcmp(msg, "func4"))//�����Ͽ�û
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0); //ȯ���� �̸��� �Է¹���
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
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
						else //ȯ���� �̸��� ã�� �� ���� ���(����ó��)
						{
							send(clientSock, "can't search that paitient", strlen("can't search that paitient"), 0);
							printf("Send Result...can't search that paitient\n");
						}
						break;
					}
				}
			}
			else if (!strcmp(msg, "func5"))//���Ѻ���(�����ڿ�)
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
				send(clientSock, result, strlen(result), 0); //UserID.txt�� �����ϴ� ������ ����(Ŭ���̾�Ʈ�� �ش� ������ ���� ���� ����)
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0); //UserID.txt�� �����ϴ� ID�� ���޹���
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
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
							if (!strcmp(user[i].ID, in_id)) //�����ϴ� ID�� ã�Ƽ� �ش� ID�� ������ ����
							{
								user[i].author = in_author;
							}
						}
						break;
					}
				}
			}
			else if (!strcmp(msg, "func6")) //����ȯ�� ��Ȳ��ȸ
			{
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0); //Ŭ���̾�Ʈ�� � �������� �������� ���޹���(�ٸ� ������ ȯ�� ������ ���� ������ ���� ����)
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);
					if (strcmp(msg, ""))
					{
						char hos[10];
						strcpy(hos, msg);
						strcat(hos, ".txt"); //���޹��� ������ .txt�� �ٿ� �ش��ϴ� ���� ������ ��
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
						printf("%s", result);
						send(clientSock, result, strlen(result), 0); //���� txt���Ͽ� �����ϴ� �����͸� ����
						break;
					}
				}
			}
			else if (!strcmp(msg, "func7")) //����ȯ�� ����Ϸ� ó��(func6���� ȯ�ڸ� ��� �ش� ȯ�ڸ� ����
			{
				char hos[10];
				while (1)
				{
					strcpy(msg, "");
					strLen = 0;
					strLen = recv(clientSock, msg, BUF_SIZE - 1, 0);
					msg[strLen] = '\0';
					printf("Server : Resieved Message -> %s\n", msg);  //Ȯ�ο� 
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
					printf("Server : Resieved Message -> %s\n", msg); 
					if (strcmp(msg, ""))
					{
						int a;
						a = atoi(msg);
						for (int i = a; i < HP_cnt-1; ++i)//�ش��ϴ� ȯ�� ���ֱ�
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
			else if (!strcmp(msg, "func0")) //����
			{
				break;
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