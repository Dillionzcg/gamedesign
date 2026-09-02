#include "ClassObject.h"

// Object 类成员函数实现
Object::Object(int rarity, string camp, string type, string describe, int buffnum)
    : Rarity(rarity), Camp(camp), Type(type), Describe(describe), BuffNum(buffnum) {
    NeedingCoin = RarityCoin[Rarity - 1];
}

int Object::GetRarity() {
    return Rarity;
}

int Object::GetNeedingCoin() {
    return NeedingCoin;
}

string Object::GetDescribe() {
    return Describe;
}

double Object::GetBuffNum() {
    return BuffNum;
}

bool Object::GetIfGotten() {
    return IfGotten;
}

void Object::GainObject() {
    IfGotten = true;
}

// 定义并初始化全局藏品池与玩家藏品组
vector<shared_ptr<Object>> ObjectPool1 = { // 初级藏品
    make_shared<Object>(1, "M", "A", "攻击力+10%", 0.1),
    make_shared<Object>(1, "M", "D", "防御力+20%", 0.2),
    make_shared<Object>(1, "M", "H", "生命上限+30%", 0.3),
    make_shared<Object>(1, "M", "HE", "每点治疗能量治疗量+5", 5),
    make_shared<Object>(1, "E", "A", "敌人攻击力-10%", -0.1),
    make_shared<Object>(1, "E", "D", "敌人防御力-10%", -0.1),
    make_shared<Object>(1, "E", "H", "敌人生命上限-10%", -0.1),
    make_shared<Object>(1, "E", "CR", "敌人暴击率-5%", -5),
};

vector<shared_ptr<Object>> ObjectPool2 = { // 中级藏品
    make_shared<Object>(2, "M", "A", "攻击力+20%", 0.2),
    make_shared<Object>(2, "M", "D", "防御力+30%", 0.3),
    make_shared<Object>(2, "M", "H", "生命上限+40%", 0.4),
    make_shared<Object>(2, "M", "HE", "每点治疗能量治疗量+10", 10),
    make_shared<Object>(2, "E", "A", "敌人攻击力-15%", -0.15),
    make_shared<Object>(2, "E", "D", "敌人防御力-15%", -0.15),
    make_shared<Object>(2, "E", "H", "敌人生命上限-15%", -0.15),
    make_shared<Object>(2, "E", "CR", "敌人暴击率-10%", -10),

    make_shared<Object>(2, "M", "IE", "我方初始能量+1", 1),
    make_shared<Object>(2, "M", "IHE", "我方初始治疗能量+1", 1),
    make_shared<Object>(2, "M", "MHE", "我方治疗能量上限+2", 2),
    make_shared<Object>(2, "M", "SC", "可选择技能+1", 1),
};

vector<shared_ptr<Object>> ObjectPool3 = { // 高级藏品
    make_shared<Object>(3, "M", "A", "攻击力+30%", 0.3),
    make_shared<Object>(3, "M", "D", "防御力+40%", 0.4),
    make_shared<Object>(3, "M", "H", "生命上限+50%", 0.5),
    make_shared<Object>(3, "M", "HE", "每点治疗能量治疗量+15", 15),
    make_shared<Object>(3, "E", "A", "敌人攻击力-20%", -0.2),
    make_shared<Object>(3, "E", "D", "敌人防御力-20%", -0.2),
    make_shared<Object>(3, "E", "H", "敌人生命上限-20%", -0.2),
    make_shared<Object>(3, "E", "CR", "敌人暴击率-15%", -15),

    make_shared<Object>(3, "M", "IE", "我方初始能量+2", 2),
    make_shared<Object>(3, "M", "IHE", "我方初始治疗能量+2", 2),
    make_shared<Object>(3, "M", "EN", "我方技能所需能量-1", -1),
    make_shared<Object>(3, "E", "EN", "敌方技能所需能量+2", 2),
    make_shared<Object>(2, "M", "SC", "可选择技能+2", 2), // 注：这里原代码稀有度写的是2，保留原样
};

vector<shared_ptr<Object>> MyObjectGroup; // 我方藏品组初始化为空