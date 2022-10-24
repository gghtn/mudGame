#include "dungeon.h"
#include <Windows.h>

CDungeon::CDungeon(CObject* p) {
	mDungeonName = "기초 수련장";
	strcpy(mPrint, "던전에 입장했습니다.");
	pO = p;
	pU = static_cast<CUser*>(pO);
}

void CDungeon::DungeonStart() {
	
	ScreenInit();
	CObject** p = new CObject*[NUM_SCARECROW];	//몬스터 생성 이중포인터
	if (p == NULL) return;
	for (int i = 0; i < NUM_SCARECROW; i++) {
		p[i] = new CScarecrow;
	}

	int death = 0;	//죽은 몬스터의 수
	while (1) {
		ScreenClear();
		Render(POS_NORMAL_ATTACK);
		ScreenFlipping();
		if (death == NUM_SCARECROW) {
			Sleep(10000);
			break;
		}
		if (pO->GetLive()) {
			int i = death;
			if (p[i]->GetLive()) {
				UserAttack(p[i]);
				//Sleep(500);
				MonsterAttack(p[i]);
			}
			else {
				death++;
			}
			if (death == NUM_SCARECROW) strcat(mPrint, "\n 모든 몬스터를 처치했습니다.");
		}
		else {
			Sleep(5000);
			break;
		}
	}
	delete[] p;
	ScreenRelease();
}

void CDungeon::Render(int x) {
	string str1 = "┌──────────────────────────────────────────────────────────────────────────────┐";
	string str2 = "│                                                                              │";
	string str3 = "└──────────────────────────────────────────────────────────────────────────────┘";
	int y = 40;
	ScreenPrint(40, y, str1);
	for (int i = 1; i < 7; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 7, str3);

	ScreenPrint(x, y + 3, "▷");

	ScreenPrint(60, y + 3, "일반공격");
	ScreenPrint(90, y + 3, "스킬공격");

	str1 = "┌──────────────────────────────────────────┐";
	str2 = "│                                          │";
	str3 = "└──────────────────────────────────────────┘";
	y = 39;
	ScreenPrint(1, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(1, y + i, str2);
	ScreenPrint(1, y + 8, str3);

	ScreenPrint(3, y + 1, "Lv. "); ScreenPrint(7, y + 1, to_string(pO->GetLevel()));
	ScreenPrint(15, y + 1, pO->GetName());
	ScreenPrint(3, y + 3, "HP: "); ScreenPrint(7, y + 3, to_string(pO->GetHP()));
	ScreenPrint(3, y + 5, "MP: "); ScreenPrint(7, y + 5, to_string(pO->GetMP()));
	char str4[100];
	sprintf(str4, "EXP: %d / %d", pU->GetExp(), pU->GetTotalExp());
	ScreenPrint(3, y + 7, str4);

	str1 = "■■■■■■■■■■■■■■■■■■■■";
	str2 = "■                                    ■";
	y = 0;
	ScreenPrint(40, y, str1);
	for(int i = 1; i < 4; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 4, str1);

	ScreenPrint(60 - (SHORT)mDungeonName.size()/2, y + 2, mDungeonName);

	ScreenPrint(2, 5, mPrint);
}

void CDungeon::UserAttack(CObject* p) {
	int key = 0, pos_x = POS_NORMAL_ATTACK;
	do {
		ScreenClear();
		key = _getch();
		if (key == 224) key = _getch();
		if (key == LEFT) {
			pos_x = POS_NORMAL_ATTACK;
		}
		else if (key == RIGHT) {
			pos_x = POS_SKILL_ATTACK;
		}
		Render(pos_x);
		ScreenFlipping();
	} while (key != ENTER);
	
	if (GetCursorPosY() >= 35) InitPrint();	//버퍼의 커서 y좌표가 35이상이면 출력문 초기화

	if (pos_x == POS_NORMAL_ATTACK) {
		strcat(mPrint, "\n\n ");
		strcat(mPrint,(pO->Attack(p)).c_str());
	}
	Render(pos_x);
	ScreenFlipping();
}

void CDungeon::MonsterAttack(CObject* p) {
	if (p->GetLive()) {
		strcat(mPrint, "\n ");
		strcat(mPrint, (p->Attack(pO)).c_str());
	}
}