#pragma once
typedef struct
{
	char ID[20];
	char PW[20];
	int author;
}User;

typedef struct
{
	char name[20];
	char ident[20];
	int age;
	char sexual[10];
	char disease[50];
	int triage;
}HPaitient;

void make_frame(int, int, int, int);	//x, y��ǥ, ������(�ִ� 118, 28)		
int menu_select(int); //�޴� ���� �������̽�
char* interface_menu(int);	//�޴� �������̽� ����
char* interface_enter(char* stat); //� �������̽��� �������� ���ϴ� �Լ�
char* interface_func1();	//����ȯ�� ���� ���� �������̽� ����(���޴��)
void interface_func1_1(char* tmp);
char* interface_func2();	//ȯ�� ���� ���� �������̽� ����
void interface_func2_2(char*);
char* interface_func3();	//���� ���� ���� �������̽� ����
char* interface_func4();	//���Ѻ��� �������̽� ����(�����ڿ�)
void interface_func4_1(char*);
char* interface_func5(User*, int);
void interface_func6(HPaitient*, char*, int);
int interface_func7(HPaitient* hp, char* hos, int cnt);
void interface_exit();