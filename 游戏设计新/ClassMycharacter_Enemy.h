#pragma once
#include"basis.h"
#include"ClassSkill_RoundBuff.h"

// 前向声明
class Enemy;

class MyCharacter {
public:
    MyCharacter() = default;

    // 成员函数声明
    void CalculateMyNum(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void CalculateMyLevelBuff();
    void CalculateMyRoundBuff(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void CalculateMyObject();

    void SetCurrentNum();

    int GetCurrentHP();
    int GetCurrentMaxHP();
    int GetCurrentAttack();
    int GetCurrentDefense();

    int GetCurrentEnergy();
    int GetMaxEnergy();
    int GetInitialEnergy();

    int GetCurrentHeal();
    int GetMaxHeal();
    int GetInitialHeal();
    int GetHealHP();

    int GetCoins();
    int GetLevel();

    void BeingAttacked(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);

    // 跨类调用的函数声明（注意：此时 Enemy 只有前向声明，所以这里用指针/智能指针是合法的）
    void AttackEnemy(std::shared_ptr<Enemy> enemy, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void SpecialAttackEnemy(std::shared_ptr<Enemy> enemy, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup, bool IfCalDefense, double AttackCrease);

    bool GetIsAlive();
    int getLeastharm();
    bool GetIfSkill();
    bool GetIfHeal();
    bool GetIfHealFull();
    double GetDefendingDeveloping();

    void EnergyUp();
    void HealUp();
    void UsingEnergy();
    void UsingHeal();

    void Heal_UsingHeal();
    void Heal(int heal);

    int GetChoiceNum();
    int GetHealAfterHarm();

    void Levelup(int num);
    void GainCoin(int num);
    void ReSetNum();

    void InitialMaxHPDevelopment(double num);
    void InitialAttackDevelopment(double num);
    void UsingCoins(int num);

private:
    int InitialMaxHP = 300;
    int InitialAttack = 80;
    int InitialDefense = 100;
    int BasicMaxHP = 0;
    int BasicAttack = 0;
    int BasicDefense = 0;
    int CurrentMaxHP = 0;
    int CurrentAttack = 0;
    int CurrentDefense = 0;
    //藏品加成
    double BasicHPDevelopment = 0;
    double BasicAttackDevelopment = 0;
    double BasicDefenseDevelopment = 0;
    int BasicHEdevelopment = 0;
    int BasicIEdevelopment = 0;
    int BasicIHEdevelopment = 0;
    int BasicMHEdevelopment = 0;
    int BasicSCdevelopment = 0;
    int BasicENdevelopment = 0;

    double LevelHPDevelopment = 0;
    double LevelAttackDevelopment = 0;
    double LevelDefenseDevelopment = 0;

    double RoundAttackDevelopment = 0;
    double RoundDefenseDevelopment = 0;
    double RoundDefendingBuff = 0;
    int CurrentHP = 0;
    int CurrentEnergy = 0;
    int InitialEnergy = 0;
    int MaxEnergy = 3;
    int CurrentHeal = 0;
    int InitialHeal = 0;
    int MaxHeal = 3;
    int HealHP = 30;
    int Coins = 0;
    int Level = 1;
    bool IsAlive = true;
    double BasicDefendingDeveloping = 2;
    double DefendingDeveloping = 2;
    double leastHarm = 0.1;
    int SkillChoiceNum = 3;
    int HealAfterHarm = 0;
};

extern MyCharacter mycharacter;
class Enemy {
public:
    // 构造函数可以保留简单实现，或者也移到 cpp 中
    Enemy(int hp, int atk, int dfs, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    Enemy() = default;

    void CalculateMyRoundBuff(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void CalculateMyNum(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void CalculateMyObject();

    void SetCurrentHP();

    int GetCurrentHP();
    int GetCurrentMaxHP();
    int GetCurrentAttack();
    int GetCurrentDefense();

    int GetCurrentEnergy();
    int GetMaxEnergy();
    int GetInitialEnergy();

    int GetCriticalRate();
    double GetCriticalHarm();

    void BeingAttacked(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);
    void BeingAttacked_NoDefense(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);

    bool AttackPlayer(MyCharacter& player, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup);

    bool GetIsAlive();
    bool GetIfSkill();

    void Heal(int heal);
    void EnergyUp();
    void UsingEnergy();
    void CriticalRateCrease(int num);
    void EnergyIncrease(int num);
    void SkillMustCritical();
    void MustNotCritical();
    void Re_CriticalRate();


private:
    int InitialMaxHP = 0;
    int InitialAttack = 0;
    int InitialDefense = 0;
    int BasicMaxHP = 0;
    int BasicAttack = 0;
    int BasicDefense = 0;
    int CurrentMaxHP = 0;
    int CurrentAttack = 0;
    int CurrentDefense = 0;

    double BasicHPDevelopment = 0;
    double BasicAttackDevelopment = 0;
    double BasicDefenseDevelopment = 0;
	double BasicCRdevelopment = 0;
    int BasicENdevelopment = 0;
	double BasicCHdevelopment = 0;
    int BasicIEdevelopment = 0;

    double RoundAttackDevelopment = 0;
    double RoundDefenseDevelopment = 0;
    int CurrentHP = 100;
    int CurrentEnergy = 0;
    int InitialEnergy = 0;
    int MaxEnergy = 6;
    int CriticalRate = 30;
    int CriticalRate_Tem = 0;
    double CriticalHarm = 2.5;
    bool IsAlive = true;
    bool MustCritical = false;
    bool MustNotCriticalBool = false;
};