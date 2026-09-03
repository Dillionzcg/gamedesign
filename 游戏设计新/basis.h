#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<random>
#include<memory>
#include<string>
#include<numeric>
#include<algorithm>
#include<stdexcept>
#include<thread>   
#include<chrono>
#include<limits>

using namespace std;

inline const string RESET = "\033[0m";
inline const string BOLD = "\033[1m";
inline const string ITALIC = "\033[3m";
inline const string BG_BLACK = "\033[40m";
inline const string WHITE = "\033[38;5;255m";
inline const string CREAM_WHITE = "\033[38;5;230m";
inline const string CREAM_WHITE_BOLD = "\033[1;38;5;230m";
inline const string CREAM_WHITE_ITALIC = "\033[3;38;5;230m";//高白
inline const string RED_BOLD = "\033[38;5;196m";    // 亮红加粗
inline const string RED_DARK = "\033[38;5;131m"; // 暗红
inline const string RED_WINE = "\033[38;5;161m";//酒红
inline const string GOLD_BOLD = "\033[38;5;220m";  // 金色加粗
inline const string DARK_GOLD = "\033[38;5;136m";//暗金
inline const string PURPLE = "\033[38;5;141m";//紫色
inline const string PURPLE_DARK = "\033[38;5;95m";//暗紫色
inline const string YELLOW = "\033[38;5;226m";//亮黄色
inline const string QING = "\033[38;5;37m";//青色
inline const string QING_GRAY = "\033[38;5;66m";//灰青色
inline const string GREEN_BRIGHT = "\033[38;5;46m";
inline const string GREEN_DEEP = "\033[38;5;82m";
inline const string HUI = "\033[38;5;245m";
inline const string BLUE = "\033[38;5;39m";
inline const string BLUE_DARK = "\033[38;5;25m";
inline const string RED_LIGHT = "\033[38;5;132m";
inline const string ROW_ALT_1 = "\033[38;5;250m";          // 柔和亮灰（奇数行基础色）
inline const string ROW_ALT_2 = "\033[38;5;240m";          // 稍暗的灰青（偶数行基础色）
inline const string ACCENT_ORANGE = "\033[38;5;208m";      // 琥珀橙（用于点缀特定数值）
inline const string ACCENT_CYAN = "\033[38;5;73m";         // 浅青蓝（用于交替数值）
inline const string STAT_HP = "\033[38;5;203m";      // 亮珊瑚红 (生命上限)
inline const string STAT_ATK = "\033[38;5;214m";     // 炽热橙金 (攻击力)
inline const string STAT_DEF = "\033[38;5;75m";      // 冰晶天蓝 (防御力)
inline const string STAT_ENERGY = "\033[38;5;111m";  // 电光蓝紫 (能量上限 - 更通透)
inline const string STAT_HEAL_MAX = "\033[38;5;46m";  // 经典亮绿 (治疗能量上限)
inline const string STAT_HEAL_VAL = "\033[38;5;211m";// 柔和桃粉 (每点治疗恢复 - 告别双绿)
inline const string STAT_LEVEL = "\033[38;5;183m";   // 淡紫罗兰 (等级)
inline const string STAT_COIN = "\033[38;5;220m";    // 纯正金币黄 (金币)

inline void Refresh() {
    cout << "\033[2J\033[H" << flush;
}

//  随机数生成器类
class RandomManager {
private:
    mt19937 rd;
public:
    RandomManager() : rd(random_device{}()) {}
    RandomManager(const RandomManager&) = delete;
    RandomManager& operator=(const RandomManager&) = delete;
    int getnum(int min, int max) {
        uniform_int_distribution<int> dist(min, max);
        return dist(rd);
    }
    vector<int> getSomeNum(int min, int max, int k) {
        int total = max - min + 1;
        vector<int> pool(total);
        iota(pool.begin(), pool.end(), min);
        shuffle(pool.begin(), pool.end(), rd);
        return vector<int>(pool.begin(), pool.begin() + k);
    }
};


extern vector<string> forcheck;
extern RandomManager rm;


inline void SafeEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

inline void WaitForSeconds(double Time) {
    int second = (int)(Time * 1000);
    this_thread::sleep_for(chrono::milliseconds(second));
}

inline int Safecin(const vector<int>& legal, bool ifblank) {
    string chose;
    forcheck.clear();
    for (auto v : legal) forcheck.push_back(to_string(v));
    while (true) {
        getline(cin, chose);
        if (ifblank && chose.empty()) return -1;
        for (auto& item : forcheck) {
            if (item == chose) return stoi(chose);
        }
        cout << "请在";
        for (auto& item : forcheck) cout << item << ",";
        cout << "中选择一个数字:";
        if (ifblank) cout << "(或者回车以继续)";
        cout << flush;
    }
}

inline void SupplementDigitNumber(string& num, int digit) {
    while (num.length() < digit) {
        num = " " + num;
    }
}
/*给小组成员：
*使用Refresh()以全屏刷新
*使用rm.getnum(min,max)以获得一定范围（闭区间）的随机int
*使用rm.getSomeNum(min,max,k)以获得一定范围（闭区间）的k个不重复随机int，返回vector<int>
*使用a=Safecin(legal,ifblank)以获得合法输入，
 legal为合法数字向量(vector<int>)，ifblank为是否允许空输入(bool值)
*使用WaitForSeconds(second)以等待特定秒数(double)
*/