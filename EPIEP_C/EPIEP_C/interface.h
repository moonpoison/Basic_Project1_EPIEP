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

void make_frame(int, int, int, int);	//x, y좌표, 생성값(최대 118, 28)		
int menu_select(int); //메뉴 선택 인터페이스
char* interface_menu(int);	//메뉴 인터페이스 생성
char* interface_enter(char* stat); //어떤 인터페이스로 진입할지 정하는 함수
char* interface_func1();	//응급환자 정보 전송 인터페이스 생성(구급대원)
void interface_func1_1(char* tmp);
char* interface_func2();	//환자 정보 열람 인터페이스 생성
void interface_func2_2(char*);
char* interface_func3();	//병원 정보 열람 인터페이스 생성
char* interface_func4();	//권한변경 인터페이스 생성(관리자용)
void interface_func4_1(char*);
char* interface_func5(User*, int);
void interface_func6(HPaitient*, char*, int);
int interface_func7(HPaitient* hp, char* hos, int cnt);
void interface_exit();