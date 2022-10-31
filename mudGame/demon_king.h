#pragma once

#include "monster.h"
#include "boss.h"

class CDemonKing : public CMonster, public CBoss {
public:
	CDemonKing() :CMonster(), CBoss() {
		SetName("고블린 킹");
		Init(GetName(), LEVEL_WEIGHT_DEMON, STAT_MIN_DEMONKING, EXP_DEMONKING, GOLD_DEMONKING, ITEM_DEMONKING);
		BossInit(ATK_DEMONKING);
	}
	string Attack(CObject* pUser) { return ""; }
};