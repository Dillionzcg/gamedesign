#pragma once
#include"StartBuff.h"
// 分隔线：红色加粗
void PrintRuneDivider(int length) {
    cout << GOLD_BOLD;
    cout << "       ";
    for (int i = 7; i < length; ++i) cout << "-";
    cout << RESET << endl;
}

// 卡片绘制：边框/星号/竖线红色加粗，全部文字米白
void DrawBuffCard(int index, const string& icon, const string& name,
    const string& desc, int indent) {
    const int W = 40;
    const string CORNER = "*", H_LINE = "*", V_LINE = "|";
    const string borderColor = DARK_GOLD;         // 边框星号红色加粗
    const string vColor = DARK_GOLD;              // 竖线红色加粗
    const string textColor = RED_BOLD;   
    const string descColor = GREEN_BRIGHT;
    string firstLine =  to_string(index) + "." + icon + name;
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
    PrintCentered("-- 你选择带入 --", QING);
    PrintRuneDivider(70);
    cout << endl;

    struct Opt { string icon, name, desc; };
    vector<Opt> opts = {
        {"", "【Messer】(一把小刀)", "基础攻击力 +10%"},
        {"", "【Trank】(一瓶药水)", "基础生命上限 +30%"},
        {"", "【Muenzbeutel】(一袋金币)", "金币 +6"}
    };

    int indent = (80 - 40) / 2;
    for (int i = 0; i < 3; ++i) {
        DrawBuffCard(i + 1, opts[i].icon, opts[i].name, opts[i].desc, indent);
        cout << endl;
    }
    PrintRuneDivider(70);
    PrintCentered("请输入编号选择 (1/2/3) : ", WHITE);
    cout << endl;

    cout << CREAM_WHITE << "> " << RESET;

    vector<int> legal = { 1, 2, 3 };
    int choice = Safecin(legal, false);

    cout << RED_BOLD;
    cout << endl;
    switch (choice) {
    case 1:
        cout << " Das scharfe Metall schneidet durch den dichten Nebel der Runen,\n und die alten Waende beginnen zu bluten." << endl;
        cout<<RED_DARK << " \n(锋利的金属切割着符文浓密的迷雾，古老的墙壁开始渗出鲜血。)" << endl;
        //锋利的金属切割着符文浓密的迷雾，古老的墙壁开始渗出鲜血。
        break;
    case 2:
        cout << " Der suesse Geruch des Lebens laesst die vertrockneten Ranken \n im Steinboden leise erzittern und wachsen." << endl;
        cout << RED_DARK << " \n(生命甜美的香气让石缝中枯萎的藤蔓开始无声地战栗与生长。)" << endl;
        //生命甜美的香气让石缝中枯萎的藤蔓开始无声地战栗与生长。
        break;
    case 3:
        cout << " Das helle Klimpern von Muenzen weckt den schlafenden Schutt der Ruinen;\n der Boden gierig gedenkt der naechsten Opfer." << endl;
        cout << RED_DARK << " \n(清脆的金币碰撞声唤醒了废墟沉睡的残骸，地面正贪婪地注视着下一个祭品。)" << endl;
        //清脆的金币碰撞声唤醒了废墟沉睡的残骸，地面正贪婪地注视着下一个祭品。
        break;
    }
    cout << endl;
    cout << HUI << "按回车继续..." << endl;
    SafeEnter();
    return choice - 1;
}
int enterbuff() {
    int buff = ChooseInitialBuff();
    cout << RESET;
    return buff;
}
