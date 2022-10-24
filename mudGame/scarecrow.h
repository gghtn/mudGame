#pragma once
#include "monster.h"

class CScarecrow:public CMonster {
	string mName;
public:
	CScarecrow();
	void Init(string, int);
};