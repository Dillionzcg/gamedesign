#pragma once
#include "basis.h"
#include "ClassSkill_RoundBuff.h"
class Enemy;

class MyCharacter {
public:
	MyCharacter() = default;
	//计算基础数值和当前数值
	void CalculateMyNum(vector<shared_ptr<RoundBuff>> RoundBuffGroup) {
		CalculateMyRoundBuff(RoundBuffGroup);
		CalculateMyLevelBuff();
		BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment + LevelHPDevelopment);
		BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment + LevelAttackDevelopment);
		BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment + LevelDefenseDevelopment);
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
					HealAfterHarm += item->GetDevelopment();
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
	void InitialMaxHPDevelopment(double num) {
		InitialMaxHP *= (1.0 + num);
	}
	void InitialAttackDevelopment(double num) {
		InitialAttack *= (1.0 + num);
	}
private:
	//初始数值，仅开局选择buff时会改变
	int InitialMaxHP = 200;
	int InitialAttack = 80;
	int InitialDefense = 50;
	//基础数值，为初始数值计算藏品加成与等级加成后的数值
	int BasicMaxHP = 0;
	int BasicAttack = 0;
	int BasicDefense = 0;
	//当前数值，为基础数值计算其余buff/debuff加成后的数值
	int CurrentMaxHP = 0;
	int CurrentAttack = 0;
	int CurrentDefense = 0;
	//藏品加成
	double BasicHPDevelopment = 0;
	double BasicAttackDevelopment = 0;
	double BasicDefenseDevelopment = 0;
	//等级加成
	double LevelHPDevelopment = 0;
	double LevelAttackDevelopment = 0;
	double LevelDefenseDevelopment = 0;
	//其余buff/debuff加成的总加成
	double CurrentHPDevelopment = 0;
	double CurrentAttackDevelopment = 0;
	double CurrentDefenseDevelopment = 0;
	//局内buff/debuff加成的总加成
	double RoundAttackDevelopment = 0;
	double RoundDefenseDevelopment = 0;
	double RoundDefendingBuff = 0;
	//当前血量
	int CurrentHP = 0;
	//能量
	int CurrentEnergy = 0;
	int InitialEnergy = 0;
	int MaxEnergy = 3;
	//治疗条
	int CurrentHeal = 0;
	int InitialHeal = 0;
	int MaxHeal = 3;
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