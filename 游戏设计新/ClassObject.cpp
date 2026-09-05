#include "ClassObject.h"

// Object 类成员函数实现
Object::Object(int rarity, string camp, string type, string describe, double buffnum)
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
void Object::ResetGaining() {
    IfGotten = false;
}
void Object::ResetObjectGroup() {
    for (auto& item : ObjectPool1) {
        item->ResetGaining();
    }
    for (auto& item : ObjectPool2) {
        item->ResetGaining();
    }
    for (auto& item : ObjectPool3) {
        item->ResetGaining();
    }
}
string Object::GetCamp() {
    return Camp;
}
string Object::GetType() {
    return Type;
}
// 定义并初始化全局藏品池与玩家藏品组
vector<shared_ptr<Object>> ObjectPool1 = { // 初级藏品
    make_shared<Object>(1, "M", "A", "Kraft：攻击力+30%", 0.3),
    make_shared<Object>(1, "M", "D", "Schutz：防御力+40%", 0.4),
    make_shared<Object>(1, "M", "H", "Leben：生命上限+50%", 0.5),
    make_shared<Object>(1, "M", "HE", "Labung：每点治疗能量治疗量+10", 5),
    make_shared<Object>(1, "E", "A", "Schwaechung：敌人攻击力-10%", -0.1),
    make_shared<Object>(1, "E", "D", "Bruch：敌人防御力-10%", -0.1),
    make_shared<Object>(1, "E", "H", "Verfall：敌人生命上限-10%", -0.1),
    make_shared<Object>(1, "E", "CR", "Block：敌人暴击率-3%", -3),
};

vector<shared_ptr<Object>> ObjectPool2 = { // 中级藏品
    make_shared<Object>(2, "M", "A", "Macht：攻击力+50%", 0.5),
    make_shared<Object>(2, "M", "D", "Schild：防御力+60%", 0.6),
    make_shared<Object>(2, "M", "H", "Vitalitaet：生命上限+70%", 0.7),
    make_shared<Object>(2, "M", "HE", "Wohl：每点治疗能量治疗量+20", 20),
    make_shared<Object>(2, "E", "A", "Laehmung：敌人攻击力-20%", -0.2),
    make_shared<Object>(2, "E", "D", "Riss：敌人防御力-20%", -0.2),
    make_shared<Object>(2, "E", "H", "Schwund：敌人生命上限-20%", -0.20),
    make_shared<Object>(2, "E", "CR", "Hemmung：敌人暴击率-6%", -6),
    make_shared<Object>(2, "M", "IE", "Antritt：我方初始能量+1", 1),
    make_shared<Object>(2, "M", "IHE", "Auftakt：我方初始治疗能量+2", 2),
    make_shared<Object>(2, "M", "MHE", "Gefaess：我方治疗能量上限+2", 2),
    make_shared<Object>(2, "M", "SC", "Auswahl：可选择技能+1", 1),
    make_shared<Object>(2, "E", "CH", "Daempfung：敌人暴击伤害-10%", -0.1),
};

vector<shared_ptr<Object>> ObjectPool3 = { // 高级藏品
    make_shared<Object>(3, "M", "A", "Staerke：攻击力+70%", 0.7),
    make_shared<Object>(3, "M", "D", "Ruestung：防御力+80%", 0.8),
    make_shared<Object>(3, "M", "H", "Gedeihen：生命上限+90%", 0.9),
    make_shared<Object>(3, "M", "HE", "Wunder：每点治疗能量治疗量+30", 30),
    make_shared<Object>(3, "E", "A", "Ermattung：敌人攻击力-30%", -0.3),
    make_shared<Object>(3, "E", "D", "Zerfall：敌人防御力-30%", -0.3),
    make_shared<Object>(3, "E", "H", "Siechtum：敌人生命上限-30%", -0.3),
    make_shared<Object>(3, "E", "CR", "Stoerung：敌人暴击率-10%", -10),
    make_shared<Object>(3, "M", "IE", "Antrieb：我方初始能量+2", 2),
    make_shared<Object>(3, "M", "IHE", "Ursprung：我方初始治疗能量+3", 3),
    make_shared<Object>(3, "M", "EN", "Effizienz：我方技能所需能量-1", -1),
    make_shared<Object>(3, "E", "EN", "Last：敌方技能所需能量+2", 2),
    make_shared<Object>(3, "M", "SC", "Vielfalt：可选择技能+2", 2),
    make_shared<Object>(3, "E", "CH", "Stumpfung：敌人暴击伤害-20%", -0.2),
};

vector<shared_ptr<Object>> MyObjectGroup; // 我方藏品组初始化为空

vector<shared_ptr<Object>> TotalObjectGroup_ForSaving = {
    make_shared<Object>(1, "M", "A", "Kraft：攻击力+30%", 0.3),
    make_shared<Object>(1, "M", "D", "Schutz：防御力+40%", 0.4),
    make_shared<Object>(1, "M", "H", "Leben：生命上限+50%", 0.5),
    make_shared<Object>(1, "M", "HE", "Labung：每点治疗能量治疗量+10", 5),
    make_shared<Object>(1, "E", "A", "Schwaechung：敌人攻击力-10%", -0.1),
    make_shared<Object>(1, "E", "D", "Bruch：敌人防御力-10%", -0.1),
    make_shared<Object>(1, "E", "H", "Verfall：敌人生命上限-10%", -0.1),
    make_shared<Object>(1, "E", "CR", "Block：敌人暴击率-3%", -3),

    make_shared<Object>(2, "M", "A", "Macht：攻击力+50%", 0.5),
    make_shared<Object>(2, "M", "D", "Schild：防御力+60%", 0.6),
    make_shared<Object>(2, "M", "H", "Vitalitaet：生命上限+70%", 0.7),
    make_shared<Object>(2, "M", "HE", "Wohl：每点治疗能量治疗量+20", 20),
    make_shared<Object>(2, "E", "A", "Laehmung：敌人攻击力-20%", -0.2),
    make_shared<Object>(2, "E", "D", "Riss：敌人防御力-20%", -0.2),
    make_shared<Object>(2, "E", "H", "Schwund：敌人生命上限-20%", -0.20),
    make_shared<Object>(2, "E", "CR", "Hemmung：敌人暴击率-6%", -6),
    make_shared<Object>(2, "M", "IE", "Antritt：我方初始能量+1", 1),
    make_shared<Object>(2, "M", "IHE", "Auftakt：我方初始治疗能量+2", 2),
    make_shared<Object>(2, "M", "MHE", "Gefaess：我方治疗能量上限+2", 2),
    make_shared<Object>(2, "M", "SC", "Auswahl：可选择技能+1", 1),
    make_shared<Object>(2, "E", "CH", "Daempfung：敌人暴击伤害-10%", -0.1),

    make_shared<Object>(3, "M", "A", "Staerke：攻击力+70%", 0.7),
    make_shared<Object>(3, "M", "D", "Ruestung：防御力+80%", 0.8),
    make_shared<Object>(3, "M", "H", "Gedeihen：生命上限+90%", 0.9),
    make_shared<Object>(3, "M", "HE", "Wunder：每点治疗能量治疗量+30", 30),
    make_shared<Object>(3, "E", "A", "Ermattung：敌人攻击力-30%", -0.3),
    make_shared<Object>(3, "E", "D", "Zerfall：敌人防御力-30%", -0.3),
    make_shared<Object>(3, "E", "H", "Siechtum：敌人生命上限-30%", -0.3),
    make_shared<Object>(3, "E", "CR", "Stoerung：敌人暴击率-10%", -10),
    make_shared<Object>(3, "M", "IE", "Antrieb：我方初始能量+2", 2),
    make_shared<Object>(3, "M", "IHE", "Ursprung：我方初始治疗能量+3", 3),
    make_shared<Object>(3, "M", "EN", "Effizienz：我方技能所需能量-1", -1),
    make_shared<Object>(3, "E", "EN", "Last：敌方技能所需能量+2", 2),
    make_shared<Object>(3, "M", "SC", "Vielfalt：可选择技能+2", 2),
    make_shared<Object>(3, "E", "CH", "Stumpfung：敌人暴击伤害-20%", -0.2),

    make_shared<Object>(0, "M", "A", "Special:死仇", 0.3),
    make_shared<Object>(0, "E", "A", "Special:死仇", 0.3),
    make_shared<Object>(0, "M", "A", "Special:瘟疫", -0.2),
    make_shared<Object>(0, "E", "A", "Special:瘟疫", -0.2),
    make_shared<Object>(0, "M", "D", "Special:崩溃", -0.3),
    make_shared<Object>(0, "E", "D", "Special:崩溃", -0.3),
    make_shared<Object>(0, "M", "IE", "Special:狂热", 2),
    make_shared<Object>(0, "E", "IE", "Special:狂热", 2),
    make_shared<Object>(0, "M", "SC", "Special:迷雾", 2),
    make_shared<Object>(0, "E", "A", "Special:贪婪", 0.2),
    make_shared<Object>(0, "M", "D", "Special:救赎", -0.3),
    make_shared<Object>(0, "M", "A", "Special:希望", 0.3),
    make_shared<Object>(0, "M", "A", "Special:绝望", -0.2),
    make_shared<Object>(0, "E", "A", "Special:绝望", 0.2),

    make_shared<Object>(0, "M", "H", "Special,MyHPDecrease1", -0.03),
    make_shared<Object>(0, "M", "H", "Special,MyHPDecrease2", -0.05),
    make_shared<Object>(0, "M", "H", "Special,MyHPDecrease3", -0.1),
};
/*藏品名字释义：（均为德语）

初级藏品 (ObjectPool1)

Kraft —— 力量（攻击力 +10%）

Schutz —— 防护（防御力 +20%）

Leben —— 生命（生命上限 +30%）

Labung —— 滋养（每点治疗能量治疗量 +5）

Schwaechung —— 削弱（敌人攻击力 -10%）

Bruch —— 破裂（敌人防御力 -10%）

Verfall —— 衰败（敌人生命上限 -10%）

Block —— 阻挡（敌人暴击率 -5%）



中级藏品 (ObjectPool2)

Macht —— 权能（攻击力 +20%）

Schild —— 盾牌（防御力 +30%）

Vitalitaet —— 活力（生命上限 +40%）

Wohl —— 安康（每点治疗能量治疗量 +10）

Laehmung —— 麻痹（敌人攻击力 -15%）

Riss —— 裂隙（敌人防御力 -15%）

Schwund —— 消减（敌人生命上限 -15%）

Hemmung —— 抑制（敌人暴击率 -10%）

Antritt —— 启动（我方初始能量 +1）

Auftakt —— 序曲（我方初始治疗能量 +1）

Gefaess —— 器皿（我方治疗能量上限 +2）

Auswahl —— 选择（可选择技能 +1）

Daempfung —— 阻尼（敌人暴击伤害 -10%）



高级藏品 (ObjectPool3)

Staerke —— 强力（攻击力 +30%）

Ruestung —— 铠甲（防御力 +40%）

Gedeihen —— 繁荣（生命上限 +50%）

Wunder —— 奇迹（每点治疗能量治疗量 +15）

Ermattung —— 疲惫（敌人攻击力 -20%）

Zerfall —— 解体（敌人防御力 -20%）

Siechtum —— 萎靡（敌人生命上限 -20%）

Stoerung —— 干扰（敌人暴击率 -15%）

Antrieb —— 驱动（我方初始能量 +2）

Ursprung —— 根源（我方初始治疗能量 +2）

Effizienz —— 效能（我方技能所需能量 -1）

Last —— 负担（敌方技能所需能量 +2）

Vielfalt —— 多样性（可选择技能 +2）

Stumpfung  —— 钝化（敌人暴击伤害 -20%）

*/