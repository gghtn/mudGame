#include "boss.h"
#pragma warning(disable:4996)

string CBoss::BossAttack(CObject* pUser) {
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
		damage = int((((rand() % 5 + 50) * GetSTR() + mbossATK) / pUser->GetDEF()) * weight);
	}

	// 1/5Ȯ���� ���� ����
	if (rand() % 5 == 0) {
		damage *= 3;
		pUser->SetDamage(damage);
		if (damage == 0)
			sprintf(result, "%s�� ������ ȸ���߽��ϴ�!", GetName());
		else if (pUser->GetLive())
			sprintf(result, "%s�� ��ų�� ����մϴ�\n ���� ������ ������ %d��ŭ�� ���ظ� �Ծ����ϴ�!", GetName(), damage);
		else sprintf(result, "%s�� ��ų�� ����մϴ�\n ġ������ �������� %s��(��) �׾����ϴ�!", GetName(), pUser->GetName());
	}
	else {
		pUser->SetDamage(damage);
		if (damage == 0)
			sprintf(result, "%s�� ������ ȸ���߽��ϴ�!", GetName());
		else if (pUser->GetLive())
			sprintf(result, "%s�� �������� %d��ŭ�� ���ظ� �Ծ����ϴ�!", GetName(), damage);
		else sprintf(result, "%s�� �������� %s��(��) �׾����ϴ�!", GetName(), pUser->GetName());
	}

	return result;
}