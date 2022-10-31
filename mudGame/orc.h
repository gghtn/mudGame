#pragma once

#include "monster.h"

class COrc :public CMonster {
public:
	COrc() :CMonster() {
		SetName("ø¿≈©");

		Init(GetName(), LEVEL_WEIGHT_ORC, STAT_MIN_ORC, EXP_ORC, GOLD_ORC, ITEM_ORC);
	}
};