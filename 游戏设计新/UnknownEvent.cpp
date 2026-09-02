#include"UnknownEvent.h"
#include"ClassSkill_RoundBuff.h"
#include"ClassMycharacter_Enemy.h"
#include"ClassRuneManager.h"
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
    cout << PURPLE_DARK;
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
    cout << RED_DARK;
    cout << "断壁残垣间横亘着一口倒悬的石棺，棺盖上剥落的咒文正向外渗出猩红的微光。" << endl;
    cout << "当你靠近时，古老的机括声撕裂了死寂，战甲在风中发出濒死的哀鸣。" << endl;
    cout << "石壁上凿刻着一行斑驳的符文箴言：" << endl;
    cout << RED_BOLD;
    cout << endl;
    cout << "Wer sich dem Schatten im Sarkophag stellt, fordert das Verderben heraus," << endl;
    cout << "denn hier ruht der Richter der Vergessenen." << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "(直面石棺中阴影之人即是向毁灭发起挑战，因为被遗忘者的审判者正长眠于此。)" << endl;
    cout << endl;
    cout << "石棺的表面覆盖着厚重的黑霜，每一次极微弱的脉动都让周遭悬浮的符文碎片剧烈战栗。" << endl;
    cout << "在这片早已被时间抛弃的废墟深处，这口石棺像是一双冷漠注视着世间万物的眼睛。" << endl;
    cout << "当你的目光与棺盖上残缺的刻痕相触时，脑海中竟莫名回荡起远征者陨落前的最后一声悲鸣。" << endl;
    cout << endl;
    cout <<HUI<< "(将迎接一场高难度战斗，胜利可获取双倍升级经验，金币与藏品)" << endl;
    cout <<HUI<< "1. 迎战" << endl;
    cout << "2. 离开" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << RED_BOLD;
        cout << "\n\"Der eiserne Waechter erwacht aus dem ewigen Schlaf und fordert den Blutzoll.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（铁面卫士自永恒的沉睡中苏醒，索取着鲜血的贡税。）" << endl;
        cout << endl;
        cout << "腐朽的护甲中隐现着虚无的悸动，仿佛某种被世界遗忘的灾厄正在苏醒。" << endl;
        cout << "它拖着残破的阔步走入阴影，脚下的裂纹深处回荡着远古的呜咽。" << endl;
        cout << "它扬起焦黑的断刃，周遭的符文瞬间被剥离成虚无的死寂。" << endl;
        cout <<HUI<< "\n按回车继续..." << endl;
        SafeEnter();
        Refresh();
        return EventBattleStart(true);
    }
    else {
        cout << RED_BOLD;
        cout << "\n\"Wer den Kampf vermeidet, wahrt das Leben, aber verliert den Pfad.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（回避战斗者保全了生命，却也失去了道途。）" << endl;
        cout << endl;
        cout << "你向后退去，靴底踩碎了一地枯萎的符文。" << endl;
        cout << "石棺在无声中轰然阖上，将所有的窥探隔绝于虚空之外。\n" << endl;
        cout << "残垣间的微光逐渐黯淡，唯有深渊的冷风在低声呜咽。\n" << endl;
        cout << "你转过身，将那抹古老的杀意留在了黑暗中。" << endl;
        cout <<HUI<< "\n按回车继续..." << endl;
        SafeEnter();
        return true;
    }
}

// ---------- 事件2：三选一高级藏品 ----------
bool Event_ChooseLoot() {
    Refresh();
    PrintCenteredHeader("英雄遗物");
    cout << RED_DARK;
    cout << "你踏入一座半塌的修道院唱诗班大厅，残破的哥特穹顶漏下惨淡的月光，地面散落着碎裂的石雕与风干的骸骨。" << endl;
    cout << "在中央由黑色玄武岩堆砌而成的祭台上，三件尘封的器物正散发着各自深邃而孤寂的微光。" << endl;
    cout << "石壁上用古老的符文凿刻着一行醒目的箴言：" << endl;
    cout << RED_BOLD;
    cout << endl;
    cout << "Waehle weise, denn jede Reliquie birgt das Gewicht einer verlorenen Seele." << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "(明智地选择，因为每一件圣物都承载着失落灵魂的重量。)" << endl;
    cout << endl;
    cout << "你只能带走其中一件，其余的注定随风消散。在此驻足的抉择，即是宿命的分岔口。" << endl;
    cout << "窗外的寒风自高耸的拱窗呼啸而过，拍打着悬挂的铁链，发出沉闷的低鸣。" << endl;
    cout << HUI;
    vector<string> loots = {
        "【断罪之刃】——镌刻着审判符文的古老重剑，剑身残存着洗刷罪孽的铁血寒光",
        "【苦修士之契】——一枚沾染着干涸血迹的银色苦修徽章，触手如冰",
        "【夜航罗盘】——指针永远指向迷雾深处的黄铜罗盘，周身缠绕着微弱的哀鸣"
    };
    cout << "\n1. " << loots[0] << endl;
    cout << "2. " << loots[1] << endl;
    cout << "3. " << loots[2] << endl;
    cout << HUI;
    cout << endl;
    cout << "(选择一个3级藏品获得)" << endl;
    int choice = Safecin({ 1,2,3 }, false);
    Refresh();



    cout << RED_BOLD;
    cout << "\n\"Der Bund ist geschlossen; die Last der Vergangenheit ruht nun auf deinen Schultern.\"" << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "（契约已然达成，过去的沉重负累如今落在了你的双肩之上。）" << endl;
    cout << endl;
    cout << "被你选中的器物缓缓脱离石台，带着冰凉而凝重的触感，沉甸甸地落入你的掌心之中。" << endl;
    cout << "它的上一任主人早已在漫长的岁月中化作尘土，唯有残存的誓言在此刻与你遥遥共鸣。" << endl;
    cout << "从这一刻起，跨越时空的因果因你而延续，它将成为你穿行于秘境唯一的凭借。" << endl;
    cout <<QING << "\n 获得高级藏品 x1" << endl;


    cout <<HUI<< "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}

// ---------- 事件3：消耗血量上限换藏品 ----------
bool Event_Sacrifice() {
    static bool done[3] = { false, false, false };
    Refresh();

    // 检查是否三次都已献祭完
    if (done[0] && done[1] && done[2]) {
        cout << RED_DARK;
        cout << "\n告解室的百叶格栅后已经空无一人，木制靠背椅上落满了陈旧的灰尘。" << endl;
        cout << "三次符文契约的额度已经见底，沉重的隔板在机械卡榫的咬合声中彻底封死。" << endl;
        cout << "你没有再作逗留，推开沉重的包铁木门离开了这间昏暗的小隔间。" << endl;
        cout <<HUI<< "\n按回车继续..." << endl;
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
        cout << RED_DARK;
        PrintCenteredHeader("告解圣堂");
        cout << RED_DARK;
        cout << "狭小的石砌室内仅有一张长椅，正前方挂着一块厚重的黑色呢绒隔离帘。" << endl;
        cout << "昏暗的蜡烛在黄铜壁灯里闪烁，空气中弥漫着老旧纸张和干枯熏香的气味。" << endl;
        cout << "木质台面上刻着一行清晰的符文：" << endl;
        cout << RED_BOLD;
        cout << endl;
        cout << "Opfere deine Lebenskraft, um die Reliquien" << endl;
        cout << "der Runen - Katakomben zu erlangen." << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "(用你的生命残余，兑换符文秘境的遗物。)\n" << endl;
        cout << HUI << "【" << ordinal << "交易】\n" << endl;
        cout <<HUI<< "(将消耗生命上限换取藏品)" << endl;
        cout << "\n1. 同意交易（降低 " << hpCost << "% 血量上限）" << endl;
        cout << "2. 拒绝并离开" << endl;

        int choice = Safecin({ 1, 2 }, false);

        if (choice == 1) {
            // ---- 执行献祭 ----
            //角色状态调整
            done[current] = true;

            Refresh();


            // 根据第几次献祭输出不同的动作描写
            if (current == 0) {
                cout << RED_BOLD;
                cout << "\n\"Der erste Bund ist geschlossen und im kalten Stein versiegelt.\"" << endl;
                cout << "\"Ein unumkehrbarer Teil deiner Lebensessenz ist leise gewichen.\"" << endl;
                cout << RED_DARK;
                cout << endl;
                cout << "（第一道契约已然达成并在冰冷的石头上封印。）" << endl;
                cout << "（你生命本源中不可逆转的一部分，正在无声地消散。）" << endl;
            }
            else if (current == 1) {
                cout << RED_BOLD;
                cout << "\n\"Der zweite Preis ist entrichtet und fordert seinen Tribut vom Fleisch.\"" << endl;
                cout << "\"Die lastende Schwere im inneren Kern deines Seins waechst weiter an.\"" << endl;
                cout << RED_DARK;
                cout << endl;
                cout << "（第二份代价已然付清并向肉体索取着它的贡品。）" << endl;
                cout << "（你生命核心内部所承载的沉重负累正在不断加剧。）" << endl;
            }
            else {
                cout << RED_BOLD;
                cout << "\n\"Der letzte Handel ist vollendet und das Buch der Opfer geschlossen.\"" << endl;
                cout << "\"Es verbleibt kein Funke mehr, der als Waehrung dienen koennte.\"" << endl;
                cout << RED_DARK;
                cout << endl;
                cout << "（最后的交易已然终结，献祭的簿册也已合拢。）" << endl;
                cout << "（再也没有哪怕一丝火星，能够当作货币继续支付了。）" << endl;
            }
            cout << endl;
            cout <<PURPLE_DARK<< "血量上限降低 " << hpCost << "%" << endl;
            cout <<QING_GRAY<< "获得 " << level << " 藏品 x1" << endl;

            if (done[0] && done[1] && done[2]) {
                cout << RED_DARK;
                cout << "\n隔离帘后传出了落锁的咔哒声，透出的微落烛光彻底熄灭。" << endl;
                cout << RED_BOLD;
                cout << endl;
                cout << "Du hast Glueck" << endl;
                cout << RED_DARK;
                cout << endl;
                cout << " (你很幸运)" << endl;
                cout <<HUI<< "\n按回车继续..." << endl;
                SafeEnter();
                return true;   // 三次完成，结束事件
            }
            else {
                cout << RED_DARK;
                cout << "\n隔离帘后响起了翻阅账本的纸张声。" << endl;
                cout << "对方没有再多说什么，留出空间让你自行决定接下来的行动。" << endl;
                cout <<HUI<< "\n按回车继续..." << endl;
                SafeEnter();
                // 继续循环，进行下一次献祭
            }

        }
        else {
            // ---- 选择离开 ----
            Refresh();
            cout << RED_BOLD;
            cout << "\n\"Wer den Pfad der Opfer verlaesst, laesst die Vergangenheit ungesehen zurueck.\"" << endl;
            cout << RED_DARK;
            cout << endl;
            cout << "（离开献祭之道者，将过往的痕迹无声地留在了身后。）" << endl;
            cout << endl;
            cout << "\n你摇了摇头，放弃了这次物资交换。" << endl;
            cout << "黑色呢绒帘静静地垂在原位，里面没有任何挽留的意思。" << endl;
            cout << "你推开侧门，回到了修道院昏暗长明的走廊里。" << endl;
            cout <<HUI<< "\n按回车继续..." << endl;
            SafeEnter();
            return true;   // 玩家主动离开，结束事件
        }
    }

    // 理论上不会走到这里，但保留安全返回
    return true;
}

// ---------- 事件4：改变该层符文 ----------
bool Event_ChangeRune() {
    Refresh();
    PrintCenteredHeader("命运晶石");
    cout << RED_DARK;
    cout << "你站在一座巨大的符文法阵中央，石质地面上交错刻印着日轮与蚀月交替的古老图腾。" << endl;
    cout << "阵眼中央悬浮着一块半透明的晶石，内部正流转着明暗不定的幽光。" << endl;
    cout << "石壁上凿刻着一行斑驳的符文：" << endl;
    cout << RED_BOLD;
    cout << endl;
    cout << "Gestalte das Schicksal dieser Ebene nach deinem Willen," << endl;
    cout << "denn das Licht und die Finsternis gehorchen nur dem Opfer." << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "(依据你的意志塑造此层的命运，因为光明与黑暗只听从牺牲者。)" << endl;
    cout <<HUI<< "\n1. 触碰晶石，改写当前层的符文" << endl;
    cout << "(有70%概率变为\"希望\"，有30概率变为\"绝望\")" << endl;
    cout << "2. 保持原状，转身离开" << endl;

    int choice = Safecin({ 1,2 }, false);

    Refresh();
    if (choice == 1) {
        int roll = rm.getnum(1, 100);
        if (roll <= 70) {
            cout << RED_DARK;
            cout << "\n石碑表面的日轮图腾骤然亮起，将蚀月的光辉尽数掩盖。" << endl;
            cout << "温热的金芒如潮水般洗净了空气中的腐臭，枯萎的石墙上竟隐约绽放出新生的藤蔓刻痕。" << endl;
            cout << "整座大厅的符文同时产生共鸣，脚下的石砖泛起一层驱散寒意的金色微光。" << endl;
            cout << RED_BOLD;
            cout << endl;
            cout << "\n\"Hoffnung\"" << endl;
            cout << "（希望）" << endl;
            cout << endl;
            RuneManager::ChangetoHope();
            cout <<HUI<< "\n本层符文已变更为：" << endl;
            cout << RED_BOLD << RuneNow->GetDescribe() << endl;
        }
        else {
            cout << RED_DARK;
            cout << "\n石碑表面的蚀月图腾骤然扩张，将日轮的纹路彻底碾碎。" << endl;
            cout << "刺骨的寒霜瞬间冻结了墙壁上的每一道缝隙，连残存的烛火也在无声中被彻底剥夺。" << endl;
            cout << "大厅内的温度骤降至冰点，符文法阵发出令人窒息的低沉金属嗡鸣。" << endl;
            cout << RED_BOLD;
            cout << endl;
            cout << "\n\"Verzweiflung\"" << endl;
            cout << "（绝望）" << endl;
            cout << endl;
            RuneManager::ChangetoDesperation();
            cout <<HUI<< "\n 本层符文已变更为：" << endl;
            cout << RED_BOLD << RuneNow->GetDescribe() << endl;
        }
    }
    else {
        cout << RED_BOLD;
        cout << "\n\"Keine Aenderung wird erzwungen; der Lauf der Dinge bleibt ungebrochen.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（未曾强行施加改变；事物的运转轨迹依然完好无损。）" << endl;
        cout << endl;
        cout << "你继续前行，未曾触碰此地的命运。" << endl;
        cout << "日轮与蚀月同时黯淡下去，晶石恢复了最初半明半暗的死寂状态。" << endl;
    }
    cout <<HUI<< "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}

// ---------- 事件5：血量上限或金币 ----------
bool Event_ChooseBoon() {
    Refresh();
    PrintCenteredHeader("抉择契约");
    cout << RED_DARK;
    cout << "圣殿的偏厅里四壁空空，唯有一张残破的石桌立于正中，桌面上摆放着两份以厚重羊皮纸制成的契约。" << endl;
    cout << "烛影在壁角剧烈摇晃，将冷冽的微光投射在斑驳的石面上，上面凿刻着一行刺目的规诫：" << endl;
    cout << RED_BOLD;
    cout << endl;
    cout << "Waehle das Leben oder das Gold, denn der Pakt duldet keinen Aufschub," << endl;
    cout << "und wer den Bund bricht, wird von der Finsternis verschlungen." << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "（抉择生命或财富，契约不容迁延，背盟之徒终将为深渊所噬。）" << endl;
    cout << endl;
    cout <<HUI<< "\n1. 签下血契——获得 30% 血量上限提升" << endl;
    cout << "2. 签下金契——获得 6 枚金币" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << RED_BOLD;
        cout << "\n\"Der Bund des Blutes staerkt deine Lebenskraft und dehnt deinen Pfad aus,\"" << endl;
        cout << "\"waehrend die ungenutzte Gunst in hellen Flammen vergeht.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（血之契约增强了你的生命力并延伸了你的道途，而那未被选择的恩惠则在明亮的火焰中消逝。）" << endl;
        cout << endl;
        cout << "\n你没有犹豫，将手指按在第一份契约的边缘。" << endl;
        cout << "纯净而温热的白色火焰瞬间将羊皮纸吞没，一股磅礴的暖流顺着掌心狂暴地涌入四肢百骸。" << endl;
        cout << "你的骨骼发出沉闷而悠长的脆响，肌肉深处传来一种生命被强行撑开、重新编织的饱胀感。" << endl;
        cout << "与此同时，桌上那份未被触碰的金之契约在无声无息中自行燃尽，化作一滩冰冷的黑灰。" << endl;
        //此处添加角色血量变化
        cout <<QING<< "\n 血量上限提升 30%" << endl;
    }
    else {
        cout << RED_BOLD;
        cout << "\n\"Der Bund des Goldes fuellt deine Haende und besiegelt das Schicksal,\"" << endl;
        cout << "\"waehrend das unberuehrte Leben im Schatten stumm verbrannt wird.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（金之契约充盈了你的双手并封印了命运，而那未被选择的生命则在阴影中默默焚毁。）" << endl;
        cout << endl;
        cout << "\n你迎着烛光，将手掌覆在了第二份契约之上。" << endl;
        cout << "厚重的羊皮纸转瞬化作六枚沉甸甸的发烫古金币，叮当清脆地落入你的掌心之中。" << endl;
        cout << "金属碰撞的回响在空旷寂静的偏厅里久久回荡，空气中弥漫着一股陈旧的熔金气味。" << endl;
        cout << "与此同时，桌上那份关于血肉的契约在无声中腾起一团灰烬，彻底归于虚无。" << endl;
        //此处添加金币变化
        cout <<YELLOW<< "\n 获得 6 金币" << endl;
    }
    cout <<HUI<< "\n按回车继续..." << endl;
    SafeEnter();
    return true;
}
// ---------- 事件6：交换商店和战斗节点 ----------
bool Event_SwapNodes() {
    Refresh();
    PrintCenteredHeader("幽暗商贾");
    cout << RED_DARK;
    cout << "斑驳的石柱后隐匿着一处狭小的凹室，堆满了沉重的货箱与成捆的羊皮纸。" << endl;
    cout << "一个身着华贵但沾满污渍的商人正蹲在阴影中，用一把小刀仔细地刮擦着一枚金币上的铜锈。" << endl;
    cout << "察觉到你的脚步声，他猛地抬起头，露出一张堆满意外与狂喜的面孔，却死死紧闭着双唇，不发一言。" << endl;
    cout << "他颤抖着将三枚沉甸甸的发烫金币推到你面前，双手疯狂地比划着，眼中闪烁着狂热而贪婪的光芒。" << endl;
    cout << "石壁上用沾血的炭笔草草勾勒出一行冰冷的符文：" << endl;
    cout << RED_BOLD;
    cout << endl;
    cout << "Der Handel findet den Weg, selbst dort, wo nur das Schwert regiert." << endl;
    cout << RED_DARK;
    cout << endl;
    cout << "(交易总能找到出路，哪怕是在唯有长剑统治的地方。)" << endl;
    cout << endl;
    cout <<HUI<< "1. 获得3枚金币，该节点改为商店节点，但会触发某种效果" << endl;
    cout << "2. 拒绝交易，转身离去" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << RED_BOLD;
        cout << "\n\"Ein Bund in der Wildnis bringt Segen und ungesehene Wende.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（荒野中的契约带来祝福，与不为人知的转机。）" << endl;
        cout << endl;
        cout << "你收下了那三枚发烫的金币，商人见状，嘴角咧开一个异样森冷而诡异的笑容。" << endl;
        cout << "他依然没有发出半点声音，只是飞快地将桌上那张错综复杂的地图合拢，身体因极度的兴奋而剧烈颤抖。" << endl;
        //此处获得三个金币并更换战斗节点
        cout <<YELLOW<< "\n 获得 3 金币" << endl;
    }
    else {
        cout << RED_BOLD;
        cout << "\n\"Wer des Handels finsteren Pakt ausschlaegt, bewahrt den eignen Schritt im Nebel.\"" << endl;
        cout << RED_DARK;
        cout << endl;
        cout << "（回绝这桩晦暗交易之人，方能在迷雾中守住自己的脚步。）" << endl;
        cout << endl;
        cout << "你冷冷地看了一眼桌上的金币，向后退开半步。" << endl;
        cout << "商人见状身体一僵，面露痛苦与失望之色，枯瘦的手指一挥，将金币尽数收回袖中，全程依旧死寂无声。" << endl;
        cout << "凹室内的烛火骤然黯淡，对方无声无息地隐匿于黑暗深处。" << endl;
        cout << "你独自转过身，继续沿着原本的道途向前行去。" << endl;
    }
    cout <<HUI<< "\n按回车继续..." << endl;
    SafeEnter();
    Refresh();
    return true;
}

vector<int> EventType_NotRepeat={1,2,3,4,5,6};
vector<int> EventType_Experience = {0,0,0,0};
class EventType;
vector<shared_ptr<EventType>> EventList = {
    make_shared<EventType>(1),
    make_shared<EventType>(2),
    make_shared<EventType>(3),
    make_shared<EventType>(4),
    make_shared<EventType>(5),
    make_shared<EventType>(6)
};
class EventType {
public:
    EventType(int type) :type(type) {}
    static void Experiencing(int num) {
        EventList[num - 1]->Experienced();
    }
    void Experienced() {
        IfExperienced = true;
    }
    void reset() {
        IfExperienced = false;
    }
    int getnum() {
        return type;
    }
    static bool Reset() {
        for (auto& item : EventList) {
            if (!item->getifused()) {
                return false;
            }
        }
        for (auto& item : EventList) {
            item->reset();
        }
        return true;
    }
    bool getifused() {
        return IfExperienced;
    }
private:
    int type = 0;
    bool IfExperienced = false;

};

// ---------- 未知节点主入口 ----------
bool EnterUnknownEvent(int floor) {
    cout << RED_DARK;
    Refresh();
    // 随机决定事件类型 (1~6)
    int eventType = EventType_Experience.back();
    EventType::Reset();
    while (eventType == EventType_Experience.back() || eventType == EventType_Experience[EventType_Experience.size() - 2]) {
        EventType_NotRepeat.clear();
        for (auto& item : EventList) {
            if (!item->getifused()) {
                EventType_NotRepeat.push_back(item->getnum());
            }
        }
        eventType = EventType_NotRepeat[rm.getnum(0, EventType_NotRepeat.size() - 1)];
    }
    EventType::Experiencing(eventType);
    EventType_Experience.push_back(eventType);
    bool result = true;
    switch (eventType) {
    case 1: result = Event_BossChallenge(floor); break;//传入层数
    case 2: result = Event_ChooseLoot(); break;
    case 3: result = Event_Sacrifice(); break;
    case 4: result = Event_ChangeRune(); break;//传入buff
    case 5: result = Event_ChooseBoon(); break;
    case 6: result = Event_SwapNodes(); break;
    default: result = true;
    }
    return result;
}