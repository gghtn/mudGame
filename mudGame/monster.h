#pragma once
#include "object.h"
#include "monster_weight.h"
#pragma warning(disable:4996)

class CMonster : public CObject {
public:
	CMonster() : CObject() {}

	string Attack(CObject* pObject);

	virtual void Init(string, int) = 0;
};