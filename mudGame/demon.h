#pragma once

#include "monster.h"

class CDemon :public CMonster {
public:
	CDemon() :CMonster() {
		SetName("µ¥¸ó");

		Init(GetName(), LEVEL_WEIGHT_DEMON, STAT_MIN_DEMON, EXP_DEMON, GOLD_DEMON, ITEM_DEMON);
	}
};