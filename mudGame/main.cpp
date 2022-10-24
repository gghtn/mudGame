#include <iostream>
#include "main_space.h"
#include "dungeon.h"
using namespace std;



int main() {
	srand((unsigned)time(NULL));
	SetConsoleSize(125, 50);
	//CMainSpace begin;
	//begin.MainStart();
	
	CObject* pUser = new CUser("test");
	CDungeon scarecrowDungeon(pUser);
	scarecrowDungeon.DungeonStart();

	/*char sdf[123] = "Sdfa";
	string str = "\n  sdffff";
	strcat(sdf, str.c_str());
	cout << sdf;*/
	return 0;
}