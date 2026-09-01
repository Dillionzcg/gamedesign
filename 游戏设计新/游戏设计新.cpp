/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*使用rm.getSomeNum(min,max,k)以获得一定范围（闭区间）的k个不重复随机int，返回vector<int>
*使用a=Safecin(legal,ifblank)以获得合法输入，
 legal为合法数字向量(vector<int>)，ifblank为是否允许空输入(bool值)
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
#include<limits>
using namespace std;

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
int Safecin(const vector<int>& legal, bool ifblank) {
	string chose;
	forcheck.clear();
	for (auto v : legal) {
		forcheck.push_back(to_string(v));
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
		cout << flush;
	}
}
void SafeEnter() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
//以下为等待时间函数
void WaitForSeconds(double Time) {
	int second =(int) Time * 1000;
	this_thread::sleep_for(chrono::milliseconds(second));
}
class RuneManager;
shared_ptr<RuneManager> RuneNow;
//以下为主要运行程序
class RuneManager {
public:
	RuneManager(int num) :ID(num) {}
	RuneManager() = default;
	string GetDescribe() {
		return RuneList[ID];
	}
	string GetDescribethroughNum(int num) {
		return RuneList[num];
	}
	string GetName() {
		return RuneName[ID];
	}
	static void RandomChangeRune() {
		int num = rm.getnum(0, 9);
		RuneNow = make_shared<RuneManager>(num);
	}
private:
	int ID=0;
	string name="0";
	//符文文本
	vector<string> RuneList = {
		//通常(0~9)
		"//死仇：我方和敌方的攻击力+30%//",
		"//瘟疫：我方和敌方的攻击力-30%//",
		"//崩溃：我方和敌方的防御力-50%//",
		"//狂热：我方和敌方技能条初始能量+2//",
		"//暗市：该层的商店不再展示商品详细信息，但该层商店的售价-50%//",
		"//迷雾：该层不再提前展示敌人信息，但可选择的技能+2//",
		"//繁荣：该层的商店售价+50%，但战斗后掉落藏品+1//",
		"//荒芜：该层的商店售价-50%，但战斗后不再掉落藏品//",
		"//贪婪：敌方攻击力+20%，但每次移动后金币+2//",
		"//救赎：在该层非boss关战斗死亡时可复活（仅限一次）,但该层战斗时防御力-30%//",
		//特殊(10~11)
		"//希望：在该层每次移动后金币+2，攻击力+30%//",
		"//绝望：所有敌人攻击力+20%，我方攻击力-20%//"
	};
	vector<string> RuneName = {
		"死仇",
		"瘟疫",
		"崩溃",
		"狂热",
		"暗市",
		"迷雾",
		"繁荣",
		"荒芜",
		"贪婪",
		"救赎",
		"希望",
		"绝望"
	};
};

class SkillManage {
public:
	SkillManage(int num) :ID(num) {}
	string GetDescribe() {
		return SkillList[ID];
	}
	string GetName() {
		switch (ID) {
		case 0: return "EA";
		case 1: return "ED";
		case 2: return "MA";
		case 3: return "MD";
		case 4: return "MB";
		case 5: return "HA";
		case 6: return "AH";
		case 7: return "AE";
		case 8: return "IA";
		case 9: return "DA";
		}
	}
	string GetDescribethroughNum(int num) {
		return SkillList[num];
	}
private:
	int ID;
	vector<string> SkillList = {
	//若干回合内生效
	"//使对方攻击力在3回合内下降30%，并攻击一次//",//EA
	"//使对方防御力在3回合内降至0，并攻击一次//",//ED
	"//使包括此回合的3回合内的攻击力+50%，并攻击一次//",//MA
	"//使包括此回合的3回合内的防御力+70%，并防御一次//",//MD
	"//使包括此回合的4回合内\"防御\"行动对防御力的加成翻倍，并防御一次//",//MB
	"//使包括此回合的3回合内每次受到伤害后回复20点血量，并防御一次//",//HA
	//仅作用于该回合
	"//对敌方进行一次250%攻击力的攻击，并回复40点血量//",//AH
	"//对敌方进行一次250%攻击力的攻击，并使敌方能量条能量-1//",//AE
	"//对敌方造成一次无视防御的300%攻击力的伤害//",//IA
	"//使该回合内敌方晕眩（无法行动），并造成一次无视防御的150%攻击力的伤害//"//DA
	};
};
//藏品类
class Object {
public:
	Object(int rarity, string camp, string type, string describe,int buffnum) :Rarity(rarity), Camp(camp), Type(type), Describe(describe),BuffNum(buffnum) {
		NeedingCoin = RarityCoin[Rarity-1];
	}
	int GetRarity() {
		return Rarity;
	}
	int GetNeedingCoin() {
		return NeedingCoin;
	}
	string GetDescribe() {
		return Describe;
	}
	double GetBuffNum() {
		return BuffNum;
	}
	bool GetIfGotten() {
		return IfGotten;
	}
	void GainObject() {
		IfGotten = true;
	}
private:
	int Rarity;//稀有度,1/2/3
	vector<int> RarityCoin = { 2,4,6 };//稀有度对应金币数
	int NeedingCoin;//购买所需金币数
	string Describe;//藏品描述
	string Camp;//阵营，"M"为我方，"E"为敌方
	string Type;//类型
	bool IfGotten = false;//是否已获得
	double BuffNum;//加成数值
};
//藏品池
vector<shared_ptr<Object>> ObjectPool1 = {//初级藏品
	make_shared<Object>(1,"M","A","攻击力+10%",0.1),
	make_shared<Object>(1,"M","D","防御力+20%",0.2),
	make_shared<Object>(1,"M","H","生命上限+30%",0.3),
	make_shared<Object>(1,"M","HE","每点治疗能量治疗量+5",5),
	make_shared<Object>(1,"E","A","敌人攻击力-10%",-0.1),
	make_shared<Object>(1,"E","D","敌人防御力-10%",-0.1),
	make_shared<Object>(1,"E","H","敌人生命上限-10%",-0.1),
	make_shared<Object>(1,"E","CR","敌人暴击率-5%",-5),
};
vector<shared_ptr<Object>> ObjectPool2 = {//中级藏品
	make_shared<Object>(2,"M","A","攻击力+20%",0.2),
	make_shared<Object>(2,"M","D","防御力+30%",0.3),
	make_shared<Object>(2,"M","H","生命上限+40%",0.4),
	make_shared<Object>(2,"M","HE","每点治疗能量治疗量+10",10),
	make_shared<Object>(2,"E","A","敌人攻击力-15%",-0.15),
	make_shared<Object>(2,"E","D","敌人防御力-15%",-0.15),
	make_shared<Object>(2,"E","H","敌人生命上限-15%",-0.15),
	make_shared<Object>(2,"E","CR","敌人暴击率-10%",-10),

	make_shared<Object>(2,"M","IE","我方初始能量+1",1),
	make_shared<Object>(2,"M","IHE","我方初始治疗能量+1",1),
	make_shared<Object>(2,"M","MHE","我方治疗能量上限+2",2),
	make_shared<Object>(2,"M","SC","可选择技能+1",1),
};
vector<shared_ptr<Object>> ObjectPool3 = {//高级藏品
	make_shared<Object>(3,"M","A","攻击力+30%",0.3),
	make_shared<Object>(3,"M","D","防御力+40%",0.4),
	make_shared<Object>(3,"M","H","生命上限+50%",0.5),
	make_shared<Object>(3,"M","HE","每点治疗能量治疗量+15",15),
	make_shared<Object>(3,"E","A","敌人攻击力-20%",-0.2),
	make_shared<Object>(3,"E","D","敌人防御力-20%",-0.2),
	make_shared<Object>(3,"E","H","敌人生命上限-20%",-0.2),
	make_shared<Object>(3,"E","CR","敌人暴击率-15%",-15),

	make_shared<Object>(3,"M","IE","我方初始能量+2",2),
	make_shared<Object>(3,"M","IHE","我方初始治疗能量+2",2),
	make_shared<Object>(3,"M","EN","我方技能所需能量-1",-1),
	make_shared<Object>(3,"E","EN","敌方技能所需能量+2",2),
	make_shared<Object>(2,"M","SC","可选择技能+2",2),
};

vector<shared_ptr<Object>> MyObjectGroup;//我方藏品组
class Enemy;
//局内buff管理，每个对象只负责一个buff
class RoundBuff {
public:
	RoundBuff() = default;
	~RoundBuff() = default;
	RoundBuff(string type, double Buffnum, int round) {
		//MA,我方攻击加成，MD,我方防御加成，MB,我方防御手段增益，EA,敌方攻击加成，ED,敌方防御加成
		LastingRounds = round;
		Bufftype = type;
		Development = Buffnum;
	}
	void RoundPass() {
		if (LastingRounds > 0) {
			LastingRounds--;
		}
		if (LastingRounds == 0) {
			Ifover = true;
		}
	}
	bool GetIfover() {
		return Ifover;
	}
	string GetType() {
		return Bufftype;
	}
	double GetDevelopment() {
		return Development;
	}
private:
	double Development = 0;
	int LastingRounds = 0;
	string Bufftype="0";
	bool Ifover = false;
};
class MyCharacter {
public:
	MyCharacter() = default;
	//计算基础数值和当前数值
	void CalculateMyNum(vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyRoundBuff(RoundBuffGroup);
		CalculateMyLevelBuff();
		BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment+LevelHPDevelopment);
		BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment+LevelAttackDevelopment);
		BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment+LevelDefenseDevelopment);
		CurrentMaxHP = BasicMaxHP * (1.0 + CurrentHPDevelopment);
		CurrentAttack = BasicAttack * (1.0 + CurrentAttackDevelopment + RoundAttackDevelopment);
		CurrentDefense = BasicDefense * (1.0 + CurrentDefenseDevelopment + RoundDefenseDevelopment);
		DefendingDeveloping = BasicDefendingDeveloping + RoundDefendingBuff;
	}
	void CalculateMyLevelBuff() {
		LevelHPDevelopment = (Level - 1) * 0.1;
		LevelAttackDevelopment = (Level - 1) * 0.1;
		LevelDefenseDevelopment = (Level - 1) * 0.1;
	}
	void CalculateMyRoundBuff(vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		RoundAttackDevelopment = 0;
		RoundDefenseDevelopment = 0;
		RoundDefendingBuff = 0;
		HealAfterHarm = 0;
		if (!RoundBuffGroup.empty()) {
			for (auto& item : RoundBuffGroup) {
				if (item->GetType() == "MA") {
					RoundAttackDevelopment += item->GetDevelopment();
				}
				else if (item->GetType() == "MD") {
					RoundDefenseDevelopment += item->GetDevelopment();
				}
				else if (item->GetType() == "MB") {
					RoundDefendingBuff += item->GetDevelopment();
				}
				else if (item->GetType() == "HA") {
					HealAfterHarm+= item->GetDevelopment();
				}
			}
		}
	}
	//设置当前血量为当前最大血量
	void SetCurrentNum() {
		CurrentHP = CurrentMaxHP;
		CurrentHeal = InitialHeal;
		CurrentEnergy = InitialEnergy;
		IsAlive = true;
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
	void BeingAttacked(int damage, vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyNum(RoundBuffGroup);
		int actualDamage = damage - CurrentDefense;
		if (actualDamage < damage * leastHarm) {
			actualDamage = damage * leastHarm;
		}
		CurrentHP -= actualDamage;
		if (CurrentHP <= 0) {
			CurrentHP = 0;
			IsAlive = false;
		}
	}
	//攻击敌人函数，具体实现在Enemy类定义后
	void AttackEnemy(shared_ptr<Enemy> enemy, vector<shared_ptr<RoundBuff>> RoundBuffGroup);
	void SpecialAttackEnemy(shared_ptr<Enemy> enemy, vector<shared_ptr<RoundBuff>> RoundBuffGroup, bool IfCalDefense, double AttackCrease);
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
	double GetDefendingDeveloping() {
		return DefendingDeveloping;
	}
	//能量条与治疗条充能
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
	//消耗所有能量条或治疗条
	void UsingEnergy() {
		CurrentEnergy = 0;
	}
	void UsingHeal() {
		CurrentHeal = 0;
	}
	//回复血量
	void Heal_UsingHeal() {
		int heal = CurrentHeal * HealHP;
		if (CurrentHP + heal <= CurrentMaxHP) {
			CurrentHP += heal;
		}
		else {
			CurrentHP = CurrentMaxHP;
		}
		UsingHeal();
	}
	void Heal(int heal) {
		if (CurrentHP + heal <= CurrentMaxHP) {
			CurrentHP += heal;
		}
		else {
			CurrentHP = CurrentMaxHP;
		}
	}
	int GetChoiceNum() {
		return SkillChoiceNum;
	}
	int GetHealAfterHarm() {
		return HealAfterHarm;
	}
	void Levelup(int num) {
		Level += num;
	}
	void GainCoin(int num) {
		Coins += num;
	}
	void ReSetNum() {
		InitialMaxHP = 300;
		InitialAttack = 80;
		InitialDefense = 50;
		Coins = 0;
		Level = 1;
		IsAlive = true;
		SkillChoiceNum = 3;

	}
private:
	//初始数值，仅开局选择buff时会改变
	int InitialMaxHP=300;
	int InitialAttack=80;
	int InitialDefense=50;
	//基础数值，为初始数值计算藏品加成与等级加成后的数值
	int BasicMaxHP=0;
	int BasicAttack=0;
	int BasicDefense=0;
	//当前数值，为基础数值计算其余buff/debuff加成后的数值
	int CurrentMaxHP=0;
	int CurrentAttack=0;
	int CurrentDefense=0;
	//藏品加成
	int BasicHPDevelopment=0;
	int BasicAttackDevelopment=0;
	int BasicDefenseDevelopment=0;
	//等级加成
	int LevelHPDevelopment = 0;
	int LevelAttackDevelopment = 0;
	int LevelDefenseDevelopment = 0;
	//其余buff/debuff加成的总加成
	int CurrentHPDevelopment=0;
	int CurrentAttackDevelopment=0;
	int CurrentDefenseDevelopment=0;
	//局内buff/debuff加成的总加成
	double RoundAttackDevelopment = 0;
	double RoundDefenseDevelopment = 0;
	double RoundDefendingBuff = 0;
	//当前血量
	int CurrentHP=0;
	//能量
	int CurrentEnergy=0;
	int InitialEnergy = 0;
	int MaxEnergy=3;
	//治疗条
	int CurrentHeal=0;
	int InitialHeal = 0;
	int MaxHeal=3;
	//每剂治疗条的治疗量
	int HealHP = 30;
	//金币
	int Coins = 0;
	//等级
	int Level = 1;
	//存活状态
	bool IsAlive = true;
	//防御手段防御力加成
	double BasicDefendingDeveloping = 2;
	double DefendingDeveloping = 2;
	//保底伤害比例
	double leastHarm = 0.1;
	//开局可抽取技能个数
	int SkillChoiceNum = 3;
	//被攻击后回复血量
	int HealAfterHarm = 0;
};

MyCharacter mycharacter;
class Enemy {
public:
	Enemy(int hp,int atk,int dfs, vector<shared_ptr<RoundBuff>> RoundBuffGroup) : InitialMaxHP(hp), InitialAttack(atk), InitialDefense(dfs) {
		CalculateMyNum(RoundBuffGroup);
		SetCurrentHP();
	}
	Enemy() = default;
	void CalculateMyRoundBuff(vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		RoundAttackDevelopment = 0;
		RoundDefenseDevelopment = 0;
		if (!RoundBuffGroup.empty()) {
			for (auto& item : RoundBuffGroup) {
				if (item->GetType() == "EA") {
					RoundAttackDevelopment += item->GetDevelopment();
				}
				else if (item->GetType() == "ED") {
					RoundDefenseDevelopment += item->GetDevelopment();
				}
			}
		}
	}
	//计算基础数值和当前数值
	void CalculateMyNum(vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyRoundBuff(RoundBuffGroup);
		BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment);
		BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment);
		BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment);
		CurrentMaxHP = BasicMaxHP * (1.0 + CurrentHPDevelopment);
		CurrentAttack = BasicAttack * (1.0 + CurrentAttackDevelopment+RoundAttackDevelopment);
		CurrentDefense = BasicDefense * (1.0 + CurrentDefenseDevelopment+RoundDefenseDevelopment);
		if (CurrentDefense <= 0) CurrentDefense = 0;
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
	double GetCriticalHarm() {
		return CriticalHarm;
	}
	//被攻击函数
	void BeingAttacked(int damage, vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyNum(RoundBuffGroup);
		int actualDamage = damage - CurrentDefense;
		if (actualDamage < damage * 0.1) {
			actualDamage = damage * 0.1;
		}
		CurrentHP -= actualDamage;
		if (CurrentHP <= 0) {
			CurrentHP = 0;
			IsAlive = false;
		}
	}
	void BeingAttacked_NoDefense(int damage, vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyNum(RoundBuffGroup);
		CurrentHP -= damage;
		if (CurrentHP <= 0) {
			CurrentHP = 0;
			IsAlive = false;
		}
	}
	//攻击我方函数
	bool AttackPlayer(MyCharacter& player, vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyNum(RoundBuffGroup);
		int NumforCritical = rm.getnum(1, 100);
		bool IfCritical = (NumforCritical <= CriticalRate);
		int damage=0;
		if (IfCritical) {
			damage = CurrentAttack*CriticalHarm;
		}
		else {
			damage = CurrentAttack;
		}
		
		player.BeingAttacked(damage,RoundBuffGroup);
		return IfCritical;
	}
	//获取存活状态
	bool GetIsAlive() {
		return IsAlive;
	}
	bool GetIfSkill() {
		return (CurrentEnergy == MaxEnergy);
	}
	//回复血量
	void Heal(int heal) {
		if (CurrentHP + heal <= CurrentMaxHP) {
			CurrentHP += heal;
		}
		else {
			CurrentHP = CurrentMaxHP;
		}
	}
	void EnergyUp() {
		if (!GetIfSkill()) {
			CurrentEnergy++;
		}
	}
	void UsingEnergy() {
		CurrentEnergy = 0;
	}
	void CriticalRateCrease(int num) {
		CriticalRate += num;
	}
	void EnergyIncrease(int num) {
		if (CurrentEnergy > 0) CurrentEnergy--;
	}
	void MustCritical() {
		CriticalRate_Tem = CriticalRate;
		CriticalRate += 100;
		if (CriticalRate > 100) CriticalRate = 100;
	}
	void Re_CriticalRate() {
		CriticalRate = CriticalRate_Tem;
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
	//其余局外buff/debuff加成的总加成
	int CurrentHPDevelopment = 0;
	int CurrentAttackDevelopment = 0;
	int CurrentDefenseDevelopment = 0;
	//局内buff/debuff加成的总加成
	double RoundAttackDevelopment = 0;
	double RoundDefenseDevelopment = 0;
	//当前血量
	int CurrentHP = 100;
	//能量
	int CurrentEnergy = 0;
	int InitialEnergy = 0;
	int MaxEnergy = 6;
	//暴击率与暴击伤害
	int CriticalRate = 20;
	int CriticalRate_Tem = 0;
	double CriticalHarm = 2;
	//存活状态
	bool IsAlive = true;
};
void MyCharacter::AttackEnemy(shared_ptr<Enemy> enemy, vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
	CalculateMyNum(RoundBuffGroup);
	int damage = CurrentAttack;
	enemy->BeingAttacked(damage,RoundBuffGroup);
}
void MyCharacter::SpecialAttackEnemy(shared_ptr<Enemy> enemy, vector<shared_ptr<RoundBuff>> RoundBuffGroup, bool IfCalDefense, double AttackCrease) {
	CalculateMyNum(RoundBuffGroup);
	int damage = CurrentAttack*(1+AttackCrease);
	if (IfCalDefense) {
		enemy->BeingAttacked(damage, RoundBuffGroup);
	}
	else {
		enemy->BeingAttacked_NoDefense(damage, RoundBuffGroup);
	}

}
class EnemyNumManager {
public:
	EnemyNumManager(int hp, int atk, int dfs) :HP(hp), Attack(atk), Defense(dfs) {}
	EnemyNumManager() = default;
	int getHP() {
		return HP;
	}
	int getAttack() {
		return Attack;
	}
	int getDefense() {
		return Defense;
	}
private:
	int HP=0;
	int Attack=0;
	int Defense=0;
};
shared_ptr<EnemyNumManager> Floor1A_S = make_shared<EnemyNumManager>(200, 100, 20);//第一层攻击特化普通模式敌人
shared_ptr<EnemyNumManager> Floor1D_S = make_shared<EnemyNumManager>(200, 80, 50);//第一层防御特化普通模式敌人
shared_ptr<EnemyNumManager> Floor1H_S = make_shared<EnemyNumManager>(300, 80, 20);//第一层生命上限特化普通模式敌人
vector<shared_ptr<EnemyNumManager>> Floor1_S = { Floor1A_S ,Floor1D_S ,Floor1H_S };
shared_ptr<EnemyNumManager> Boss1_S = make_shared<EnemyNumManager>(600, 100, 40);//第一层普通模式Boss

shared_ptr<EnemyNumManager> Floor1A_H = make_shared<EnemyNumManager>(500, 100, 20);//第一层攻击特化困难模式敌人
shared_ptr<EnemyNumManager> Floor1D_H = make_shared<EnemyNumManager>(500, 80, 50);//第一层防御特化困难模式敌人
shared_ptr<EnemyNumManager> Floor1H_H = make_shared<EnemyNumManager>(600, 80, 20);//第一层生命上限特化困难模式敌人
vector<shared_ptr<EnemyNumManager>> Floor1_H = { Floor1A_H ,Floor1D_H ,Floor1H_H };
shared_ptr<EnemyNumManager> Boss1_H = make_shared<EnemyNumManager>(1000, 100, 40);//第一层困难模式Boss

shared_ptr<EnemyNumManager> EnemyNum_ThisBattle;//本次战斗敌人数据
vector<string> EnemyType = { "攻击力较高","防御力较高","生命值较高" };
void ChooseEnemy(int floor, bool IsBoss) {
	int Choice = -1;
	switch (floor) {
	case 1:
		if (IsBoss) {
			EnemyNum_ThisBattle = Boss1_S;
		}
		else {
			Choice= rm.getnum(0, 2);
			EnemyNum_ThisBattle = Floor1_S[Choice];
		}
		break;
	}
	if (!IsBoss) {
		cout << "该次战斗的敌人【" << EnemyType[Choice] << "】,请选择合适的技能以应对。" << endl;
	}
	else {
		cout << "以下是该次战斗的Boss的各项数值，请选择合适的技能以应对。" << endl;
	}
	cout << "敌人的各项数值为：" << endl;
	cout << "攻击力：" << EnemyNum_ThisBattle->getAttack()<<endl;
	cout << "防御力：" << EnemyNum_ThisBattle->getDefense() << endl;
	cout << "生命上限：" << EnemyNum_ThisBattle->getHP() << endl;
	cout << endl;
}
vector<shared_ptr<SkillManage>> MySkillManager;
shared_ptr<SkillManage> ChooseSkill(int ChoiceNum,int floor,bool IsBoss) {
	Refresh();
	vector<int> Choice=rm.getSomeNum(0, 9, ChoiceNum);
	MySkillManager.clear();
	for (auto& item:Choice) {
		MySkillManager.push_back(make_shared<SkillManage>(item));
	}
	ChooseEnemy(floor, IsBoss);
	cout << "请在下列技能中选择一个,技能在技能条满时可以释放："<<endl;
	cout << endl;
	int i = 0;
	for (auto& item : MySkillManager) {
		i++;
		cout << i << "." << item->GetDescribe()<<endl;
		cout << endl;
	}
	vector<int> legal;
	for (int idx = 1; idx <= ChoiceNum; ++idx) legal.push_back(idx);
	int pick = Safecin(legal, false);
	if (pick >= 1 && pick <= (int)MySkillManager.size()) {
		return MySkillManager[pick - 1];
	}
	return MySkillManager[0];
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
	for (int i = 0;i < 8;i++) {
		for (int j = 0;j < 100;j++) {
			cout << Themap[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void SupplementDigitNumber(string &num,int digit) {
	while (num.length() < digit) {
		num = " " + num;
	}
}
int Battlerow = 20;
int Battlecol = 90;
bool IfBattleIsOver = false;
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
	SupplementDigitNumber(myhp,4);
	SupplementDigitNumber(myHP,4);
	SupplementDigitNumber(enemyhp,4);
	SupplementDigitNumber(enemyHP,4);
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
	for(int j=32;j<=59;j++) {
		Battlemap[2][j] = "-";
		Battlemap[4][j] = "-";
	}
	for(int j=32;j<32+MyHpBarLength;j++) {
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
	for(int j=32;j<=59;j++) {
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
	Battlemap[16][78] = to_string(round/10);
	Battlemap[16][79] = to_string(round%10);
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
	cout << "我方攻击力:【" << myData[6] << "】,我方防御力:【"<< myData[7] << "】,每剂治疗量:【" << myData[8] <<"】" << endl;
	//打印地图
	for(int i = 0; i < Battlerow; i++) {
		for(int j = 0; j < Battlecol; j++) {
			cout << Battlemap[i][j]<<flush;
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
vector<shared_ptr<RoundBuff>> InitialRoundBuffGroup;//创建时使用的数组
vector<shared_ptr<RoundBuff>> RoundBuffGroup;//筛选后实际使用的数组
bool EnemyIfDizzy = false;
//添加局内buff函数
void AddRoundBuff(string type, double buffnum, int round) {
	InitialRoundBuffGroup.push_back(make_shared<RoundBuff>(type, buffnum, round));
	RoundBuffGroup.push_back(make_shared<RoundBuff>(type, buffnum, round));
}
//更新当前数值状态
void UpdateData(shared_ptr<Enemy> enemy) {
	mycharacter.CalculateMyNum(RoundBuffGroup);
	enemy->CalculateMyNum(RoundBuffGroup);
	MydataWhenBattle[0] = mycharacter.GetCurrentHP();
	MydataWhenBattle[1] = mycharacter.GetCurrentMaxHP();
	MydataWhenBattle[2] = mycharacter.GetCurrentEnergy();
	MydataWhenBattle[3] = mycharacter.GetMaxEnergy();
	MydataWhenBattle[4] = mycharacter.GetCurrentHeal();
	MydataWhenBattle[5] = mycharacter.GetMaxHeal();
	MydataWhenBattle[6] = mycharacter.GetCurrentAttack();
	MydataWhenBattle[7] = mycharacter.GetCurrentDefense();
	MydataWhenBattle[8] = mycharacter.GetHealHP();
	//血量，血量上限，能量，能量上限，治疗条，治疗条上限，攻击，防御，每剂治疗量
	EnemydataWhenBattle[0] = enemy->GetCurrentHP();
	EnemydataWhenBattle[1] = enemy->GetCurrentMaxHP();
	EnemydataWhenBattle[2] = enemy->GetCurrentEnergy();
	EnemydataWhenBattle[3] = enemy->GetMaxEnergy();
	EnemydataWhenBattle[4] = enemy->GetCurrentAttack();
	EnemydataWhenBattle[5] = enemy->GetCurrentDefense();
	EnemydataWhenBattle[6] = enemy->GetCriticalRate();
	//血量，血量上限，能量，能量上限，攻击，防御，暴击率
}
shared_ptr<SkillManage> MySkill;
shared_ptr<SkillManage> EnemySkill;
int UseSkill(shared_ptr<SkillManage> skill) {
	string name = skill->GetName();
	if (name == "EA") {
		AddRoundBuff("EA", -0.3, 3);
		return 1;//攻击一次
	}
	else if (name == "ED") {
		AddRoundBuff("ED", -100, 3);
		return 1;
	}
	else if(name=="MA") {
		AddRoundBuff("MA", 0.5, 3);
		return 1;
	}
	else if(name=="MD") {
		AddRoundBuff("MD", 0.7, 3);
		return 2;
	}
	else if (name == "MB") {
		AddRoundBuff("MB", 1, 4);
		return 2;
	}
	else if (name == "HA") {
		AddRoundBuff("HA", 20, 3);
		return 2;
	}
	else if (name == "AH") {
		return 14;
	}
	else if (name == "AE") {
		return 13;
	}
	else if (name == "IA") {
		return -1;
	}
	else if (name == "DA") {
		EnemyIfDizzy = true;
		return 77;
	}
}
void MyAttack(shared_ptr<Enemy> enemy,int round,bool ifskill) {
	int EnemyHP0 = enemy->GetCurrentHP();
	UpdateData(enemy);
	mycharacter.AttackEnemy(enemy, RoundBuffGroup);
	UpdateData(enemy);
	PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
	int Harm = EnemyHP0 - enemy->GetCurrentHP();
	if (ifskill) {
		cout << "已使用技能" << MySkill->GetDescribe() << endl;
	}
	cout << "敌方受到了 " << Harm << " 点伤害！" << endl;
}
void MyDefend(shared_ptr<Enemy> enemy, int round,bool ifskill){
	mycharacter.CalculateMyNum(RoundBuffGroup);
	AddRoundBuff("MD", mycharacter.GetDefendingDeveloping() - 1, 1);
	UpdateData(enemy);
	PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
	if (ifskill) {
		cout << "已使用技能" << MySkill->GetDescribe() << endl;
	}
	cout << "已使用防御，本回合防御力提升至" << mycharacter.GetDefendingDeveloping() << "倍。" << endl;
}
//回合开始函数
int RoundStart(int round, shared_ptr<Enemy> enemy) {
	EnemyIfDizzy = false;
	if (round % 10 == 0) enemy->CriticalRateCrease(10);//每十回合敌方的暴击率提升10
	//检查该回合过期的buff
	RoundBuffGroup.clear();
	for (auto& item : InitialRoundBuffGroup) {
		item->RoundPass();
		if (!item->GetIfover()) {
			RoundBuffGroup.push_back(item);
		}
	}
	UpdateData(enemy);
	if (round == 1) {
		mycharacter.SetCurrentNum();
		UpdateData(enemy);
	}
	//我方回合
	int RoundChoice = 0;
	vector<int> LegalRoundChoice = { 1,2,3,4,11,12,21,22 };
	while (1) {
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 1);
		if (enemy->GetCurrentAttack() - mycharacter.GetCurrentDefense() >= mycharacter.GetCurrentHP()) {
			cout << "(本回合敌方普通攻击将致我方血量归零，请谨慎选择行动)" << endl;
		}
		else if (enemy->GetCriticalRate() != 0 && enemy->GetCurrentAttack() * enemy->GetCriticalHarm() - mycharacter.GetCurrentDefense() >= mycharacter.GetCurrentHP()) {
			cout << "(本回合敌方若暴击将致我方血量归零，请谨慎选择行动)" << endl;
		}
		if (enemy->GetIfSkill()) {
			cout << "(请注意，敌方技能能量已满，本回合必定暴击)" << endl;
		}
		cout << "请选择本回合的行动：" << endl;
		cout << "1.攻击" << endl;
		cout << "2.防御(不攻击且防御力提升至" << mycharacter.GetDefendingDeveloping() << "倍)" << endl;
		cout << "3.释放技能";
		cout << "(我方技能为：" << MySkill->GetDescribe() << ")"<<endl;
		cout << "4.治疗(治疗条能量不低于2时将额外进行一次防御)";
		cout << "(将消耗所有治疗条进行治疗，每点治疗条回复" << mycharacter.GetHealHP() << "点生命值)";
		cout << endl;
		RoundChoice = Safecin(LegalRoundChoice, false);
		if (RoundChoice == 1 || RoundChoice == 2||RoundChoice == 11 || RoundChoice == 12 || RoundChoice == 21 || RoundChoice == 22) {
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
		else if(RoundChoice==4){
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
	//选择充能
	if (RoundChoice == 1 || RoundChoice == 2||RoundChoice==11||RoundChoice==12||RoundChoice==21||RoundChoice==22) {

		if (!(mycharacter.GetIfHealFull() && mycharacter.GetIfSkill())){
			if (mycharacter.GetIfHealFull()) {
				if (RoundChoice == 11 || RoundChoice == 21) {
					mycharacter.EnergyUp();
				}
				else {
					mycharacter.EnergyUp();
					cout << "治疗条已满，已自动为能量条充能。(2秒后继续)";
					WaitForSeconds(2);
				}
				
			}
			else if (mycharacter.GetIfSkill()) {
				if (RoundChoice == 12 || RoundChoice == 22) {
					mycharacter.HealUp();
				}
				else {
					mycharacter.HealUp();
					cout << "能量条已满，已自动为治疗条充能。(2秒后继续)";
					WaitForSeconds(2);
				}
			}
			else {
				if (RoundChoice == 1 || RoundChoice == 2) {
					PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 1);
					cout << "请选择充能方向：" << endl;
					cout << "1.为能量条充能" << endl;
					cout << "2.为治疗条充能" << endl;
					vector<int> LegalEnergy = { 1,2 };
					int EnergyChoice;
					EnergyChoice = Safecin(LegalEnergy, false);
					if (EnergyChoice == 1) {
						mycharacter.EnergyUp();
					}
					else {
						mycharacter.HealUp();
					}
				}
				else {
					if (RoundChoice == 11 || RoundChoice == 21) {
						mycharacter.EnergyUp();
					}
					else {
						mycharacter.HealUp();
					}
				}
			}
		}
		else {
			cout << "治疗条与能量条均已满，无法充能。(2秒后继续)";
			WaitForSeconds(2);
		}
	}
	if (RoundChoice == 1||RoundChoice==11||RoundChoice==12) {
		MyAttack(enemy, round,false);
	}
	else if (RoundChoice == 2 || RoundChoice == 21 || RoundChoice == 22) {
		MyDefend(enemy, round,false);
	}
	else if (RoundChoice == 3) {//我方技能
		int AttachingAction = 0;
		AttachingAction=UseSkill(MySkill);
		mycharacter.UsingEnergy();
		if (AttachingAction == 1) {
			MyAttack(enemy, round,true);
		}
		else if (AttachingAction == 2) {
			MyDefend(enemy, round,true);
		}
		else if (AttachingAction == 14) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, true, 1.5);
			int SkillHeal_14 = 40;
			mycharacter.Heal(SkillHeal_14);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << "已使用技能" << MySkill->GetDescribe() << endl;
			cout << "敌方受到了 " << Harm << " 点伤害！" << endl;
			cout << "已回复" << SkillHeal_14 << "点血量。" << endl;
		}
		else if (AttachingAction == 13) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, true, 1.5);
			enemy->EnergyIncrease(1);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << "已使用技能" << MySkill->GetDescribe() << endl;
			cout << "敌方受到了 " << Harm << " 点伤害！" << endl;
			cout << "敌方能量-1" << endl;
		}
		else if (AttachingAction == -1) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, false, 2);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << "已使用技能" << MySkill->GetDescribe() << endl;
			cout << "敌方受到了 " << Harm << " 点伤害！" << endl;
		}
		else if (AttachingAction == 77) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, false, 0.5);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << "已使用技能" << MySkill->GetDescribe() << endl;
			cout << "敌方受到了 " << Harm << " 点伤害！" << endl;
		}
		
	}
	else if(RoundChoice==4){
		bool IfUsingDefense = false;
		if (mycharacter.GetCurrentHeal() > 1) {
			AddRoundBuff("MD", mycharacter.GetDefendingDeveloping() - 1, 1);
			IfUsingDefense = true;
		}
		int MyHP0 = mycharacter.GetCurrentHP();
		mycharacter.Heal_UsingHeal();
		UpdateData(enemy);
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
		if (IfUsingDefense) {
			cout << "治疗条能量不低于2，已进行一次防御。" << endl;
		}
		cout << "已消耗所有治疗条回复" << mycharacter.GetCurrentHP() - MyHP0 << "点血量。" << endl;
	}
	if (!enemy->GetIsAlive()) {
		IfBattleIsOver = true;
		cout << "战斗胜利。" << endl;
		cout << "按回车以继续。" << endl;
		SafeEnter();
		return 1;
	}
	cout << "按回车以进入敌方回合...";
	SafeEnter();
	//敌方回合
	Refresh();
	if (!EnemyIfDizzy) {
		if (!enemy->GetIfSkill()) {
			int MyHP0 = mycharacter.GetCurrentHP();
			bool IfCritical = false;
			UpdateData(enemy);
			IfCritical = enemy->AttackPlayer(mycharacter, RoundBuffGroup);
			enemy->EnergyUp();
			int Harm = MyHP0 - mycharacter.GetCurrentHP();
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				mycharacter.Heal(mycharacter.GetHealAfterHarm());
			}
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 2);

			cout << "敌方发动了普通攻击！" << endl;
			if (IfCritical) {
				cout << "敌方造成了暴击伤害！攻击力提升至" << enemy->GetCriticalHarm() << "倍!" << endl;
			}
			cout << "我方受到了 " << Harm << " 点伤害！" << endl;
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				cout << "我方回复了 " << mycharacter.GetHealAfterHarm() << " 点血量。" << endl;
			}

		}
		else {//技能部分
			int MyHP0 = mycharacter.GetCurrentHP();
			bool IfCritical = false;
			enemy->MustCritical();
			UpdateData(enemy);
			IfCritical = enemy->AttackPlayer(mycharacter, RoundBuffGroup);
			enemy->UsingEnergy();
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				mycharacter.Heal(mycharacter.GetHealAfterHarm());
			}
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 2);
			int Harm = MyHP0 - mycharacter.GetCurrentHP();
			cout << "敌方发动了技能！" << endl;
			if (IfCritical) {
				cout << "敌方造成了暴击伤害！攻击力提升至" << enemy->GetCriticalHarm() << "倍!" << endl;
			}
			enemy->EnergyUp();
			cout << "我方受到了 " << Harm << " 点伤害！" << endl;
			enemy->Re_CriticalRate();
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				cout << "我方回复了 " << mycharacter.GetHealAfterHarm() << " 点血量。" << endl;
			}
		}
		UpdateData(enemy);
		if (mycharacter.GetIsAlive()) {
			cout << "按回车以进入我方回合..." << endl;
			return -1;
		}
		else {
			IfBattleIsOver = true;
			cout << "生命值归零。" << endl;
			cout << "你迷失在符文秘境。" << endl;
			cout << "按回车以返回标题界面..." << endl;
			RoundBuffGroup.clear();
			MyObjectGroup.clear();
			SafeEnter();
			return 0;
		}
	}
	else {
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 2);
		cout << "敌方被晕眩，按回车进入我方回合..." << endl;
		return -1;
	}
	
}
void PostWarSettleMent(bool IfBoss) {
	Refresh();
	string separator = string(55, '=');
	cout << separator << endl;
	cout << "战斗结束，你汲取了战场上的生命能量！" << endl;
	int levelUp = IfBoss ? 2 : 1;
	cout << "等级提升：Lv." << mycharacter.GetLevel();
	mycharacter.Levelup(levelUp);
	cout << " → Lv." << mycharacter.GetLevel() << endl;
	cout << separator << endl << endl;
	struct Artifact {
		string name;
		string effect;
		string rarity;
	};

	cout << separator << endl;
	cout << "你从秘境中获得了藏品！" << endl;
	int RandomNumForObject = rm.getnum(1, 100);
	vector<shared_ptr<Object>> ObjectPoolForRandom;
	//随机选择藏品池，40%概率一级，40%概率二级，20%概率三级
	if (RandomNumForObject <= 40) {
		for (auto& item : ObjectPool1) {
			if (!item->GetIfGotten()) {
				ObjectPoolForRandom.push_back(item);
			}
		}
	}
	else if (RandomNumForObject <= 80) {
		for (auto& item : ObjectPool2) {
			if (!item->GetIfGotten()) {
				ObjectPoolForRandom.push_back(item);
			}
		}
	}
	else {
		for (auto& item : ObjectPool3) {
			if (!item->GetIfGotten()) {
				ObjectPoolForRandom.push_back(item);
			}
		}
	}
	int ObjectNum = rm.getnum(0, (int)ObjectPoolForRandom.size() - 1);
	shared_ptr<Object> RandomObject = ObjectPoolForRandom[ObjectNum];
	MyObjectGroup.push_back(RandomObject);
	cout << RandomObject->GetRarity() << " 级藏品:" << endl;
	cout << RandomObject->GetDescribe()<<endl;
	if (IfBoss) {//如果是boss战斗，额外获得一个藏品
		int RandomNumForObject_2 = rm.getnum(1, 100);
		vector<shared_ptr<Object>> ObjectPoolForRandom_2;
		//随机选择藏品池，40%概率一级，40%概率二级，20%概率三级
		if (RandomNumForObject_2 <= 40) {
			for (auto& item : ObjectPool1) {
				if (!item->GetIfGotten()) {
					ObjectPoolForRandom_2.push_back(item);
				}
			}
		}
		else if (RandomNumForObject_2 <= 80) {
			for (auto& item : ObjectPool2) {
				if (!item->GetIfGotten()) {
					ObjectPoolForRandom_2.push_back(item);
				}
			}
		}
		else {
			for (auto& item : ObjectPool3) {
				if (!item->GetIfGotten()) {
					ObjectPoolForRandom_2.push_back(item);
				}
			}
		}
		int ObjectNum_2 = rm.getnum(0, (int)ObjectPoolForRandom_2.size() - 1);
		shared_ptr<Object> RandomObject_2 = ObjectPoolForRandom_2[ObjectNum_2];
		MyObjectGroup.push_back(RandomObject_2);
		cout << RandomObject_2->GetRarity() << " 级藏品:" << endl;
		cout << RandomObject_2->GetDescribe() << endl;
	}
	cout << separator << endl << endl;

	int coinGain = IfBoss ? 6 : 3;
	vector<string> bossCoinStories = {
		"你从 Boss 腐朽的宝座上发现了一袋沉甸甸的金币，散发着远古的光泽。",
		"你搜索 Boss 的遗物箱，找到了 6 枚刻有神秘符文的古金币。",
		"你在 Boss 的巢穴深处发现了一个隐藏的金库，里面整齐码放着 6 枚金币。"
	};
	vector<string> normalCoinStories = {
		"你在敌人残骸中翻找，摸到了 3 枚带着余温的金币。",
		"你掀开一块松动的石板，下面赫然藏着 3 枚金币。",
		"破旧的宝箱里发出叮当声，你打开后获得 3 枚金币。",
		"你从敌人褴褛的衣袋里搜出 3 枚金币，看来是搜刮来的战利品。",
		"一只乌鸦叼来一个钱袋，里面恰好有 3 枚金币——算是友好的馈赠。"
	};
	vector<string>& stories = IfBoss ? bossCoinStories : normalCoinStories;
	int storyIdx = rm.getnum(0, (int)stories.size() - 1);

	cout << separator << endl;
	cout << stories[storyIdx] << endl;
	cout << "你获得了 " << coinGain << " 枚金币！" << endl;
	mycharacter.GainCoin(coinGain);
	cout << "当前金币总数：" << mycharacter.GetCoins() << endl;
	cout << separator << endl << endl;
	//当前等级加成
	cout << separator << endl;
	cout << "当前等级加成：基础生命/攻击/防御 +" << (mycharacter.GetLevel() - 1) * 10 << "%" << endl;
	cout << separator << endl;
	cout << "\n按回车继续...";
}
//战斗开始函数
bool BattleStart(int floor,bool isBoss) {
	RoundBuffGroup.clear();
	InitialRoundBuffGroup.clear();
	IfBattleIsOver = false;
	int round = 1;
	shared_ptr<Enemy> enemy = make_shared<Enemy>();
	MySkill=ChooseSkill(mycharacter.GetChoiceNum(),floor,isBoss);
	enemy= make_shared<Enemy>(EnemyNum_ThisBattle->getHP(), EnemyNum_ThisBattle->getAttack(), EnemyNum_ThisBattle->getDefense(), RoundBuffGroup);
	int IfWin = -1;
	while (1) {
		IfWin=RoundStart(round, enemy);
		if (IfWin == 1||IfWin==0) {
			break;
		}
		round++;
		SafeEnter();
	}
	if (IfWin == 1) {
		PostWarSettleMent(isBoss);
		return true;
	}
	else {
		return false;
	}
}
int main() {
	while (1) {
		//程序运行总循环，输了之后会回到这里
		mycharacter.ReSetNum();
		int floor = 1;
		int	step = 0;
		int thisfloor = 0;
		bool Ifwin = true;
		while (1) {
			//一局游戏循环
			if (thisfloor != floor) {
				RuneManager::RandomChangeRune();
			}
			thisfloor = floor;
			DrawMap(floor, step);
			cout << "当前符文为：" << endl;
			cout << RuneNow->GetDescribe() << endl;
			cout << endl;
			PrintMaphelp();
			cout << endl;
			Ifwin = true;
			switch (Maptype[step]) {
			case 1://普通战斗
				cout << "进入战斗节点，按回车继续..." << endl;
				SafeEnter();
				Ifwin=BattleStart(floor, false);
				break;
			case 4://boss战斗
				cout << "进入Boss战斗节点，按回车继续..." << endl;
				SafeEnter();
				Ifwin=BattleStart(floor, true);
				break;
			case 2://非战斗节点
				cout << "进入未知事件节点，按回车继续..." << endl;
				SafeEnter();
				PrintEventGround(2);
				break;
			case 3://商店节点
				cout << "进入商店节点，按回车继续..." << endl;
				SafeEnter();
				PrintEventGround(3);
				break;
			case 5://双节点
				cout << "进入双节点，请选择节点。输入1以选择战斗节点，输入2以选择未知事件节点：" << endl;
				while (1) {
					int choice = 0;
					vector<int> legal = { 1,2 };
					choice = Safecin(legal, false);
					if (choice == 1) {
						Ifwin = BattleStart(floor, false);
						break;
					}
					else if (choice == 2) {
						PrintEventGround(2);
						break;
					}
				}
				break;
			}
			if (!Ifwin) {
				break;
			}
			SafeEnter();
			step++;
			if (step >= Maptype.size() && floor < 3) {
				step = 0;
				floor++;
			}
			if (step >= Maptype.size() && floor == 3) {
				break;
			}
		}
		
	}
	return 0;
}