#pragma once
typedef struct
{
	int sev;
	char dis[100];
}triage;
void skip_utf8_bom(FILE* file);
void gotoxy(int x, int y);	//좌표 설정
void color(int color);	//글자 색 변경
char func_KTAS1(char* root);
char* func_KTAS2(char* root);
triage func_KTAS3(char* code);