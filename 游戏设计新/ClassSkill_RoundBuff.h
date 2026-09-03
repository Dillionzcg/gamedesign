#pragma once

#include "basis.h"


using namespace std;

// 技能管理类
class SkillManage {
public:
    SkillManage(int num);

    string GetDescribe();
    string GetName();
    string GetDescribethroughNum(int num);
    int GetID();

private:
    int ID;
    // 静态声明，避免每个对象都复制一份庞大的字符串列表
    static const vector<string> SkillList;
};

// 局内 Buff 管理类
class RoundBuff {
public:
    RoundBuff() = default;
    ~RoundBuff() = default;
    RoundBuff(string type, double Buffnum, int round);

    void RoundPass();
    bool GetIfover();
    string GetType();
    double GetDevelopment();

private:
    double Development = 0;
    int LastingRounds = 0;
    string Bufftype = "0";
    bool Ifover = false;
};

// 声明全局技能管理器容器（使用 extern 避免多重定义）
extern vector<shared_ptr<SkillManage>> MySkillManager;

// 声明选择技能函数
shared_ptr<SkillManage> ChooseSkill(int ChoiceNum, int floor, bool IsBoss, bool IfHard);
extern vector<shared_ptr<RoundBuff>> InitialRoundBuffGroup;//创建时使用的数组
extern vector<shared_ptr<RoundBuff>> RoundBuffGroup;//筛选后实际使用的数组