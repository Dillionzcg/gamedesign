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
	cout <<BLUE_DARK << "    每点治疗能量恢复  :  " << mycharacter.GetHealHP() << " 点生命" << RESET << endl;

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
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 100; j++) {
			cout << Themap[i][j] ;
		}
		cout << endl;
	}
	cout << endl;
}
void PrintBalttleGround_Help() {
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
	cout << YELLOW << "将窗口全屏以获得最佳游戏体验" << endl;
	cout << BLUE << "本游戏为基于终端的Roguelike类MUD游戏" << endl;
	cout << "游戏地图如下：" << endl;
	cout << endl;
	DrawMap_Help(2, 1);
	cout << "当前符文为：" << endl;
	cout << "//死仇：我方和敌方的攻击力+30%//" << endl;
	PrintMaphelp();
	cout << endl;
	cout << BLUE;
	cout << "符文秘境一共有三层，通过三层后即为通关。" << endl;
	cout << "中途在战斗过程中血量归零则游戏结束。" << endl;
	cout << "\n每层都会随机刷新出一个带有特殊增益减益效果的符文，符文效果仅作用于该层。一些事件可能可以改变该层符文。" << endl;
	cout << "\n战斗节点中可通过与敌人战斗，战斗胜利后获得升级，金币与随机藏品" << endl;
	cout << "其中升级后生命值，攻击力与防御力均能得到提升。" << endl;
	cout << "金币可以用与在商店购买不同稀有度的藏品" << endl;
	cout << "藏品为获得后将作用于一整局的增益效果，可通过战斗掉落，商店购买与事件获得。" << endl;
	cout << "\n未知事件节点中，玩家可以通过碰到不同的事件，触发不同的增益减益效果，获取资源等。部分未知事件节点带有特殊效果。" << endl;
	cout <<HUI<< "\n按回车以进入战斗界面说明..." << endl;
	SafeEnter();
	Refresh();
	cout << BLUE << "战斗画面如下：" << endl;
	cout << HUI;
	cout << endl;
	PrintBalttleGround_Help();
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
	cout << "每回合可以选择攻击，防御，释放技能和治疗。具体效果如上所示。" << endl;
	cout << RED_WINE << "选择攻击或防御时可以同时选择为能量条或治疗条的其中之一充能。" << endl;
	cout <<BLUE<< "能量条满时可以释放技能，技能在战斗开始前根据提供的敌人的属性在随机列表中选择。" << endl;
	cout << "治疗条不为空时可以消耗所有治疗能量进行治疗，每点能量为自己回复一定生命值。" << endl;
	cout << RED_WINE << "在对战斗玩法熟悉后，可以直接在输入界面同时输入该回合行动与充能方向，如输入\"12\"代表攻击且为治疗条充能" << endl;
	cout << BLUE << "\n在敌方回合中，敌方默认进行普通攻击，每次攻击均会为敌方能量条充能。" << endl;
	cout << RED_WINE << "请注意，敌方攻击时有概率触发暴击，造成数倍伤害，基础暴击伤害为敌方攻击力的2倍。敌方的暴击率见战场下方的标识。基础暴击率为30%" << endl;
	cout << RED_WINE << "敌方技能能量满之后将释放技能，释放技能时必定暴击。" << endl;
	cout << RED_WINE << "每十回合敌方的暴击率增加10%，上回合敌方暴击后本回合暴击率降至0。(本回合为技能回合除外)" << endl;
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
void Game_VictoryPrologue() {
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