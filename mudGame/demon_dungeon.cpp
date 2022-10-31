#include "demon_dungeon.h"

void CDemonDungeon::DungeonStart() {

	ScreenInit();
	int count = GetMonsterCount();
	CObject** p = new CObject * [count];
	if (p == NULL) return;
	for (int i = 0; i < count; i++) {
		if (i == count - 1) p[i] = new CDemonKing;
		else p[i] = new CDemon;
	}
	SetIsBoss();		//보스 존재 여부 true
	Battle(p);
	delete[] p;
	ScreenRelease();

}