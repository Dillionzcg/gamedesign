#pragma once
#include "basis.h"
#include "ClassSkill_RoundBuff.h"
class MyCharacter;
class Enemy {
public:
	Enemy(int hp, int atk, int dfs, vector<shared_ptr<RoundBuff>> RoundBuffGroup) : InitialMaxHP(hp), InitialAttack(atk), InitialDefense(dfs) {
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
		CurrentAttack = BasicAttack * (1.0 + CurrentAttackDevelopment + RoundAttackDevelopment);
		CurrentDefense = BasicDefense * (1.0 + CurrentDefenseDevelopment + RoundDefenseDevelopment);
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
	bool AttackPlayer(MyCharacter& player, vector<shared_ptr<RoundBuff>> RoundBuffGroup);
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