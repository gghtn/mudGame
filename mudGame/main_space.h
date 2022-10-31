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

	void MainStart();	// ���� ����

	void Render();		// ���� �Լ�

	void SelectDungeon(CObject* pUser, int y);	// ���� ���� �Լ�
};