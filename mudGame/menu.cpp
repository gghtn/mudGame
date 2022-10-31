#include "menu.h"
#include "key_pos.h"

int DungeonMenu(int key, int pos_y) {
	int result;
	int x = 35, y = 15;
	RectRender(x, y, 16);

	ScreenPrint(x + 20, POS_BASIC, "���� ������");
	ScreenPrint(x + 20, POS_GOBLIN, " ��� ��");
	ScreenPrint(x + 20, POS_ORC, "��ũ ������");
	ScreenPrint(x + 20, POS_DEMON, " ������ ��");
	ScreenPrint(x + 20, POS_MAIN, "   �� ��");

	if (pos_y == 0) {
		ScreenPrint(x + 17, 17, "��");
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
		ScreenPrint(x + 17, pos_y, "��");
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
		sprintf(tmp, "��ȭ: ��ȭ�� %d�� ��� %dG �ʿ�", wc, wc * 100);
		ScreenPrint(x + 10, y + 28, tmp);
		sprintf(tmp, "��ȭ��: %d  ���: %d", pU->GetItem(), pU->GetGold());
		ScreenPrint(x + 5, POS_ITEMGOLD, tmp);
		sprintf(tmp, "���� ���ݷ�: %d", pU->GetWeapon());
		ScreenPrint(x + 17, POS_WEAPONATK, tmp);
		ScreenPrint(x + 23, POS_INHANCE, "�� ȭ");
		ScreenPrint(x + 23, POS_MAIN, "�� ��");
		ScreenPrint(x + 20, posY, "��");
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
		string str1 = "������������������������������������������������������������������������������������������������������";
		string str2 = "��                        ��                        ��";
		string str3 = "������������������������������������������������������������������������������������������������������";
		string str4 = "��������������������������������������������������������������������������������������������������";
		ScreenPrint(x, y, str1);
		for (int i = 1; i < 25; i++) ScreenPrint(x, y + i, str2);
		ScreenPrint(x, y + 25, str3);
		ScreenPrint(x+1, y + 2, str4);
		ScreenPrint(x + 1, y + 4, str4);

		ScreenPrint(x + 20, y + 1, "[�������ͽ�]");
		sprintf(tmp, "Lv. %d   %s   Point: %d", pU->GetLevel(), pU->GetName(), pU->GetPoint());
		ScreenPrint(x + 15, y + 3, tmp);

		ScreenPrint(x + 9, y + 5, "[�⺻����]");

		sprintf(tmp, "�����(HP)  %d", pU->GetMaxHP());
		ScreenPrint(x + 5, POS_HP, tmp);
		sprintf(tmp, "����(MP)    %d", pU->GetMaxMP());
		ScreenPrint(x + 5, POS_MP, tmp);
		sprintf(tmp, "��          %d", pU->GetSTR());
		ScreenPrint(x + 5, POS_STR, tmp);
		sprintf(tmp, "��ø        %d", pU->GetDEX());
		ScreenPrint(x + 5, POS_DEX, tmp);
		sprintf(tmp, "����      %d", pU->GetDEF());
		ScreenPrint(x + 5, POS_DEF, tmp);
		sprintf(tmp, "���߷�      %d", pU->GetAccuracy());
		ScreenPrint(x + 5, POS_ACC, tmp);
		sprintf(tmp, "ȸ����      %d", pU->GetResilience());
		ScreenPrint(x + 5, POS_RES, tmp);
		sprintf(tmp, "Exp %d / %d", pU->GetExp(), pU->GetTotalExp());
		ScreenPrint(x + 5, POS_RES+4, tmp);

		ScreenPrint(x + 3, posY, "+");

		ScreenPrint(x + 34, y + 5, "[������ų]");

		if(pU->GetSkill(0)) ScreenPrint(x + 32, y + 8, " [Ʈ���� ����]");
		if (pU->GetSkill(1)) ScreenPrint(x + 32, y + 11, "    [ȸ��]");
		if (pU->GetSkill(2)) ScreenPrint(x + 32, y + 14, "  [Ʈ�� ����]");
		if (pU->GetSkill(3)) ScreenPrint(x + 32, y + 17, "[���� ���̵�]");

		ScreenPrint(x, y + 33, "���ư���(ESC), ��ø������ ȸ��Ȯ�� ������Ų��.");
		ScreenPrint(x, y + 35, "HP, MP�� 1����Ʈ�� 50����, ȸ������ 10�����Ѵ�.");
		ScreenPrint(x, y + 37, "��ų�� Lv.10, Lv.20, Lv.30, Lv.40 ���� �ϳ��� ����ȴ�.");

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
	string str1 = "������������������������������������������������������������������������������������������������������";
	string str2 = "��                                                 ��";
	string str3 = "������������������������������������������������������������������������������������������������������";
	ScreenPrint(x, y, str1);
	for (int i = 1; i < h; i++) ScreenPrint(x, y + i, str2);
	ScreenPrint(x, y + h, str3);
}