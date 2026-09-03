#pragma once
#include "basis.h"

using namespace std;

// 藏品类
class Object {
public:
    Object(int rarity, string camp, string type, string describe, int buffnum);
    static void ResetObjectGroup();
    int GetRarity();
    int GetNeedingCoin();
    string GetDescribe();
    double GetBuffNum();
    bool GetIfGotten();
    void GainObject();
    void ResetGaining();
    
private:
    int Rarity;                 // 稀有度,1/2/3
    vector<int> RarityCoin = { 2, 4, 6 }; // 稀有度对应金币数
    int NeedingCoin;            // 购买所需金币数
    string Describe;            // 藏品描述
    string Camp;                // 阵营，"M"为我方，"E"为敌方
    string Type;                // 类型
    bool IfGotten = false;      // 是否已获得
    double BuffNum;             // 加成数值
};

// 声明全局变量（供其他文件使用）
extern vector<shared_ptr<Object>> ObjectPool1; // 初级藏品池
extern vector<shared_ptr<Object>> ObjectPool2; // 中级藏品池
extern vector<shared_ptr<Object>> ObjectPool3; // 高级藏品池
extern vector<shared_ptr<Object>> MyObjectGroup; // 我方藏品组