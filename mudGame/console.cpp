#include "console.h"
#pragma warning(disable:4996)

void gotoxy(SHORT x, SHORT y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//�ܼ�â ũ�� ����
void SetConsoleSize(int x, int y) {
	char command[100];
	sprintf(command, "mode con lines=%d cols=%d", y, x);
	system(command);
}

//Ŀ������
void CursorView(bool b) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1;			//Ŀ�� ����
	cursor.bVisible = b;	    //Ŀ�� visible
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

//Ű�ٿ�
bool IsKeyDown(int key) {
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}