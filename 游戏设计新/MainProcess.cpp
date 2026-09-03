#include"MainProcess.h"
using namespace std;
vector<string> forcheck;
RandomManager rm;

MyCharacter mycharacter;

vector<shared_ptr<RoundBuff>> InitialRoundBuffGroup;//创建时使用的数组
vector<shared_ptr<RoundBuff>> RoundBuffGroup;//筛选后实际使用的数组

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
bool EnemyIfDizzy = false;
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
	else if (name == "MA") {
		AddRoundBuff("MA", 0.5, 3);
		return 1;
	}
	else if (name == "MD") {
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
void MyAttack(shared_ptr<Enemy> enemy, int round, bool ifskill) {
	int EnemyHP0 = enemy->GetCurrentHP();
	UpdateData(enemy);
	mycharacter.AttackEnemy(enemy, RoundBuffGroup);
	UpdateData(enemy);
	PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
	int Harm = EnemyHP0 - enemy->GetCurrentHP();
	if (ifskill) {
		cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
	}
	cout << RED_BOLD << "敌方受到了 " << Harm << " 点伤害！" << endl;
}
void MyDefend(shared_ptr<Enemy> enemy, int round, bool ifskill) {
	mycharacter.CalculateMyNum(RoundBuffGroup);
	AddRoundBuff("MD", mycharacter.GetDefendingDeveloping() - 1, 1);
	UpdateData(enemy);
	PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
	if (ifskill) {
		cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
	}
	cout << YELLOW << "已使用防御，本回合防御力提升至" << mycharacter.GetDefendingDeveloping() << "倍。" << endl;
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
			cout << RED_BOLD << "(本回合敌方普通攻击将致我方血量归零，请谨慎选择行动)" << endl;
		}
		else if (enemy->GetCriticalRate() != 0 && enemy->GetCurrentAttack() * enemy->GetCriticalHarm() - mycharacter.GetCurrentDefense() >= mycharacter.GetCurrentHP()) {
			cout << RED_BOLD << "(本回合敌方若暴击将致我方血量归零，请谨慎选择行动)" << endl;
		}
		if (enemy->GetIfSkill()) {
			cout << RED_BOLD << "(请注意，敌方技能能量已满，本回合必定暴击)" << endl;
		}
		cout << RESET;
		cout << "请选择本回合的行动：" << endl;
		cout << "1.攻击" << endl;
		cout << "2.防御(不攻击且防御力提升至" << mycharacter.GetDefendingDeveloping() << "倍)" << endl;
		if (mycharacter.GetIfSkill()) {
			cout << YELLOW;
		}
		else {
			cout << HUI;
		}
		cout << "3.释放技能";
		cout << "(我方技能为：" << MySkill->GetDescribe() << ")" << endl;
		if (mycharacter.GetIfHeal()) {
			cout << BLUE;
		}
		else {
			cout << HUI;
		}
		cout << "4.治疗";
		cout << "(治疗条能量不低于2时将额外进行一次防御)";
		cout << "(将消耗所有治疗条进行治疗，每点治疗条回复" << mycharacter.GetHealHP() << "点生命值)";
		cout << endl;
		RoundChoice = Safecin(LegalRoundChoice, false);
		if (RoundChoice == 1 || RoundChoice == 2 || RoundChoice == 11 || RoundChoice == 12 || RoundChoice == 21 || RoundChoice == 22) {
			break;
		}
		else if (RoundChoice == 3) {
			if (mycharacter.GetIfSkill()) {
				break;
			}
			else {
				cout << RED_DARK;
				cout << "技能未充能满，无法释放!" << endl;
				cout << "请重新选择行动。" << endl;
				cout << "2秒后刷新界面...";
				WaitForSeconds(1);
				cout << "\r\033[K" << "1秒后刷新界面..." << flush;
				WaitForSeconds(1);
			}
		}
		else if (RoundChoice == 4) {
			if (mycharacter.GetIfHeal()) {
				break;
			}
			else {
				cout << RED_DARK;
				cout << "治疗条为空，无法治疗!" << endl;
				cout << "请重新选择行动。" << endl;
				cout << "2秒后刷新界面...";
				WaitForSeconds(1);
				cout << "\r\033[K" << "1秒后刷新界面..." << flush;
				WaitForSeconds(1);
			}
		}
	}
	//选择充能
	if (RoundChoice == 1 || RoundChoice == 2 || RoundChoice == 11 || RoundChoice == 12 || RoundChoice == 21 || RoundChoice == 22) {

		if (!(mycharacter.GetIfHealFull() && mycharacter.GetIfSkill())) {
			if (mycharacter.GetIfHealFull()) {
				if (RoundChoice == 11 || RoundChoice == 21) {
					mycharacter.EnergyUp();
				}
				else {
					mycharacter.EnergyUp();
					cout << RED_DARK;
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
					cout << RED_DARK;
					cout << "能量条已满，已自动为治疗条充能。(2秒后继续)";
					WaitForSeconds(2);
				}
			}
			else {
				if (RoundChoice == 1 || RoundChoice == 2) {
					PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 1);
					cout << RESET;
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
			cout << RED_BOLD;
			cout << "治疗条与能量条均已满，无法充能。(2秒后继续)";
			WaitForSeconds(2);
		}
	}
	if (RoundChoice == 1 || RoundChoice == 11 || RoundChoice == 12) {
		MyAttack(enemy, round, false);
	}
	else if (RoundChoice == 2 || RoundChoice == 21 || RoundChoice == 22) {
		MyDefend(enemy, round, false);
	}
	else if (RoundChoice == 3) {//我方技能
		int AttachingAction = 0;
		AttachingAction = UseSkill(MySkill);
		mycharacter.UsingEnergy();
		if (AttachingAction == 1) {
			MyAttack(enemy, round, true);
		}
		else if (AttachingAction == 2) {
			MyDefend(enemy, round, true);
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
			cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
			cout << RED_BOLD << "敌方受到了 " << Harm << " 点伤害！" << endl;
			cout << BLUE << "已回复" << SkillHeal_14 << "点血量。" << endl;
		}
		else if (AttachingAction == 13) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, true, 1.5);
			enemy->EnergyIncrease(1);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
			cout << RED_BOLD << "敌方受到了 " << Harm << " 点伤害！" << endl;
			cout << RED_DARK << "敌方能量-1" << endl;
		}
		else if (AttachingAction == -1) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, false, 2);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
			cout << RED_BOLD << "敌方受到了 " << Harm << " 点伤害！" << endl;
		}
		else if (AttachingAction == 77) {
			int EnemyHP0 = enemy->GetCurrentHP();
			UpdateData(enemy);
			mycharacter.SpecialAttackEnemy(enemy, RoundBuffGroup, false, 0.5);
			UpdateData(enemy);
			PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 3);
			int Harm = EnemyHP0 - enemy->GetCurrentHP();
			cout << BOLD << "已使用技能" << GREEN_BRIGHT << MySkill->GetDescribe() << endl;
			cout << RED_BOLD << "敌方受到了 " << Harm << " 点伤害！" << endl;
		}

	}
	else if (RoundChoice == 4) {
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
			cout << YELLOW << "治疗条能量不低于2，已进行一次防御。" << endl;
		}
		cout << BLUE << "已消耗所有治疗条回复" << mycharacter.GetCurrentHP() - MyHP0 << "点血量。" << endl;
	}
	if (!enemy->GetIsAlive()) {
		IfBattleIsOver = true;
		cout << YELLOW << "战斗胜利。" << endl;
		cout << "按回车以继续。" << endl;
		SafeEnter();
		return 1;
	}
	cout << HUI << "按回车以进入敌方回合...";
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

			cout << RESET << "敌方发动了普通攻击！" << endl;
			if (IfCritical) {
				cout << RED_BOLD << "敌方造成了暴击伤害！攻击力提升至" << enemy->GetCriticalHarm() << "倍!" << endl;
			}
			cout << RED_DARK << "我方受到了 " << Harm << " 点伤害！" << endl;
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				cout << BLUE << "我方回复了 " << mycharacter.GetHealAfterHarm() << " 点血量。" << endl;
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
			cout << RED_BOLD << "敌方发动了技能！" << endl;
			if (IfCritical) {
				cout << RED_BOLD << "敌方造成了暴击伤害！攻击力提升至" << enemy->GetCriticalHarm() << "倍!" << endl;
			}
			enemy->EnergyUp();
			cout << RED_DARK << "我方受到了 " << Harm << " 点伤害！" << endl;
			enemy->Re_CriticalRate();
			if (mycharacter.GetIsAlive() && mycharacter.GetHealAfterHarm() != 0) {
				cout << BLUE << "我方回复了 " << mycharacter.GetHealAfterHarm() << " 点血量。" << endl;
			}
		}
		UpdateData(enemy);
		if (mycharacter.GetIsAlive()) {
			cout << HUI << "按回车以进入我方回合..." << endl;
			return -1;
		}
		else {
			IfBattleIsOver = true;
			cout << PURPLE << "生命值归零。" << endl;
			cout << "你迷失在符文秘境。" << endl;
			cout << HUI << "按回车以返回标题界面..." << endl;
			RoundBuffGroup.clear();
			MyObjectGroup.clear();
			SafeEnter();
			return 0;
		}
	}
	else {
		PrintBalttleGround(MydataWhenBattle, EnemydataWhenBattle, round, 2);
		cout << YELLOW << "敌方被晕眩，按回车进入我方回合..." << endl;
		return -1;
	}

}
void PostWarSettleMent(bool IfBoss) {
	Refresh();
	string separator = string(55, '=');
	cout << HUI << separator << endl;
	cout << WHITE;
	cout << "战斗结束，你汲取了战场上的符文能量！" << endl;
	int levelUp = IfBoss ? 2 : 1;
	cout << YELLOW;
	cout << "等级提升：Lv." << mycharacter.GetLevel();
	mycharacter.Levelup(levelUp);
	cout << " → Lv." << mycharacter.GetLevel() << endl;
	cout << endl;
	struct Artifact {
		string name;
		string effect;
		string rarity;
	};
	cout << WHITE;
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
	cout << QING;
	cout << RandomObject->GetRarity() << " 级藏品:" << endl;
	cout << GREEN_BRIGHT;
	cout << RandomObject->GetDescribe() << endl;
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
		cout << QING;
		cout << RandomObject_2->GetRarity() << " 级藏品:" << endl;
		cout << GREEN_BRIGHT;
		cout << RandomObject_2->GetDescribe() << endl;
	}
	cout << endl;
	int coinGain = IfBoss ? 6 : 3;
	vector<string> bossCoinStories = {
		"你破开试炼之影的残骸，在厚重的黑霜下搜出了 6 枚刻有禁忌符文的古金币。",
		"石棺的底座在震颤中裂开，里面整齐码放着 6 枚沉甸甸的殉葬金币。"
	};

	vector<string> normalCoinStories = {
		"你在冰冷的尸骸中翻找，从凝固的血迹下摸出了 3 枚犹带余温的金币。",
		"你掀开一块布满青苔的石板，狭窄的暗格内静静躺着 3 枚古旧金币。",
		"你自敌人的褴褛行囊中剥离出 3 枚金属货币，上面还沾染着未干的尘土。",
		"穿堂风卷过空旷的回廊，吹落了一只悬挂的钱袋，落地时散落出恰好 3 枚金币。"
	};
	vector<string>& stories = IfBoss ? bossCoinStories : normalCoinStories;
	int storyIdx = rm.getnum(0, (int)stories.size() - 1);

	cout << WHITE << stories[storyIdx] << endl;
	cout << YELLOW << "你获得了 " << coinGain << " 枚金币！" << endl;
	mycharacter.GainCoin(coinGain);
	cout << HUI;
	cout << GOLD_BOLD << "当前金币总数：" << mycharacter.GetCoins() << endl;
	;
	//当前等级加成
	cout << endl;
	cout << RED_BOLD << "当前等级加成：基础生命/攻击/防御 +" << (mycharacter.GetLevel() - 1) * 10 << "%" << endl;
	cout << HUI << separator << endl;
	cout << "\n按回车继续...";
	SafeEnter();
}
//战斗开始函数
bool BattleStart(int floor, bool isBoss, bool IfHard) {
	ResetLastBarLength();
	RoundBuffGroup.clear();
	InitialRoundBuffGroup.clear();
	IfBattleIsOver = false;
	int round = 1;
	shared_ptr<Enemy> enemy = make_shared<Enemy>();
	MySkill = ChooseSkill(mycharacter.GetChoiceNum(), floor, isBoss, IfHard);
	enemy = make_shared<Enemy>(EnemyNum_ThisBattle->getHP(), EnemyNum_ThisBattle->getAttack(), EnemyNum_ThisBattle->getDefense(), RoundBuffGroup);
	int IfWin = -1;
	while (1) {
		IfWin = RoundStart(round, enemy);
		if (IfWin == 1 || IfWin == 0) {
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


int MapChoose(int floor, int step, int type) {
	vector<int> MapLegalChoice;
	if (type != 5) {
		MapLegalChoice = { 0,9 };
	}
	else {
		MapLegalChoice = { 0,1,2,9 };
	}

	int MapChoice = 0;
	while (1) {
		DrawMap(floor, step);
		switch (floor) {
		case 1:cout << QING;break;
		case 2:cout << YELLOW;break;
		case 3:cout << RED_WINE;break;
		}
		cout << "当前符文为：" << endl;
		cout << RuneNow->GetDescribe() << endl;
		cout << endl;
		PrintMaphelp();
		cout << endl;
		switch (type) {
		case 1://普通战斗
			cout << "进入战斗节点，按回车继续...（或输入0以查看当前状态，输入9以存档）" << endl;
			break;
		case 4://boss战斗
			cout << "进入Boss战斗节点，按回车继续...（或输入0以查看当前状态，输入9以存档）" << endl;
			break;
		case 2://非战斗节点
			cout << "进入未知事件节点，按回车继续...（或输入0以查看当前状态，输入9以存档）" << endl;
			break;
		case 3://商店节点
			cout << "进入商店节点，按回车继续...（或输入0以查看当前状态，输入9以存档）" << endl;
			break;
		case 5://双节点
			cout << "进入双节点，请选择节点。输入1以选择战斗节点，输入2以选择未知事件节点：（或输入0以查看当前状态，输入9以存档）" << endl;
			break;
		}
		if (type != 5) {
			MapChoice = Safecin(MapLegalChoice, true);
		}
		else {
			MapChoice = Safecin(MapLegalChoice, false);
		}

		if (MapChoice != 0) {
			break;
		}
		else {
			PrintMyCharacterStatus();
		}
	}
	return MapChoice;
}
void MainProgress() {
	while (1) {
		//程序运行总循环，输了之后会回到这里
		int floor = 1;
		int	step = 0;
		int thisfloor = 0;
		bool Ifwin = true;
		int ModeChoice = 0;
		bool IfHard = false;
		ModeChoice = showTitle();
		if (ModeChoice == 1) {
			IfHard = false;
		}
		else if (ModeChoice == 2) {
			IfHard = true;
		}
		mycharacter.ReSetNum();
		RoundBuffGroup.clear();
		InitialRoundBuffGroup.clear();
		MyObjectGroup.clear();
		Object::ResetObjectGroup();
		int selectedBuff = enterbuff();
		switch (selectedBuff) {
		case 0:
			mycharacter.InitialAttackDevelopment(0.1);
			break;
		case 1:
			mycharacter.InitialMaxHPDevelopment(0.3);
			break;
		case 2:
			mycharacter.GainCoin(6);
			break;
		}
		while (1) {
			//一局游戏循环
			if (thisfloor != floor) {
				RuneManager::RandomChangeRune();
			}
			thisfloor = floor;
			int IfSave = 0;
			Ifwin = true;
			UpdateMap(floor, step);
			switch (Maptype[step]) {
			case 1://普通战斗
				IfSave = MapChoose(floor, step, 1);
				Ifwin = BattleStart(floor, false, IfHard);
				break;
			case 4://boss战斗
				IfSave = MapChoose(floor, step, 4);
				Ifwin = BattleStart(floor, true, IfHard);
				break;
			case 2://非战斗节点
				IfSave = MapChoose(floor, step, 2);
				Ifwin = EnterUnknownEvent(floor,IfHard);
				break;
			case 3://商店节点
				IfSave = MapChoose(floor, step, 3);
				PrintEventGround(3);
				break;
			case 5://双节点
				IfSave = MapChoose(floor, step, 5);
				if (IfSave == 1) {
					Ifwin = BattleStart(floor, false, IfHard);
				}
				else if (IfSave == 2) {
					Ifwin = EnterUnknownEvent(floor,IfHard);
				}
				break;
			}
			if (!Ifwin) {
				break;
			}
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
}