#pragma once

#include"basis.h"

using namespace std;

// 敌人数值管理类
class EnemyNumManager {
public:
    EnemyNumManager(int hp, int atk, int dfs);
    EnemyNumManager() = default;

    int getHP();
    int getAttack();
    int getDefense();

private:
    int HP = 0;
    int Attack = 0;
    int Defense = 0;
};

// 声明全局敌人数据指针和容器（使用 extern 避免多重定义）
extern shared_ptr<EnemyNumManager> Floor1A_S, Floor1D_S, Floor1H_S;
extern vector<shared_ptr<EnemyNumManager>> Floor1_S;
extern shared_ptr<EnemyNumManager> Boss1_S;
extern shared_ptr<EnemyNumManager> Floor1_Event_S;

extern shared_ptr<EnemyNumManager> Floor1A_H, Floor1D_H, Floor1H_H;
extern vector<shared_ptr<EnemyNumManager>> Floor1_H;
extern shared_ptr<EnemyNumManager> Boss1_H;
extern shared_ptr<EnemyNumManager> Floor1_Event_H;

extern shared_ptr<EnemyNumManager> Floor2A_S, Floor2D_S, Floor2H_S;
extern vector<shared_ptr<EnemyNumManager>> Floor2_S;
extern shared_ptr<EnemyNumManager> Boss2_S;
extern shared_ptr<EnemyNumManager> Floor2_Event_S;

extern shared_ptr<EnemyNumManager> Floor2A_H, Floor2D_H, Floor2H_H;
extern vector<shared_ptr<EnemyNumManager>> Floor2_H;
extern shared_ptr<EnemyNumManager> Boss2_H;
extern shared_ptr<EnemyNumManager> Floor2_Event_H;

extern shared_ptr<EnemyNumManager> Floor3A_S, Floor3D_S, Floor3H_S;
extern vector<shared_ptr<EnemyNumManager>> Floor3_S;
extern shared_ptr<EnemyNumManager> Boss3_S;
extern shared_ptr<EnemyNumManager> Floor3_Event_S;

extern shared_ptr<EnemyNumManager> Floor3A_H, Floor3D_H, Floor3H_H;
extern vector<shared_ptr<EnemyNumManager>> Floor3_H;
extern shared_ptr<EnemyNumManager> Boss3_H;
extern shared_ptr<EnemyNumManager> Floor3_Event_H;

// 当前战斗敌人及类型声明
extern shared_ptr<EnemyNumManager> EnemyNum_ThisBattle;
extern vector<string> EnemyType;

// 选择敌人函数声明
void ChooseEnemy(int floor, bool IsBoss, bool IfHard);