#include "menu.h"
#include "key_pos.h"

int DungeonMenu(int key, int pos_y) {
	int result;
	int x = 35, y = 15;
	RectRender(x, y, 16);

	ScreenPrint(x + 20, POS_BASIC, "기초 수련장");
	ScreenPrint(x + 20, POS_GOBLIN, " 고블린 숲");
	ScreenPrint(x + 20, POS_ORC, "오크 서식지");
	ScreenPrint(x + 20, POS_DEMON, " 데몬의 성");
	ScreenPrint(x + 20, POS_MAIN, "   취 소");

	if (pos_y == 0) {
		ScreenPrint(x + 17, 17, "▷");
		pos_y = POS_BASIC;
	}
	else{
		switch (key) {
		case UP:
			if (pos_y > POS_BASIC) pos_y -= 3;
			else pos_y = POS_MAIN;
			break;
		case DOWN:
			if (pos_y < POS_MAIN) pos_y += 3;
			else pos_y = POS_BASIC;
			break;
		default:
			break;
		}
		ScreenPrint(x + 17, pos_y, "▷");
	}
	result = pos_y;

	return result;
}

void InhanceItemMenu(CUser* pU) {
	int posY = POS_INHANCE, key;
	char tmp[100];
	while (1) {
		ScreenClear();
		int x = 35, y = 15;
		RectRender(x, y, 16);

		int wc = pU->GetWeaponClass();
		sprintf(tmp, "강화: 강화석 %d개 골드 %dG 필요", wc, wc * 100);
		ScreenPrint(x + 10, y + 28, tmp);
		sprintf(tmp, "강화석: %d  골드: %d", pU->GetItem(), pU->GetGold());
		ScreenPrint(x + 5, POS_ITEMGOLD, tmp);
		sprintf(tmp, "무기 공격력: %d", pU->GetWeapon());
		ScreenPrint(x + 17, POS_WEAPONATK, tmp);
		ScreenPrint(x + 23, POS_INHANCE, "강 화");
		ScreenPrint(x + 23, POS_MAIN, "취 소");
		ScreenPrint(x + 20, posY, "▷");
		ScreenFlipping();

		key = _getch();
		if (key == 224) key = _getch();
		switch (key) {
		case UP:
			posY = POS_INHANCE;
			break;
		case DOWN:
			posY = POS_MAIN;
			break;
		case ENTER:
			if (posY == POS_INHANCE) {				
				if (pU->GetItem() >= wc && pU->GetGold() >= wc * 100) {
					pU->InhanceWeapon();
					pU->WeaponUP();
					pU->SetItemGold(wc);
				}
			}
			else {
				goto end;
			}
			break;
		default:
			break;
		}
	}
end: {}
}

void InhanceHeroMenu(CUser* pU) {
	int posY = POS_HP, key;
	char tmp[100];
	while (1) {
		ScreenClear();
		int x = 35, y = 8;
		string str1 = "┌─────────────────────────────────────────────────┐";
		string str2 = "│                        │                        │";
		string str3 = "└─────────────────────────────────────────────────┘";
		string str4 = "─────────────────────────────────────────────────";
		ScreenPrint(x, y, str1);
		for (int i = 1; i < 25; i++) ScreenPrint(x, y + i, str2);
		ScreenPrint(x, y + 25, str3);
		ScreenPrint(x+1, y + 2, str4);
		ScreenPrint(x + 1, y + 4, str4);

		ScreenPrint(x + 20, y + 1, "[스테이터스]");
		sprintf(tmp, "Lv. %d   %s   Point: %d", pU->GetLevel(), pU->GetName(), pU->GetPoint());
		ScreenPrint(x + 15, y + 3, tmp);

		ScreenPrint(x + 9, y + 5, "[기본정보]");

		sprintf(tmp, "생명력(HP)  %d", pU->GetMaxHP());
		ScreenPrint(x + 5, POS_HP, tmp);
		sprintf(tmp, "마력(MP)    %d", pU->GetMaxMP());
		ScreenPrint(x + 5, POS_MP, tmp);
		sprintf(tmp, "힘          %d", pU->GetSTR());
		ScreenPrint(x + 5, POS_STR, tmp);
		sprintf(tmp, "민첩        %d", pU->GetDEX());
		ScreenPrint(x + 5, POS_DEX, tmp);
		sprintf(tmp, "방어력      %d", pU->GetDEF());
		ScreenPrint(x + 5, POS_DEF, tmp);
		sprintf(tmp, "명중률      %d", pU->GetAccuracy());
		ScreenPrint(x + 5, POS_ACC, tmp);
		sprintf(tmp, "회복력      %d", pU->GetResilience());
		ScreenPrint(x + 5, POS_RES, tmp);
		sprintf(tmp, "Exp %d / %d", pU->GetExp(), pU->GetTotalExp());
		ScreenPrint(x + 5, POS_RES+4, tmp);

		ScreenPrint(x + 3, posY, "+");

		ScreenPrint(x + 34, y + 5, "[보유스킬]");

		if(pU->GetSkill(0)) ScreenPrint(x + 32, y + 8, " [트리플 어택]");
		if (pU->GetSkill(1)) ScreenPrint(x + 32, y + 11, "    [회복]");
		if (pU->GetSkill(2)) ScreenPrint(x + 32, y + 14, "  [트루 어택]");
		if (pU->GetSkill(3)) ScreenPrint(x + 32, y + 17, "[오러 블레이드]");

		ScreenPrint(x, y + 33, "돌아가기(ESC), 민첩스탯은 회피확률 증가시킨다.");
		ScreenPrint(x, y + 35, "HP, MP는 1포인트당 50증가, 회복력은 10증가한다.");
		ScreenPrint(x, y + 37, "스킬은 Lv.10, Lv.20, Lv.30, Lv.40 마다 하나씩 개방된다.");

		ScreenFlipping();

		key = _getch();
		if (key == 224) key = _getch();
		switch (key) {
		case UP:
			if (posY != POS_HP) posY -= 2;
			break;
		case DOWN:
			if (posY != POS_RES) posY += 2;
			break;
		case ENTER:
			if (pU->GetPoint()) {
				switch (posY) {
				case POS_HP:
					pU->SetMaxHP(pU->GetMaxHP() + 50);
					break;
				case POS_MP:
					pU->SetMaxMP(pU->GetMaxMP() + 50);
					break;
				case POS_STR:
					pU->SetSTR(pU->GetSTR() + 1);
					break;
				case POS_DEX:
					pU->SetDEX(pU->GetDEX() + 1);
					break;
				case POS_DEF:
					pU->SetDEF(pU->GetDEF() + 1);
					break;
				case POS_ACC:
					pU->SetAccuracy();
					break;
				case POS_RES:
					pU->SetResilience();
					break;
				}
				pU->SetPoint();
			}
			break;
		case ESC:
			goto end;
		default:
			break;
		}
	}
end: {}
}

void RectRender(int x, int y, int h) {
	string str1 = "┌─────────────────────────────────────────────────┐";
	string str2 = "│                                                 │";
	string str3 = "└─────────────────────────────────────────────────┘";
	ScreenPrint(x, y, str1);
	for (int i = 1; i < h; i++) ScreenPrint(x, y + i, str2);
	ScreenPrint(x, y + h, str3);
}