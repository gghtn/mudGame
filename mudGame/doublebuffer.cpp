#include "doublebuffer.h"

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

//ȭ�� ���� �ʱ�ȭ
void ScreenInit()
{
    CONSOLE_CURSOR_INFO cci;

    // ȭ�� ���� 2���� �����.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // Ŀ���� �����.
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

//Ȱ��ȭ�� ���ۿ� ��Ȱ��ȭ ���� ��ü
void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

//���۰� ȭ�鿡 ǥ�õǴ� ���� ��Ȱ��ȭ�� ���۸� ����� �Լ�
void ScreenClear()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    //(���ϴ� ��, ���ϴ� ����(' '), ���ϴ� ����, ���ϴ� Ŀ��, ���̸� ��ȯ�� ��)
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 100 * 50, Coor, &dw);
}

//(x, y)��ǥ�� string ���
void ScreenPrint(SHORT x, SHORT y, string str)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], str.c_str(), str.size(), &dw, NULL);
}

//���� Ŀ�� y��ǥ
int GetCursorPosY() {
    CONSOLE_SCREEN_BUFFER_INFO cursor;
    GetConsoleScreenBufferInfo(g_hScreen[0], &cursor);
    return cursor.dwCursorPosition.Y;
}

void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}