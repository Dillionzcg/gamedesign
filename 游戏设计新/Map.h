#pragma once
#include"basis.h"


vector<vector<string>> Themap(8, vector<string>(100, " "));
void DrawBlock(int blocktype, int line) {
	if (blocktype != 5 && blocktype != 0) {//blocktype为5为双节点，blocktype为0为已经过节点
		for (int j = line; j < line + 5; j++) {
			Themap[2][j] = "#";
			Themap[4][j] = "#";
			Themap[3][line] = "#";
			Themap[3][line + 4] = "#";
		}
		switch (blocktype) {
		case 1:
			Themap[3][line + 2] = "*";//普通战斗
			break;
		case 2:
			Themap[3][line + 2] = "?";//非战斗节点
			break;
		case 3:
			Themap[3][line + 2] = "$";//商店节点
			break;
		case 4:
			Themap[3][line + 2] = "B";//boss节点
			break;
		}
	}
	else if (blocktype == 0) {
		for (int j = line; j < line + 5; j++) {
			Themap[2][j] = "#";
			Themap[3][j] = "#";
			Themap[4][j] = "#";
		}
	}
	else {//双节点
		for (int i = 1; i < 4; i++) {
			Themap[3][line - i] = " ";
		}
		for (int i = 1; i <= 5; i++) {
			if (i != 3) {
				Themap[i][line - 3] = "|";
				Themap[i][line + 6] = "|";
			}
		}
		Themap[1][line - 2] = "-";
		Themap[5][line - 2] = "-";
		Themap[1][line - 1] = ">";
		Themap[5][line - 1] = ">";
		Themap[1][line + 5] = "-";
		Themap[5][line + 5] = "-";
		Themap[3][line + 7] = "-";
		Themap[3][line + 8] = ">";
		for (int i = 0; i < 7; i++) {
			if (i != 3) {
				Themap[i][line] = "#";
				Themap[i][line + 4] = "#";
			}
		}
		for (int i = 1; i <= 3; i++) {
			Themap[0][line + i] = "#";
			Themap[2][line + i] = "#";
			Themap[4][line + i] = "#";
			Themap[6][line + i] = "#";
		}
		Themap[1][line + 2] = "*";
		Themap[5][line + 2] = "?";
	}
	if (blocktype != 5 && blocktype != 4) {//boss节点不需要箭头,此处为单节点的箭头设置
		Themap[3][line + 5] = "-";
		Themap[3][line + 6] = "-";
		Themap[3][line + 7] = "-";
		Themap[3][line + 8] = ">";
	}
}
void PrintMaphelp() {
	cout << HUI;
	cout << endl;
	cout << "地图说明：" << endl;
	cout << " * :战斗节点" << endl;
	cout << " ? :未知事件节点" << endl;
	cout << " $ :商店节点" << endl;
	cout << " B :Boss节点" << endl;
	cout << " ^ :当前位置" << endl;
}
vector<int> Maptype;
int Map1[5] = { 2,2,5,3,4 };
int Map2[6] = { 2,1,1,5,3,4 };
int Map3[7] = { 2,2,1,1,5,3,4 };
void UpdateMap(int floor, int step) {
	Maptype.clear();
	switch (floor) {
	case 1:
		for (int i = 0; i < 5; i++) {
			Maptype.push_back(Map1[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++) {
			Maptype.push_back(Map2[i]);
		}
		break;
	case 3:
		for (int i = 0; i < 7; i++) {
			Maptype.push_back(Map3[i]);
		}
		break;
	}
	for (int n = 0; n < step; n++) {
		Maptype[n] = 0;
	}
}
void DrawMap(int floor, int step) {
	Refresh();
	UpdateMap(floor, step);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 100; j++) {
			Themap[i][j] = " ";
		}
	}

	for (int n = 0; n < Maptype.size(); n++) {
		DrawBlock(Maptype[n], n * 9);
	}
	if (Maptype[step] != 5) {
		Themap[5][step * 9 + 2] = "^";

	}
	else {
		Themap[7][step * 9 + 2] = "^";
	}
	switch (floor) {
	case 1:
		cout << PURPLE;
		cout << "第一层 初始遗迹" << endl;
		cout << endl;
		cout << "远古石碑流转着晦暗的微光，斑驳的苔藓下封印着破碎的咒文。\n唯有踏入这片禁忌废墟，试炼的钟声方才悄然敲响。" << endl;
		break;
	case 2:
		cout << PURPLE;
		cout << "第二层 迷失回廊" << endl;
		cout << endl;
		cout << "虚无的迷雾中回荡着失落的低语，错综的符文法阵真假难辨。\n唯有堪破内心深处的恐惧，才能寻得通往核心的唯一生路。" << endl;
		break;
	case 3:
		cout << PURPLE;
		cout << "第三层 终焉圣殿" << endl;
		cout << endl;
		cout << "狂暴的魔力风暴撕裂苍穹，远古神祇的虚影在血色符文中苏醒。\n唯有直面神明的终极审判，方能揭开秘境尘封的真相。" << endl;
		break;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 100; j++) {
			cout << Themap[i][j] << RED_BOLD;
		}
		cout << endl;
	}
	cout << endl;
}

int Battlerow = 20;
int Battlecol = 90;
bool IfBattleIsOver = false;
vector<vector<string>> Battlemap(Battlerow, vector<string>(Battlecol, " "));
void PrintBalttleGround(int* myData, int* enemyData, int round, int turn) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";
		}
	}
	string myhp = to_string(myData[0]);
	string myHP = to_string(myData[1]);
	string enemyhp = to_string(enemyData[0]);
	string enemyHP = to_string(enemyData[1]);
	SupplementDigitNumber(myhp, 4);
	SupplementDigitNumber(myHP, 4);
	SupplementDigitNumber(enemyhp, 4);
	SupplementDigitNumber(enemyHP, 4);
	auto safe_div = [](int a, int b) -> double { return (b > 0) ? (double)a / b : 0.0; };
	double MyHpPercent = safe_div(myData[0], myData[1]);
	double EnemyHpPercent = safe_div(enemyData[0], enemyData[1]);
	double MyEnergyPercent = safe_div(myData[2], myData[3]);
	int MyEnergyBarLength = (int)(MyEnergyPercent * 19);
	double Myhealpercent = safe_div(myData[4], myData[5]);
	int MyhealBarLength = (int)(Myhealpercent * 19);
	double EnemyEnergyPercent = safe_div(enemyData[2], enemyData[3]);
	int EnemyEnergyBarLength = (int)(EnemyEnergyPercent * 19);
	int MyHpBarLength = (int)(MyHpPercent * 28);
	int EnemyHpBarLength = (int)(EnemyHpPercent * 28);
	if (MyEnergyBarLength < 0) MyEnergyBarLength = 0;
	if (MyEnergyBarLength > 19) MyEnergyBarLength = 19;
	if (MyhealBarLength < 0) MyhealBarLength = 0;
	if (MyhealBarLength > 19) MyhealBarLength = 19;
	if (EnemyEnergyBarLength < 0) EnemyEnergyBarLength = 0;
	if (EnemyEnergyBarLength > 19) EnemyEnergyBarLength = 19;
	if (MyHpBarLength < 0) MyHpBarLength = 0;
	if (MyHpBarLength > 28) MyHpBarLength = 28;
	if (EnemyHpBarLength < 0) EnemyHpBarLength = 0;
	if (EnemyHpBarLength > 28) EnemyHpBarLength = 28;
	if (turn != 2) {
		Refresh();
	}
	for (int i = 0; i < Battlerow; i++) {
		Battlemap[i][0] = "#";
		Battlemap[i][Battlecol - 1] = "#";
	}
	for (int j = 0; j < Battlecol; j++) {
		Battlemap[0][j] = "#";
		Battlemap[Battlerow - 1][j] = "#";
	}
	Battlemap[1][40] = "M";
	Battlemap[1][41] = "y";
	Battlemap[1][42] = "C";
	Battlemap[1][43] = "h";
	Battlemap[1][44] = "a";
	Battlemap[1][45] = "r";
	Battlemap[1][46] = "a";
	Battlemap[1][47] = "c";
	Battlemap[1][48] = "t";
	Battlemap[1][49] = "e";
	Battlemap[1][50] = "r";
	Battlemap[18][43] = "E";
	Battlemap[18][44] = "n";
	Battlemap[18][45] = "e";
	Battlemap[18][46] = "m";
	Battlemap[18][47] = "y";
	//以下为我方血量条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32;j <= 59;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for (int j = 32;j < 32 + MyHpBarLength;j++) {
		Battlemap[3][j] = "|";
		if (!IfBattleIsOver) {
			Battlemap[3][32] = "|";
		}
	}
	Battlemap[5][38] = "H";
	Battlemap[5][39] = "P";
	Battlemap[5][40] = ":";
	Battlemap[5][41] = myhp[0];
	Battlemap[5][42] = myhp[1];
	Battlemap[5][43] = myhp[2];
	Battlemap[5][44] = myhp[3];
	Battlemap[5][45] = "/";
	Battlemap[5][46] = myHP[0];
	Battlemap[5][47] = myHP[1];
	Battlemap[5][48] = myHP[2];
	Battlemap[5][49] = myHP[3];
	//以下为我方能量条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6;j <= 24;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	Battlemap[5][11] = "E";
	Battlemap[5][12] = "n";
	Battlemap[5][13] = "e";
	Battlemap[5][14] = "r";
	Battlemap[5][15] = "g";
	Battlemap[5][16] = "y";
	Battlemap[5][17] = ":";
	Battlemap[5][18] = to_string(myData[2]);
	Battlemap[5][19] = "/";
	Battlemap[5][20] = to_string(myData[3]);
	for (int j = 6;j < 6 + MyEnergyBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	//以下为我方治疗条位置
	for (int i = 2;i <= 4;i++) {
		Battlemap[i][66] = "#";
		Battlemap[i][86] = "#";
	}
	for (int j = 67;j <= 85;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	Battlemap[5][73] = "H";
	Battlemap[5][74] = "e";
	Battlemap[5][75] = "a";
	Battlemap[5][76] = "l";
	Battlemap[5][77] = ":";
	Battlemap[5][78] = to_string(myData[4]);
	Battlemap[5][79] = "/";
	Battlemap[5][80] = to_string(myData[5]);
	for (int j = 67;j < 67 + MyhealBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	//以下为敌方血量条位置
	for (int i = 15;i <= 17;i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32;j <= 59;j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	for (int j = 32;j < 32 + EnemyHpBarLength;j++) {
		Battlemap[16][j] = "|";
		if (!IfBattleIsOver) {
			Battlemap[16][32] = "|";
		}
	}
	Battlemap[14][38] = "H";
	Battlemap[14][39] = "P";
	Battlemap[14][40] = ":";
	Battlemap[14][41] = enemyhp[0];
	Battlemap[14][42] = enemyhp[1];
	Battlemap[14][43] = enemyhp[2];
	Battlemap[14][44] = enemyhp[3];
	Battlemap[14][45] = "/";
	Battlemap[14][46] = enemyHP[0];
	Battlemap[14][47] = enemyHP[1];
	Battlemap[14][48] = enemyHP[2];
	Battlemap[14][49] = enemyHP[3];
	//以下为敌方能量条位置
	for (int i = 15;i <= 17;i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6;j <= 24;j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	Battlemap[14][11] = "E";
	Battlemap[14][12] = "n";
	Battlemap[14][13] = "e";
	Battlemap[14][14] = "r";
	Battlemap[14][15] = "g";
	Battlemap[14][16] = "y";
	Battlemap[14][17] = ":";
	Battlemap[14][18] = to_string(enemyData[2]);
	Battlemap[14][19] = "/";
	Battlemap[14][20] = to_string(enemyData[3]);
	for (int j = 6;j < 6 + EnemyEnergyBarLength;j++) {
		Battlemap[16][j] = "|";
	}
	Battlemap[16][73] = "R";
	Battlemap[16][74] = "o";
	Battlemap[16][75] = "u";
	Battlemap[16][76] = "n";
	Battlemap[16][77] = "d";
	Battlemap[16][78] = to_string(round / 10);
	Battlemap[16][79] = to_string(round % 10);
	if (turn == 1) {
		// 等待用户输入 - 显示 "Please input..."
		string prompt = "Please input...";
		int prow = 9;
		int pcol = 39; // 从原有位置开始填充
		for (size_t k = 0; k < prompt.size(); ++k) {
			if (pcol + (int)k >= 0 && pcol + (int)k < Battlecol)
				Battlemap[prow][pcol + k] = string(1, prompt[k]);
		}
	}
	else {
		// 敌方回合 - 在居中位置显示 "Enter"
		string enter = "Enter";
		int erow = 9;
		int ecol = (Battlecol - (int)enter.size()) / 2; // 水平居中起始列
		for (size_t k = 0; k < enter.size(); ++k) {
			if (ecol + (int)k >= 0 && ecol + (int)k < Battlecol)
				Battlemap[erow][ecol + k] = string(1, enter[k]);
		}
	}
	for (int i = 0;i < 20;i++) {
		cout << " ";
	}
	cout << "我方攻击力:【" << myData[6] << "】,我方防御力:【" << myData[7] << "】,每剂治疗量:【" << myData[8] << "】" << endl;
	//打印地图
	for (int i = 0; i < Battlerow; i++) {
		for (int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j] << flush;
		}
		cout << endl;
	}
	for (int i = 0;i < 20;i++) {
		cout << " ";
	}
	cout << "敌方攻击力:【" << enemyData[4] << "】,敌方防御力:【" << enemyData[5] << "】,敌方暴击率:【" << enemyData[6] << "%】" << endl;
	cout << endl;
}
void PrintEventGround(int Type) {
	Refresh();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";
		}
	}
	for (int j = 0; j < Battlecol; j++) {
		Battlemap[0][j] = "#";
		Battlemap[Battlerow - 1][j] = "#";
	}
	//打印地图
	for (int i = 0; i < Battlerow; i++) {
		for (int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j];
		}
		cout << endl;
	}
}
int MydataWhenBattle[9] = { 0 };
int EnemydataWhenBattle[7] = { 0 };
