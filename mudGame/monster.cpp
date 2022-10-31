#include "monster.h"

void CMonster::Init(string name, int weight, int status, int exp, int gold, int item) {
	int level = rand() % 10 + weight;
	SetName(name);
	SetLevel(level);
	SetMaxHP(100 * level);
	SetHP(GetMaxHP());
	SetSTR(rand() % 10 + status + level);
	SetDEX(rand() % 10 + status + level);
	SetDEF(rand() % 10 + status + level);
	SetMonsterInfo(exp + level * 10, gold + level * 10, item);
}

string CMonster::Attack(CObject* pUser) {
	char result[100];
	int damage, avoid;
	float weight;

	avoid = pUser->GetDEX() + pUser->GetLevel() - GetLevel();
	if (avoid <= 0) avoid = 0;
	else {
		if (rand() % 10 < avoid / 10) avoid = 1;
		else avoid = 0;
	}

	if (avoid) damage = 0;
	else {
		weight = LevelWeight(pUser);
		damage = int((((rand() % 10 + 20) * GetSTR()) / pUser->GetDEF()) * weight);
	}

	pUser->SetDamage(damage);
	if (damage == 0)
		sprintf(result, "%s�� ������ ȸ���߽��ϴ�!", GetName());
	else if (pUser->GetLive())
		sprintf(result, "%s�� �������� %d��ŭ�� ���ظ� �Ծ����ϴ�!", GetName(), damage);
	else sprintf(result, "%s�� �������� %s��(��) �׾����ϴ�!", GetName(), pUser->GetName());

	return result;
}