/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*使用rm.getSomeNum(min,max,k)以获得一定范围（闭区间）的k个不重复随机int，返回vector<int>
*使用a=Safecin(legal,length,ifblank)以获得合法输入，
 legal为合法数字数组(int数组)，length为数组长度(int)，ifblank为是否允许空输入(bool值)
*使用WaitForSeconds(second)以等待特定秒数(double)
*/
#include<iostream>
#include<random>
#include<vector>
#include<memory>
#include<string>
#include<numeric>
#include<algorithm>
#include<stdexcept>
#include<thread>   
#include<chrono>
using namespace std;
//符文文本
string Rune[12] = {
	//通常(0~9)
	"//死仇：我方和敌方的攻击力+30%//",
	"//瘟疫：我方和敌方的攻击力-30%//",
	"//崩溃：我方和敌方的防御力-50%//",
	"//狂热：我方和敌方技能条所需能量-1//",
	"//暗市：该层的商店不再展示商品详细信息，但该层商店的售价-50%//",
	"//迷雾：该层不再提前展示敌人技能信息，但可选择的技能+2//",
	"//繁荣：该层的商店售价+50%，但战斗后掉落藏品+1//",
	"//荒芜：该层的商店售价-50%，但战斗后不再掉落藏品//",
	"//贪婪：敌方攻击力+20%，但每次移动后金币+2//",
	"//救赎：在该层非boss关战斗死亡时可复活（仅限一次）,但该层战斗时防御力-30%//",
	//特殊(10~11)
	"//希望：在该层每次移动后金币+2，攻击力+30%//",
	"//绝望：所有敌人攻击力+20%，我方攻击力-20%//"
};
void Refresh() {
	cout << "\033[2J\033[H" << flush;
}
//以下为随机数生成器
class RandomManager {
private:
	mt19937 rd;
public:
	RandomManager() :rd(random_device{}()) {}
	RandomManager(const RandomManager&) = delete;
	RandomManager& operator=(const RandomManager&) = delete;
	int getnum(int min, int max) {
		uniform_int_distribution<int> dist(min, max);
		return dist(rd);
	}
	vector<int> getSomeNum(int min, int max, int k) {
		int total = max - min + 1;
		vector<int> pool(total);
		iota(pool.begin(), pool.end(), min);
		shuffle(pool.begin(), pool.end(), rd);
		return vector<int>(pool.begin(), pool.begin() + k);
	}
};
RandomManager rm;
//以下为输入检查函数
vector<string> forcheck;
int Safecin(int legal[], int length, bool ifblank) {
	string chose;
	forcheck.clear();
	for (int i = 0; i < length; i++) {
		forcheck.push_back(to_string(legal[i]));
	}
	while (1) {
		getline(cin, chose);
		if (ifblank) {
			if (chose.empty()) {
				return -1;
			}
		}
		for (auto& item : forcheck) {
			if (item == chose) {
				return stoi(chose);
			}
		}
		cout << "请在";
		for (auto& item : forcheck) {
			cout << item << ",";
		}
		cout << "中选择一个数字:";
		if (ifblank) cout << "(或者回车以继续)";
	}
}
//以下为等待时间函数
void WaitForSeconds(double Time) {
	int second = Time * 1000;
	this_thread::sleep_for(chrono::milliseconds(second));
}


//以下为主要运行程序
class Enemy;
class MyCharacter {
public:
	MyCharacter() = default;
	//计算基础数值和当前数值
	void CalculateMyNum() {
		BasicMaxHP = InitialMaxHP * (1.0+BasicHPDevelopment);
		BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment);
		BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment);
		CurrentMaxHP = BasicMaxHP * (1.0 + CurrentHPDevelopment);
		CurrentAttack = BasicAttack * (1.0 + CurrentAttackDevelopment);
		CurrentDefense = BasicDefense * (1.0 + CurrentDefenseDevelopment);
	}
	//设置当前血量为当前最大血量
	void SetCurrentHP() {
		CurrentHP = CurrentMaxHP;
	}
	//获取当前数值
	int GetCurrentHP() {
		return CurrentHP;
	}
	int GetCurrentMaxHP() {
		return CurrentMaxHP;
	}
	int GetCurrentAttack() {
		return CurrentAttack;
	}
	int GetCurrentDefense() {
		return CurrentDefense;
	}
	//获取当前其他数值
	//能量
	int GetCurrentEnergy() {
		return CurrentEnergy;
	}
	int GetMaxEnergy() {
		return MaxEnergy;
	}
	int GetInitialEnergy() {
		return InitialEnergy;
	}
	//治疗条
	int GetCurrentHeal() {
		return CurrentHeal;
	}
	int GetMaxHeal() {
		return MaxHeal;
	}
	int GetInitialHeal() {
		return InitialHeal;
	}
	int GetHealHP() {
		return HealHP;
	}
	//获取当前金币和等级
	int GetCoins() {
		return Coins;
	}
	int GetLevel() {
		return Level;
	}
	//被攻击函数
	void BeingAttacked(int damage) {
		int actualDamage = damage - CurrentDefense;
		if (actualDamage < damage*leastHarm) {
			actualDamage = damage*leastHarm;
		}
		CurrentHP -= actualDamage;
		if (CurrentHP < 0) {
			CurrentHP = 0;
			IsAlive = false;
		}
	}
	//攻击敌人函数，具体实现在Enemy类定义后
	void AttackEnemy(shared_ptr<Enemy> enemy);
	//获取存活状态
	bool GetIsAlive() {
		return IsAlive;
	}
	//获取保底伤害倍数
	int getLeastharm() {
		return leastHarm * 10;
	}
	//获取技能状态
	bool GetIfSkill() {
		return (CurrentEnergy == MaxEnergy);
	}
	//获取是否可以治疗（治疗条不为空）
	bool GetIfHeal() {
		return (CurrentHeal != 0);
	}
	//获取治疗条是否满
	bool GetIfHealFull() {
		return (CurrentHeal == MaxHeal);
	}
	void EnergyUp() {
		if (!GetIfSkill()) {
			CurrentEnergy++;
		}
	}
	void HealUp() {
		if (!GetIfHealFull()) {
			CurrentHeal++;
		}
	}
private:
	//初始数值，仅开局选择buff时会改变
	int InitialMaxHP=200;
	int InitialAttack=80;
	int InitialDefense=50;
	//基础数值，为初始数值计算藏品加成与等级加成后的数值
	int BasicMaxHP=200;
	int BasicAttack=80;
	int BasicDefense=50;
	//当前数值，为基础数值计算其余buff/debuff加成后的数值
	int CurrentMaxHP=200;
	int CurrentAttack=80;
	int CurrentDefense=50;
	//藏品加成与等级加成的总加成
	int BasicHPDevelopment=0;
	int BasicAttackDevelopment=0;
	int BasicDefenseDevelopment=0;
	//其余buff/debuff加成的总加成
	int CurrentHPDevelopment=0;
	int CurrentAttackDevelopment=0;
	int CurrentDefenseDevelopment=0;
	//当前血量
	int CurrentHP=200;
	//能量
	int CurrentEnergy=0;
	int InitialEnergy = 0;
	int MaxEnergy=3;
	//治疗条
	int CurrentHeal=0;
	int InitialHeal = 0;
	int MaxHeal=3;
	//每剂治疗条的治疗量
	int HealHP = 20;
	//金币
	int Coins = 0;
	//等级
	int Level = 1;
	//存活状态
	bool IsAlive = true;
	//防御手段防御力加成
	double DefendingDeveloping = 2;
	//保底伤害比例
	double leastHarm = 0.1;
};

MyCharacter mycharacter;
class Enemy {
public:
	Enemy(int hp,int atk,int dfs) : InitialMaxHP(hp), InitialAttack(atk), InitialDefense(dfs) {
		CalculateMyNum();
		SetCurrentHP();
	}
	Enemy() = default;
	//计算基础数值和当前数值
	void CalculateMyNum() {
		BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment);
		BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment);
		BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment);
		CurrentMaxHP = BasicMaxHP * (1.0 + CurrentHPDevelopment);
		CurrentAttack = BasicAttack * (1.0 + CurrentAttackDevelopment);
		CurrentDefense = BasicDefense * (1.0 + CurrentDefenseDevelopment);
	}
	//设置当前血量为当前最大血量
	void SetCurrentHP() {
		CurrentHP = CurrentMaxHP;
	}
	//获取当前数值
	int GetCurrentHP() {
		return CurrentHP;
	}
	int GetCurrentMaxHP() {
		return CurrentMaxHP;
	}
	int GetCurrentAttack() {
		return CurrentAttack;
	}
	int GetCurrentDefense() {
		return CurrentDefense;
	}
	//获取能量
	int GetCurrentEnergy() {
		return CurrentEnergy;
	}
	int GetMaxEnergy() {
		return MaxEnergy;
	}
	int GetInitialEnergy() {
		return InitialEnergy;
	}
	//获取暴击率
	int GetCriticalRate() {
		return CriticalRate;
	}
	//被攻击函数
	void BeingAttacked(int damage) {
		int actualDamage = damage - CurrentDefense;
		if (actualDamage < damage * 0.1) {
			actualDamage = damage * 0.1;
		}
		CurrentHP -= actualDamage;
		if (CurrentHP < 0) {
			CurrentHP = 0;
			IsAlive = false;
		}
	}
	//攻击我方函数
	void AttackPlayer(shared_ptr<MyCharacter> player) {
		int damage = CurrentAttack;
		player->BeingAttacked(damage);
	}
	//获取存活状态
	bool GetIsAlive() {
		return IsAlive;
	}
private:
	//初始数值
	int InitialMaxHP = 0;
	int InitialAttack = 0;
	int InitialDefense = 0;
	//基础数值，为初始数值计算藏品加成与等级加成后的数值
	int BasicMaxHP = 0;
	int BasicAttack = 0;
	int BasicDefense = 0;
	//当前数值，为基础数值计算其余buff/debuff加成后的数值
	int CurrentMaxHP = 0;
	int CurrentAttack = 0;
	int CurrentDefense = 0;
	//藏品加成与等级加成的总加成
	int BasicHPDevelopment = 0;
	int BasicAttackDevelopment = 0;
	int BasicDefenseDevelopment = 0;
	//其余buff/debuff加成的总加成
	int CurrentHPDevelopment = 0;
	int CurrentAttackDevelopment = 0;
	int CurrentDefenseDevelopment = 0;
	//当前血量
	int CurrentHP = 100;
	//能量
	int CurrentEnergy = 0;
	int InitialEnergy = 0;
	int MaxEnergy = 5;
	//暴击率
	int CriticalRate = 0.3;
	//存活状态
	bool IsAlive = true;
};
void MyCharacter::AttackEnemy(shared_ptr<Enemy> enemy) {
	int damage = CurrentAttack;
	enemy->BeingAttacked(damage);
}
vector<vector<string>> Themap(8, vector<string>(100, " "));
void DrawBlock(int blocktype, int line) {
	if (blocktype != 5 && blocktype != 0) {//blocktype为5为双节点，blocktype为0为已经过节点
		for (int j = line; j < line + 5;j++) {
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
		for (int i = 1;i < 4;i++) {
			Themap[3][line - i] = " ";
		}
		for (int i = 1;i <= 5;i++) {
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
		for (int i = 0;i < 7;i++) {
			if (i != 3) {
				Themap[i][line] = "#";
				Themap[i][line + 4] = "#";
			}
		}
		for (int i = 1;i <= 3;i++) {
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
	cout << "地图说明：" << endl;
	cout << " * :战斗节点" << endl;
	cout << " ? :未知事件节点" << endl;
	cout << " $ :商店节点" << endl;
	cout << " B :Boss节点" << endl;
	cout << " ^ :当前位置" << endl;
}
vector<int> Maptype;
int Map1[5] = { 1,2,5,3,4 };
int Map2[6] = { 2,1,1,5,3,4 };
int Map3[7] = { 2,2,1,1,5,3,4 };
void DrawMap(int floor, int step) {
	Refresh();
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 100;j++) {
			Themap[i][j] = " ";
		}
	}
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
	for (int n = 0;n < step;n++) {
		Maptype[n] = 0;
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
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 100;j++) {
			cout << Themap[i][j];
		}
		cout << endl;
	}
	cout << "目前在第" << floor << "层"<<endl;
	cout << endl;
}
void SupplementDigitNumber(string &num) {
	while (num.length() < 3) {
		num = "0" + num;
	}
}
int Battlerow = 20;
int Battlecol = 90;
vector<vector<string>> Battlemap(Battlerow, vector<string>(Battlecol, " "));
void PrintBalttleGround(int *myData, int *enemyData,int round,int turn) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 90; j++) {
			Battlemap[i][j] = " ";	
		}
	}
	string myhp = to_string(myData[0]);
	string myHP = to_string(myData[1]);
	string enemyhp = to_string(enemyData[0]);
	string enemyHP = to_string(enemyData[1]);
	SupplementDigitNumber(myhp);
	SupplementDigitNumber(myHP);
	SupplementDigitNumber(enemyhp);
	SupplementDigitNumber(enemyHP);
	double MyHpPercent = (double)myData[0] / myData[1];
	double EnemyHpPercent = (double)enemyData[0] / enemyData[1];
	double MyEnergyPercent = (double)myData[2] / myData[3];
	int MyEnergyBarLength = (int)(MyEnergyPercent * 19);
	double Myhealpercent = (double)myData[4] / myData[5];
	int MyhealBarLength = (int)(Myhealpercent * 19);
	double EnemyEnergyPercent = (double)enemyData[2] / enemyData[3];
	int EnemyEnergyBarLength = (int)(EnemyEnergyPercent * 19);
	int MyHpBarLength = (int)(MyHpPercent * 28);
	int EnemyHpBarLength = (int)(EnemyHpPercent * 28);
	Refresh();
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
	for(int j=32;j<=59;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for(int j=32;j<32+MyHpBarLength;j++) {
		Battlemap[3][j] = "|";
	}
	Battlemap[5][40] = "H";
	Battlemap[5][41] = "P";
	Battlemap[5][42] = ":";
	Battlemap[5][43] = myhp[0];
	Battlemap[5][44] = myhp[1];
	Battlemap[5][45] = myhp[2];
	Battlemap[5][46] = "/";
	Battlemap[5][47] = myHP[0];
	Battlemap[5][48] = myHP[1];
	Battlemap[5][49] = myHP[2];
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
	for(int j=32;j<=59;j++) {
		Battlemap[15][j] = "-";
		Battlemap[17][j] = "-";
	}
	for (int j = 32;j < 32 + EnemyHpBarLength;j++) {
		Battlemap[16][j] = "|";
	}
	Battlemap[14][40] = "H";
	Battlemap[14][41] = "P";
	Battlemap[14][42] = ":";
	Battlemap[14][43] = enemyhp[0];
	Battlemap[14][44] = enemyhp[1];
	Battlemap[14][45] = enemyhp[2];
	Battlemap[14][46] = "/";
	Battlemap[14][47] = enemyHP[0];
	Battlemap[14][48] = enemyHP[1];
	Battlemap[14][49] = enemyHP[2];
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
	Battlemap[16][78] = to_string(round);
	//以下为回合指示器（箭头图案）
	if (turn == 1) {
		//我方回合
		for (int i = 7;i <= 10;i++) {
			Battlemap[i][i + 32] = "\\";
		}
		for (int i = 7;i <= 10;i++) {
			Battlemap[i][54 - i] = "/";
		}
		Battlemap[11][43] = "|";
	}
	else {
		//敌方回合
		for (int i = 8;i <= 11;i++) {
			Battlemap[i][i+36] = "\\";
		}
		for (int i = 8;i <= 11;i++) {
			Battlemap[i][50-i] = "/";
		}
		Battlemap[7][43] = "|";
	}
	//打印地图
	for(int i = 0; i < Battlerow; i++) {
		for(int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j]<<flush;
		}
		cout << endl;
	}
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
int MydataWhenBattle[6] = { 0 };
int EnemydataWhenBattle[4] = { 0 };
//更新当前数值状态
void UpdateData(shared_ptr<Enemy> enemy) {
	MydataWhenBattle[0] = mycharacter.GetCurrentHP();
	MydataWhenBattle[1] = mycharacter.GetCurrentMaxHP();
	MydataWhenBattle[2] = mycharacter.GetCurrentEnergy();
	MydataWhenBattle[3] = mycharacter.GetMaxEnergy();
	MydataWhenBattle[4] = mycharacter.GetCurrentHeal();
	MydataWhenBattle[5] = mycharacter.GetMaxHeal();
	//血量，血量上限，能量，能量上限，治疗条，治疗条上限
	EnemydataWhenBattle[0] = enemy->GetCurrentHP();
	EnemydataWhenBattle[1] = enemy->GetCurrentMaxHP();
	EnemydataWhenBattle[2] = enemy->GetCurrentEnergy();
	EnemydataWhenBattle[3] = enemy->GetMaxEnergy();
	//血量，血量上限，能量，能量上限
}
//回合开始函数
void RoundStart(int round, shared_ptr<Enemy> enemy) {
	UpdateData(enemy);
	//我方回合
	int RoundChoice = 0;
	int LegalRoundChoice[4] = { 1,2,3,4 };
	while (1) {
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 1);
		cout << "请选择本回合的行动：" << endl;
		cout << "1.攻击" << endl;
		cout << "2.防御(不攻击且防御力提升至" << mycharacter.getLeastharm() << "倍)" << endl;
		cout << "3.释放技能";
		if (!mycharacter.GetIfSkill()) {
			cout << "(技能未充能满，无法释放)";
		}
		else {
			cout << "(///技能已充能满，可以释放///)";
		}
		cout << endl;
		cout << "4.治疗";
		if (!mycharacter.GetIfHeal()) {
			cout << "(治疗条为空，无法治疗)";
		}
		else {
			cout << "(将消耗所有治疗条进行治疗，每点治疗条回复" << mycharacter.GetHealHP() << "点生命值)";
		}
		cout << endl;
		RoundChoice=Safecin(LegalRoundChoice, 4, false);
		if (RoundChoice == 1 || RoundChoice == 2) {
			break;
		}
		else if (RoundChoice == 3) {
			if (mycharacter.GetIfSkill()) {
				break;
			}
			else {
				cout << "技能未充能满，无法释放!" << endl;
				cout << "请重新选择行动。" << endl;
				cout << "2秒后刷新界面...";
				WaitForSeconds(1);
				cout << "\r\033[K" << "1秒后刷新界面..." << flush;
				WaitForSeconds(1);
			}
		}
		else {
			if (mycharacter.GetIfHeal()) {
				break;
			}
			else {
				cout << "治疗条为空，无法治疗!" << endl;
				cout << "请重新选择行动。"<<endl;
				cout << "2秒后刷新界面...";
				WaitForSeconds(1);
				cout << "\r\033[K" << "1秒后刷新界面..." << flush;
				WaitForSeconds(1);
			}
		}
	}
	//选择攻击
	if (RoundChoice == 1 || RoundChoice == 2) {
		if (!(mycharacter.GetIfHealFull() && mycharacter.GetIfSkill())){
			if (mycharacter.GetIfHealFull()) {
				mycharacter.EnergyUp();
				cout << "治疗条已满，已自动为能量条充能。(2秒后继续)";
				WaitForSeconds(2);
			}
			else if (mycharacter.GetIfSkill()) {
				mycharacter.HealUp();
				cout << "能量条已满，已自动为治疗条充能。(2秒后继续)";
				WaitForSeconds(2);
			}
			else {
				cout << "请选择充能方向，输入1为技能条充能，输入2为治疗条充能：";
				int LegalEnergy[2] = { 1,2 };
				int EnergyChoice;
				EnergyChoice = Safecin(LegalEnergy, 2, false);
				if (EnergyChoice == 1) {
					mycharacter.EnergyUp();
				}
				else {
					mycharacter.HealUp();
				}
			}
		}
		else {
			cout << "治疗条与能量条均已满，无法充能。(2秒后继续)";
			WaitForSeconds(2);
		}
	}
	if (RoundChoice == 1) {
		int EnemyHP0 = enemy->GetCurrentHP();
		mycharacter.AttackEnemy(enemy);
		UpdateData(enemy);
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 1);
		int Harm=EnemyHP0- enemy->GetCurrentHP();
		cout << "敌方受到了 " << Harm << " 点伤害！"<<endl;
	}
	cout << "按回车以进入敌方回合...";
	cin.ignore();
	//敌方回合
	PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round,2);
}
//战斗开始函数
void BattleStart(int floor,bool isBoss) {
	int round = 1;
	shared_ptr<Enemy> enemy = make_shared<Enemy>();
	switch (floor) {
	case 1:
		if (isBoss) {
			enemy = make_shared<Enemy>(2000, 100, 40);
		}
		else {
			enemy = make_shared<Enemy>(500, 80, 20);
		}
		break;
	}
	while (1) {
		RoundStart(round, enemy);
		round++;
		cin.ignore();
	}
}
int main() {
	int floor = 1;
	int	step = 0;
	int RuneNow = -1;
	int thisfloor = 0;
	while (1) {
		if (thisfloor != floor) {
			RuneNow = rm.getnum(0, 8);
		}
		thisfloor = floor;
		DrawMap(floor, step);
		cout << Rune[RuneNow] << endl;
		cout << endl;
		PrintMaphelp();
		cout << endl;
		switch (Maptype[step]) {
		case 1://普通战斗
			cout << "进入战斗节点，按回车继续..." << endl;
			cin.ignore();
			BattleStart(floor, false);
			break;
		case 4://boss战斗
			cout << "进入Boss战斗节点，按回车继续..." << endl;
			cin.ignore();
			BattleStart(floor, true);
			break;
		case 2://非战斗节点
			cout << "进入未知事件节点，按回车继续..." << endl;
			cin.ignore();
			PrintEventGround(2);
			break;
		case 3://商店节点
			cout << "进入商店节点，按回车继续..." << endl;
			cin.ignore();
			PrintEventGround(3);
			break;
		case 5://双节点
			cout << "进入双节点，请选择节点。输入1以选择战斗节点，输入2以选择未知事件节点：" << endl;
			while (1) {
				int choice=0;
				int legal[2] = { 1,2 };
				choice=Safecin(legal, 2, false);
				if (choice == 1) {
					BattleStart(floor, false);
					break;
				}
				else if (choice == 2) {
					PrintEventGround(2);
					break;
				}
			}
			break;
		}
		cin.ignore();
		step++;
		if (step >= Maptype.size() && floor < 3) {
			step = 0;
			floor++;
		}
		if (step >= Maptype.size() && floor == 3) {
			break;
		}
	}
	return 0;
}