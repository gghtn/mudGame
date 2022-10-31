#pragma once

#include "monster.h"
#include "boss.h"

class COrcKing : public CMonster, public CBoss {
public:
	COrcKing() :CMonster(), CBoss() {
		SetName("ø¿≈© ≈∑");
		Init(GetName(), LEVEL_WEIGHT_ORC, STAT_MIN_ORCKING, EXP_ORCKING, GOLD_ORCKING, ITEM_ORCKING);
		BossInit(ATK_ORCKING);
	}
	string Attack(CObject* pUser) { return ""; }
};