#pragma once
#include "object.h"

class CBoss: virtual public CObject {
	int mbossATK;
public:
	CBoss() : CObject() { mbossATK = 0; }
	virtual ~CBoss() {}

	void BossInit( int atk) { mbossATK = atk; }

	string Attack(CObject* pUser) { return ""; }
	string BossAttack(CObject* pUser);
};