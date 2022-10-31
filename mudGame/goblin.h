#pragma once

#include "monster.h"

class CGoblin :public CMonster {
public:
	CGoblin() :CMonster() {
		SetName("°íºí¸°");

		Init(GetName(), LEVEL_WEIGHT_GOBLIN, STAT_MIN_GOBLIN, EXP_GOBLIN, GOLD_GOBLIN, ITEM_GOBLIN);
	}
};