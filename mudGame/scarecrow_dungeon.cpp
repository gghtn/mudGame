#include "scarecrow_dungeon.h"

void CScarecrowDungeon::DungeonStart() {

	ScreenInit();
	int count = GetMonsterCount();
	CObject** p = new CObject * [count];	//���� ���� ����������
	if (p == NULL) return;
	for (int i = 0; i < count; i++) {
		p[i] = new CScarecrow;
	}
	Battle(p);
	delete[] p;
	ScreenRelease();
}