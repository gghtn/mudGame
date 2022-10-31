#include "dungeon.h"
#include <Windows.h>

CDungeon::CDungeon(CObject* p) {
	mDungeonName = "";
	strcpy(mPrint, "던전에 입장했습니다.");
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
		if (!(pO->GetLive())) {						//유저가 죽었을 시 종료
			pU->LoseExp();
			Sleep(3000);
			break;
		}
		if (i == mMonsterCount) {		//몬스터가 전부 죽었을 시 종료
			Sleep(3000);
			break;
		}
		if (i == mMonsterCount - 1 && mbBoss) {	//마지막 몬스터-> 보스
			sprintf(appearMonster, "\n [보스 출현!!]");
			sprintf(tmp, "\n Lv.%d %s이(가) 나타났습니다", p[i]->GetLevel(), p[i]->GetName());
			strcat(appearMonster, tmp);
		}
		else {
			sprintf(appearMonster, "\n Lv.%d %s이(가) 나타났습니다", p[i]->GetLevel(), p[i]->GetName());
		}
		strcat(mPrint, appearMonster);
		Render(POS_NORMAL_ATTACK);
		ScreenFlipping();
		while (1) {
			if (pO->GetLive()) {
				if (i != pU->GetKillCount()) break;
				pU->AutoRecovery();					//자동회복

				if (p[i]->GetLive()) {				//몬스터가 있을 시
					Select(p[i]);

					if (mbExit) break;

					if (i == mMonsterCount - 1 && mbBoss) BossTrun(p[i]);	//마지막 몬스터 -> 보스
					else MonsterTrun(p[i]);

				}
				if (pU->GetKillCount() == mMonsterCount) {
					strcat(mPrint, "\n 모든 몬스터를 처치했습니다.");
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
	string str1 = "┌──────────────────────────────────────────────────────────────────────────────┐";
	string str2 = "│                                                                              │";
	string str3 = "└──────────────────────────────────────────────────────────────────────────────┘";
	char str4[100];
	int y = 39;
	ScreenPrint(40, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 8, str3);

	if (is_skill) {
		ScreenPrint(48, y + 2, "[key/ MP소모량]");
		if(pU->GetSkill(3))
			ScreenPrint(48, y + 4, "트리플 어택(A/50)  회복(S/10%)  트루 어택(D/20%)  오러 블레이드(F/30%)");
		else if(pU->GetSkill(2))
			ScreenPrint(48, y + 4, "트리플 어택(A/50)  회복(S/10%)  트루 어택(D/20%)");
		else if(pU->GetSkill(1))
			ScreenPrint(48, y + 4, "트리플 어택(A/50)  회복(S/10%)");
		else if(pU->GetSkill(0))
			ScreenPrint(48, y + 4, "트리플 어택(A/50)");
		ScreenPrint(48, y + 6, "취소(ESC)");
	}
	else {
		ScreenPrint(x, y + 4, "▷");
		ScreenPrint(60, y + 4, "일반공격");
		ScreenPrint(90, y + 4, "스킬사용");
	}
	

	str1 = "┌──────────────────────────────────────────┐";
	str2 = "│                                          │";
	str3 = "└──────────────────────────────────────────┘";
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

	sprintf(str4, "남은 몬스터: %d", mMonsterCount - pU->GetKillCount());
	ScreenPrint(10, 2, str4);

	str1 = "■■■■■■■■■■■■■■■■■■■■";
	str2 = "■                                    ■";
	y = 0;
	ScreenPrint(40, y, str1);
	for(int i = 1; i < 4; i++) ScreenPrint(40, y + i, str2);
	ScreenPrint(40, y + 4, str1);

	ScreenPrint(100, y + 2, "ESC: 종료");

	ScreenPrint(60 - (SHORT)mDungeonName.size()/2, y + 2, mDungeonName);

	ScreenPrint(2, 5, mPrint);
}

void CDungeon::ExitRender() {
	string str1 = "┌────────────────────────────────────────────────────────────┐";
	string str2 = "│                                                            │";
	string str3 = "└────────────────────────────────────────────────────────────┘";
	int y = 19;
	ScreenPrint(30, y, str1);
	for (int i = 1; i < 8; i++) ScreenPrint(30, y + i, str2);
	ScreenPrint(30, y + 8, str3);

	ScreenPrint(40, y + 3, "경험치를 잃을 수 있습니다. 종료하시겠습니까?");
	ScreenPrint(50, y + 5, "예(ENTER)  아니오(ESC)");
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
	} while (UserTrun(p, pos_x));	//스킬 선택시 ESC키 입력할 경우 공격선택화면으로 돌아감
end: {}

}

bool CDungeon::UserTrun(CObject* p, int pos_x) {
	string skillStr;

	if (pos_x == POS_NORMAL_ATTACK) {
		if (GetCursorPosY() >= 32) InitPrint();	//버퍼의 커서 y좌표가 32이상이면 출력문 초기화
		strcat(mPrint, "\n\n ");
		strcat(mPrint,(pO->Attack(p)).c_str());
	}
	else {
		Render(pos_x, 1);
		ScreenFlipping();

		skillStr = pU->SkillActivate(p);
		if (skillStr == "0") return true;	//ESC입력시

		if (GetCursorPosY() >= 32) InitPrint();
		strcat(mPrint, "\n\n ");
		strcat(mPrint, skillStr.c_str());
	}
	
	if (!(p->GetLive())) {					//공격에 몬스터가 죽었을 시
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