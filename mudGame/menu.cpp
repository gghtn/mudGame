#include "menu.h"
#include "key_pos.h"

int DungeonMenu(int key, int pos_y) {
	int result;
	
	int x = 35, y = 15;
	string str1 = "┌─────────────────────────────────────────────────┐";
	string str2 = "│                                                 │";
	string str3 = "└─────────────────────────────────────────────────┘";
	ScreenPrint(x, y, str1);
	for (int i = 1; i < 16; i++) ScreenPrint(x, y + i, str2);
	ScreenPrint(x, y + 16, str3);

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

void InhanceItemMenu() {

}

void InhanceHeroMenu() {

}