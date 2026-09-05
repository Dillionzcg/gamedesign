#include "ClassMycharacter_Enemy.h"

void MyCharacter::CalculateMyObject() {
	BasicHPDevelopment = 0;
	BasicAttackDevelopment = 0;
	BasicDefenseDevelopment = 0;
	BasicHEdevelopment = 0;
    BasicIEdevelopment = 0;
    BasicIHEdevelopment = 0;
    BasicMHEdevelopment = 0;
    BasicSCdevelopment = 0;
    BasicENdevelopment = 0;
    for (auto& item : MyObjectGroup) {
        if (item->GetCamp() == "M") {
            string ObjectType=item->GetType();
            double Num = item->GetBuffNum();
            if (ObjectType == "A") {
                BasicAttackDevelopment += Num;
            }
            else if(ObjectType=="D") {
				BasicDefenseDevelopment += Num;
            }
			else if (ObjectType == "H") {
				BasicHPDevelopment += Num;
			}
			else if (ObjectType == "HE") {
				BasicHEdevelopment += Num;
			}
			else if (ObjectType == "IE") {
				BasicIEdevelopment += Num;
			}
			else if (ObjectType == "IHE") {
				BasicIHEdevelopment += Num;
			}
			else if (ObjectType == "MHE") {
				BasicMHEdevelopment += Num;
			}
			else if (ObjectType == "SC") {
				BasicSCdevelopment += Num;
			}
            else if (ObjectType == "EN") {
                BasicENdevelopment += Num;
            }
        }
    }
    for (auto& item : RuneDevelopment) {
        if (item->GetCamp() == "M") {
            string ObjectType = item->GetType();
            double Num = item->GetBuffNum();
            if (ObjectType == "A") {
                BasicAttackDevelopment += Num;
            }
            else if (ObjectType == "D") {
                BasicDefenseDevelopment += Num;
            }
            else if (ObjectType == "H") {
                BasicHPDevelopment += Num;
            }
            else if (ObjectType == "HE") {
                BasicHEdevelopment += Num;
            }
            else if (ObjectType == "IE") {
                BasicIEdevelopment += Num;
            }
            else if (ObjectType == "IHE") {
                BasicIHEdevelopment += Num;
            }
            else if (ObjectType == "MHE") {
                BasicMHEdevelopment += Num;
            }
            else if (ObjectType == "SC") {
                BasicSCdevelopment += Num;
            }
            else if (ObjectType == "EN") {
                BasicENdevelopment += Num;
            }
        }
    }
}
void MyCharacter::CalculateMyNum(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
    CalculateMyRoundBuff(RoundBuffGroup);
    CalculateMyLevelBuff();
    CalculateMyObject();
    BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment + LevelHPDevelopment);
    BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment + LevelAttackDevelopment);
    BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment + LevelDefenseDevelopment);
    CurrentMaxHP = BasicMaxHP;
    CurrentAttack = BasicAttack * (1.0 + RoundAttackDevelopment);
    CurrentDefense = BasicDefense * (1.0 + RoundDefenseDevelopment);
    DefendingDeveloping = BasicDefendingDeveloping + RoundDefendingBuff;
    if (CurrentDefense < 0) CurrentDefense = 0;
	HealHP = 30 + BasicHEdevelopment;
	InitialEnergy = 0 + BasicIEdevelopment;
	InitialHeal = 0 + BasicIHEdevelopment;
	MaxEnergy = 3 + BasicENdevelopment;
	SkillChoiceNum = 3 + BasicSCdevelopment;
    if (SkillChoiceNum > 10) SkillChoiceNum = 10;
	MaxHeal = 3 + BasicMHEdevelopment;
    if(InitialHeal>MaxHeal) {
        InitialHeal = MaxHeal;
    }
    if(InitialEnergy>MaxEnergy) {
        InitialEnergy = MaxEnergy;
    }
    if (MaxEnergy < 1) {
		MaxEnergy = 1;
    }
}

void MyCharacter::CalculateMyLevelBuff() {
    LevelHPDevelopment = (Level - 1) * 0.1;
    LevelAttackDevelopment = (Level - 1) * 0.1;
    LevelDefenseDevelopment = (Level - 1) * 0.1;
}

void MyCharacter::CalculateMyRoundBuff(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
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

void MyCharacter::SetCurrentNum() {
    CurrentHP = CurrentMaxHP;
    CurrentHeal = InitialHeal;
    CurrentEnergy = InitialEnergy;
    IsAlive = true;
}
void Enemy::SetCurrentNum() {
    CurrentHP = CurrentMaxHP;
    CurrentEnergy = InitialEnergy;
    IsAlive = true;
}
int MyCharacter::GetCurrentHP() { return CurrentHP; }
int MyCharacter::GetCurrentMaxHP() { return CurrentMaxHP; }
int MyCharacter::GetCurrentAttack() { return CurrentAttack; }
int MyCharacter::GetCurrentDefense() { return CurrentDefense; }
int MyCharacter::GetCurrentEnergy() { return CurrentEnergy; }
int MyCharacter::GetMaxEnergy() { return MaxEnergy; }
int MyCharacter::GetInitialEnergy() { return InitialEnergy; }
int MyCharacter::GetCurrentHeal() { return CurrentHeal; }
int MyCharacter::GetMaxHeal() { return MaxHeal; }
int MyCharacter::GetInitialHeal() { return InitialHeal; }
int MyCharacter::GetHealHP() { return HealHP; }
int MyCharacter::GetCoins() { return Coins; }
int MyCharacter::GetLevel() { return Level; }
int MyCharacter::GetInitialAttack() { return InitialAttack; }
int MyCharacter::GetInitialDefense() { return InitialDefense; }
int MyCharacter::GetInitialMaxHP() { return InitialMaxHP; }

void MyCharacter::BeingAttacked(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
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

bool MyCharacter::GetIsAlive() { return IsAlive; }
int MyCharacter::getLeastharm() { return leastHarm * 10; }
bool MyCharacter::GetIfSkill() { return (CurrentEnergy == MaxEnergy); }
bool MyCharacter::GetIfHeal() { return (CurrentHeal != 0); }
bool MyCharacter::GetIfHealFull() { return (CurrentHeal == MaxHeal); }
double MyCharacter::GetDefendingDeveloping() { return DefendingDeveloping; }

void MyCharacter::EnergyUp() {
    if (!GetIfSkill()) { CurrentEnergy++; }
}

void MyCharacter::HealUp() {
    if (!GetIfHealFull()) { CurrentHeal++; }
}

void MyCharacter::UsingEnergy() { CurrentEnergy = 0; }
void MyCharacter::UsingHeal() { CurrentHeal = 0; }

void MyCharacter::Heal_UsingHeal() {
    int heal = CurrentHeal * HealHP;
    if (CurrentHP + heal <= CurrentMaxHP) { CurrentHP += heal; }
    else { CurrentHP = CurrentMaxHP; }
    UsingHeal();
}

void MyCharacter::Heal(int heal) {
    if (CurrentHP + heal <= CurrentMaxHP) { CurrentHP += heal; }
    else { CurrentHP = CurrentMaxHP; }
}

int MyCharacter::GetChoiceNum() { return SkillChoiceNum; }
int MyCharacter::GetHealAfterHarm() { return HealAfterHarm; }
void MyCharacter::Levelup(int num) { Level += num; }
void MyCharacter::GainCoin(int num) { Coins += num; }

void MyCharacter::ReSetNum() {
    InitialMaxHP = 300;
    InitialAttack = 80;
    InitialDefense = 100;
    Coins = 0;
    Level = 1;
    IsAlive = true;
    SkillChoiceNum = 3;
}

void MyCharacter::UsingCoins(int num) {
    Coins -= num;
}

void MyCharacter::InitialMaxHPDevelopment(double num) { InitialMaxHP *= (1.0 + num); }
void MyCharacter::InitialAttackDevelopment(double num) { InitialAttack *= (1.0 + num); }

void MyCharacter::ReadData(int inihp, int iniatk, int inidfs, int level, int coins) {
    InitialMaxHP = inihp;
    InitialAttack = iniatk;
    InitialDefense = inidfs;
    Level = level;
    Coins = coins;
}


Enemy::Enemy(int hp, int atk, int dfs, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup)
    : InitialMaxHP(hp), InitialAttack(atk), InitialDefense(dfs) {
    CalculateMyNum(RoundBuffGroup);
    SetCurrentHP();
}

void Enemy::CalculateMyRoundBuff(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
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
void Enemy::CalculateMyObject() {
	BasicHPDevelopment = 0;
    BasicAttackDevelopment = 0;
    BasicDefenseDevelopment = 0;
	BasicCRdevelopment = 0;
	BasicENdevelopment = 0;
	BasicCHdevelopment = 0;
	BasicIEdevelopment = 0;
	for (auto& item : MyObjectGroup) {
		if (item->GetCamp() == "E") {
			string ObjectType = item->GetType();
			double Num = item->GetBuffNum();
			if (ObjectType == "A") {
				BasicAttackDevelopment += Num;
			}
			else if (ObjectType == "D") {
				BasicDefenseDevelopment += Num;
			}
			else if (ObjectType == "H") {
				BasicHPDevelopment += Num;
			}
			else if (ObjectType == "EN") {
				BasicENdevelopment += Num;
			}
            else if (ObjectType == "CR") {
                BasicCRdevelopment += Num;
            }
            else if (ObjectType == "CH") {
                BasicCHdevelopment += Num;
            }
            else if (ObjectType == "IE") {
                BasicIEdevelopment += Num;
            }
		}
	}
    for (auto& item : RuneDevelopment) {
        if (item->GetCamp() == "E") {
            string ObjectType = item->GetType();
            double Num = item->GetBuffNum();
            if (ObjectType == "A") {
                BasicAttackDevelopment += Num;
            }
            else if (ObjectType == "D") {
                BasicDefenseDevelopment += Num;
            }
            else if (ObjectType == "H") {
                BasicHPDevelopment += Num;
            }
            else if (ObjectType == "EN") {
                BasicENdevelopment += Num;
            }
            else if (ObjectType == "CR") {
                BasicCRdevelopment += Num;
            }
            else if (ObjectType == "CH") {
                BasicCHdevelopment += Num;
            }
            else if (ObjectType == "IE") {
                BasicIEdevelopment += Num;
            }
        }
    }
}
void Enemy::CalculateMyNum(std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
    CalculateMyRoundBuff(RoundBuffGroup);
	CalculateMyObject();
    BasicMaxHP = InitialMaxHP * (1.0 + BasicHPDevelopment);
    BasicAttack = InitialAttack * (1.0 + BasicAttackDevelopment);
    BasicDefense = InitialDefense * (1.0 + BasicDefenseDevelopment);
    CurrentMaxHP = BasicMaxHP;
    CurrentAttack = BasicAttack * (1.0 + RoundAttackDevelopment);
    CurrentDefense = BasicDefense * (1.0 + RoundDefenseDevelopment);
    if (CurrentDefense <= 0) CurrentDefense = 0;

	MaxEnergy = 6 + BasicENdevelopment;
	InitialEnergy = 0 + BasicIEdevelopment;
	CriticalRate = 30 + BasicCRdevelopment;
	CriticalHarm = 2 + BasicCHdevelopment;
    if (InitialEnergy > MaxEnergy) {
        InitialEnergy = MaxEnergy;
    }
    if(CriticalRate<0) {
        CriticalRate = 0;
    }
    if (MustCritical) {
        CriticalRate = 100;
    }
    if (MustNotCriticalBool) {
        CriticalRate = 0;
    }
}

void Enemy::SetCurrentHP() { CurrentHP = CurrentMaxHP; }

int Enemy::GetCurrentHP() { return CurrentHP; }
int Enemy::GetCurrentMaxHP() { return CurrentMaxHP; }
int Enemy::GetCurrentAttack() { return CurrentAttack; }
int Enemy::GetCurrentDefense() { return CurrentDefense; }
int Enemy::GetCurrentEnergy() { return CurrentEnergy; }
int Enemy::GetMaxEnergy() { return MaxEnergy; }
int Enemy::GetInitialEnergy() { return InitialEnergy; }
int Enemy::GetCriticalRate() { return CriticalRate; }
double Enemy::GetCriticalHarm() { return CriticalHarm; }

void Enemy::BeingAttacked(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
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

void Enemy::BeingAttacked_NoDefense(int damage, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
    CalculateMyNum(RoundBuffGroup);
    CurrentHP -= damage;
    if (CurrentHP <= 0) {
        CurrentHP = 0;
        IsAlive = false;
    }
}

bool Enemy::AttackPlayer(MyCharacter& player, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
    CalculateMyNum(RoundBuffGroup);
    int NumforCritical = rm.getnum(1, 100); 
    bool IfCritical = (NumforCritical <= CriticalRate);
    int damage = 0;
    if (IfCritical) {
        damage = CurrentAttack * CriticalHarm;
    }
    else {
        damage = CurrentAttack;
    }

    player.BeingAttacked(damage, RoundBuffGroup);
    return IfCritical;
}

bool Enemy::GetIsAlive() { return IsAlive; }
bool Enemy::GetIfSkill() { return (CurrentEnergy == MaxEnergy); }

void Enemy::Heal(int heal) {
    if (CurrentHP + heal <= CurrentMaxHP) { CurrentHP += heal; }
    else { CurrentHP = CurrentMaxHP; }
}

void Enemy::EnergyUp() {
    if (!GetIfSkill()) { CurrentEnergy++; }
}

void Enemy::UsingEnergy() { CurrentEnergy = 0; }
void Enemy::CriticalRateCrease(int num) { CriticalRate += num; }
void Enemy::EnergyIncrease(int num) { if (CurrentEnergy > 0) CurrentEnergy--; }

void Enemy::SkillMustCritical() {
    MustCritical = true;
}

void Enemy::MustNotCritical() {
    MustNotCriticalBool = true;
}
void Enemy::Re_CriticalRate() {
    MustCritical = false; 
    MustNotCriticalBool = false;
}

void MyCharacter::AttackEnemy(std::shared_ptr<Enemy> enemy, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup) {
    CalculateMyNum(RoundBuffGroup);
    int damage = CurrentAttack;
    enemy->BeingAttacked(damage, RoundBuffGroup);
}

void MyCharacter::SpecialAttackEnemy(std::shared_ptr<Enemy> enemy, std::vector<std::shared_ptr<RoundBuff>> RoundBuffGroup, bool IfCalDefense, double AttackCrease) {
    CalculateMyNum(RoundBuffGroup);
    int damage = CurrentAttack * (1 + AttackCrease);
    if (IfCalDefense) {
        enemy->BeingAttacked(damage, RoundBuffGroup);
    }
    else {
        enemy->BeingAttacked_NoDefense(damage, RoundBuffGroup);
    }
}