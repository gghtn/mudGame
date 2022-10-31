#include <iostream>
#include "main_space.h"
using namespace std;

int main() {
	srand((unsigned)time(NULL));
	SetConsoleSize(125, 50);

	CMainSpace begin;
	begin.MainStart();

	return 0;
}