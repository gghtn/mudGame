#include "goblin_dungeon.h"

void CGoblinDungeon::DungeonStart() {

	ScreenInit();
	int count = GetMonsterCount();
	CObject** p = new CObject * [count];
	if (p == NULL) return;
	for (int i = 0; i < count; i++) {
		if (i == count - 1) p[i] = new CGoblinKing;
		else p[i] = new CGoblin;
	}
	SetIsBoss();		//���� ���� ���� true
	Battle(p);
	delete[] p;
	ScreenRelease();

}