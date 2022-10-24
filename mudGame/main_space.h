#pragma once
#include <string>
#include "menu.h"
#include "dungeon.h"
using namespace std;

class CMainSpace {
	int mX, mY;
	bool mbInhanceItem, mbInhanceHero, mbDungeon;
	bool mbGameStart;
	string mUserStr;
public:
	CMainSpace();

	void MainStart();

	void Render();
};