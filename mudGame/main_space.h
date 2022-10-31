#pragma once
#include <string>
#include "menu.h"
#include "scarecrow_dungeon.h"
#include "goblin_dungeon.h"
#include "orc_dungeon.h"
#include "demon_dungeon.h"
using namespace std;

class CMainSpace {
	int mX, mY;
	bool mbInhanceItem, mbInhanceHero, mbDungeon;
	bool mbGameStart, mbGameOver;
	string mUserStr;
public:
	CMainSpace();

	void MainStart();	// 게임 시작

	void Render();		// 렌더 함수

	void SelectDungeon(CObject* pUser, int y);	// 던전 생성 함수
};