#pragma once
#include "basis.h"

using namespace std;

class RuneManager {
public:
    RuneManager(int num);
    RuneManager() = default;

    string GetDescribe();
    string GetDescribethroughNum(int num);
    string GetName();

    static void RandomChangeRune();
    static void ChangetoHope();
    static void ChangetoDesperation();

private:
    int ID = 0;
    string name = "0";

    // 符文文本
    vector<string> RuneList = {
        // 通常(0~9)
        "//【Feindschaft】死仇：我方和敌方的攻击力+30%//",
             "//【Seuche】瘟疫：我方和敌方的攻击力-30%//",
            "//【Kollaps】崩溃：我方和敌方的防御力-50%//",
            "//【Ekstase】狂热：我方和敌方技能条初始能量+2//",
       "//【Schwarzmarkt】暗市：该层的商店不再展示商品详细信息，但该层商店的售价-50%//",
              "//【Nebel】迷雾：该层不再提前展示敌人信息，但可选择的技能+2//",
             "//【Bluete】繁荣：该层的商店售价+50%，但战斗后掉落藏品+1//",
               "//【Oede】荒芜：该层的商店售价-50%，但战斗后不再掉落藏品//",
               "//【Gier】贪婪：敌方攻击力+20%，但每次移动后金币+2//",
          "//【Erloesung】救赎：在该层非boss关战斗死亡时可复活（仅限一次）,但该层战斗时防御力-30%//",
        // 特殊(10~11)
           "//【Hoffnung】希望：在该层每次移动后金币+2，攻击力+30%//",
       "//【Verzweiflung】绝望：所有敌人攻击力+20%，我方攻击力-20%//"
    };

    vector<string> RuneName = {
        "死仇", "瘟疫", "崩溃", "狂热", "暗市", "迷雾",
        "繁荣", "荒芜", "贪婪", "救赎", "希望", "绝望"
    };
};

// 声明全局变量（供其他文件使用）
extern shared_ptr<RuneManager> RuneNow;