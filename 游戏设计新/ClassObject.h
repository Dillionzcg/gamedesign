#pragma once
#include "basis.h"
//藏品类
class Object {
public:
	Object(int rarity, string camp, string type, string describe, int buffnum) :Rarity(rarity), Camp(camp), Type(type), Describe(describe), BuffNum(buffnum) {
		NeedingCoin = RarityCoin[Rarity - 1];
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
