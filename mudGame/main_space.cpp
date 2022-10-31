#include "main_space.h"

CMainSpace::CMainSpace() {
	mX = 60, mY = 25, mUserStr = "▶";
	mbInhanceItem = false;
	mbInhanceHero = false;
	mbDungeon = false;
	mbGameStart = false;
	mbGameOver = false;
}

void CMainSpace::MainStart() {
	string name;								// 캐릭터 이름 설정
	gotoxy(5, 25);
	cout << "캐릭터 이름을 설정하시오: ";
	cin >> name;

	CObject* pUser = new CUser(name);			// 유저 오브젝트 생성
	CUser* pU = static_cast<CUser*> (pUser);

	int count = 0, key = 0;	// 속도 조절 변수, 입력받을 키를 저장할 변수
	int posY = POS_MAIN;	// y좌표 초기화

	while (1) {
		ScreenInit();
		while (1) {
			ScreenClear();
			count++;
			if (count % 10 == 0) {				// 유저 이동 
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

			if (_kbhit()) {
				if (_getch() == ESC) {
					mbGameOver = true;
					break;
				}
			}

			if (110 <= mX && mX < 120 && 20 <= mY && mY <= 23) mbDungeon = true;
			if (1 <= mX && mX < 11 && 20 <= mY && mY <= 23) mbInhanceItem = true;
			if (55 <= mX && mX < 65 && 1 <= mY && mY <= 5) mbInhanceHero = true;

			Render();
			ScreenFlipping();

			//던전 메뉴
			if (mbDungeon) {
				mbDungeon = false;
				posY = 0;
				key = 0;
				do {
					ScreenClear();
					Render();
					posY = DungeonMenu(key, posY);	// 던전메뉴 선택 함수
					ScreenFlipping();
					key = _getch();
					if (key == 224) key = _getch();
				} while (key != ENTER);
				mX = 60, mY = 25;					// 위치초기화
			}
			if (posY != POS_MAIN) break;			// 취소선택 안할 시 무한루프 탈출

			//아이템 강화 메뉴
			if (mbInhanceItem) {
				mbInhanceItem = false;
				InhanceItemMenu(pU);				// 아이템 강화 메뉴 함수
				mX = 60, mY = 25;
			}

			//스탯 강화 메뉴
			if (mbInhanceHero) {
				mbInhanceHero = false;
				InhanceHeroMenu(pU);				// 스탯 강화 메뉴 함수
				mX = 60, mY = 25;
			}
		}// roof 2
		ScreenRelease();
		if (mbGameOver) {
			system("cls");
			cout << "게임을 종료합니다.";
			Sleep(3000);
			break;
		}
		SelectDungeon(pUser, posY);			//던전선택
		posY = POS_MAIN;
		pUser->SetHP(pUser->GetMaxHP());	// hp 초기화
		pUser->SetMP(pUser->GetMaxMP());	// mp 초기화
		pU->SetKillCountZero();				// kill 초기화

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

//인스턴트 던전 생성
void CMainSpace::SelectDungeon(CObject* pUser, int y) {
	switch (y) {
		CDungeon* pD;
	case POS_BASIC:
	{
		pD = new CScarecrowDungeon(pUser);
		pD->DungeonStart();
		delete pD;
		break;
	}
	case POS_GOBLIN:
	{
		pD = new CGoblinDungeon(pUser);
		pD->DungeonStart();
		delete pD;
		break;
	}
	case POS_ORC:
	{
		pD = new COrcDungeon(pUser);
		pD->DungeonStart();
		delete pD;
		break;
	}
	case POS_DEMON:
	{
		pD = new CDemonDungeon(pUser);
		pD->DungeonStart();
		delete pD;
		break;
	}
	default:
		break;
	}
}