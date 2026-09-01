#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
//颜色配置
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string ITALIC = "\033[3m";
const string BG_BLACK = "\033[40m";
const string WHITE = "\033[38;5;255m";
const string CREAM_WHITE = "\033[38;5;230m";
const string CREAM_WHITE_BOLD = "\033[1;38;5;230m";
const string CREAM_WHITE_ITALIC = "\033[3;38;5;230m";
const string RED_BOLD = "\033[1;31m";   // 亮红加粗
const string RED_DARK = "\033[1;31m"; // 暗红
const string GOLD_BOLD = "\033[38;5;220m";  // 金色加粗
const string DARK_GOLD = "\033[38;5;136m";
const string PURPLE = "\033[38;5;141m";
const string YELLOW = "\033[38;5;226m";
const string QING = "\033[38;5;37m";

void Refresh() {
    cout << "\033[2J\033[H" << flush;
}

vector<string> forcheck;

int Safecin(const vector<int>& legal, bool ifblank) {
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

// 分隔线：红色加粗
void PrintRuneDivider(int length = 60) {
    cout << GOLD_BOLD;
    cout << "       ";
    for (int i = 7; i < length; ++i) cout << "-";
    cout << RESET << endl;
}

// 卡片绘制：边框/星号/竖线红色加粗，全部文字米白
void DrawBuffCard(int index, const string& icon, const string& name,
    const string& desc, int indent = 0) {
    const int W = 40;
    const string CORNER = "*", H_LINE = "*", V_LINE = "|";
    const string borderColor = RED_BOLD;         // 边框星号红色加粗
    const string vColor = RED_BOLD;              // 竖线红色加粗
    const string textColor = CREAM_WHITE_BOLD;   // 名称加粗米白
    const string descColor = CREAM_WHITE_ITALIC; // 描述斜体米白
    string firstLine = "[" + to_string(index) + "] " + icon + name;
    int padLen = (W - 2) - (int)firstLine.length();
    if (padLen < 0) padLen = 0;
    firstLine += string(padLen - 1, ' ');
    auto printWithIndent = [&](const string& line) {
        cout << string(indent, ' ') << line;
        };
    // 上边框
    printWithIndent(borderColor + CORNER + string(W - 2, '*') + CORNER + RESET);
    cout << endl;
    // 第一行
    printWithIndent(vColor + V_LINE + RESET + " " + textColor + firstLine + vColor + V_LINE + RESET);
    cout << endl;
    // 第二行（描述）
    string descLine = descColor + desc;
    int descPad = (W - 2) - (int)desc.length() - 1;
    if (descPad < 0) descPad = 0;
    descLine += string(descPad, ' ');
    printWithIndent(vColor + V_LINE + RESET + " " + descLine + vColor + V_LINE + " " + RESET);
    cout << endl;
    // 空行
    printWithIndent(vColor + V_LINE + string(W - 2, ' ') + V_LINE + " " + RESET);
    cout << endl;
    // 下边框
    printWithIndent(borderColor + CORNER + string(W - 2, '*') + CORNER + RESET);
    cout << endl;
}

void PrintCentered(const string& text, const string& color) {
    int width = 80;
    int pad = (width - (int)text.length()) / 2;
    if (pad < 0) pad = 0;
    cout << string(pad, ' ') << color << text << RESET << endl;
}

int ChooseInitialBuff() {
    Refresh();
    cout << BG_BLACK;

    PrintCentered("    符文秘境 · 初始抉择    ", YELLOW);
    PrintCentered("-- 在远古遗迹中唤醒你的力量 --", PURPLE);
    PrintRuneDivider(70);
    cout << endl;

    struct Opt { string icon, name, desc; };
    vector<Opt> opts = {
        {"", "好战", "攻击力 +30%"},
        {"", "惜生", "生命上限 +50%"},
        {"", "贪财", "金币 +50"}
    };

    int indent = (80 - 40) / 2;
    for (int i = 0; i < 3; ++i) {
        DrawBuffCard(i + 1, opts[i].icon, opts[i].name, opts[i].desc, indent);
        cout << endl;
    }
    PrintRuneDivider(70);
    PrintCentered("请输入编号选择你的初始之力 (1/2/3) : ", WHITE);
    cout << endl;

    cout << CREAM_WHITE << "> " << RESET;

    vector<int> legal = { 1, 2, 3 };
    int choice = Safecin(legal, false);
    if (choice == -1) choice = 1;

    cout << RESET;
    return choice - 1;
}
void enterbuff() {
    int buff = ChooseInitialBuff();
    cout << RESET;
    cout << "\n" << CREAM_WHITE_BOLD << "你选择了：";
    switch (buff) {
    case 0: cout << "好战（攻击力 +30%）" << RESET << endl; break;
    case 1: cout << "惜生（生命上限 +50%）" << RESET << endl; break;
    case 2: cout << "贪财（金币 +50）" << RESET << endl; break;
    }
    cout << "\n" << RED_BOLD << "按回车键退出..." << RESET;
    cin.get();
}
