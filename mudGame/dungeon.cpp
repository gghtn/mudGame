#include "dungeon.h"
#include <Windows.h>

CDungeon::CDungeon(CObject* p) {
	mDungeonName = "";
	strcpy(mPrint, "������ �����߽��ϴ�.");
	mMonsterCount = 0;
	mbExit = false, mbBoss = false;
	pO = p;
	pU = static_cast<CUser*>(pO);
}

void CDungeon::Battle(CObject** p) {
	char appearMonster[100], tmp[100];
	while (1) {
		ScreenClear();
		int i = pU->GetKillCount();		
		if (!(pO->GetLive())) {						//������ �׾��� �� ����
			pU->LoseExp();
			Sleep(3000);
			break;
		}
		if (i == mMonsterCount) {		//���Ͱ� ���� �׾��� �� ����
			Sleep(3000);
			break;
		}
		if (i == mMonsterCount - 1 && mbBoss) {	//������ ����-> ����
			sprintf(appearMonster, "\n [���� ����!!]");
			sprintf(tmp, "\n Lv.%d %s��(��) ��Ÿ�����ϴ�", p[i]->GetLevel(), p[i]->GetName());
			strcat(appearMonster, tmp);
		}
		else {
			sprintf(appearMonster, "\n Lv.%d %s��(��) ��Ÿ�����ϴ�", p[i]->GetLevel(), p[i]->GetName());
		}
		strcat(mPrint, appearMonster);
		Render(POS_NORMAL_ATTACK);
		ScreenFlipping();
		while (1) {
			if (pO->GetLive()) {
				if (i != pU->GetKillCount()) break;
				pU->AutoRecovery();					//�ڵ�ȸ��

				if (p[i]->GetLive()) {				//���Ͱ� ���� ��
					Select(p[i]);

					if (mbExit) break;

					if (i == mMonsterCount - 1 && mbBoss) BossTrun(p[i]);	//������ ���� -> ����
					else MonsterTrun(p[i]);

				}
				if (pU->GetKillCount() == mMonsterCount) {
					strcat(mPrint, "\n ��� ���͸� óġ�߽��ϴ�.");
					ScreenClear();
					Render(POS_NORMAL_ATTACK);
					ScreenFlipping();
					break;
				}
			}
			else {
				break;
			}
		}
		if (mbExit) {
			pU->LoseExp();
			break;
		}
	}

}

void CDungeon::Render(int x, bool is_skill) {
	string str1 = "����������������������������������������������������������������������������������������������������������������������������������������������������������������";
	string str2 = "��                                                                              ��";
	string str3 = "����������������������������������������������������������������������������������������������������������������������������������������������������������������";
	char str4[100];
	int y = 39;
	ScreenPrint(40, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 8, str3);

	if (is_skill) {
		ScreenPrint(48, y + 2, "[key/ MP�Ҹ�]");
		if(pU->GetSkill(3))
			ScreenPrint(48, y + 4, "Ʈ���� ����(A/50)  ȸ��(S/10%)  Ʈ�� ����(D/20%)  ���� ���̵�(F/30%)");
		else if(pU->GetSkill(2))
			ScreenPrint(48, y + 4, "Ʈ���� ����(A/50)  ȸ��(S/10%)  Ʈ�� ����(D/20%)");
		else if(pU->GetSkill(1))
			ScreenPrint(48, y + 4, "Ʈ���� ����(A/50)  ȸ��(S/10%)");
		else if(pU->GetSkill(0))
			ScreenPrint(48, y + 4, "Ʈ���� ����(A/50)");
		ScreenPrint(48, y + 6, "���(ESC)");
	}
	else {
		ScreenPrint(x, y + 4, "��");
		ScreenPrint(60, y + 4, "�Ϲݰ���");
		ScreenPrint(90, y + 4, "��ų���");
	}
	

	str1 = "����������������������������������������������������������������������������������������";
	str2 = "��                                          ��";
	str3 = "����������������������������������������������������������������������������������������";
	ScreenPrint(1, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(1, y + i, str2);
	ScreenPrint(1, y + 8, str3);

	ScreenPrint(3, y + 1, "Lv. "); ScreenPrint(7, y + 1, to_string(pO->GetLevel()));
	ScreenPrint(15, y + 1, pO->GetName());
	
	sprintf(str4, "HP: %d / %d",pO->GetHP(), pO->GetMaxHP());
	ScreenPrint(3, y + 3, str4);
	sprintf(str4, "MP: %d / %d", pO->GetMP(), pO->GetMaxMP());
	ScreenPrint(3, y + 5, str4);
	sprintf(str4, "EXP: %d / %d", pU->GetExp(), pU->GetTotalExp());
	ScreenPrint(3, y + 7, str4);

	sprintf(str4, "���� ����: %d", mMonsterCount - pU->GetKillCount());
	ScreenPrint(10, 2, str4);

	str1 = "���������������������";
	str2 = "��                                    ��";
	y = 0;
	ScreenPrint(40, y, str1);
	for(int i = 1; i < 4; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 4, str1);

	ScreenPrint(100, y + 2, "ESC: ����");

	ScreenPrint(60 - (SHORT)mDungeonName.size()/2, y + 2, mDungeonName);

	ScreenPrint(2, 5, mPrint);
}

void CDungeon::ExitRender() {
	string str1 = "����������������������������������������������������������������������������������������������������������������������������";
	string str2 = "��                                                            ��";
	string str3 = "����������������������������������������������������������������������������������������������������������������������������";
	int y = 19;
	ScreenPrint(30, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(30, y + i, str2);
	ScreenPrint(30, y + 8, str3);

	ScreenPrint(40, y + 3, "����ġ�� ���� �� �ֽ��ϴ�. �����Ͻðڽ��ϱ�?");
	ScreenPrint(50, y + 5, "��(ENTER)  �ƴϿ�(ESC)");
}

void CDungeon::Select(CObject* p) {
	int key = 0, pos_x = POS_NORMAL_ATTACK;
	do {
		do {
			ScreenClear();
			Render(pos_x);
			ScreenFlipping();
			key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == LEFT) {
					pos_x = POS_NORMAL_ATTACK;
				}
				else if (key == RIGHT) {
					pos_x = POS_SKILL_ATTACK;
				}
			}
			else if (key == ESC) {
				ScreenClear();
				ExitRender();
				ScreenFlipping();
				while (1) {
					key = _getch();
					if (key == ENTER) {
						mbExit = true;
						goto end;
					}
					else if (key == ESC) {
						break;
					}
				}				
			}
		} while (key != ENTER);
	} while (UserTrun(p, pos_x));	//��ų ���ý� ESCŰ �Է��� ��� ���ݼ���ȭ������ ���ư�
end: {}

}

bool CDungeon::UserTrun(CObject* p, int pos_x) {
	string skillStr;

	if (pos_x == POS_NORMAL_ATTACK) {
		if (GetCursorPosY() >= 32) InitPrint();	//������ Ŀ�� y��ǥ�� 32�̻��̸� ��¹� �ʱ�ȭ
		strcat(mPrint, "\n\n ");
		strcat(mPrint,(pO->Attack(p)).c_str());
	}
	else {
		Render(pos_x, 1);
		ScreenFlipping();

		skillStr = pU->SkillActivate(p);
		if (skillStr == "0") return true;	//ESC�Է½�

		if (GetCursorPosY() >= 32) InitPrint();
		strcat(mPrint, "\n\n ");
		strcat(mPrint, skillStr.c_str());
	}
	
	if (!(p->GetLive())) {					//���ݿ� ���Ͱ� �׾��� ��
		ScreenClear();
		Render(pos_x);
		ScreenFlipping();
		Sleep(2000);
		InitPrint();
	}
	return false;
}

void CDungeon::MonsterTrun(CObject* p) {
	if (p->GetLive()) {
		strcat(mPrint, "\n ");
		strcat(mPrint, (p->Attack(pO)).c_str());
	}
}

void CDungeon::BossTrun(CObject* p) {
	CBoss* pb = dynamic_cast<CBoss*>(p);
	if (p->GetLive()) {
		strcat(mPrint, "\n ");
		strcat(mPrint, (pb->BossAttack(pO)).c_str());
	}
}