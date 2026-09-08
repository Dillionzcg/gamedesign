#include"Map.h"


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
//int Map1[5] = {2,2,2,2,2};
vector<int> Map1 = {1,2,1,5,3,4};
vector<int> Map2 = {2,1,2,1,5,3,4};
vector<int> Map3 = {2,2,1,1,2,5,3,4};
void ChangeShopToBattle(int floor) {
	switch (floor) {
	case 1:
		Map1[(int)Map1.size()-2] = 1;break;
	case 2:
		Map2[(int)Map2.size()-2] = 1;break;
	case 3:
		Map3[(int)Map3.size()-2] = 1;break;
	default:break;
	}
}
void UpdateMap(int floor, int step) {
	Maptype.clear();
	switch (floor) {
	case 1:
		for (int i = 0; i < 6; i++) {
			Maptype.push_back(Map1[i]);
		}
		break;
	case 2:
		for (int i = 0; i < 7; i++) {
			Maptype.push_back(Map2[i]);
		}
		break;
	case 3:
		for (int i = 0; i < 8; i++) {
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
		cout << QING;
		cout << "第一层 初始遗迹" << endl;
		cout << endl;
		cout << "远古石碑流转着晦暗的微光，斑驳的苔藓下封印着破碎的咒文。\n唯有踏入这片禁忌废墟，试炼的钟声方才悄然敲响。" << endl;
		break;
	case 2:
		cout << YELLOW;
		cout << "第二层 迷失回廊" << endl;
		cout << endl;
		cout << "虚无的迷雾中回荡着失落的低语，错综的符文法阵真假难辨。\n唯有堪破内心深处的恐惧，才能寻得通往核心的唯一生路。" << endl;
		break;
	case 3:
		cout << RED_WINE;
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
int MyLastHpBarLength = 28;
int EnemyLastHpBarLength = 28;
int MyLastEnergyBarLength = 0;
int EnemyLastEnergyBarLength = 0;
int MyLasthealBarLength = 0;
void ResetLastBarLength() {
	MyLastHpBarLength = 28;
	EnemyLastHpBarLength = 28;
	MyLastEnergyBarLength = 0;
	EnemyLastEnergyBarLength = 0;
	MyLasthealBarLength = 0;
}
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
	if (round == 1 && turn == 1) {
		MyLastHpBarLength = MyHpBarLength;
		EnemyLastHpBarLength = EnemyHpBarLength;
		MyLastEnergyBarLength = MyEnergyBarLength;
		EnemyLastEnergyBarLength = EnemyEnergyBarLength;
		MyLasthealBarLength = MyhealBarLength;
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
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32; j <= 59; j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for (int j = 32; j < 32 + MyLastHpBarLength; j++) {
		Battlemap[3][j] = "∣";
		Battlemap[3][32] = "∣";
	}
	for (int j = 32; j < 32 + MyHpBarLength; j++) {
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
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6; j <= 24; j++) {
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
	for (int j = 6; j < 6 + MyLastEnergyBarLength; j++) {
		Battlemap[3][j] = "∣";
	}
	for (int j = 6; j < 6 + MyEnergyBarLength; j++) {
		Battlemap[3][j] = "|";
	}
	//以下为我方治疗条位置
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][66] = "#";
		Battlemap[i][86] = "#";
	}
	for (int j = 67; j <= 85; j++) {
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
	for (int j = 67; j < 67 + MyLasthealBarLength; j++) {
		Battlemap[3][j] = "∣";
	}
	for (int j = 67; j < 67 + MyhealBarLength; j++) {
		Battlemap[3][j] = "|";
	}
	//以下为敌方血量条位置
	for (int i = 15; i <= 17; i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32; j <= 59; j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	for (int j = 32; j < 32 + EnemyLastHpBarLength; j++) {
		Battlemap[16][j] = "∣";
		Battlemap[16][32] = "∣";
	}
	for (int j = 32; j < 32 + EnemyHpBarLength; j++) {
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
	for (int i = 15; i <= 17; i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6; j <= 24; j++) {
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
	for (int j = 6; j < 6 + EnemyLastEnergyBarLength; j++) {
		Battlemap[16][j] = "∣";
	}
	for (int j = 6; j < 6 + EnemyEnergyBarLength; j++) {
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
	for (int i = 0; i < 20; i++) {
		cout << " ";
	}
	cout << GREEN_BRIGHT;
	cout << "我方攻击力:【" << myData[6] << "】,我方防御力:【" << myData[7] << "】,每剂治疗量:【" << myData[8] << "】" << endl;
	//打印地图
	for (int i = 0; i < Battlerow; i++) {
		for (int j = 0; j < Battlecol; j++) {
			if (Battlemap[i][j] == "#" || Battlemap[i][j] == "-") {
				cout << RED_WINE;
			}
			else if (Battlemap[i][j] == "|") {
				cout << BLUE;
			}
			else if (Battlemap[i][j] == "∣") {
				cout << RED_LIGHT;
			}
			else {
				cout << HUI;
			}
			cout << Battlemap[i][j] << flush;
		}
		cout << endl;
	}
	for (int i = 0; i < 20; i++) {
		cout << " ";
	}
	cout << PURPLE;
	cout << "敌方攻击力:【" << enemyData[4] << "】,敌方防御力:【" << enemyData[5] << "】,敌方暴击率:【" << enemyData[6] << "%】" << endl;
	cout << endl;
	cout << HUI;
	MyLastHpBarLength = MyHpBarLength;
	EnemyLastHpBarLength = EnemyHpBarLength;
	MyLastEnergyBarLength = MyEnergyBarLength;
	EnemyLastEnergyBarLength = EnemyEnergyBarLength;
	MyLasthealBarLength = MyhealBarLength;
}
int MydataWhenBattle[9] = { 0 };
int EnemydataWhenBattle[7] = { 0 };
void PrintMyCharacterStatus() {
	RuneDevelopment.clear();
	if (RuneNow->GetName() == "死仇") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "A", "Special:死仇", 0.3));
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "A", "Special:死仇", 0.3));
	}
	else if (RuneNow->GetName() == "瘟疫") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "A", "Special:瘟疫", -0.2));
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "A", "Special:瘟疫", -0.2));
	}
	else if (RuneNow->GetName() == "崩溃") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "D", "Special:崩溃", -0.3));
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "D", "Special:崩溃", -0.3));
	}
	else if (RuneNow->GetName() == "狂热") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "IE", "Special:狂热", 2));
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "IE", "Special:狂热", 2));
	}
	else if (RuneNow->GetName() == "迷雾") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "SC", "Special:迷雾", 2));
	}
	else if (RuneNow->GetName() == "贪婪") {
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "A", "Special:贪婪", 0.2));
	}
	else if (RuneNow->GetName() == "救赎") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "D", "Special:救赎", -0.3));
	}
	else if (RuneNow->GetName() == "希望") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "A", "Special:希望", 0.3));
	}
	else if (RuneNow->GetName() == "绝望") {
		RuneDevelopment.push_back(make_shared<Object>(0, "M", "A", "Special:绝望", -0.2));
		RuneDevelopment.push_back(make_shared<Object>(0, "E", "A", "Special:绝望", 0.2));
	}
	//清屏
	Refresh();
	//重新计算当前属性
	mycharacter.CalculateMyNum(RoundBuffGroup);
	RuneDevelopment.clear();
	cout << endl;
	cout <<QING << "==================================================" << RESET << endl;
	cout << QING << "                  【角色状态】" << RESET << endl;
	cout << QING << "==================================================" << RESET << endl;
	cout << endl;

	// 【基础属性栏】统一使用亮红/暗红系
	cout << QING << "  【基础属性】" << RESET << endl;
	cout << QING << "  ────────────────────────────────────────────────" << RESET << endl;
	cout << STAT_HP << "    生命上限          :  " << mycharacter.GetCurrentMaxHP() << RESET << endl;
	cout << STAT_ATK << "    攻击力            :  " << mycharacter.GetCurrentAttack() << RESET << endl;
	cout << GREEN_BRIGHT << "    防御力            :  " << mycharacter.GetCurrentDefense() << RESET << endl;

	cout << endl;

	// 【能量栏】统一使用亮黄系
	cout << QING << "  【能量】" << RESET << endl;
	cout << QING << "  ────────────────────────────────────────────────" << RESET << endl;
	cout << PURPLE << "    能量上限          :  " << mycharacter.GetMaxEnergy() << RESET << endl;
	cout << PURPLE << "    初始能量          :  " << mycharacter.GetInitialEnergy() << RESET << endl;


	cout << endl;

	// 【治疗栏】统一使用亮绿系
	cout << QING << "  【治疗】" << RESET << endl;
	cout << QING << "  ────────────────────────────────────────────────" << RESET << endl;
	cout << STAT_DEF << "    治疗能量上限      :  " << mycharacter.GetMaxHeal() << RESET << endl;
	cout << STAT_DEF << "    初始治疗能量      :  " << mycharacter.GetInitialHeal() << RESET << endl;
	cout <<BLUE_DARK << "    每点治疗能量恢复  :  " <<(int)mycharacter.GetHealHP()*mycharacter.GetCurrentMaxHP() << " 点生命" << RESET << endl;

	cout << endl;

	// 【探险信息栏】统一使用金/紫系（这里用 GOLD_BOLD 凸显财富与等级）
	cout << QING << "  【探险信息】" << RESET << endl;
	cout << QING << "  ────────────────────────────────────────────────" << RESET << endl;
	cout << RED_DARK << "    等级              :  Lv." << mycharacter.GetLevel() << RESET << endl;
	cout << GOLD_BOLD << "    金币              :  " << mycharacter.GetCoins() << RESET << endl;
	cout << endl;
	cout << QING << "  【已获得藏品】" << RESET << endl;
	cout << QING << "  ────────────────────────────────────────────────" << RESET << endl;
	int i = 0;
	cout << "    ";
	for (auto& item : MyObjectGroup) {
		switch (item->GetRarity()) {
		case 1:
			cout << BLUE_S;
			cout << item->GetDescribe() << "  ";
			i++;
			break;
		case 2:
			cout << PURPLE_S;
			cout << item->GetDescribe() << "  ";
			i++;
			break;
		case 3:
			cout << GOLD_S;
			cout << item->GetDescribe() << "  ";
			i++;
			break;
		default:
			break;
		}
		if (item->GetRarity() != 0) {
			if (i % 2 == 0) {
				cout << endl;
				cout << endl;
				cout << "    ";
			}
		}
	}
	if (i == 0) {
		cout <<QING<< "\n    暂未获得藏品" << endl;
	}
	cout << endl;
	cout << QING << "==================================================" << RESET << endl;
	cout << QING << "                    按回车键返回" << RESET << endl;
	cout << QING << "==================================================" << RESET << endl;

	SafeEnter();
}

// ---------- 游戏开场语：符文秘境之门 ----------
void Game_OpeningPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Wer diesen Pfad betritt, verkauft seine Seele an die Ewigkeit," << endl;
	cout << "denn hier erwacht das Verderben aus dem Stein.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（踏上此道者，便是将灵魂出卖给永恒，因为毁灭正自冰冷的石缝中苏醒。）" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << RED_DARK;
	cout << "荒芜的平原上，狂风卷过焦黑的残垣，空气中弥漫着一股铁锈与陈旧羊皮纸的枯寂气味。" << endl;
	cout << "你独自站在那座传说中被世界遗忘的巨大石拱门前，脚下是无数先驱者化为白骨的残骸。" << endl;
	cout << "斑驳的石柱上，密密麻麻的古老符文正闪烁着忽明忽暗的幽蓝微光，仿佛在无声地审视着你的到来。" << endl;
	cout << "远处的深渊深处传来了齿轮咬合的沉闷轰鸣，整座秘境正因你的涉足而发出贪婪的战栗。" << endl;
	cout << "命运的齿轮已然咬合，退路在身后被无形的迷雾彻底封死。" << endl;
	cout << "你深吸了一口气，握紧了手中的武器，毅然踏入了那片未知的黑暗。" << endl;
	cout << HUI << "\n是否要阅读游戏说明？输入1以阅读，回车以跳过..." << endl;
	vector<int> SHUOMING = { 1 };
	int shuomingchoice;
	shuomingchoice=Safecin(SHUOMING, true);
	if (shuomingchoice == 1) {
		GameHelp();
	}
}

void DrawMap_Help(int floor, int step) {
	UpdateMap(floor, step);
	cout << HUI;
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
	cout << HUI;
	switch (floor) {
	case 1:
		cout << "第一层 初始遗迹" << endl;
		cout << endl;
		cout << "远古石碑流转着晦暗的微光，斑驳的苔藓下封印着破碎的咒文。\n唯有踏入这片禁忌废墟，试炼的钟声方才悄然敲响。" << endl;
		break;
	case 2:
		cout << "第二层 迷失回廊" << endl;
		cout << endl;
		cout << "虚无的迷雾中回荡着失落的低语，错综的符文法阵真假难辨。\n唯有堪破内心深处的恐惧，才能寻得通往核心的唯一生路。" << endl;
		break;
	case 3:
		cout << "第三层 终焉圣殿" << endl;
		cout << endl;
		cout << "狂暴的魔力风暴撕裂苍穹，远古神祇的虚影在血色符文中苏醒。\n唯有直面神明的终极审判，方能揭开秘境尘封的真相。" << endl;
		break;
	}
	cout << endl;
	cout << endl;
	cout << RED_DARK;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 100; j++) {
			cout << Themap[i][j] ;
		}
		cout << endl;
	}
	cout << endl;
}
void PrintBalttleGround_Help() {
	cout << WHITE;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";
		}
	}
	string myhp = to_string(200);
	string myHP = to_string(300);
	string enemyhp = to_string(400);
	string enemyHP = to_string(500);
	SupplementDigitNumber(myhp, 4);
	SupplementDigitNumber(myHP, 4);
	SupplementDigitNumber(enemyhp, 4);
	SupplementDigitNumber(enemyHP, 4);
	auto safe_div = [](int a, int b) -> double { return (b > 0) ? (double)a / b : 0.0; };
	double MyHpPercent = safe_div(200, 300);
	double EnemyHpPercent = safe_div(400,500);
	double MyEnergyPercent = safe_div(1, 3);
	int MyEnergyBarLength = (int)(MyEnergyPercent * 19);
	double Myhealpercent = safe_div(2, 3);
	int MyhealBarLength = (int)(Myhealpercent * 19);
	double EnemyEnergyPercent = safe_div(2, 6);
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
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32; j <= 59; j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for (int j = 32; j < 32 + MyHpBarLength; j++) {
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
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6; j <= 24; j++) {
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
	Battlemap[5][18] = to_string(1);
	Battlemap[5][19] = "/";
	Battlemap[5][20] = to_string(3);
	for (int j = 6; j < 6 + MyEnergyBarLength; j++) {
		Battlemap[3][j] = "|";
	}
	//以下为我方治疗条位置
	for (int i = 2; i <= 4; i++) {
		Battlemap[i][66] = "#";
		Battlemap[i][86] = "#";
	}
	for (int j = 67; j <= 85; j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	Battlemap[5][73] = "H";
	Battlemap[5][74] = "e";
	Battlemap[5][75] = "a";
	Battlemap[5][76] = "l";
	Battlemap[5][77] = ":";
	Battlemap[5][78] = to_string(2);
	Battlemap[5][79] = "/";
	Battlemap[5][80] = to_string(3);
	for (int j = 67; j < 67 + MyhealBarLength; j++) {
		Battlemap[3][j] = "|";
	}
	//以下为敌方血量条位置
	for (int i = 15; i <= 17; i++) {
		Battlemap[i][31] = "#";
		Battlemap[i][60] = "#";
	}
	for (int j = 32; j <= 59; j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	for (int j = 32; j < 32 + EnemyHpBarLength; j++) {
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
	for (int i = 15; i <= 17; i++) {
		Battlemap[i][5] = "#";
		Battlemap[i][25] = "#";
	}
	for (int j = 6; j <= 24; j++) {
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
	Battlemap[14][18] = to_string(2);
	Battlemap[14][19] = "/";
	Battlemap[14][20] = to_string(6);
	for (int j = 6; j < 6 + EnemyEnergyBarLength; j++) {
		Battlemap[16][j] = "|";
	}
	Battlemap[16][73] = "R";
	Battlemap[16][74] = "o";
	Battlemap[16][75] = "u";
	Battlemap[16][76] = "n";
	Battlemap[16][77] = "d";
	Battlemap[16][78] = to_string(0);
	Battlemap[16][79] = to_string(5);
	// 等待用户输入 - 显示 "Please input..."
	string prompt = "Please input...";
	int prow = 9;
	int pcol = 39; // 从原有位置开始填充
	for (size_t k = 0; k < prompt.size(); ++k) {
		if (pcol + (int)k >= 0 && pcol + (int)k < Battlecol)
			Battlemap[prow][pcol + k] = string(1, prompt[k]);
	}
	for (int i = 0; i < 20; i++) {
		cout << " ";
	}
	cout << "我方攻击力:【" << 80 << "】,我方防御力:【" << 100 << "】,每剂治疗量:【" << 30 << "】" << endl;
	//打印地图
	for (int i = 0; i < Battlerow; i++) {
		for (int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j] << flush;
		}
		cout << endl;
	}
	for (int i = 0; i < 20; i++) {
		cout << " ";
	}
	cout << "敌方攻击力:【" << 80 << "】,敌方防御力:【" << 50 << "】,敌方暴击率:【" << 30 << "%】" << endl;
	cout << endl;
	cout << HUI;
}
void GameHelp() {
	Refresh();
	cout << BLUE << "本游戏为基于终端的Roguelike类MUD游戏" << endl;
	cout << "游戏地图如下：(例)" << endl;
	cout << endl;
	DrawMap_Help(2, 1);
	cout << RED_DARK << "当前符文(例)为：" << endl;
	cout << "//死仇：我方和敌方的攻击力+30%//" << endl;
	PrintMaphelp();
	cout << endl;
	cout << BLUE;
	cout <<HUI << "玩法介绍" << endl;
	cout << "符文秘境一共有三层，通过三层后即为通关。" << endl;
	cout << "中途在战斗过程中血量归零则游戏结束。" << endl;
	cout << BLUE;
	cout << "\n每层都会随机刷新出一个带有特殊增益减益效果的符文，符文效果仅作用于该层。一些事件可能可以改变该层符文。" << endl;
	cout << RED_DARK;
	cout << "\n战斗节点中可通过与敌人战斗，战斗胜利后获得升级，金币与随机藏品" << endl;
	cout << "其中升级后生命值，攻击力与防御力均能得到提升。" << endl;
	cout << "金币可以用与在商店购买不同稀有度的藏品" << endl;
	cout << "藏品为获得后将作用于一整局的增益效果，可通过战斗掉落，商店购买与事件获得。" << endl;
	cout << BLUE;
	cout << "\n未知事件节点中，玩家可以通过碰到不同的事件，触发不同的增益减益效果，获取资源等。部分未知事件节点带有特殊效果。" << endl;
	cout <<HUI<< "\n按回车以进入战斗界面说明..." << endl;
	SafeEnter();
	Refresh();
	cout << BLUE << "战斗画面如下：" << endl;
	cout << WHITE;
	cout << endl;
	PrintBalttleGround_Help();
	cout << HUI;
	cout << "请选择本回合的行动：" << endl;
	cout << "1.攻击" << endl;
	cout << "2.防御(不攻击且防御力提升至2倍)" << endl;
	cout << "3.释放技能";
	cout << "(我方技能为：//使对方攻击力在3回合内下降30%，并攻击一次//)" << endl;
	cout << "4.治疗";
	cout << "(治疗条能量不低于2时将额外进行一次防御)";
	cout << "(将消耗所有治疗条进行治疗，每点治疗条回复30点生命值)";
	cout << endl;
	cout << BLUE;
	cout << endl;
	cout << "战斗为回合制。我方回合开始。" << endl;
	cout << RED_WINE << "每次战斗开始时都会回复我方生命值至当前生命值的上限。" << endl;
	cout <<QING<< "每回合可以选择攻击，防御，释放技能和治疗。具体效果如上所示。" << endl;
	cout << RED_WINE << "选择攻击或防御时可以同时选择为能量条或治疗条的其中之一充能。" << endl;
	cout <<BLUE<< "能量条满时可以释放技能，技能在战斗开始前根据提供的敌人的属性在随机列表中选择。" << endl;
	cout << "治疗条不为空时可以消耗所有治疗能量进行治疗，每点能量为自己回复生命值上限一定比率的生命值。" << endl;
	cout << YELLOW << "\n在对战斗玩法熟悉后，可以直接在输入界面同时输入该回合行动与充能方向，如输入" << RED_BOLD << "\"12\"" << YELLOW << "代表攻击且为治疗条充能" << endl;
	cout << BLUE << "\n在敌方回合中，敌方默认进行普通攻击，每次攻击均会为敌方能量条充能。" << endl;
	cout << RED_WINE << "请注意，敌方攻击时有概率触发暴击，造成数倍伤害，基础暴击伤害为敌方攻击力的2倍。敌方的暴击率见战场下方的标识。基础暴击率为30%" << endl;
	cout << RED_WINE << "敌方技能能量满之后将释放技能，释放技能时必定暴击。" << endl;
	cout << RED_WINE << "每十回合敌方的暴击率增加5%，上回合敌方暴击后本回合暴击率降至0。(本回合为技能回合除外)" << endl;
	cout <<HUI<< "\n按回车进入游戏..." << endl;
	SafeEnter();
}

// ---------- 游戏战败：陨落与归寂 ----------
void Game_GameOverPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Der Vorhangfaellt, und die Nacht verschlingt den letzten Funken," << endl;
	cout << "denn der Pfad war stumm und unerbittlich.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（帷幕落下，黑夜吞噬了最后一丝火星，因为这条道途是沉默而冷酷的。）" << endl;
	cout << endl;
	cout << RED_DARK;
	cout << "剧烈的痛楚在一瞬间被冰冷彻底剥离，你手中的武器发出不堪重负的哀鸣，最终从无力的掌心滑落。" << endl;
	cout << "视野中的血色与微光开始疯狂褪去，取而代之的是无边无际的深邃黑暗。" << endl;
	cout << "你单膝跪倒在残破的石砖上，靴底渗出的鲜血与地面上古老的符文交织在一起，渗入这片被诅咒的土地。" << endl;
	cout << "远处的机括声渐渐归于死寂，那些曾经冷眼注视你前行的雕像仿佛在黑暗中发出了无声的嘲弄。" << endl;
	cout << "无数先驱者的骸骨在你的身旁隐现，它们向你伸出冰冷的手掌，将你彻底拉入永恒的沉眠。" << endl;
	cout << "你未竟的宏愿与所有的挣扎，最终都化作了废墟深处一段无人知晓的悲鸣。" << endl;
	cout << HUI << "\n按回车以返回标题界面..." << endl;
	SafeEnter();
}

// ---------- 游戏通关：破晓与荣光 ----------
void Game_VictoryPrologue(bool IfHard) {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Wer den Abgrund bezwingt, bricht den Fluch der Eiseskaelte," << endl;
	cout << "und das Licht erobert den ewigen Thron zurueck.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（征服深渊者，终能打破极寒的诅咒，而光明也将重新夺回永恒的王座。）" << endl;
	cout << endl;
	cout << RED_DARK;
	cout << "随着最后一尊盘踞在深渊之底的古老灾厄在你剑下轰然崩解，整座秘境爆发出了前所未有的剧烈震颤。" << endl;
	cout << "厚重的穹顶在头顶碎裂，压抑了千百年的铅灰色阴云被一道刺破苍穹的金芒彻底撕开。" << endl;
	cout << "温热的晨曦如潮水般涌入这座暗无天日的地下废墟，将那些斑驳的符文与诡异的黑霜尽数净化。" << endl;
	cout << "你站在堆满宝藏与残骸的王座前，手中的剑刃正闪烁着历经血战后的耀眼辉光。" << endl;
	cout << "那些曾经禁锢你前行的迷雾与锁链在阳光下化作点点流光，消散在呼啸而过的自由之风中。" << endl;
	cout << "你用双脚丈量了这片被遗忘的绝望之地，并用手中的利刃为自己劈开了一条通往新生的道路。" << endl;
	cout << endl;
	cout << endl;
	cout << RED_BOLD;
	cout << "你通关了该游戏的";
	if (IfHard) {
		cout << "困难模式" << endl;
	}
	else {
		cout << "普通模式" << endl;
	}
	cout << endl;
	cout << BLUE << "感谢游玩" << endl;
	cout << "\n制作：" << endl;
	cout << "Dillionzcg" << endl;
	cout << "HungryZ06" << endl;
	cout << "Quntriumpth" << endl;
	cout << "yanami126" << endl;
	cout << "zl0323280" << endl;
	cout << "\n项目github仓库地址：" << endl;
	cout << "https://github.com/Dillionzcg/gamedesign" << endl;
	cout << HUI << "\n按回车以返回标题界面..." << endl;
	SafeEnter();
}

//第一层商店文案
void FirstFloor_ShopPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Im Schatten der alten Ruinen handelt der Tod mit vergessenen Schaetzen," << endl;
	cout << "doch jeder Preis ist mit Blut bezahlt.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（在古老遗迹的阴影中，死神与人交易着被遗忘的宝藏，但每一份代价皆以鲜血支付。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "斑驳的石柱后隐匿着一处干燥的石室，四周的墙壁上爬满了枯萎的苔藓与残破的咒文符刻。" << endl;
	cout << "一盏燃烧着幽绿色鬼火的烛台下，一个身披厚重破旧斗篷的身影正无声地盘腿坐在堆满货箱的角落里。" << endl;
	cout << "你确信来时的路上这里绝无活物，而当你的脚步声打破死寂时，那身影缓缓抬起了头。" << endl;
	cout << "阴影之中，一张苍白干裂的脸庞若隐若现，对方非但没有半点面对生者的惊慌，反而咧开嘴，露出一排森冷可怖的笑容。" << endl;
	cout << "他自始至终没有吐露半个字，只是用枯瘦如柴的手指在冰冷的石桌上轻轻敲击——桌面上，赫然摆放着各种散发着诡异灵光的远古遗物与稀罕秘宝。" << endl;
	cout << "在这个危机四伏的废墟深处，这个来历不明的哑巴人仿佛早已在此等候你的多时，空气中弥漫着令人毛骨悚然的诡异契约感。" << endl;
	cout << endl;
	cout << HUI << "（当前拥有金币数： " << GOLD_BOLD << mycharacter.GetCoins() << HUI << " ）" << endl;
	cout << HUI << "\n按回车键以进入商店..." << endl;
	SafeEnter();
}

//第二层商店文案

// ---------- 第二层商店节点：迷失回廊的幻影商铺 ----------
void SecondFloor_ShopPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Im truebenden Nebel sucht die Habgier vergebens nach Wahrheit," << endl;
	cout << "doch der Handel schliesst den Kreis der Furcht.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（在迷蒙的雾气中，贪婪徒劳地寻找着真相，但交易却闭合了恐惧的环路。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "虚无的迷雾在四周翻滚流淌，回荡着失落低语的回廊中，竟凭空出现了一座结构错综复杂的奇异石亭。" << endl;
	cout << "亭内悬浮着数道明灭不定的符文法阵，真假难辨的光影将四周切割得光怪陆离。" << endl;
	cout << "那个披着破旧斗篷的哑巴商人正安然坐在法阵中央的石椅上，仿佛早已算准了你会从迷雾中蹚出一条生路。" << endl;
	cout << "他枯瘦的手指在石桌上轻轻叩击，发出清脆的回响。桌面上摆满了散发着奇异灵光的秘宝与卷轴。" << endl;
	cout << "他依旧闭口不言，只是用那双空洞而贪婪的眼睛死死盯着你，无声地等待着这场虚实交织的交易。" << endl;
	cout << endl;
	cout << HUI << "（当前拥有金币数： " << GOLD_BOLD << mycharacter.GetCoins() << HUI << " ）" << endl;
	cout << HUI << "\n按回车键以进入商店..." << endl;
	SafeEnter();
}

//第三层商店文案

// ---------- 第三层商店节点：终焉圣殿的宿命重逢 ----------
void ThirdFloor_ShopPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Vor den Toren des letzten Urteils feilschen die Seelen mit dem Verderben," << endl;
	cout << "und der Preis ist das Ende aller Tage.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（在终极审判之门前，灵魂与毁灭讨价还价，而代价便是万物的终结。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "狂暴的魔力风暴在圣殿穹顶外撕裂苍穹，血色符文将整座巨殿映照得如同修罗场般猩红。" << endl;
	cout << "在这片连空气都因神明苏醒而战栗的废墟边缘，却诡异地隔绝出一片死寂的避风港。" << endl;
	cout << "一个熟悉的身影端坐在神坛残垣之上——从第一层深渊开始，那个一路阴魂不散的哑巴商人正静静地等在这里。" << endl;
	cout << "他那件破旧的斗篷在狂风中猎猎作响，脚下堆满了成箱的古老财宝与沾满神魔血迹的残骸。" << endl;
	cout << "当你的靴底踏碎脚边的枯骨，他缓缓抬起头。苍白的面孔上，咧开一个无声而森冷的弧度。" << endl;
	cout << "没有言语，也没有多余的动作。他只是枯瘦的手指一拂，将几件散发着诡异压迫感的终局遗物推上了冰冷的石台。" << endl;
	cout << "在这场通往毁灭的旅途尽头，他仿佛早已备好了所有的筹码，冷冷注视着你将最后的生机与财富一并押上这最后的赌局。" << endl;
	cout << endl;
	cout << HUI << "（当前拥有金币数： " << GOLD_BOLD << mycharacter.GetCoins() << HUI << " ）" << endl;
	cout << HUI << "\n按回车键以进入商店..." << endl;
	SafeEnter();
}


// ---------- 第一层普通战斗节点（压迫、诡异、恐怖主题） ----------
void FirstFloor_UniqueBattlePrologue() {
	static vector<int> battlePool;
	static size_t currentIndex = 3;

	if (currentIndex >= 3 || battlePool.empty()) {
		battlePool = rm.getSomeNum(1, 3, 3); 
		currentIndex = 0;
	}

	int battleType = battlePool[currentIndex++];

	Refresh();

	switch (battleType) {
	case 1:
		// 变体一：无声的审判（纯粹的心理压迫感与窒息）
		cout << RED_BOLD;
		cout << "\n\"Ein alter Eid rostet im Schutt, und das Schweigen erdrueckt die Seele.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（古老的誓言在废墟中生锈，而这无边的死寂足以将灵魂生生压碎。）" << endl;
		cout << endl;
		cout << "四周的石壁仿佛在以极其缓慢的幅度向内挤压，空气变得粘稠如铁，每一次呼吸都带著肺腑的刺痛。" << endl;
		cout << "前方漆黑的拱门下，一尊披挂着残破重铠的高大身影无声伫立，它没有呼吸，也听不到任何生机。" << endl;
		cout << "但在它空洞的头盔面罩内，两团冰冷的幽蓝魂火正死死锁死在你的身上。" << endl;
		cout << "一种被远古死物彻底看透的战栗感瞬间窜上脊背，周遭的空间仿佛在此刻彻底凝固。" << endl;
		break;
	case 2:
		// 变体二：深渊的凝视（无形窥视与理智剥离的恐怖）
		cout << RED_BOLD;
		cout << "\n\"Im blinden Nebel fluestern die Schatten, die niemals lebten.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（在盲目的迷雾中，那些从未真正活过的影子正在窃窃私语。）" << endl;
		cout << endl;
		cout << "脚下的古老石板隐隐透出诡异的靛蓝色反光，仿佛你正踩在某种深不可测的巨大眼球之上。" << endl;
		cout << "四周的阴影违背常理地扭曲着，明明空无一物，耳畔却不断响起无数人在重叠呢喃的低语声。" << endl;
		cout << "空气中弥漫着理智正在融化的虚无感，仿佛只要多看一眼黑暗深处，脑海中就会多出一段不属于你的恐怖记忆。" << endl;
		cout << "黑暗中，某种不可名状的轮廓正伴随着诡异的折射光线缓缓逼近，带来令人窒息的精神威压。" << endl;
		break;
	case 3:
	default:
		// 变体三：禁忌的苏醒（远古法则与空间压制）
		cout << RED_BOLD;
		cout << "\n\"Wenn der Stein sich regt, bricht das Urteil ueber den Geist.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（当巨石开始运转，对生者意志的终极审判便已降临。）" << endl;
		cout << endl;
		cout << "这是一处空旷得令人绝望的地下广场，残破的巨型石柱孤零零地支撑着不见尽头的穹顶。" << endl;
		cout << "没有任何预兆，远处的残垣断壁间突然腾起一团不自然的深紫色迷雾，周遭的空气在高温与极寒中剧烈扭曲。" << endl;
		cout << "那一刻，整座废墟的重力仿佛骤然倍增，压得人膝盖发酸。一尊由黑色禁忌晶石雕琢而成的巨大守卫自虚空中凝聚成形。" << endl;
		cout << "它胸口那颗猩红的非自然核心甫一亮起，便将周遭的光线尽数吞噬，散发出一种不容抗拒的绝对毁灭气息。" << endl;
		break;
	}

	cout << HUI << "\n按回车键以进入战斗..." << endl;
	SafeEnter();
}



// ---------- 第一层 BOSS 节点：异化教宗的圣殿审判 ----------
void FirstFloor_BossPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Der letzte Hirte kniet im Ascheregen, und sein Gebet ist ein Todesurteil.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（最后的牧羊人跪在灰烬之雨中，他的祈祷便是死刑的判决。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "你推开最后一扇沉重的黑铁圣门，迎面而来的不是风，而是一股浓烈到令人窒息的冷香与陈旧干涸的檀木气息。" << endl;
	cout << "这里是修道院最核心的大礼拜堂。数十根庞大的巨型石柱支撑着幽暗的穹顶，无数面残破的圣徒壁画在微弱的血色月光下显得光怪陆离。" << endl;
	cout << "\n空旷的中央大殿内，没有信徒，没有颂歌，只有成千上万根燃烧的白烛静静地插在倒悬的十字架上，蜡油如凝固的血泪般剥落。" << endl;
	cout << "在最高处的主祭坛前，那个身影背对着你静静伫立——那是这座圣殿的最高统治者，如今却已被某种不可名状的伟力彻底异化。" << endl;
	cout << "\n他那件原本洁白如雪的教宗法袍早已和枯萎的血肉长在一起，后背的脊骨硬生生刺穿布料，延展出数道畸形、宛如巨大羽翼般的惨白骨刺。" << endl;
	cout << "仿佛察觉到了生者的气息，那具庞大而扭曲的身躯缓缓转过身来。" << endl;
	cout << "\n在他的面部，没有眼睛，也没有嘴唇，唯有一轮不断向外渗出黑色圣水的实体光环死死嵌在颅骨之上，散发出令人灵魂战栗的绝对威压。" << endl;
	cout << "整个空间在此刻陷入绝对的死寂，他缓缓抬起那只枯瘦如柴、覆盖着黑色鳞片的手掌，向你降下了第一层最终的审判。" << endl;
	cout << endl;
	cout << HUI << "\n按回车键以进入boss战斗..." << endl;
	SafeEnter();
}

#include "Map.h"
#include <vector>

// ---------- 第二层普通战斗节点（内含不重复随机文案管理） ----------
void SecondFloor_UniqueBattlePrologue() {
	static vector<int> battlePool;
	static size_t currentIndex = 4;

	// 如果刚进入第二层或者前四种文案已经用完，重新洗牌
	if (currentIndex >= 4 || battlePool.empty()) {
		battlePool = rm.getSomeNum(1, 4, 4);
		currentIndex = 0;
	}

	int battleType = battlePool[currentIndex++];

	Refresh();

	// 根据随机结果输出四种更具沉浸感与威胁性的战斗开场
	switch (battleType) {
	case 1:
		// 变体一：潮湿的水道（阴暗与潜伏的掠食者）
		cout << RED_BOLD;
		cout << "\n\"Im finsteren Schlamm kriecht das Vergessen, das niemals ruht.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（在黑暗的淤泥中，永不歇息的遗忘正在匍匐前行。）" << endl;
		cout << endl;
		cout << "脚下的石板路已被漫进来的冰冷黑水淹没，每走一步都会溅起粘稠的波纹，空气中弥漫着一股浓重的咸腥气味。" << endl;
		cout << "两侧低矮的拱形涵洞内，积水突然剧烈翻涌起来。一头身形佝偻、浑身覆盖着灰白鳞片的类人怪物从阴影中猛地站起。" << endl;
		cout << "它那双惨白的眼睛死死盯住你，手中拖拽着一柄生锈的鱼叉，喉咙里发出野兽般沙哑的咯咯声。" << endl;
		cout << "水花四溅中，它已经带着刺骨的寒意朝你直扑过来。" << endl;
		break;
	case 2:
		// 变体二：残破的藏书库（被诅咒的学者傀儡）
		cout << RED_BOLD;
		cout << "\n\"Verstaubtes Wissen brennt wie Feuer in den kalten Hallen.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（陈旧的知识在这冰冷的殿堂中，如同烈火般灼烧。）" << endl;
		cout << endl;
		cout << "这是一间死气沉沉的地下图书馆，高大的书架上堆满了腐烂的羊皮卷，无数碎纸片像雪花般在阴风中胡乱飘散。" << endl;
		cout << "在成堆的典籍中央，一尊身穿破烂长袍、由干枯皮肉与铁架拼凑而成的畸形学者僵硬地转过身。" << endl;
		cout << "它空洞的眼窝里没有眼珠，只有两团跳动的幽绿色鬼火，枯瘦的手指正死死扣住一本散发着黑气的厚重古籍。" << endl;
		cout << "伴随着纸张撕裂的尖啸，它扬手甩出一道由文字凝成的冰冷气刃，直逼你的面门。" << endl;
		break;
	case 3:
		// 变体三：坍塌的矿坑（重压与狂暴的工程造物）
		cout << RED_BOLD;
		cout << "\n\"Schwere Ketten brechen das Schweigen der tiefen Erde.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（沉重的铁锁，打破了深层大地的死寂。）" << endl;
		cout << endl;
		cout << "头顶斜插着断裂的粗大原木，四周是开凿粗糙的岩壁，厚厚的煤灰与铁锈味混合在一起，呛得人胸口发闷。" << endl;
		cout << "前方狭窄的通道被一架庞大的废弃矿车堵死，而在矿车后方，一头由黄铜与黑铁铸造的重型守卫正挥舞着巨锤砸碎岩石。" << endl;
		cout << "它听到了你的脚步声，沉重的头颅咔哒一声转了过来，胸口破损的炉膛内陡然喷出一股炽热的黑烟。" << endl;
		cout << "它咆哮着撞碎挡路的障碍，带着沉闷的轰鸣声向你横冲直撞而来。" << endl;
		break;
	case 4:
	default:
		// 变体四：狭窄的哨所（埋伏的守夜人残党）
		cout << RED_BOLD;
		cout << "\n\"Der letzte Waechter vergisst seinen Posten nie.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（最后的守夜人，永远不会遗忘他的职责。）" << endl;
		cout << endl;
		cout << "这是一个废弃已久的地下哨卡，残破的拒马和木质路障七零八落地倒在地上，四周挂着几盏早已熄灭的铁皮风灯。" << endl;
		cout << "阴影里，一个身披重铠、身形魁梧的哨所守卫长静静地靠在墙边，仿佛已经和冰冷的岩石融为一体。" << endl;
		cout << "当你从他身旁走过时，他那把生满铁锈的重剑突然出鞘，擦着地面划出一溜刺耳的火星。" << endl;
		cout << "他没有发出任何声音，只是用那冰冷的铁面具面对着你，随后大步跨出，挥起重剑当头劈下。" << endl;
		break;
	}

	cout << HUI << "\n按回车键以进入战斗..." << endl;
	SafeEnter();
}


// ---------- 第二层 BOSS 节点：深渊档案馆的首席学者 ----------
void SecondFloor_BossPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Jede Seite, die nicht verbrennt, wird zum Grab fuer den Verstand.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（每一页未能燃尽的纸张，最终都化作了埋葬理智的坟墓。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "你推开最后一扇半掩的青铜巨门，滚烫而干燥的热浪伴随着浓烈的陈年墨水气味扑面而来。" << endl;
	cout << "这里是一处空间广阔得近乎无垠的地下档案馆。数百万册泛黄的巨型古籍堆积成高耸入云的书山，无数碎裂的羊皮纸在昏暗的虚空中如雪般无声飘落。" << endl;
	cout << "\n在空旷大厅的正中央，无数条由黑色活体墨水汇聚而成的溪流在地面上纵横交错，发出令人毛骨悚然的咕嘟声。" << endl;
	cout << "在那片墨水汇聚的源头，一个身高数米、身披残破学者长袍的高大身影正背对着你悬浮在半空。" << endl;
	cout << "\n他的上半身依然维持着人类学者的轮廓，但双臂和下半身早已彻底融化，同成千上万册翻卷的巨型禁忌典籍纠缠在一起，化作一团不断蠕动的庞大肉质书卷。" << endl;
	cout << "仿佛察觉到了生者的呼吸，那个畸形的庞大身躯极其生硬地转了过来。" << endl;
	cout << "在他的面部，没有眼睛，也没有鼻梁，只有一张裂开到耳根、由密密麻麻活体文字缝合而成的巨口，正向外喷吐着泛蓝的死寂辉光。" << endl;
	cout << "\n伴随着无数书页疯狂翻动的巨大轰鸣，他缓缓抬起那条由厚重典籍拼凑而成的巨臂，向你降下了第二层最终的审判。" << endl;
	cout << endl;
	cout << HUI << "\n按回车键以进入boss战斗..." << endl;
	SafeEnter();
}


// ---------- 第三层普通战斗节点（末日与终局主题，内含不重复随机文案管理） ----------
void ThirdFloor_UniqueBattlePrologue() {
	// 静态变量保存当前层的战斗变体顺序，确保同一局游戏中前五次绝不重复
	static vector<int> battlePool;
	static size_t currentIndex = 5;

	// 如果刚进入第三层或者前五种文案已经用完，重新洗牌
	if (currentIndex >= 5 || battlePool.empty()) {
		battlePool = rm.getSomeNum(1, 5, 5); // 调用你的 RandomManager 获取 1 到 5 的不重复排列
		currentIndex = 0;
	}

	int battleType = battlePool[currentIndex++];

	Refresh();

	// 根据随机结果输出五种极致的末日与终局感
	switch (battleType) {
	case 1:
		// 变体一：破碎的天幕（世界边界的解体）
		cout << RED_BOLD;
		cout << "\n\"Der Himmel bricht in Scherben, und die Welt verliert ihren Halt.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（天幕碎裂成无数晶片，而整个世界再也找不到落脚之处。）" << endl;
		cout << endl;
		cout << "头顶原本坚固的穹顶彻底消失，取而代之的是一片翻滚着混沌紫黑气旋的无垠虚空，无数碎裂的大陆板块正在深渊中缓缓下坠。" << endl;
		cout << "你脚下的路只剩下一条窄得可怜的残破石梁，四周不断有狂暴的时空乱流呼啸而过，将空气撕扯得粉碎。" << endl;
		cout << "在虚空的风暴边缘，一尊由破碎星屑与重铠拼凑而成的无面末日巨人正挥舞着巨刃踏碎虚空而来。" << endl;
		cout << "它每向前一步，脚下的空间便彻底坍塌湮灭，将最后的退路尽数封死。" << endl;
		break;
	case 2:
		// 变体二：熄灭的星火（文明终结的死寂）
		cout << RED_BOLD;
		cout << "\n\"Das letzte Licht erlischt, und das Nichts fordert seinen Zoll.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（最后一抹微光彻底熄灭，而虚无正在索取它应得的代价。）" << endl;
		cout << endl;
		cout << "这是一处曾经无比辉煌、如今却彻底化作焦土的远古王座大厅，四周悬挂着无数熄灭了成百上千年的巨型黑铁烛台。" << endl;
		cout << "空气中连最后一丝温度都已抽离，唯有无孔不入的绝对冰冷像无数根细针般刺入骨髓。" << endl;
		cout << "在王座前方残破的废墟中，一具身披残破帝王冕服、浑身燃烧着幽蓝末日残火的高大焦黑枯骨缓缓站直了身躯。" << endl;
		cout << "他手中那柄断裂的权杖轻轻顿地，一股横扫一切的冰冷死寂瞬间向你横推而至。" << endl;
		break;
	case 3:
		// 变体三：枯萎的根源（世界树残骸与终焉之兽）
		cout << RED_BOLD;
		cout << "\n\"Wenn die Wurzeln sterben, faellt auch die letzte Hoffnung.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（当根基彻底枯死，最后的希望也随之陨落。）" << endl;
		cout << endl;
		cout << "四周全是被某种不可名状的力量彻底腐化、变成灰白色的巨型枯木与庞大根系，它们如巨蟒般交错盘结在不见天日的深渊两侧。" << endl;
		cout << "厚重的灰色孢子雾气在死寂的空气中缓缓飘荡，每一次呼吸都带著肺腑被冰封的剧痛。" << endl;
		cout << "在交错的枯根深处，一头体型堪比山峦、浑身覆盖着惨白骨甲与腐朽枝桠的四足巨兽正睁开猩红的双眼。" << endl;
		cout << "它没有发出任何咆哮，只是带着摧毁一切生机的绝对重压，朝着你直冲而下。" << endl;
		break;
	case 4:
		// 变体四：终焉的审判庭（因果律的断裂）
		cout << RED_BOLD;
		cout << "\n\"Das Gesetz der Goetter ist verbrannt, und das Urteil ist gesprochen.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（诸神的律法已被焚烧，而审判早已尘埃落定。）" << endl;
		cout << endl;
		cout << "这是一处呈现出非欧几里得几何扭曲的宏大审判广场，无数巨大的黑色石碑自地面斜刺里倒插入虚空，违背了所有的重力常识。" << endl;
		cout << "广场中央悬浮着一轮不断向外喷涌黑色雷霆的破碎日轮，将所有残存的光线扭曲成病态的惨绿色。" << endl;
		cout << "在扭曲的立柱阴影中，三个身披重度侵蚀黑袍、面部被纯铁面具焊死的审判官正无声无息地并肩出现。" << endl;
		cout << "他们手中同时扬起刺目的审判之刃，将整个空间的退路彻底锁死在绝望的网格之中。" << endl;
		break;
	case 5:
	default:
		// 变体五：虚无的洪流（万物归寂的深渊）
		cout << RED_BOLD;
		cout << "\n\"Alles fliesst in den Abgrund, bis nichts mehr uebrig bleibt.\"" << endl;
		cout << RED_DARK;
		cout << endl;
		cout << "（万物终将流向深渊，直到连残渣也不复存在。）" << endl;
		cout << endl;
		cout << "你站在通往世界尽头的最后一级黑色阶梯上，阶梯下方是连光线都无法逃脱的纯黑虚无，正以肉眼可见的速度向上侵蚀。" << endl;
		cout << "四周所有的建筑、岩石和废墟都在抵达这里的瞬间化作无数细碎的黑色沙砾，消散在无形的罡风中。" << endl;
		cout << "在虚无的浪潮正前方，一个由无数痛苦面孔与流动黑水拼凑而成的庞大无定形巨怪正从深渊中缓缓探出半身。" << endl;
		cout << "它空洞的核心处散发着一种让万物归寂的恐怖引力，向你发起了终局的挑战。" << endl;
		break;
	}

	cout << HUI << "\n按回车键继续..." << endl;
	SafeEnter();
}


// ---------- 第三层 BOSS 节点：世界本身的终局审判 ----------
void ThirdFloor_BossPrologue() {
	Refresh();
	cout << RED_BOLD;
	cout << "\n\"Wenn das Rad der Welt zerbricht, wird das Ende zum einzigen Gesetz.\"" << endl;
	cout << RED_DARK;
	cout << endl;
	cout << "（当世界的巨轮彻底粉碎，终结便化作了唯一的法则。）" << endl;
	cout << endl;

	cout << RED_DARK;
	cout << "你终于走到了所有道路的尽头。这里没有地面，没有天空，也没有光芒，只有一片悬浮在无垠深渊之上的破碎废墟。" << endl;
	cout << "远处的星辰早已熄灭成冰冷的死灰，整个世界的边界正像一张被烈火焚烧的羊皮纸般，无可挽回地向内卷曲、崩塌。" << endl;
	cout << "\n在这片万物归寂的虚无中心，端坐着这个世界最后的模样——它庞大得无法用言语形容，由亿万年流淌的文明残骸、破碎的大陆板块与无数干枯的星轨交织纠缠在一起。" << endl;
	cout << "那是一尊没有面孔、没有终点的宏大庞然之物，它既是创造这片苦难废墟的摇篮，也是埋葬一切因果的终极墓穴。" << endl;
	cout << "\n仿佛察觉到了你这个历经千难万险终于抵达终点的异乡人，那座由世界残骸拼凑而成的庞大身躯极其缓慢地向前倾斜。" << endl;
	cout << "在它那空洞的核心深处，亿万道熄灭的极光同时迸发出病态的惨白辉光，将整个破碎的虚空彻底照亮。" << endl;
	cout << "没有怒吼，没有审判，整个宇宙残存的重力在这一刻尽数压向你的双肩——世界本身，向你投来了冰冷而绝对的注视。" << endl;
	cout << endl;
	cout << HUI << "\n按回车键继续..." << endl;
	SafeEnter();
}