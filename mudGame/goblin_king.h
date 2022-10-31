#pragma once

#include "monster.h"
#include "boss.h"

class CGoblinKing : public CMonster, public CBoss {
public:
	CGoblinKing() :CMonster(), CBoss() {
		SetName("��� ŷ");
		Init(GetName(), LEVEL_WEIGHT_GOBLIN, STAT_MIN_GOBLINKING, EXP_GOBLINKING, GOLD_GOBLINKING, ITEM_GOBLINKING);
		BossInit(ATK_GOBLINKING);
	}
	string Attack(CObject* pUser) { return ""; }
};