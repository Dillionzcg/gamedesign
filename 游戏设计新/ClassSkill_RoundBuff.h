#pragma once
#include "basis.h"
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
	string Bufftype = "0";
	bool Ifover = false;
};


