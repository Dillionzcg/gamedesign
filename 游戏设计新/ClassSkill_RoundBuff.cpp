#include"ClassSkill_RoundBuff.h"
#include"ClassEnemyNum.h"
const vector<string> SkillManage::SkillList = {
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

SkillManage::SkillManage(int num) : ID(num) {}

string SkillManage::GetDescribe() {
    return SkillList[ID];
}

string SkillManage::GetName() {
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
    default: return "Unknown";
    }
}

string SkillManage::GetDescribethroughNum(int num) {
    if (num >= 0 && num < (int)SkillList.size()) {
        return SkillList[num];
    }
    return "Invalid Skill";
}

int SkillManage::GetID() {
    return ID;
}

RoundBuff::RoundBuff(string type, double Buffnum, int round) {
    LastingRounds = round;
    Bufftype = type;
    Development = Buffnum;
}

void RoundBuff::RoundPass() {
    if (LastingRounds > 0) {
        LastingRounds--;
    }
    if (LastingRounds == 0) {
        Ifover = true;
    }
}

bool RoundBuff::GetIfover() {
    return Ifover;
}

string RoundBuff::GetType() {
    return Bufftype;
}

double RoundBuff::GetDevelopment() {
    return Development;
}

// 定义并初始化全局技能管理器容器
vector<shared_ptr<SkillManage>> MySkillManager;

// 选择技能函数实现
shared_ptr<SkillManage> ChooseSkill(int ChoiceNum, int floor, bool IsBoss, bool IfHard) {
    Refresh();
    cout << WHITE;
    vector<int> Choice = rm.getSomeNum(0, 9, ChoiceNum);
    MySkillManager.clear();
    for (auto& item : Choice) {
        MySkillManager.push_back(make_shared<SkillManage>(item));
    }
    ChooseEnemy(floor, IsBoss, IfHard);
    cout << WHITE;
    cout << "请在下列技能中选择一个,技能在技能条满时可以释放：" << endl;
    cout << endl;

    int i = 0;
    for (auto& item : MySkillManager) {
        i++;
        if (item->GetID() < 3) {
            cout << RED_WINE;
        }
        else if (item->GetID() < 6) {
            cout << YELLOW;
        }
        else {
            cout << PURPLE;
        }
        cout << i << "." << item->GetDescribe() << endl;
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