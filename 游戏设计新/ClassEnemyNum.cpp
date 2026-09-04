#include "ClassEnemyNum.h"


// EnemyNumManager 成员函数实现
EnemyNumManager::EnemyNumManager(int hp, int atk, int dfs) : HP(hp), Attack(atk), Defense(dfs) {}

int EnemyNumManager::getHP() {
    return HP;
}

int EnemyNumManager::getAttack() {
    return Attack;
}

int EnemyNumManager::getDefense() {
    return Defense;
}

// 定义并初始化第一层敌人数据
shared_ptr<EnemyNumManager> Floor1A_S = make_shared<EnemyNumManager>(200, 100, 20);
shared_ptr<EnemyNumManager> Floor1D_S = make_shared<EnemyNumManager>(200, 80, 50);
shared_ptr<EnemyNumManager> Floor1H_S = make_shared<EnemyNumManager>(300, 80, 20);
vector<shared_ptr<EnemyNumManager>> Floor1_S = { Floor1A_S, Floor1D_S, Floor1H_S };
shared_ptr<EnemyNumManager> Boss1_S = make_shared<EnemyNumManager>(600, 100, 40);
shared_ptr<EnemyNumManager> Floor1_Event_S = make_shared<EnemyNumManager>(250, 150, 20);

shared_ptr<EnemyNumManager> Floor1A_H = make_shared<EnemyNumManager>(500, 100, 20);
shared_ptr<EnemyNumManager> Floor1D_H = make_shared<EnemyNumManager>(500, 80, 50);
shared_ptr<EnemyNumManager> Floor1H_H = make_shared<EnemyNumManager>(600, 80, 20);
vector<shared_ptr<EnemyNumManager>> Floor1_H = { Floor1A_H, Floor1D_H, Floor1H_H };
shared_ptr<EnemyNumManager> Boss1_H = make_shared<EnemyNumManager>(1000, 100, 40);
shared_ptr<EnemyNumManager> Floor1_Event_H = make_shared<EnemyNumManager>(800, 150, 20);

// 定义并初始化第二层敌人数据
shared_ptr<EnemyNumManager> Floor2A_S = make_shared<EnemyNumManager>(500, 200, 50);
shared_ptr<EnemyNumManager> Floor2D_S = make_shared<EnemyNumManager>(500, 150, 100);
shared_ptr<EnemyNumManager> Floor2H_S = make_shared<EnemyNumManager>(700, 150, 50);
vector<shared_ptr<EnemyNumManager>> Floor2_S = { Floor2A_S, Floor2D_S, Floor2H_S };
shared_ptr<EnemyNumManager> Boss2_S = make_shared<EnemyNumManager>(2000, 250, 100);
shared_ptr<EnemyNumManager> Floor2_Event_S = make_shared<EnemyNumManager>(1500, 300, 50);

shared_ptr<EnemyNumManager> Floor2A_H = make_shared<EnemyNumManager>(1000, 250, 80);
shared_ptr<EnemyNumManager> Floor2D_H = make_shared<EnemyNumManager>(1000, 200, 120);
shared_ptr<EnemyNumManager> Floor2H_H = make_shared<EnemyNumManager>(1300, 200, 80);
vector<shared_ptr<EnemyNumManager>> Floor2_H = { Floor2A_H, Floor2D_H, Floor2H_H };
shared_ptr<EnemyNumManager> Boss2_H = make_shared<EnemyNumManager>(3000, 300, 150);
shared_ptr<EnemyNumManager> Floor2_Event_H = make_shared<EnemyNumManager>(2000, 400, 80);

// 定义并初始化第三层敌人数据
shared_ptr<EnemyNumManager> Floor3A_S = make_shared<EnemyNumManager>(1000, 400, 100);
shared_ptr<EnemyNumManager> Floor3D_S = make_shared<EnemyNumManager>(1000, 350, 200);
shared_ptr<EnemyNumManager> Floor3H_S = make_shared<EnemyNumManager>(1500, 350, 100);
vector<shared_ptr<EnemyNumManager>> Floor3_S = { Floor3A_S, Floor3D_S, Floor3H_S };
shared_ptr<EnemyNumManager> Boss3_S = make_shared<EnemyNumManager>(5000, 500, 300);
shared_ptr<EnemyNumManager> Floor3_Event_S = make_shared<EnemyNumManager>(3000, 600, 100);

shared_ptr<EnemyNumManager> Floor3A_H = make_shared<EnemyNumManager>(2000, 600, 150);
shared_ptr<EnemyNumManager> Floor3D_H = make_shared<EnemyNumManager>(2000, 450, 300);
shared_ptr<EnemyNumManager> Floor3H_H = make_shared<EnemyNumManager>(3000, 450, 150);
vector<shared_ptr<EnemyNumManager>> Floor3_H = { Floor3A_H, Floor3D_H, Floor3H_H };
shared_ptr<EnemyNumManager> Boss3_H = make_shared<EnemyNumManager>(8000, 800, 400);
shared_ptr<EnemyNumManager> Floor3_Event_H = make_shared<EnemyNumManager>(5000, 1000, 150);

// 定义当前战斗敌人和类型
shared_ptr<EnemyNumManager> EnemyNum_ThisBattle = nullptr;
vector<string> EnemyType = { "攻击力较高", "防御力较高", "生命值较高" };

// 选择敌人函数实现
void ChooseEnemy(int floor, bool IsBoss, bool IfHard) {
    int Choice = -1;
    switch (floor) {
    case 1:
        if (IsBoss) {
            EnemyNum_ThisBattle = IfHard ? Boss1_H : Boss1_S;
        }
        else {
            Choice = rm.getnum(0, 2);
            EnemyNum_ThisBattle = IfHard ? Floor1_H[Choice] : Floor1_S[Choice];
        }
        break;
    case 2:
        if (IsBoss) {
            EnemyNum_ThisBattle = IfHard ? Boss2_H : Boss2_S;
        }
        else {
            Choice = rm.getnum(0, 2);
            EnemyNum_ThisBattle = IfHard ? Floor2_H[Choice] : Floor2_S[Choice];
        }
        break;
    case 3:
        if (IsBoss) {
            EnemyNum_ThisBattle = IfHard ? Boss3_H : Boss3_S;
        }
        else {
            Choice = rm.getnum(0, 2);
            EnemyNum_ThisBattle = IfHard ? Floor3_H[Choice] : Floor3_S[Choice];
        }
        break;
    case 10:
        EnemyNum_ThisBattle = IfHard ? Floor1_Event_H : Floor1_Event_S;
        break;
    case 20:
        EnemyNum_ThisBattle = IfHard ? Floor2_Event_H : Floor2_Event_S;
        break;
    case 30:
        EnemyNum_ThisBattle = IfHard ? Floor3_Event_H : Floor3_Event_S;
        break;
    }

    cout << RED_BOLD;
    if (floor % 10 == 0) {
        cout << "请注意，该敌人攻击力极高，防御力较低，请选择合适的技能以应对。" << endl;
    }
    else if (!IsBoss) {
        cout << "该次战斗的敌人【" << EnemyType[Choice] << "】,请选择合适的技能以应对。" << endl;
    }
    else {
        cout << "以下是该次战斗的Boss的各项数值，请选择合适的技能以应对。" << endl;
    }
    cout << RED_DARK;
    cout << "敌人的各项基础数值为：" << endl;
    cout << "攻击力：" << EnemyNum_ThisBattle->getAttack() << endl;
    cout << "防御力：" << EnemyNum_ThisBattle->getDefense() << endl;
    cout << "生命上限：" << EnemyNum_ThisBattle->getHP() << endl;
    cout << endl;
}