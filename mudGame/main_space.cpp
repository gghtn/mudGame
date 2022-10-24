#include "main_space.h"

CMainSpace::CMainSpace() {
	mX = 60, mY = 25, mUserStr = "▶";
	mbInhanceItem = false;
	mbInhanceHero = false;
	mbDungeon = false;
	mbGameStart = false;
}

void CMainSpace::MainStart() {
	CObject* pUser = new CUser("test");
	int count = 0, key = 0;
	int selectDungeon = POS_MAIN;
	while (1) {
		ScreenInit();

		while (1) {
			ScreenClear();
			count++;
			if (count % 20 == 0) {
				if (IsKeyDown(VK_LEFT)) {
					if (mX > 0) mX--;
					mUserStr = "◀";
				}
				if (IsKeyDown(VK_RIGHT)) {
					if (mX < 120) mX++;
					mUserStr = "▶";
				}
				if (IsKeyDown(VK_UP)) {
					if (mY > 0) mY--;
					mUserStr = "▲";
				}
				if (IsKeyDown(VK_DOWN)) {
					if (mY < 39) mY++;
					mUserStr = "▼";
				}
			}

			if (110 <= mX && mX < 120 && 20 <= mY && mY <= 23) mbDungeon = true;

			Render();
			ScreenFlipping();

			if (mbDungeon) {
				Sleep(50);
				mbDungeon = false;
				selectDungeon = 0;
				key = 0;
				do {
					ScreenClear();
					Render();
					selectDungeon = DungeonMenu(key,selectDungeon);
					ScreenFlipping();
					key = _getch();
					if (key == 224) key = _getch();
				} while (key != ENTER);
				mX = 60, mY = 25;
			}
			if (selectDungeon != POS_MAIN) break;

		}// roof 2

		ScreenRelease();

		switch (selectDungeon) {
		case POS_BASIC:
		{
			CDungeon scarecrowDungeon(pUser);
			scarecrowDungeon.DungeonStart();
			break;
		}
		case POS_GOBLIN:
			break;
		case POS_ORC:
			break;
		case POS_DEMON:
			break;
		default:
			break;
		}
		selectDungeon = POS_MAIN;

	}// roof 1
}


void CMainSpace::Render() {
	string str1 = "┌──────────────────────────────────────────────────────────────────────────────┐";
	string str2 = "│                                                                              │";
	string str3 = "└──────────────────────────────────────────────────────────────────────────────┘";
	int y = 40;
	ScreenPrint(20, y, str1);
	for (int i = 1; i < 7; i++) ScreenPrint(20, y + i, str2);
	ScreenPrint(20, y + 7, str3);

	str1 = "┌─────────┐";
	str2 = "│         │";
	str3 = "└─────────┘";
	y = 20;
	string str4 = "▷장비 강화◁";
	ScreenPrint(1, y, str1);
	ScreenPrint(1, y + 1, str2);
	ScreenPrint(1, y + 2, str2);
	ScreenPrint(1, y + 3, str3);
	ScreenPrint(1, y + 4, str4);

	str4 = "  ▷던 전◁  ";
	ScreenPrint(110, y, str1);
	ScreenPrint(110, y + 1, str2);
	ScreenPrint(110, y + 2, str2);
	ScreenPrint(110, y + 3, str3);
	ScreenPrint(110, y + 4, str4);

	y = 1;
	str4 = "▷영웅 강화◁";
	ScreenPrint(55, y, str1);
	ScreenPrint(55, y + 1, str2);
	ScreenPrint(55, y + 2, str2);
	ScreenPrint(55, y + 3, str3);
	ScreenPrint(55, y + 4, str4);

	ScreenPrint(mX, mY, mUserStr);
}