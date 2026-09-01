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
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "        【试炼之影 · 挑战】" << endl;
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "\n" << endl;
    cout << "遗迹深处有一口倒悬的石棺，棺盖上的咒文比周围任何一块碑文都要古老。" << endl;
    cout << "你靠近时，石棺自行翻转，棺盖坠地，一个身披腐朽战甲的身影缓缓坐起。" << endl;
    cout << "\n1. 迎战" << endl;
    cout << "2. 离开" << endl;

    int choice = Safecin({ 1,2 }, false);
    Refresh();
    if (choice == 1) {
        cout << "\n腐朽铠甲中传出深沉的吐息声，像是有某种沉睡之物正在加速苏醒。" << endl;
        cout << "它缓缓从石棺中站起身，每一步踏出，脚下的裂纹便向外蔓延一寸。" << endl;
        cout << "\n一道声音从铠甲内部传出——干涩、古老，像生锈的铁片在互相摩擦：" << endl;
        cout << "\n『很久……没有人应战了。』\n『很好。很好。』\n" << endl;
        cout << "它抬起右手，空气中凝结出一柄半透明的断刃。" << endl;
        cout << "\n 战斗开始！" << endl;
        WaitForSeconds(1);
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        Refresh();
        return EventBattleStart(true);
    }
    else {
        cout << "\n你后退一步。" << endl;
        cout << "石棺中的身影微微一顿，缓缓放下了抬起的右手。" << endl;
        cout << "石棺自行合拢，翻转回原位。\n" << endl;
        cout << "咒文重新亮起，像什么都没有发生过。\n" << endl;
        cout << "你离开了。一切归于寂静。" << endl;
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        return true;
    }
}

// ---------- 事件2：三选一高级藏品 ----------
bool Event_ChooseLoot() {
    Refresh();
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "          【英雄遗物】" << endl;
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "你踏入一座半塌的塔楼，地面散落着碎裂的符文石板。" << endl;
    cout << "在中央石台上，三件器物正散发着各自不同的微光——" << endl;
    cout << "它们都曾是某位已逝英雄的遗物，如今静静等待新的主人。" << endl;
    cout << "你只能带走一件。选择，即是命运的分岔。" << endl;

    vector<string> loots = {
        "【断罪之刃】——古老的符文短剑，剑刃上刻着“审判”二字",
        "【霜狼之契】——一枚冰蓝色的狼首徽章，触手冰冷",
        "【时砂罗盘】——一只漏沙永不停歇的青铜罗盘"
    };//此处添加符文名称
    cout << "\n1. " << loots[0] << endl;
    cout << "2. " << loots[1] << endl;
    cout << "3. " << loots[2] << endl;
    cout << "4. 不选，离开" << endl;

    int choice = Safecin({ 1,2,3,4 }, false);
    Refresh();
    if (choice >= 1 && choice <= 3) {
        cout << "\n" << endl;
        cout << "被你选中的器物缓缓落入你的掌心，冰凉或温热，沉重或轻盈——" << endl;
        cout << "它的上一任主人已经逝去多年。" << endl;
        cout << "从此刻起，它是你的了。" << endl;
        cout << "\n 获得高级藏品 x1" << endl;
        //此处获得符文
        cout << "\n未选择的两件器物化作细碎的光尘，消散在空气中。" << endl;
        cout << "你听见一个遥远的声音，像是某位已逝英雄的呓语：" << endl;
        cout << "“你选了它……那就替它走完没走完的路吧。”" << endl;
    }
    else {
        cout << "\n你收回了手。" << endl;
        cout << "三件器物的光芒同时黯淡了一瞬，像是一声无声的叹息。" << endl;
        cout << "它们继续静静地躺在石台上，等待下一个有缘人。" << endl;
        cout << "你转身离开了塔楼。" << endl;
    }
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
        cout << "════════════════════════════════════════════════════" << endl;
        cout << "          【血契祭坛】" << endl;
        cout << "════════════════════════════════════════════════════" << endl;
        cout << "\n祭坛上的符文已经彻底沉寂。" << endl;
        cout << "三祭已终，此坛永封。" << endl;
        cout << "你离开了祭坛。" << endl;
        cout << "\n按回车继续..." << endl;
        SafeEnter();
        return true;
    }

    // 循环献祭，直到玩家离开或三次完成
    while (true) {
        // 找当前是第几次（0开始）
        int current = -1;
        for (int i = 0; i < 3; ++i) {
            if (!done[i]) { current = i; break; }
        }
        if (current == -1) break; // 三次都已献祭，退出循环

        // 计算本次代价与奖励
        int hpCost = (current == 0) ? 3 : (current == 1 ? 4 : 5);
        string level = (current == 0) ? "初级" : (current == 1) ? "中级" : "高级";
        string ordinal = (current == 0) ? "第一次" : (current == 1) ? "第二次" : "第三次";

        Refresh();
        cout << "════════════════════════════════════════════════════" << endl;
        cout << "          【血契祭坛】" << endl;
        cout << "════════════════════════════════════════════════════" << endl;
        cout << "你面前浮现出一座暗红色的祭坛，表面刻满螺旋状的古符文。" << endl;
        cout << "古符文上只有一句话：" << endl;
        cout << "\"以血换物，以命易命。三祭三得，去留自便。\"" << endl;
        cout << "\n【" << ordinal << "献祭】" << endl;
        cout << "祭坛的低语在你耳边响起：" << endl;
        cout << "『献出 " << hpCost << "% 血量上限，可得一 " << level << " 藏品。』" << endl;
        cout << "\n1. 献祭（永久降低 " << hpCost << "% 血量上限）" << endl;
        cout << "2. 离开（结束献祭）" << endl;

        int choice = Safecin({ 1, 2 }, false);

        if (choice == 1) {
            // ---- 执行献祭 ----
            //角色状态调整
            done[current] = true;

            Refresh();
            cout << "════════════════════════════════════════════════════" << endl;
            cout << "          【血契祭坛】" << endl;
            cout << "════════════════════════════════════════════════════" << endl;

            // 根据第几次献祭输出不同的动作描写
            if (current == 0) {
                cout << "\n你将手腕伸向祭坛。" << endl;
                cout << "骨针自行浮起，在你的指尖轻轻刺入——" << endl;
                cout << "不疼，但你清晰地感觉到有什么东西被抽走了。" << endl;
                cout << "那是一种你从未察觉自己拥有过的东西。" << endl;
            }
            else if (current == 1) {
                cout << "\n你再次伸出手。" << endl;
                cout << "这一次，骨针刺入得稍深了一些——" << endl;
                cout << "你感到胸口一阵空虚，像是有什么东西被从骨头里抽走了。" << endl;
                cout << "但那件浮现在你面前的器物，明显比上一件更加沉重、更加古老。" << endl;
            }
            else {
                cout << "\n你深吸一口气，第三次伸出手腕。" << endl;
                cout << "骨针这一次没有刺入——它悬停在你的指尖上方，轻轻震颤。" << endl;
                cout << "祭坛上的螺旋符文骤然亮起，整座祭坛都在嗡鸣。" << endl;
                cout << "\n一个低沉的声音从石台深处升起：" << endl;
                cout << "『第三祭……你当真要献？』" << endl;
                cout << "『这一祭之后，你将不再是进来时的你。』" << endl;
                cout << "\n骨针落下。" << endl;
                cout << "这一次，你感到的不是空虚——" << endl;
                cout << "而是一种被完整填满又彻底掏空的奇异感受。" << endl;
                cout << "\n一件散发着远古威压的器物缓缓成形。" << endl;
                cout << "它比之前两件加起来都要古老。" << endl;
            }

            cout << "\n 血量上限永久降低 " << hpCost << "%" << endl;
            cout << " 获得 " << level << " 藏品 x1" << endl;

            if (done[0] && done[1] && done[2]) {
                cout << "\n祭坛的声音彻底沉寂。骨针碎裂成粉末。" << endl;
                cout << "『三祭已终。此坛永封。』" << endl;
                cout << "\n按回车继续..." << endl;
                SafeEnter();
                return true;   // 三次完成，结束事件
            }
            else {
                cout << "\n『第" << (current + 1) << "祭，已成。』" << endl;
                cout << "『你还有 " << (2 - current) << " 次机会。』" << endl;
                cout << "\n按回车继续..." << endl;
                SafeEnter();
                // 继续循环，进行下一次献祭
            }

        }
        else {
            // ---- 选择离开 ----
            Refresh();
            cout << "════════════════════════════════════════════════════" << endl;
            cout << "          【血契祭坛】" << endl;
            cout << "════════════════════════════════════════════════════" << endl;
            cout << "\n你收回手，退后半步。" << endl;
            cout << "祭坛上的符文缓缓归于沉寂。" << endl;
            cout << "骨针静止不动，像是从未被碰触过。" << endl;

            if (current == 0) {
                cout << "\n那个低语的声音没有挽留你，只是轻声说了一句：" << endl;
                cout << "『你保留了你的完整。但你也保留了自己的空无。』" << endl;
                cout << "『走吧。这条路或许不适合你。』" << endl;
            }
            else {
                cout << "\n你转身离开了祭坛。" << endl;
                cout << "身体完整，掌心空空。" << endl;
            }
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
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "          【命运晶石】" << endl;
    cout << "════════════════════════════════════════════════════" << endl;
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
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "          【抉择契约】" << endl;
    cout << "════════════════════════════════════════════════════" << endl;
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
    cout << "════════════════════════════════════════════════════" << endl;
    cout << "        【疯子的恶作剧】" << endl;
    cout << "════════════════════════════════════════════════════" << endl;
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
    Refresh();
    // 随机决定事件类型 (1~6)
    int eventType = rm.getnum(1, 6);
    cout << "╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║               ★ 未知事件触发 ★                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝" << endl;
    cout << "你踏入了一片迷雾笼罩的区域……" << endl;
    cout << "\n按回车继续..." << endl;
    SafeEnter();

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