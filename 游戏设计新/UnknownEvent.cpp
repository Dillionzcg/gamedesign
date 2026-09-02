
#pragma once
#include"UnknownEvent.h"

using namespace std;

// 在文件内添加一个小工具函数用于居中打印标题
// 辅助函数：计算 UTF-8 字符串在终端中的实际显示宽度
static inline int GetDisplayWidth(const string& str) {
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        if (c < 0x80) {
            width += 1;
            i += 1;
        }
        else if (c < 0xE0) {
            width += 1;
            i += 2;
        }
        else if (c < 0xF0) {
            // 检查是否为制表符 '═' (\xE2\x95\x90)，它在终端中通常宽度为 1
            if (i + 2 < str.length() && (unsigned char)str[i] == 0xE2 && (unsigned char)str[i + 1] == 0x95 && (unsigned char)str[i + 2] == 0x90) {
                width += 1;
            }
            else {
                // 其他 3 字节字符（如汉字、【】等全角符号）通常宽度为 2
                width += 2;
            }
            i += 3;
        }
        else {
            width += 2;
            i += 4;
        }
    }
    return width;
}

static inline void PrintCenteredHeader(const string& title) {
    const string sep = "════════════════════════════════════════════════════";
    string display = "【" + title + "】";

    int sepLen = GetDisplayWidth(sep);
    int dispLen = GetDisplayWidth(display);

    int left = 0;
    if (sepLen > dispLen) {
        left = (sepLen - dispLen) / 2;

        // 【微调区】如果当前肉眼看依然觉得偏右，可以尝试将左侧空格数减 1
        // 你可以根据实际效果决定是否启用这一行：
        if (left > 0) left -= 5;
    }

    cout << sep << endl;
    for (int i = 0; i < left; ++i) cout << ' ';
    cout << display << endl;
    cout << sep << endl;
}
//模拟对战（默认胜利，需要补充）
bool EventBattleStart(bool isBoss) {
    cout << "\n 战斗开始！ (模拟战斗)" << endl;
    // 简单模拟：玩家获胜
    cout << "你经过一番苦战，击败了强敌！" << endl;
    if (isBoss) {
        // 额外战胜文案（Boss）
        cout << "\n腐朽战甲在最后一击中轰然散落，化作一地锈蚀的铁片与灰烬。" << endl;
        cout << "石棺内部传来一声极轻的、几乎像是叹息的回响：" << endl;
        cout << "\n“你……过关了。”" << endl;
        cout << "“带走你应得的。我不再需要它们了。”" << endl;
        cout << "\n灰烬中浮现出微光" << endl;
        cout << "\n 获得Boss级奖励：大量经验 + 高级藏品" << endl;
    }
    else {
        cout << " 获得普通奖励：经验 + 藏品" << endl;
    }
    cout << "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}


// ---------- 事件1：高难度敌人 ----------
bool Event_BossChallenge(int floor) {
    Refresh();
    PrintCenteredHeader("试炼之影 · 挑战");
    cout << "\n" << endl;
    cout << "断壁残垣间横亘着一口倒悬的石棺，棺盖上剥落的咒文正向外渗出猩红的微光。" << endl;
    cout << "当你靠近时，古老的机括声撕裂了死寂，战甲在风中发出濒死的哀鸣。" << endl;
    cout << "无形的气流在残破的石雕间盘旋剥离，每一寸空气都弥漫着被放逐千百年的古老死寂。" << endl;
    cout << "那是被虚空裂隙遗忘的禁忌之地，地面上纵横交错的裂纹仿佛在无声地向外诉说着某种不为人知的灾厄。" << endl;
    cout << "石棺的表面覆盖着厚重的黑霜，每一次极微弱的脉动都让周遭悬浮的符文碎片剧烈战栗。" << endl;
    cout << "你每向前迈出一步，脚下的尘埃便如同受到某种无形意志的驱使般向两侧退避。" << endl;
    cout << "在这片早已被时间抛弃的废墟深处，这口石棺像是一双冷漠注视着世间万物的眼睛。" << endl;
    cout << "当你的目光与棺盖上残缺的刻痕相触时，脑海中竟莫名回荡起远征者陨落前的最后一声悲鸣。" << endl;
    cout << endl;
    cout << "1. 迎战" << endl;
    cout << "2. 离开" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << "\n腐朽的护甲中隐现着虚无的悸动，仿佛某种被世界遗忘的灾厄正在苏醒。" << endl;
        cout << "它拖着残破的阔步走入阴影，脚下的裂纹深处回荡着远古的呜咽。" << endl;
        cout << "\n嘶哑的声音穿透虚空，如锈蚀的刀刃在残破的灵魂上刮擦：" << endl;
        cout << "\n『很久……没有人向深渊叩门了。』\n『那就……化作归途的骨骸吧。』\n" << endl;
        cout << "它扬起焦黑的断刃，周遭的符文瞬间被剥离成虚无的死寂。" << endl;
        cout << "\n 战斗开始！" << endl;
        WaitForSeconds(1);
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        Refresh();
        return EventBattleStart(true);
    }
    else {
        cout << "\n你向后退去，靴底踩碎了一地枯萎的符文。" << endl;
        cout << "阴影中的身影微不可查地一顿，缓缓垂下了蓄势待发的双臂。" << endl;
        cout << "石棺在无声中轰然阖上，将所有的窥探隔绝于虚空之外。\n" << endl;
        cout << "残垣间的微光逐渐黯淡，唯有深渊的冷风在低声呜咽。\n" << endl;
        cout << "你转过身，将那抹古老的杀意留在了黑暗中。" << endl;
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        return true;
    }
}

// ---------- 事件2：三选一高级藏品 ----------
bool Event_ChooseLoot() {
    Refresh();
    PrintCenteredHeader("英雄遗物");
    cout << "你踏入一座半塌的塔楼，残破的穹顶漏下惨淡的月光，地面散落着碎裂的符文石板与风干的骸骨。" << endl;
    cout << "在中央由黑曜石堆砌而成的古老石台上，三件尘封的器物正散发着各自深邃而孤寂的微光——" << endl;
    cout << "它们都曾是某位在虚空裂隙中陨落的英雄之遗物，历经岁月洗礼，如今静静等待着新的主人。" << endl;
    cout << "四周的空气中隐隐回荡着历代持有者的悲怆低语，每一寸光尘都诉说着未竟的执念。" << endl;
    cout << "你只能带走其中一件，其余的注定随风消散。在此驻足的抉择，即是宿命的分岔口。" << endl;
    cout << "虚空之风自塔窗呼啸而过，像是在催促你做出那个无法回头的决定。" << endl;

    vector<string> loots = {
        "【断罪之刃】——古老的符文短剑，剑刃上刻着“审判”二字",
        "【霜狼之契】——一枚冰蓝色的狼首徽章，触手冰冷",
        "【时砂罗盘】——一只漏沙永不停歇的青铜罗盘"
    };//此处添加符文名称
    cout << "\n1. " << loots[0] << endl;
    cout << "2. " << loots[1] << endl;
    cout << "3. " << loots[2] << endl;
    cout << "4. 不选，离开" << endl;

    int choice = Safecin({ 1,2,3 }, false);
    Refresh();
    cout << "\n" << endl;
    cout << "被你选中的器物缓缓脱离石台，带着冰凉或温热的触感，沉甸甸地落入你的掌心之中——" << endl;
    cout << "它的上一任主人早已在漫长的岁月中化作黄土，唯有残存的意志在此刻与你共鸣。" << endl;
    cout << "从此刻起，这道跨越时空的因果因你而延续，它将成为你对抗虚空唯一的凭仗。" << endl;
    cout << "\n 获得高级藏品 x1" << endl;
    cout << "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}

// ---------- 事件3：消耗血量上限换藏品 ----------
bool Event_Sacrifice() {
    static bool done[3] = { false, false, false };
    Refresh();

    // 检查是否三次都已献祭完
    if (done[0] && done[1] && done[2]) {
        PrintCenteredHeader("告解圣堂");
        cout << "\n告解室的百叶格栅后已经空无一人，木制靠背椅上落满了陈旧的灰尘。" << endl;
        cout << "三次符文契约的额度已经见底，沉重的隔板在机械卡榫的咬合声中彻底封死。" << endl;
        cout << "你没有再作逗留，推开沉重的包铁木门离开了这间昏暗的小隔间。" << endl;
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        return true;
    }

    // 循环献祭，直到玩家离开或三次完成
    while (true) {
        // 查当前是第几次（0开始）
        int current = -1;
        for (int i = 0; i < 3; ++i) {
            if (!done[i]) { current = i; break; }
        }
        if (current == -1) break; // 三次都已献祭，退出循环

        // 计算本次代价与奖励
        int hpCost = (current == 0) ? 3 : (current == 1 ? 4 : 5);
        string level = (current == 0) ? "初级" : (current == 1) ? "中级" : "高级";
        string ordinal;
        if (current == 0) ordinal = "第一阶段";
        else if (current == 1) ordinal = "第二阶段";
        else ordinal = "最终阶段";

        Refresh();
        PrintCenteredHeader("告解圣堂");
        cout << "狭小的石砌室内仅有一张长椅，正前方挂着一块厚重的黑色呢绒隔离帘。" << endl;
        cout << "昏暗的蜡烛在黄铜壁灯里闪烁，空气中弥漫着老旧纸张和干枯熏香的气味。" << endl;
        cout << "木质台面上刻着一行清晰的德语标语：" << endl;
        cout << RED_BOLD;
        cout << "Opfere deine Lebenskraft, um die Reliquien" << endl;
        cout << "der Runen - Katakakomben zu erlangen." << endl;
        cout << "(用你的生命残余，兑换符文秘境的遗物。)" << endl;
        cout << RED_DARK;
        cout << "\n【" << ordinal << "交易】" << endl;
        cout << "\n1. 同意交易（永久降低 " << hpCost << "% 血量上限）" << endl;
        cout << "2. 拒绝并离开" << endl;

        int choice = Safecin({ 1, 2 }, false);

        if (choice == 1) {
            // ---- 执行献祭 ----
            //角色状态调整
            done[current] = true;

            Refresh();
            PrintCenteredHeader("告解圣堂");

            // 根据第几次献祭输出不同的动作描写
            if (current == 0) {
                cout << "\n\"Der erste Bund ist geschlossen und im kalten Stein versiegelt.\"" << endl;
                cout << "\"Ein unumkehrbarer Teil deiner Lebensessenz ist leise gewichen.\"" << endl;
                cout << "（第一道契约已然达成并在冰冷的石头上封印。）" << endl;
                cout << "（你生命本源中不可逆转的一部分，正在无声地消散。）" << endl;
            }
            else if (current == 1) {
                cout << "\n\"Der zweite Preis ist entrichtet und fordert seinen Tribut vom Fleisch.\"" << endl;
                cout << "\"Die lastende Schwere im inneren Kern deines Seins wächst weiter an.\"" << endl;
                cout << "（第二份代价已然付清并向肉体索取着它的贡品。）" << endl;
                cout << "（你生命核心内部所承载的沉重负累正在不断加剧。）" << endl;
            }
            else {
                cout << "\n\"Der letzte Handel ist vollendet und das Buch der Opfer geschlossen.\"" << endl;
                cout << "\"Es verbleibt kein Funke mehr, der als Währung dienen könnte.\"" << endl;
                cout << "（最后的交易已然终结，献祭的簿册也已合拢。）" << endl;
                cout << "（再也没有哪怕一丝火星，能够当作货币继续支付了。）" << endl;
            }
            cout << "\n 血量上限永久降低 " << hpCost << "%" << endl;
            cout << " 获得 " << level << " 藏品 x1" << endl;

            if (done[0] && done[1] && done[2]) {
                cout << "\n隔离帘后传出了落锁的咔哒声，透出的微落烛光彻底熄灭。" << endl;
                cout << "『三次契约已满。此房间不再开放。』" << endl;
                cout << "\n按回车继续..." << endl;
                SafeEnter();
                return true;   // 三次完成，结束事件
            }
            else {
                cout << "\n隔离帘后响起了翻阅账本的纸张声。" << endl;
                cout << "对方没有再多说什么，留出空间让你自行决定接下来的行动。" << endl;
                cout << "\n按回车继续..." << endl;
                SafeEnter();
                // 继续循环，进行下一次献祭
            }

        }
        else {
            // ---- 选择离开 ----
            Refresh();
            PrintCenteredHeader("告解圣堂");
            cout << "\n你摇了摇头，放弃了这次物资交换。" << endl;
            cout << "黑色呢绒帘静静地垂在原位，里面没有任何挽留的意思。" << endl;
            cout << "你推开侧门，回到了修道院昏暗长明的走廊里。" << endl;
            cout << "\n按回车继续..." << endl;
            SafeEnter();
            return true;   // 玩家主动离开，结束事件
        }
    }

    // 理论上不会走到这里，但保留安全返回
    return true;
}

// ---------- 事件4：改变该层符文 ----------
//输入参数，currentRune
bool Event_ChangeRune(int& currentRune) {
    Refresh();
    PrintCenteredHeader("命运晶石");
    cout << "你站在一座巨大的符文法阵中央，法阵的一半刻着太阳纹，一半刻着月蚀纹。" << endl;
    cout << "阵眼处悬浮着一颗暗淡的晶石——它需要有人为它注入意志。" << endl;
    cout << "\n两道声音在你脑海中交织：" << endl;
    cout << "左：『点亮它。让此层之人皆受庇护。』" << endl;
    cout << "右：『熄灭它。让此层之物皆为猎物。』" << endl;
    cout << "\n1. 注入意志，改变此层符文" << endl;
    cout << "2. 离开，不做改变" << endl;

    int choice = Safecin({ 1,2 }, false);

    Refresh();
    if (choice == 1) {
        int roll = rm.getnum(1, 100);
        if (roll <= 70) {
            cout << "\n你的意志注入晶石。" << endl;
            cout << "晶石内部的暗色骤然破碎，暖金色的光芒从裂隙中汹涌而出——" << endl;
            cout << "太阳纹骤然亮起，将月蚀纹完全覆盖。" << endl;
            cout << "\n整层楼的符文法阵同时共振，脚下的地面泛起一层淡淡的金色波纹。" << endl;
            cout << "\n 本层符文已变更为：希望（纯增益效果）" << endl;
            currentRune = 10; // 此处参数变为希望
        }
        else {
            cout << "\n你的意志注入晶石。" << endl;
            cout << "晶石内部的金色光芒在一瞬间被黑暗吞噬——" << endl;
            cout << "月蚀紋骤然亮起，将太阳纹彻底压碎。" << endl;
            cout << "\n整层楼的温度骤降，符文法阵发出低沉的嗡鸣。" << endl;
            cout << "\n 本层符文已变更为：绝望（纯减益效果）" << endl;
            currentRune = 11; // 此处参数变为绝望
        }
    }
    else {
        cout << "\n你从晶石上收回了手。" << endl;
        cout << "太阳纹与月蚀纹同时暗淡下去，晶石恢复了之前那种半明半暗的状态。" << endl;
        cout << "你没有改变这一层的命运。你只是路过了它。" << endl;
    }
    cout << "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}

// ---------- 事件5：血量上限或金币 ----------
bool Event_ChooseBoon() {
    Refresh();
    PrintCenteredHeader("抉择契约");
    cout << "圣殿的偏厅里有一张残破的石桌，桌上放着两份契约。" << endl;
    cout << "『以此血契，延汝命途三成。』" << endl;
    cout << "『以此金契，赠汝六枚古金。』" << endl;
    cout << "二者皆可签。但签其一，另一即焚。" << endl;
    cout << "\n1. 签下血契——获得 30% 血量上限提升" << endl;
    cout << "2. 签下金契——获得 6 枚金币" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << "\n你拿起第一份契约，指尖在『血契』二字上划过。" << endl;
        cout << "纸张自行燃烧，火焰是温热的白色——" << endl;
        cout << "一股暖流顺着你的指尖涌入体内。" << endl;
        cout << "你的骨骼微微作响，肌肉深处传来一种被重新编织的饱胀感。" << endl;
        cout << "第二份契约在桌上无声自燃，化为灰烬。" << endl;
        //此处添加角色血量变化
        cout << "\n“血契已签。汝命途延三成。”" << endl;
        cout << "\n 血量上限永久提升 30%" << endl;
    }
    else {
        cout << "\n你拿起第二份契约，指尖触碰到『金契』二字的墨迹。" << endl;
        cout << "纸张化为一枚枚发烫的古金币，叮当落入你的掌心——" << endl;
        cout << "六枚，一枚不少。" << endl;
        cout << "第一份契约在桌上无声自燃。" << endl;
        //此处添加金币变化
        cout << "\n“金契已签。六枚古金已入汝手。”" << endl;
        cout << "\n 获得 6 金币" << endl;
    }
    cout << "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}

// ---------- 事件6：交换商店和战斗节点 ----------
bool Event_SwapNodes() {
    Refresh();
    PrintCenteredHeader("疯子的恶作剧");
    cout << "你踢到一块松动的石板，石板下方露出一只铁皮包裹的暗格。" << endl;
    cout << "暗格里没有宝物，没有陷阱——只有三枚尚有余温的金币，" << endl;
    cout << "和一张被反复折叠过无数次的兽皮地图。" << endl;
    cout << "你将地图展开，上面绘着这一层的完整路线。" << endl;
    cout << "\n『曾可购物之地，如今需以命搏。』" << endl;
    cout << "『曾需搏命之地，如今可换器物。』" << endl;
    cout << "\n兽皮背面有一行用炭笔写下的潦草字迹：" << endl;
    cout << "『我已改此路。送三币，当赔罪。』" << endl;
    cout << "\n三枚金币在你的掌心微微发烫。" << endl;
    cout << "这条路已经变了。" << endl;
    cout << "\n1. 接受改变（获得3金币，交换本层商店与战斗节点）" << endl;
    cout << "2. 拒绝改变，保持原样" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << "\n你握紧那三枚金币，金币的温度骤然升高，" << endl;
        cout << "烫得你几乎松手，却在下一瞬冷却为金属的沉实触感。" << endl;
        cout << "你手中的兽皮地图无声地燃起青灰色的火焰——" << endl;
        cout << "纸面卷曲、焦黑、碎裂，火焰却不灼人。" << endl;
        cout << "\n一阵沉闷的震动从脚下传来，从地底深处升起，" << endl;
        cout << "像是有巨大的齿轮在你感知不到的地方转动了一圈。" << endl;
        cout << "\n你隐约感觉到，这一层的空间结构正在悄然重组——" << endl;
        cout << "一处本该摆着货物的角落，正在变成染血的角斗场；" << endl;
        cout << "一处本该弥漫血腥气的地方，开始透出流转的微光。" << endl;
        //此处获得三个金币并更换战斗节点
        cout << "\n 获得 3 金币" << endl;
        cout << " 本层商店节点 <-> 战斗节点 已互换" << endl;
        cout << "\n最后的灰烬在空中凝成一行字：" << endl;
        cout << "『路已改。别谢我。』" << endl;
    }
    else {
        cout << "你犹豫片刻，将那三枚金币放回暗格。\n金币接触暗格底部的瞬间，温度骤失，像是某种邀请被正式收回。\n兽皮地图上的标记停止了移动。" << endl;
        cout << "石板自行合拢，暗格沉入地面，缝隙严丝合缝，仿佛从未存在过。" << endl;
        cout << "这一层的路线维持原样。" << endl;
    }
    cout << "\n按回车继续..." << endl;
    SafeEnter();
    Refresh();
    return true;
}

// ---------- 未知节点主入口 ----------
bool EnterUnknownEvent(int floor, int& currentRune) {
    cout << RED_DARK;
    Refresh();
    // 随机决定事件类型 (1~6)
    int eventType = rm.getnum(1, 6);

    bool result = true;
    switch (eventType) {
    case 1: result = Event_BossChallenge(floor); break;//传入层数
    case 2: result = Event_ChooseLoot(); break;
    case 3: result = Event_Sacrifice(); break;
    case 4: result = Event_ChangeRune(currentRune); break;//传入buff
    case 5: result = Event_ChooseBoon(); break;
    case 6: result = Event_SwapNodes(); break;
    default: result = true;
    }
    return result;
}